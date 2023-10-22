





CwebHttpResponse *list_users(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_root(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }
    char *start_path  = NULL;

    if(obj.exist(entries,START_PATH_ENTRIE)){
        aply_path_protection(entries, START_PATH_ENTRIE);
        start_path = obj.getString(entries,START_PATH_ENTRIE);
    }


    obj.set_default(entries,INCLUDE_TOKEN_ENTRIE,hash.newBool(false));
    bool include_tokens = obj.getBool_converting(entries,INCLUDE_TOKEN_ENTRIE);

    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }
    
    CHash *description = describe_all_users(database,start_path,include_tokens);
    return send_chash_cleaning_memory(description, HTTP_OK);

}