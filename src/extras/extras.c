

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
        obj.set_once(all,key_val->key,hash.newString(key_val->value) );
    }
    return  all;
}
