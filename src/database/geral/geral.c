
DtwResource *find_element_by_id(DtwResource *folder,const char *id){

    DtwResource *elements = resource.sub_resource(folder, ELEMENTS_PATH);
    DtwResource *element = resource.sub_resource(elements,id);
    if(resource.type(element) == DTW_NOT_FOUND){
        return  NULL;
    }
    return element;
}

DtwResource * find_element_by_index(DtwResource *folder, const char *index_name,const  char *index){
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



    if(resource.type(current_element) != DTW_FOLDER_TYPE){
        return  NULL;
    }
    return current_element;
}

void set_index(DtwResource *folder,const char *id, const char *index_name, const char *value){
    //folder/index
    DtwResource *  all_index_folder = resource.sub_resource(folder, INDEX_PATH);
    //folder/index/email
    DtwResource *selected_index = resource.sub_resource(all_index_folder, index_name);
    //folder/index/email/user@gmail.com
    DtwResource  *element_reference = resource.sub_resource(selected_index,value);
    resource.set_string(element_reference,id);

    //folder/elements
    DtwResource * elements_folder = resource.sub_resource(folder,ELEMENTS_PATH);
    DtwResource * current_element = resource.sub_resource(elements_folder,id);

    DtwResource *current_element_value = resource.sub_resource(current_element,index_name);
    resource.set_string(current_element_value,value);

}
