
void private_parse_chash_to_cweb_dict(CHash *value,CwebDict *target){
    if(!value){
        return;
    }
    long size = hash.get_size(value);
    for(int i = 0; i < size; i++){

        char *key = obj.get_key_by_index(value,i);
        int type = obj.get_type(value, key);

        if(type == CHASH_STRING){
            CwebDict_set(target,key,obj.getString(value,key));
        }

        if(type == CHASH_NUMBER){
            char converted[20] ={0};
            sprintf(converted,"%lf",obj.getNumber(value,key));
            CwebDict_set(target,key,converted);
        }

        if(type == CHASH_BOOL){
            char converted[20] ={0};
            sprintf(converted,"%s",obj.getBool(value,key) ? "true":"false");
            CwebDict_set(target,key,converted);
        }
    }

}


CwebHttpResponse * ApiBridge_call_server_full(
        ApiBridge *self,
        const char *route,
        CHash *params,
        CHash *headers,
        const char *content_type,
        unsigned  char *content,
        long content_size
){
    CwebHttpRequest * request = newCwebHttpRequest(-1);
    private_parse_chash_to_cweb_dict(params,request->params);
    private_parse_chash_to_cweb_dict(headers,request->headers);
    if(content){
        CwebDict_set(request->headers,"Content-type",content_type);
        request->content_length = content_size;
        request->content = content;
    }
    return  main_sever(request);

}

CwebHttpResponse * ApiBridge_call_server(ApiBridge*self, const char *route, CHash *entries){
    return ApiBridge_call_server_full(self, route, NULL, entries,NULL,NULL,-1);
}


