

CwebHttpResponse *get_self_props(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate(request,entries,database);
    DtwResource_catch(database){
        return NULL;
    }
    if(auth.error){
        return  auth.response_error;
    }

    DtwResource *user = auth.user;

    obj.set_default(entries, INCLUDE_TOKEN_ENTRE, hash.newBool(false));
    bool include_tokens = obj.getBool_converting(entries, INCLUDE_TOKEN_ENTRE);


    char *token = obj.getString(entries,TOKEN_ENTRE);
    char *host = obj.getString(entries,HOST_ENTRIE);

    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }
    bool include_root_props = false;
    bool is_root = resource.get_bool_from_sub_resource(user,IS_ROOT_PATH);

    if(is_root){
        obj.set_default(entries, INCLUDE_ROOT_PROPS_ENTRE, hash.newBool(false));
        include_root_props = obj.getBool_converting(entries, INCLUDE_ROOT_PROPS_ENTRE);
    }

    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    CHashObject  *description = describe_user(user,include_tokens,include_root_props,token,host);
    DtwResource_catch(database){
        return NULL;
    }

    commit_transaction(database);

    return send_chash_cleaning_memory(description, HTTP_OK);

}