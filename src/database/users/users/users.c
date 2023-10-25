


DtwResource *find_user_by_username_or_email(DtwResource  *database,const char *username_or_email){
    DtwResource *users = resource.sub_resource(database, USERS_PATH);

    DtwResource *possible_user = find_element_by_index(
            users,
            EMAIL_PATH,
            username_or_email
            );
    if(possible_user){
        return  possible_user;
    }
    possible_user = find_element_by_index(
            users,
            USERNAME_PATH,
            username_or_email
    );
    return possible_user;
}

DtwResource *find_user_by_id(DtwResource  *database,const char *id){
    //users/
    DtwResource *users = resource.sub_resource(database, USERS_PATH);
    //users/elements/{id}
    return find_element_by_id(users,id);
}

bool is_root(DtwResource *user){
    //users/elements/{user}/is_root
    return resource.get_bool_from_sub_resource(user,IS_ROOT_PATH);
}




void database_remove_user(DtwResource *database, DtwResource *user){

    DtwResource * all_user = resource.sub_resource(database, USERS_PATH);

    char *email = resource.get_string_from_sub_resource(user,EMAIL_PATH);
    destroy_index(all_user,EMAIL_PATH,email);

    char *username = resource.get_string_from_sub_resource(user,USERNAME_PATH);
    destroy_index(all_user,USERNAME_PATH,username);
    resource.destroy(user);
}



void database_create_user( DtwResource  *database,const char *username,const char *email,const char *password,bool is_root,bool verified){

    //users
    DtwResource * users = resource.sub_resource(database, USERS_PATH);

    //users/elements
    DtwResource *elements = resource.sub_resource(users,ELEMENTS_PATH);

    //users/elements/2o3023dsds
    DtwResource *created_user = resource.sub_resource_random(elements, NULL);


    create_index(users, created_user->name, EMAIL_PATH, email);
    create_index(users, created_user->name, USERNAME_PATH, username);


    DtwResource *password_resource = resource.sub_resource(created_user,PASSWORD_PATH);
    char *password_sha = dtw_generate_sha_from_string(password);
    resource.set_string(password_resource,password_sha);
    free(password_sha);

    DtwResource *verified_resource = resource.sub_resource(created_user,VERIFIED_PATH);
    resource.set_bool(verified_resource,verified);

    resource.set_long_in_sub_resource(created_user, time(NULL),CREATION_PATH);
    resource.set_long_in_sub_resource(created_user, time(NULL),LAST_UPDATE_PATH);


    DtwResource  *is_root_resource = resource.sub_resource(created_user,IS_ROOT_PATH);
    resource.set_bool(is_root_resource,is_root);


}

void database_modify_user( DtwResource  *database,DtwResource *user,const char *new_username,const char *new_email,const char *new_password,bool set_is_root, bool is_root){

    //users
    DtwResource * all_users = resource.sub_resource(database, USERS_PATH);

    if(new_email){
        char *old_email = resource.get_string_from_sub_resource(user,EMAIL_PATH);
        destroy_index(all_users, EMAIL_PATH, old_email);
        create_index(all_users, user->name, EMAIL_PATH, new_email);
        resource.set_bool_in_sub_resource(user,false,VERIFIED_PATH);
    }

    if(new_username){
        char *old_username = resource.get_string_from_sub_resource(user,USERNAME_PATH);
        destroy_index(all_users, USERNAME_PATH, old_username);
        create_index(all_users, user->name, USERNAME_PATH, new_username);
    }

    if(new_password){
        char *sha = dtw_generate_sha_from_string(new_password);
        resource.set_string_in_sub_resource(user,sha,PASSWORD_PATH);
        free(sha);
    }

    if(set_is_root){
        resource.set_bool_in_sub_resource(user,is_root,IS_ROOT_PATH);
    }

}

void database_upload_profile_picture(DtwResource *user,const char *extension,bool public, unsigned char *value,long size){
    resource.set_bool_in_sub_resource(user,public,PUBLIC_PATH);
    resource.set_binary_in_sub_resource(user,value,size,"file.%s",extension);
}

bool  password_are_equal(DtwResource *user, char *entrie_passworld){
    DtwResource  *password = resource.sub_resource(user,PASSWORD_PATH);
    char *password_sha = resource.get_string(password);
    char *entre_sha = dtw.generate_sha_from_string(entrie_passworld);
    bool result = strcmp(password_sha,entre_sha) == 0;
    free(entre_sha);
    return  result;
}

bool  password_are_equal_if_password_provided(DtwResource *user, char *entrie_passworld){
    const bool ENTRIE_NOT_PROVIDED = true;
    if(!entrie_passworld){
        return ENTRIE_NOT_PROVIDED;
    }
    return password_are_equal(user,entrie_passworld);
}


short get_user_index_status_if_new_value_provided(DtwResource *database, DtwResource *user, const char *value_path, char *new_value){

    if(!new_value){
        return NEW_VALUE_NOT_PROVIDED;
    }

    DtwResource *already_exist = find_user_by_username_or_email(database,new_value);
    if(!already_exist){
        return USER_NOT_EXIST_INTERNAL;
    }

    char *old_value = resource.get_string_from_sub_resource(user,"%s",value_path);

    if(!strcmp(old_value,new_value)){
        return USER_HAVE_THE_SAME_NAME_INTERNAL;
    }
    return USER_ALREADY_EXIST_INTERNAl;

}