
bool verify_if_there_is_an_root_user(){
    DtwResource *database = resource.newResource(DATABASE_PATH);
    DtwResource *all_users = resource.sub_resource(database, USERS_PATH);
    all_users = resource.sub_resource(all_users,ELEMENTS_PATH);
    DtwStringArray * elements = resource.list_names(all_users);
    for(long i = 0; i < elements->size; i++){
        char *current_name = elements->strings[i];
        DtwResource *current_user = resource.sub_resource(all_users,current_name);
        bool is_root = resource.get_bool_from_sub_resource(current_user,IS_ROOT_PATH);
        if(is_root){
            resource.free(database);
            dtw.string_array.free(elements);
            return  true;
        }
    }
    resource.free(database);
    dtw.string_array.free(elements);
    return  false;
}

void create_root_user_if_not_exist(){
    if(verify_if_there_is_an_root_user()){
        return;
    }
    DtwResource *database = resource.newResource(DATABASE_PATH);
    database_create_user(database,START_ROOT_NAME,START_ROOT_NAME,START_ROOT_PASSWORD,true);
    resource.commit(database);
    resource.free(database);
}