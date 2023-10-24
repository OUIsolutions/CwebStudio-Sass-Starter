





CwebHttpResponse *create_token(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    aply_path_protection(entries, USERNAME_OR_EMAIL_ENTRIE);
    char *username_or_email = obj.getString(entries, USERNAME_OR_EMAIL_ENTRIE);
    char *password = obj.getString(entries, PASSWORD_ENTRIE);

    obj.set_default(entries, EXPIRATION_ENTRIE, hash.newNumber(DEFAULT_EXPIRATION));
    long expiration = (long)obj.getNumber_converting(entries, EXPIRATION_ENTRIE);

    if(expiration != -1 && expiration <=0){
        validator.raise_error_by_key(entries,
                 EXPIRATION_ENTRIE,
                 INVALID_EXPIRATION,
                 NOT_VALID_EXPIRATION_MENSSAGE,
                 NULL
        );
    }

    obj.set_default(entries, RENEW_ENTRIE, hash.newBool(DEFAULT_ALLOW_RENEW));

    bool allow_renew = obj.getBool_converting(entries, RENEW_ENTRIE);


    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    DtwResource *user = find_user_by_username_or_email(database,username_or_email);

    if(!user){
        return send_error(
                request,
                NOT_FOUND,
                USER_NOT_EXIST,
                USER_NOT_EXIST_MENSSAGE,
                username_or_email
        );
    }

    if(!password_are_equal(user, password)){
        return send_error(
                request,
                FOREBIDEN,
                WRONG_PASSWORD,
                WRONG_PASSWORD_MENSSAGE
        );
    }

    //the token assignature will be formed by the user password + time + id
    char *user_id = user->name;
    bool infinite = expiration == -1;

    char *token = NULL;

    if(infinite){
        #ifdef MAX_INFINITE_TOKENS
                long total_tokens = count_infinite_token(user);
                if(total_tokens >= MAX_INFINITE_TOKENS){
                    int total_to_remove = (total_tokens - MAX_INFINITE_TOKENS) + 1;
                    remove_last_updated_infinite_token(user, total_to_remove);
                }

        #endif
        token = create_infinite_token(user);
    }

    if(infinite == false){
        remove_expired_tokens(user);

        #ifdef MAX_FINITE_TOKENS
            long total_tokens = count_finite_token(user);
            if(total_tokens > MAX_FINITE_TOKENS){
                int total_to_remove = (total_tokens - MAX_FINITE_TOKENS) +1;
                remove_last_updated_finite_token(user,total_to_remove);
            }
        #endif

        create_finite_token(user, token, allow_renew, expiration);
    }


    resource.commit(database);
    CHash *response_hash = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            TOKEN_KEY,hash.newString(token)
            );

    if(infinite){
        obj.set_once(response_hash,EXPIRATION_KEY,hash.newString(NEVER_EXPIRATION));
    }

    if(infinite == false){
        long now  = time(NULL);
        long final_expiration = now + (expiration * 60);
        char *expiration_in_str = dtw_convert_unix_time_to_string(final_expiration);
        obj.set_once(response_hash,EXPIRATION_KEY,hash.newString(expiration_in_str));
        free(expiration_in_str);
    }


    free(token);
    return send_chash_cleaning_memory(response_hash,HTTP_CREATED);
}