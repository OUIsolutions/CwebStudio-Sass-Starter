

CHash * save_start_request(CwebHttpRequest *request){
    long now = time(NULL);
    CHashObject *request_obj =  newCHashObject(
            "route",hash.newString(request->route),
            "method",hash.newString(request->method),
            "client_ip",hash.newString(request->client_ip)
    );

    #ifdef INCLUDE_URL_OBSERVER
        obj.set_once(request_obj,"url",hash.newString(request->url));
    #endif

    #ifdef INCLUDE_QUERY_PARAMS_OBSERVER
            CHash *paramns = newCHashObjectEmpty();
            CwebDict *query_paramns = request->params;
            for(int i = 0; i < query_paramns->size; i++){
                CwebKeyVal *key_val = query_paramns->keys_vals[i];
                obj.set_once(paramns,key_val->key,hash.newString(key_val->value) );
            }
            obj.set_once(request_obj,"parramns",paramns);
    #endif

    #ifdef INCLUDE_HEADDERS_OBSERVER
    CHash *headders_obj = newCHashObjectEmpty();
    CwebDict *heeaders = request->headers;
    for(int i = 0; i < heeaders->size; i++){
        CwebKeyVal *key_val = heeaders->keys_vals[i];
        obj.set_once(headders_obj,key_val->key,hash.newString(key_val->value) );
    }
    obj.set_once(request_obj,"headders",headders_obj);
    #endif

    CHashObject * element = newCHashObject(
             "request", request_obj,
            "start",hash.newNumber(now),
            "end",hash.newNULL(),
            "duration",hash.newNULL(),
            "response",hash.newNULL()
     );

    char *text  = hash.dump_to_json_string(element);
    char *sha = dtw_generate_sha_from_string(text);
    CTextStack *path = newCTextStack_string_empty();
    stack.format(
        path,
        "%s/%d%-sc.jsom",
        REQUESTS_OBSERVER_PATH,
        now,
        sha
    );
    dtw.write_string_file_content(path->rendered_text,text);
    free(text);
    stack.free(path);
    return  element;
}
