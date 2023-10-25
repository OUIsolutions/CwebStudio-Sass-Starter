
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
    return  false;
}


CTextStack  *construct_profile_picture_url(const char *user_id,bool public,const char *token, const char *host){

    CTextStack *url = newCTextStack_string(host);

    if(public){
        stack.format(url, "%s?%s=%s", GET_PUBLIC_PROFILE_PICTURE_ROUTE,
                     USER_ID_ENTRE, user_id
        );
        return url;
    }
    Token *t = extract_token(token);
    DtwHash *dt_hash = newDtwHash();
    dtw.hash.digest_string(dt_hash,t->sha->rendered_text);
    const char *SECRETE_NAME = "profile";
    dtw.hash.digest_string(dt_hash,SECRETE_NAME);
    CTextStack *sha = newCTextStack_string(dt_hash->hash);
    dtw.hash.free(dt_hash);
    stack.self_substr(sha,0,SHA_SIZE);

    stack.format(url, "%s?%s=%s&%s=%t&%s=%tc", GET_PRIVATE_PROFILE_PICTURE_ROUTE
           USER_ID_ENTRE, user_id,
           TOKEN_ID_ENTRE,t->token_id,
           SHA_ENTRE,sha
    );

    Token_free(t);

    return url;

}