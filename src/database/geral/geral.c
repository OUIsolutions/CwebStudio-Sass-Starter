

DtwResource * find_element_by_index(DtwResource *folder, const char *index_name,const  char *index,bool lock){
    //folder/index
    DtwResource *  all_index_folder = resource.sub_resource(folder, INDEX_PATH);
    //folder/index/email
    DtwResource *selected_index = resource.sub_resource(all_index_folder, index_name);
    //folder/index/email/user@gmail.com
    DtwResource  *element_reference = resource.sub_resource(selected_index,index);

    char *id =  resource.get_string(element_reference);
    if(!id){
        return  NULL;
    }
    //folder/elements
    DtwResource * elements_folder = resource.sub_resource(folder,ELEMENTS_PATH);
    DtwResource * current_element = resource.sub_resource(elements_folder,id);
    if(lock){
        resource.lock(current_element);
    }
    if(resource.type(current_element) != DTW_FOLDER_TYPE){
        return  NULL;
    }
    return current_element;
}
