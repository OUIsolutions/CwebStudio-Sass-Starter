





CwebHttpResponse *list_users(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_root(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }
    char *contains  = NULL;

    if(obj.exist(entries, CONTAINS_ENTRE)){
        aply_path_protection(entries, CONTAINS_ENTRE);
        contains = obj.getString(entries, CONTAINS_ENTRE);
    }

    obj.set_default(entries, CASE_SENSITIVE_ENTRE, hash.newBool(false));
    bool case_sensitive = obj.getBool_converting(entries, CASE_SENSITIVE_ENTRE);


    obj.set_default(entries, INCLUDE_TOKEN_ENTRE, hash.newBool(false));
    bool include_tokens = obj.getBool_converting(entries, INCLUDE_TOKEN_ENTRE);

    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    CHash *description = describe_all_users(database,contains,case_sensitive,include_tokens,true);
    return send_chash_cleaning_memory(description, HTTP_OK);

}