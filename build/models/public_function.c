

CwebHttpResponse *function_name(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){


    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }
   
    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY,hash.newString("route ok")
    );
    resource.commit(database);

    return send_chash_cleaning_memory(response,HTTP_OK);

}
