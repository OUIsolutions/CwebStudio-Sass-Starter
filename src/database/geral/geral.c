
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
