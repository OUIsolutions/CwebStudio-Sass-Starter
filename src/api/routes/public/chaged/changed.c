

CwebHttpResponse *chaged_static_route(CwebHttpRequest *request){
    UniversalGarbage *garbage = newUniversalGarbage();
    DtwHash * hasher = newDtwHash();
    UniversalGarbage_add(garbage,DtwHash_free,hasher);
    dtw.hash.digest_folder_by_last_modification(hasher,cweb_static_folder);

    char * saved_hash = dtw_load_string_file_content(STATIC_AASSIGNATURE);
    UniversalGarbage_add_simple(garbage,saved_hash);

    CHashObject *response = newCHashObject(
            CODE_KEY,hash.newNumber(INTERNAL_OK),
            CHAGEND_KEY,hash.newBool(true)
    );

    if(strings_equal(saved_hash,hasher->hash)){
        obj.set_bool(response,CHAGEND_KEY,false);
    }

    
    UniversalGarbage_free(garbage);
    return send_chash_cleaning_memory(response,CWEB_OK);
}
