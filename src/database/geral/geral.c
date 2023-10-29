
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

    char *id =  resource.get_string(element_reference);
    if(!id){
        return  NULL;
    }
    //folder/elements
    DtwResource * elements_folder = resource.sub_resource(folder,ELEMENTS_PATH);
    //folder/elements/{{user_id}}
    DtwResource * current_element = resource.sub_resource(elements_folder,id);
    if(resource.type(current_element) != DTW_FOLDER_TYPE){
        return  NULL;
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


    return KEEP;
}

void commit_transaction(DtwResource *database){
    resource.commit(database);

    #ifndef SAVE_USER_TRANSACTIONS
        return;
    #endif

    DtwTransaction * transaction = database->transaction;
    if(transaction->size == 0){
        return;
    }


#ifndef SAVE_TOKEN_TRANSACTIONS

    dtw.transaction.filter(transaction, remove_currenct_action_if_is_a_token);
    if(transaction->size == 0){
        return;
    }
#endif

    cJSON * transaction_json = dtw.transaction.dumps_transaction_to_json(transaction);

    char *transaction_content = cJSON_Print(transaction_json);
    char *transaction_sha = dtw.generate_sha_from_string(transaction_content);
    long now = time(NULL);
    CTextStack * formated_path = newCTextStack_string_empty();
    stack.format(formated_path,"%s/%d:%s.json",TRANSACTION_PATH,now,transaction_sha);
    dtw.write_string_file_content(formated_path->rendered_text,transaction_content);
    cJSON_Delete(transaction_json);
    free(transaction_sha);
    stack.free(formated_path);

}

void reload_all_transactions(){
    dtw_remove_any(DATABASE_PATH);
    DtwStringArray  *elements = dtw.list_files(TRANSACTION_PATH,true);
    for(int i = 0; i < elements->size; i++){
        char *current_transaction_path = elements->strings[i];
        DtwTransaction *current = dtw.transaction.newTransaction_from_json_file(current_transaction_path);
        dtw.transaction.commit(current,NULL);
        dtw.transaction.free(current);
    }
    dtw.string_array.free(elements);
}
