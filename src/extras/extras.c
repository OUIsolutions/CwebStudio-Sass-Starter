
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
        obj.set_string(all,key_val->key,key_val->value );
    }
    CwebDict *heeaders = request->headers;
    for(int i = 0; i < heeaders->size; i++){
        CwebKeyVal *key_val = heeaders->keys_vals[i];
#ifdef  ALL_ENTRIES_LOWER
        CTextStack *converted = stack.newStack_string(key_val->key);
        stack.self_lower(converted);
        obj.set_string(all,converted->rendered_text,key_val->value );
        stack.free(converted);
#else
        obj.set_once(all,key_val->key,hash.newString(key_val->value) );
#endif

    }
    return  all;
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
    return  false;
}


CTextStack  *construct_profile_picture_url(const char *user_id, bool is_public, const char *token, const char *host){

    CTextStack *url = newCTextStack_string(host);

    if(is_public){
        stack.format(url, "%s?%s=%s", GET_PUBLIC_PROFILE_PICTURE_ROUTE,
                     USER_ID_ENTRE, user_id
        );
        return url;
    }

    CTextStack *token_generated = create_sub_token_string_from_token_string(token,PROFILE_PICTURE_PATH);
    stack.format(url, "%s?%s=%tc",GET_PRIVATE_PROFILE_PICTURE_ROUTE,
                 SUB_TOKEN_ENTRE,token_generated
    );

    return url;

}

CTextStack  * construct_verification_url(const char *user_id,const char *verification_key,const char *host){
    CTextStack *url = newCTextStack_string(host);

    stack.format(url, "%s?%s=%s&%s=%s", VERIFY_EMAIL_ROUTE,
                 USER_ID_ENTRE, user_id,
                 VERIFICATION_KEY_ENTRE, verification_key
    );

    return url;
}

long get_time(){
    if(api_time != -1){
        return  api_time;
    }

    return time(NULL);

}
