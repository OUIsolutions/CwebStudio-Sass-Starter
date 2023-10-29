
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

void commit_transaction(DtwResource *database){
    resource.commit(database);

    #ifndef SAVE_USER_TRANSACTIONS
        return;
    #endif

    DtwTransaction * transaction = database->transaction;
    if(transaction->size == 0){
        return;
    }

    cJSON * transaction_json = dtw.transaction.dumps_transaction_to_json(transaction);

#ifndef SAVE_TOKEN_TRANSACTIONS
    int size = cJSON_GetArraySize(transaction_json);
    for(int i =0 ; i < size; i++){
        cJSON * current = cJSON_GetArrayItem(transaction_json,i);
        cJSON *source = cJSON_GetObjectItem(current,"source");
        CTextStack *source_stack = newCTextStack_string(source->valuestring);
        bool is_finite_token_transaction = stack.index_of(source_stack,FINITE_TOKENS_PATH) != -1;
        if(is_finite_token_transaction){
            size-=1;
            cJSON_DeleteItemFromArray(transaction_json,i);
            stack.free(source_stack);
            continue;
        }
        bool is_infinite_token_transaction = stack.index_of(source_stack,INFINITE_TOKENS_PATH) != -1;
        if(is_infinite_token_transaction){
            size-=1;

            cJSON_DeleteItemFromArray(transaction_json,i);
        }
        stack.free(source_stack);
    }

    if(size == 0){
        cJSON_Delete(transaction_json);
        return;
    }

#endif


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