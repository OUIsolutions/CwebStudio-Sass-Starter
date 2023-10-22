


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
    return find_element_by_id(users,id);
}

bool is_root(DtwResource *user){
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



void database_create_user( DtwResource  *database,const char *username,const char *email,const char *password,bool is_root){
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
    DtwResource  *is_root_resource = resource.sub_resource(created_user,IS_ROOT_PATH);
    resource.set_bool(is_root_resource,is_root);


}
bool  password_are_equal(DtwResource *user, char *entrie_passworld){
    DtwResource  *password = resource.sub_resource(user,PASSWORD_PATH);
    char *password_sha = resource.get_string(password);
    char *entrie_sha = dtw.generate_sha_from_string(entrie_passworld);
    bool result = strcmp(password_sha,entrie_sha) == 0;
    free(entrie_sha);
    return  result;
}