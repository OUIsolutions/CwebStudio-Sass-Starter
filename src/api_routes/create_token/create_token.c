





CwebHttpResponse *create_token(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    char *username_or_email = obj.getString(entries,USERNAME_OR_EMAIL);
    char *password = obj.getString(entries,PASSWORD);
    obj.set_default(entries,EXPIRATION,hash.newNumber(DEFAULT_EXPIRATION));
    long expiration = (long)obj.getNumber_converting(entries,EXPIRATION);

    obj.set_default(entries,ALLOW_RENEW,hash.newBool(DEFAULT_ALLOW_RENEW));
    bool allow_renew = obj.getBool_converting(entries,ALLOW_RENEW);


    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }


    DtwResource *user = find_user_by_username_or_email(database,username_or_email,true);

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
    DtwHash * token_assignature = newDtwHash();
    dtw.hash.digest_string(token_assignature,user_id);
    dtw.hash.digest_string(token_assignature,password);
    dtw.hash.digest_long(token_assignature, time(NULL));

    CHash *token_obj = newCHashObject(
            "hash",token_assignature,
            "userid",user_id
    );
    char *token_json = hash.dump_to_json_string(token_obj);
    hash.free(token_obj);
    dtw.hash.free(token_assignature);
    char *token = dtw_base64_encode((unsigned char *)user_id, strlen(token_json));



    resource.commit(database);

    return cweb.response.send_text("ok",200);



}