

CHash * save_start_request(CwebHttpRequest *request){

    long total = dtw_get_total_itens_of_dir(REQUESTS_OBSERVER_PATH);
    if(total > MAX_REQUESTS_SAVE){
        return NULL;
    }

    long now_in_unix =time(NULL);
    char *now = dtw_convert_unix_time_to_string(now_in_unix);

    CHashObject *request_obj =  newCHashObject(
            "route",hash.newString(request->route),
            "method",hash.newString(request->method),
            "client_ip",hash.newString(request->client_ip)
    );

    #ifdef INCLUDE_URL_OBSERVER
        obj.set_string(request_obj,"url",request->url);
    #endif

    #ifdef INCLUDE_QUERY_PARAMS_OBSERVER
            CHash *paramns = newCHashObjectEmpty();
            CwebDict *query_paramns = request->params;
            for(int i = 0; i < query_paramns->size; i++){
                CwebKeyVal *key_val = query_paramns->keys_vals[i];
                obj.set_string(paramns,key_val->key,key_val->value );
            }
            obj.set_any(request_obj,"paramns",paramns);
    #endif

    #ifdef INCLUDE_HEADDERS_OBSERVER
    CHash *headders_obj = newCHashObjectEmpty();
    CwebDict *heeaders = request->headers;
    for(int i = 0; i < heeaders->size; i++){
        CwebKeyVal *key_val = heeaders->keys_vals[i];
        obj.set_string(headders_obj,key_val->key,key_val->value );
    }
    obj.set_any(request_obj,"headders",headders_obj);
    #endif

    CHashObject * element = newCHashObject(
            "start",hash.newString(now),
            "start_unix",hash.newNumber(now_in_unix),
            "end",hash.newNULL(),
            "duration",hash.newNULL(),
            "client",hash.newString(request->client_ip),
            "request", request_obj,
            "response",hash.newNULL()
     );

    char *text  = hash.dump_to_json_string(element);

    char *sha = dtw_generate_sha_from_string(text);
    CTextStack * cutted_sha = newCTextStack_string_empty();
    stack.format(cutted_sha,"%sc",sha);
    stack.self_substr(cutted_sha,0,15);

    CTextStack *path = newCTextStack_string_empty();
    stack.format(
        path,
        "%s/%sc-%tc.jsom",
        REQUESTS_OBSERVER_PATH,
        now,
        cutted_sha
    );

    dtw.write_string_file_content(path->rendered_text,text);
    free(text);
    stack.free(path);
    return  element;
}

void  save_end_request(CHash *generated,CwebHttpRequest *request,CwebHttpResponse *response){

    
}
