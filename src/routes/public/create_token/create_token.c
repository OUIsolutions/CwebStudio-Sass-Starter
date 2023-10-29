

void remove_max_ifinite_tokens(DtwResource *user){
#ifdef MAX_INFINITE_TOKENS
    long total_tokens = count_infinite_token(user);
    if(total_tokens >= MAX_INFINITE_TOKENS){
        int total_to_remove = (total_tokens - MAX_INFINITE_TOKENS) + 1;
        remove_last_updated_infinite_token(user, total_to_remove);
    }

#endif
}

void remove_max_finite_tokens(DtwResource *user){
#ifdef MAX_FINITE_TOKENS
    long total_tokens = count_finite_token(user);
    if(total_tokens > MAX_FINITE_TOKENS){
        int total_to_remove = (total_tokens - MAX_FINITE_TOKENS) +1;
        remove_last_updated_finite_token(user,total_to_remove);
    }
#endif
}

CwebHttpResponse *create_token(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    char *username_or_email = obj.getString(entries, USERNAME_OR_EMAIL_ENTRE);
    char *password = obj.getString(entries, PASSWORD_ENTRE);

    obj.set_default(entries, EXPIRATION_ENTRE, hash.newNumber(DEFAULT_EXPIRATION));
    long expiration = (long)obj.getNumber_converting(entries, EXPIRATION_ENTRE);

    bool invalid_token =expiration != -1 && expiration <=0;
    

    if(invalid_token){
        validator.raise_error_by_key(entries,
                 EXPIRATION_ENTRE,
                 INVALID_EXPIRATION,
                 NOT_VALID_EXPIRATION_MENSSAGE,
                 NULL
        );
    }

    obj.set_default(entries, RENEW_ENTRE, hash.newBool(DEFAULT_ALLOW_RENEW));

    bool allow_renew = obj.getBool_converting(entries, RENEW_ENTRE);


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

    bool infinite = expiration == -1;
    Token  *token;

    if(infinite){
        remove_max_ifinite_tokens(user);
        token = database_create_infinite_token(user,password);
    }

    if(infinite == false){
        remove_expired_tokens(user);
        remove_max_finite_tokens(user);
        token = database_create_finite_token(user, password, allow_renew, expiration);
    }


    resource.commit(database);
    CHash *response_hash = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            TOKEN_KEY,hash.newString(token->token_string->rendered_text)
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

    Token_free(token);

    return send_chash_cleaning_memory(response_hash,HTTP_CREATED);
}