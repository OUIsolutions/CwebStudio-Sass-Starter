
CwebHttpResponse  *send_chash_cleaning_memory(CHash *element,int status_code){
    cJSON *element_converted = hash.dump_to_cJSON(element);
    hash.free(element);
    return cweb.response.send_cJSON_cleaning_memory(element_converted,status_code);
}

CHashObject *join_headders_and_paramns(CwebHttpRequest *request){
    CHashObject * all = obj.newObjectEmpty();
    CwebDict *query_paramns = request->params;
    for(int i = 0; i < query_paramns->size; i++){
        CwebKeyVal *key_val = query_paramns->keys_vals[i];
        obj.set_once(all,key_val->key,hash.newString(key_val->value) );
    }
    CwebDict *heeaders = request->headers;
    for(int i = 0; i < heeaders->size; i++){
        CwebKeyVal *key_val = heeaders->keys_vals[i];
#ifdef  ALL_ENTRIES_LOWER
        CTextStack *converted = stack.newStack_string(key_val->key);
        stack.self_lower(converted);
        obj.set_once(all,converted->rendered_text,hash.newString(key_val->value) );
        stack.free(converted);
#else
        obj.set_once(all,key_val->key,hash.newString(key_val->value) );
#endif

    }
    return  all;
}
void aply_path_protection(CHashObject *element,const  char *key){
    CTextStack *string = obj.getStack(element,key);
    CHash_protected(element){
        stack.self_replace(string,"/","");
    }

}

bool strings_equal(const char *string_a ,const char *string_b){
    if(!string_a){
        return false;
    }
    if(!string_b){
        return false;
    }
    if(strcmp(string_a,string_b) ==0){
        return true;
    }
}
