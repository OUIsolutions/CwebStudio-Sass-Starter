





CwebHttpResponse *list_users(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_root(request,entries,database);
    DtwResource_catch(database){
        return NULL;
    }

    if(auth.error){
        return  auth.response_error;
    }
    char *contains  = NULL;

    if(obj.exist(entries, CONTAINS_ENTRE)){
        contains = obj.getString(entries, CONTAINS_ENTRE);
    }

    obj.set_default(entries, CASE_SENSITIVE_ENTRE, hash.newBool(false));
    bool case_sensitive = obj.getBool_converting(entries, CASE_SENSITIVE_ENTRE);


    obj.set_default(entries, INCLUDE_TOKEN_ENTRE, hash.newBool(false));
    bool include_tokens = obj.getBool_converting(entries, INCLUDE_TOKEN_ENTRE);

    obj.set_default(entries, INCLUDE_ROOT_PROPS_ENTRE, hash.newBool(false));
    bool include_root_props = obj.getBool_converting(entries, INCLUDE_ROOT_PROPS_ENTRE);
    char *token = obj.getString(entries,TOKEN_ENTRE);
    char *host = obj.getString(entries,HOST_ENTRIE);
    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    CHash *description = describe_all_users(database,contains,case_sensitive,include_tokens,include_root_props,token, host);
    DtwResource_catch(database){
        return NULL;
    }

    commit_transaction(database);

    return send_chash_cleaning_memory(description, HTTP_OK);

}