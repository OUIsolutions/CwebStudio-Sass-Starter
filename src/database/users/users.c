


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


CHash * describe_user(DtwResource *user, bool include_tokens){
    CHashObject * user_obj = newCHashObjectEmpty();

    char *username = resource.get_string_from_sub_resource(user,USERNAME_PATH);
    obj.set_once(user_obj,USERNAME_KEY,hash.newString(username));


    char *email = resource.get_string_from_sub_resource(user,EMAIL_PATH);


    obj.set_once(user_obj,EMAIL_KEY,hash.newString(email));

    bool is_root = resource.get_bool_from_sub_resource(user,IS_ROOT_PATH);


    obj.set_once(user_obj,IS_ROOT_KEY,hash.newBool(is_root));

    if(!include_tokens){
        return user_obj;
    }

    CHashArray * finite_tokens = newCHashArrayEmpty();
    obj.set_once(user_obj,FINITE_TOKENS_KEY,finite_tokens);

    DtwResource  *finite_tokens_resource = resource.sub_resource(user,FINITE_TOKENS_PATH);
    DtwStringArray *finite_tokens_list = resource.list_names(finite_tokens_resource);

    for(int i = 0; i < finite_tokens_list->size; i ++){
        CHashObject *current_token_obj = newCHashObjectEmpty();
        array.append_once(finite_tokens,current_token_obj);

        DtwResource *current_token_resource = resource.sub_resource(
                finite_tokens_resource,
                finite_tokens_list->strings[i]
        );

        long creation = resource.get_long_from_sub_resource(current_token_resource,CREATION_PATH);
        char *converted_creation = dtw_convert_unix_time_to_string(creation);
        obj.set_once(current_token_obj,CREATION_KEY,hash.newString(converted_creation));
        free(converted_creation);

        bool allow_renew = resource.get_bool_from_sub_resource(current_token_resource,ALLOW_RENEW_PATH);

        obj.set_once(current_token_obj,ALLOW_RENEW_KEY,hash.newBool(allow_renew));

        long expiration = resource.get_long_from_sub_resource(current_token_resource,EXPIRATION_PATH);

        long last_update = resource.get_long_from_sub_resource(current_token_resource,LAST_UPDATE_PATH);

        char *last_update_in_str = dtw_convert_unix_time_to_string(last_update);
        obj.set_once(current_token_obj,LAST_UPDATE_KEY,hash.newString(last_update_in_str));
        free(last_update_in_str);

        long expiration_time = last_update + expiration;
        bool is_expired = time(NULL) >=  expiration_time;
        if(is_expired){
            obj.set_once(current_token_obj,EXPIRATION_KEY,hash.newString(EXPIRED_RESPONSE));
        }
        else{
            char *expiration_string = dtw_convert_unix_time_to_string(expiration_time);
            obj.set_once(current_token_obj,EXPIRATION_KEY,hash.newString(expiration_string));
            free(expiration_string);
        }


    }

    dtw.string_array.free(finite_tokens_list);

    CHashArray *infinite_tokens = newCHashArrayEmpty();
    obj.set_once(user_obj,INFINITE_TOKENS_KEY,infinite_tokens);
    DtwResource * infinite_tokens_resource = resource.sub_resource(user,INFINITE_TOKENS_PATH);
    DtwStringArray * infinite_tokens_list = resource.list_names(infinite_tokens_resource);
    for(int i = 0; i < infinite_tokens_list->size; i ++){
        CHashObject *current_token_obj = newCHashObjectEmpty();
        array.append_once(infinite_tokens,current_token_obj);

        DtwResource *current_token_resource = resource.sub_resource(
                infinite_tokens_resource,
                infinite_tokens_list->strings[i]
        );

        long creation = resource.get_long_from_sub_resource(current_token_resource,CREATION_PATH);
        char *converted_creation = dtw_convert_unix_time_to_string(creation);
        obj.set_once(current_token_obj,CREATION_KEY,hash.newString(converted_creation));
        free(converted_creation);

        long last_update = resource.get_long_from_sub_resource(current_token_resource,LAST_UPDATE_PATH);
        char *last_update_in_str = dtw_convert_unix_time_to_string(last_update);
        obj.set_once(current_token_obj,LAST_UPDATE_KEY,hash.newString(last_update_in_str));
        free(last_update_in_str);

    }

    dtw.string_array.free(infinite_tokens_list);


    return user_obj;
}
void database_create_user( DtwResource  *database,const char *username,const char *email,const char *password,bool is_root){

    DtwResource * all_users = resource.sub_resource(database,USERS_PATH);

    DtwResource *created_user = resource.sub_resource_random(all_users,NULL);

    set_index(all_users,created_user->name,EMAIL_PATH,email);
    set_index(all_users,created_user->name,USERNAME_PATH,username);

    DtwResource *password_resource = resource.sub_resource(created_user,PASSWORD_PATH);
    resource.set_string(password_resource,password);
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
