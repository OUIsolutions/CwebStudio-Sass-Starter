
bool verify_if_there_is_an_root_user(){
    UniversalGarbage *garbage = newUniversalGarbage();
    DtwResource *database = resource.newResource(DATABASE_PATH);
    UniversalGarbage_add(garbage, DtwResource_free,database);

    DtwResource *all_users = resource.sub_resource(database, USERS_PATH);
    all_users = resource.sub_resource(all_users,ELEMENTS_PATH);
    DtwStringArray * elements = resource.list_names(all_users);
    UniversalGarbage_add(garbage, DtwStringArray_free,elements);

    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return false;
    }

    for(long i = 0; i < elements->size; i++){
        char *current_name = elements->strings[i];
        DtwResource *current_user = resource.sub_resource(all_users,current_name);
        bool is_root = resource.get_bool_from_sub_resource(current_user,IS_ROOT_PATH);
        DtwResource_catch(database){
            UniversalGarbage_free(garbage);
            return false;
        }

        if(is_root){
            UniversalGarbage_free(garbage);
            return true;

        }
    }
    UniversalGarbage_free(garbage);
    return false;
}


void create_root_user_if_not_exist(){

    bool root_already_exist = verify_if_there_is_an_root_user();

    if(root_already_exist){
        return;
    }

    DtwResource *database = resource.newResource(DATABASE_PATH);
    database_create_user(database,START_ROOT_NAME,START_ROOT_NAME,START_ROOT_PASSWORD,true,true);
    DtwResource_catch(database){
        return;
    }

    commit_transaction(database);
    resource.free(database);
}