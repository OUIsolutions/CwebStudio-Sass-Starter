


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

CHash * describe_user(DtwResource *user, bool include_tokens){
    CHashObject * user_obj = newCHashObjectEmpty();

    char *username = resource.get_string(
                    resource.sub_resource(user,"username")
    );
    obj.set_once(user_obj,"username",hash.newString(username));

    char *email = resource.get_string(
            resource.sub_resource(user,"email")
    );
    obj.set_once(user_obj,"email",hash.newString(email));

    bool is_root = resource.get_bool(
            resource.sub_resource(user,"email")
    );
    obj.set_once(user_obj,"email",hash.newBool(is_root));

    if(!include_tokens){
        return user_obj;
    }

    CHashArray * finite_tokens = newCHashArrayEmpty();

    DtwResource  *finite_tokens_resource = resource.sub_resource(user,FINITE_TOKENS_PATH);
    DtwStringArray *finite_tokens_list = resource.list_names(finite_tokens_resource);

    for(int i = 0; i < finite_tokens_list->size; i ++){

        DtwResource *current_token_resource = resource.sub_resource(
                finite_tokens_resource,
                finite_tokens_list->strings[i]
        );

        long creation = resource.get_long(
                resource.sub_resource(current_token_resource,CREATION_PATH)
        );
        char *converted_creation = dtw_convert_unix_time_to_string(creation);

        long expiration = resource.get_long(
                resource.sub_resource(current_token_resource,EXPIRATION_PATH)
        );
        char * converted_expiration = dtw_convert_unix_time_to_string(expiration);


        array.append_once(finite_tokens, newCHashObject(
                TOKEN_KEY,hash.newString(current_token_resource->name),
                CREATION_KEY, hash.newString(converted_creation),
                EXPIRATION_KEY,hash.newString(converted_expiration)
        ));

        free(converted_creation);
        free(converted_expiration);
    }

    dtw.string_array.free(finite_tokens_list);

    obj.set_once(user_obj,FINITE_TOKENS_KEY,finite_tokens);



    return user_obj;
}

bool  password_are_equal(DtwResource *user, char *entrie_passworld){
    DtwResource  *password = resource.sub_resource(user,PASSWORD_PATH);
    char *password_sha = resource.get_string(password);
    char *entrie_sha = dtw.generate_sha_from_string(entrie_passworld);
    bool result = strcmp(password_sha,entrie_sha) == 0;
    free(entrie_sha);
    return  result;
}
