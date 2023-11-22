
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


CwebHttpResponse * ApiBridge_call_server(ApiBridge *self,const char *route, CHash *params, CHash *headers){
    CwebHttpRequest * request = newCwebHttpRequest(-1);
    private_parse_chash_to_cweb_dict(params,request->params);
    private_parse_chash_to_cweb_dict(params,request->headers);
    return  main_sever(request);

}

CwebHttpResponse * ApiBridge_call_server_with_only_headders(ApiBridge*self,const char *route, CHash *headers){
    return ApiBridge_call_server(self,route, NULL, headers);
}


