

CwebHttpResponse *create_token(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){




    char *username_or_email = obj.getString(entries,USERNAME_OR_EMAIL);
    char *password = obj.getString(entries,PASSWORD);
    obj.set_default(entries,EXPIRATION,hash.newNumber(30));
    long expiration = (long)obj.getNumber_converting(entries,EXPIRATION);

    obj.set_default(entries,ALLOW_RENEW,hash.newBool(true));
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

    resource.commit(database);

    return cweb.response.send_text("ok",200);



}