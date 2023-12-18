
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

void generate_script_constant_file(const char *path){
    UniversalGarbage *garbage = newUniversalGarbage();
    char *content = dtw.load_string_file_content(path);
    UniversalGarbage_add_simple(garbage,content);
    CTextStack *result = newCTextStack_string(content);
    UniversalGarbage_add(garbage,stack.free,result);
    stack.self_replace(result,"#define","const");

    DtwPath * output = dtw.path.newPath(path);
    UniversalGarbage_add(garbage,dtw.path.free,output);
    dtw.path.set_extension(output,"js");

    char * formated_dir = dtw_concat_path(cweb_static_folder,FRONT_END_CONSTANTS_PATH);
    UniversalGarbage_add_simple(garbage,formated_dir);

    dtw.path.set_dir(output,formated_dir);

    dtw.write_string_file_content(dtw.path.get_path(output),result->rendered_text);
    UniversalGarbage_free(garbage);



}
void create_script_constants(){
    generate_script_constant_file("src/routes.h");

}