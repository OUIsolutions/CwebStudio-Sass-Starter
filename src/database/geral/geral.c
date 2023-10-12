

char * find_element_by_index(DtwResource *folder, const char *index_name, char *index){
    DtwResource *  all_index = resource.sub_resource(folder, INDEX_PATH);
    DtwResource *selected_index = resource.sub_resource(all_index,index_name);
    DtwResource  *current_element = resource.sub_resource(selected_index,index);
    return resource.get_string(current_element);
}