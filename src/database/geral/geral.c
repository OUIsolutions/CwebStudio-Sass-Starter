
DtwResource *find_element_by_id(DtwResource *folder,const char *id){

    DtwResource *elements = resource.sub_resource(folder, ELEMENTS_PATH);
    DtwResource *element = resource.sub_resource(elements,id);
    if(resource.type(element) == DTW_NOT_FOUND){
        return  NULL;
    }
    return element;
}

DtwResource * find_element_by_index(DtwResource *folder, const char *index_name,const  char *value){
    //folder/index
    DtwResource *  all_index_folder = resource.sub_resource(folder, INDEX_PATH);
    //folder/index/email
    DtwResource *selected_index = resource.sub_resource(all_index_folder, index_name);
    char *converted_value = dtw.generate_sha_from_string(value);
    //folder/index/email/user@gmail.com
    DtwResource  *element_reference = resource.sub_resource(selected_index, converted_value);
    free(converted_value);
    if(resource.type(element_reference) ==DTW_NOT_FOUND){
        return  NULL;
    }

    char *id =  resource.get_string(element_reference);
    DtwResource_catch(folder){
        return NULL;
    }

    //folder/elements
    DtwResource * elements_folder = resource.sub_resource(folder,ELEMENTS_PATH);
    //folder/elements/{{user_id}}
    DtwResource * current_element = resource.sub_resource(elements_folder,id);
    //folder/elements/{{user_id}}/email
    DtwResource * current_element_index = resource.sub_resource(current_element,index_name);
    char *current_element_index_value = resource.get_string(current_element_index);
    DtwResource_catch(folder){
        return NULL;
    }

    if(!strings_equal(current_element_index_value,value)){
        return NULL;
    }

    return current_element;
}

void destroy_index(DtwResource *folder,const char *index_name,const  char *value){
    //folder/index
    DtwResource *  all_index_folder = resource.sub_resource(folder, INDEX_PATH);
    //folder/index/email
    DtwResource *selected_index = resource.sub_resource(all_index_folder, index_name);
    //folder/index/email/user@gmail.com
    char *converted_value = dtw.generate_sha_from_string(value);
    DtwResource  *element_reference = resource.sub_resource(selected_index, converted_value);
    free(converted_value);
    resource.destroy(element_reference);

}


void create_index(DtwResource *folder, const char *id, const char *index_name, const char *value){
    //users/index
    DtwResource *  all_index_folder = resource.sub_resource(folder, INDEX_PATH);
    //users/index/email
    DtwResource *selected_index = resource.sub_resource(all_index_folder, index_name);
    //users/index/email/user@gmail.com
    char *converted_value = dtw.generate_sha_from_string(value);
    DtwResource  *element_reference = resource.sub_resource(selected_index,converted_value);
    free(converted_value);
    resource.set_string(element_reference,id);

    //users/elements
    DtwResource * elements_folder = resource.sub_resource(folder,ELEMENTS_PATH);
    DtwResource * current_element = resource.sub_resource(elements_folder,id);

    DtwResource *current_element_value = resource.sub_resource(current_element,index_name);
    resource.set_string(current_element_value,value);

}


bool remove_currenct_action_if_is_a_token(DtwActionTransaction *action){

    CTextStack *possible_token = stack.newStack_string(action->source);
    const bool REMOVE = false;
    const bool KEEP = true;

    bool is_a_finite_token_modification = stack.index_of(possible_token,FINITE_TOKENS_PATH) != -1;
    if(is_a_finite_token_modification){
        stack.free(possible_token);
        return REMOVE;
    }

    bool is_a_infinite_token_modification = stack.index_of(possible_token,INFINITE_TOKENS_PATH) != -1;
    if(is_a_infinite_token_modification){
        stack.free(possible_token);
        return REMOVE;
    }
    bool is_last_update = stack.index_of(possible_token,LAST_UPDATE_PATH)!=-1;
    if(is_last_update){
        stack.free(possible_token);
        return REMOVE;
    }


    stack.free(possible_token);
    return KEEP;
}

void commit_transaction(DtwResource *database){
    resource.commit(database);

    #ifndef SAVE_USER_TRANSACTIONS
        return;
    #endif

    DtwTransaction * transaction = database->root_props->transaction;
    if(transaction->size == 0){
        return;
    }


#ifndef SAVE_TOKEN_TRANSACTIONS

    dtw.transaction.filter(transaction, remove_currenct_action_if_is_a_token);
    if(transaction->size == 0){
        return;
    }
#endif
    UniversalGarbage *garbage = newUniversalGarbage();
    cJSON * transaction_json = dtw.transaction.dumps_transaction_to_json(transaction);
    UniversalGarbage_add(garbage, cJSON_Delete,transaction_json);
    char *transaction_content = cJSON_Print(transaction_json);
    UniversalGarbage_add_simple(garbage,transaction_content);

    char *transaction_sha = dtw.generate_sha_from_string(transaction_content);
    UniversalGarbage_add_simple(garbage,transaction_sha);

    char * now = dtw_convert_unix_time_to_string(get_time());
    UniversalGarbage_add_simple(garbage,now);

    CTextStack * formated_path = newCTextStack_string_empty();
    UniversalGarbage_add(garbage,stack.free,formated_path);

    stack.format(formated_path,"%s/%s:%s.json",TRANSACTION_PATH,now,transaction_sha);
    dtw.write_string_file_content(formated_path->rendered_text,transaction_content);

    UniversalGarbage_free(garbage);

}

void reload_all_transactions(){

    CTextStack *back_up_path = newCTextStack_string(BACKUP_PATH);
    char *now = dtw_convert_unix_time_to_string(get_time());
    stack.format(back_up_path,"/%sc", now);
    dtw_move_any(DATABASE_PATH,back_up_path->rendered_text,DTW_NOT_MERGE);
    stack.free(back_up_path);

    DtwStringArray  *elements = dtw.list_files(TRANSACTION_PATH,true);
    dtw.string_array.sort(elements);
    for(int i = 0; i < elements->size; i++){
        char *current_transaction_path = elements->strings[i];
        DtwTransaction *current = dtw.transaction.newTransaction_from_json_file(current_transaction_path);
        dtw.transaction.commit(current,NULL);
        dtw.transaction.free(current);
    }
    dtw.string_array.free(elements);
}
