

CwebHttpResponse *get_user_props(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_root(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    char *username_or_email = obj.getString(entries, LOGIN);
    obj.set_default(entries, INCLUDE_TOKEN_ENTRE, hash.newBool(false));
    bool include_tokens = obj.getBool_converting(entries, INCLUDE_TOKEN_ENTRE);
    char *token = obj.getString(entries,TOKEN_ENTRE);
    char *host = obj.getString(entries,HOST_ENTRIE);
    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    DtwResource *user_found = find_user_by_username_or_email(database,username_or_email);
    DtwResource_catch(database){
        return NULL;
    }


    if(!user_found){
        return send_error(
                request,
                NOT_FOUND,
                USER_NOT_EXIST,
                USER_NOT_EXIST_MENSSAGE,
                username_or_email
        );
    }

    CHashObject  *description = describe_user(user_found,include_tokens,true,token,host);
    DtwResource_catch(database){
        return NULL;
    }

    commit_transaction(database);

    return send_chash_cleaning_memory(description, HTTP_OK);

}