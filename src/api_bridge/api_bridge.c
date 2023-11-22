

ApiBridge *newApiBridge(){
    ApiBridge *self = UniversalGarbage_create_empty_struct(self,ApiBridge);
    self->garbage = newUniversalGarbage();
    return  self;
}

void ApiBridge_set_token(ApiBridge *self,const char *token){
    if(self->token){
        free(self->token);
    }
    self->token = strdup(token);
}

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


int  ApiBridge_call_server_full(
        ApiBridge *self,
        const char *route,
        CHash *params,
        CHash *headers,
        const char *content_type,
        unsigned  char *content,
        long content_size
){
    CwebHttpRequest * request = newCwebHttpRequest(-1);
    request->route = strdup(route);
    private_parse_chash_to_cweb_dict(params,request->params);
    private_parse_chash_to_cweb_dict(headers,request->headers);
    if(content){
        CwebDict_set(request->headers,"Content-type",content_type);
        request->content_length = content_size;
        request->content = content;
    }

    if(self->token){
        CwebDict_set(request->headers,TOKEN_ENTRE,self->token);
    }

    CwebHttpResponse*  response = main_sever(request);
    if(!response){
        self->last_response = NULL;
        self->last_content = NULL;
        self->last_content_size = -1;
        self->last_status_code = -1;
        self->last_hash = NULL;
        return -1;
    }

    UniversalGarbage_add(self->garbage, CwebHttpResponse_free,response);
    self->last_response =response;
    self->last_content = response->content;
    self->last_content_size = response->content_length;
    self->last_status_code = response->status_code;

    if(response->content){
        self->last_hash = CHash_load_from_json_strimg((char*)response->content);
        UniversalGarbage_add(self->garbage, CHash_free,self->last_hash);
    }
    return response->status_code;
}


int ApiBridge_call_server(ApiBridge*self, const char *route, CHash *entries){
    return ApiBridge_call_server_full(self, route, NULL, entries,NULL,NULL,-1);
}





void ApiBridge_free(ApiBridge *self){
    UniversalGarbage_free(self->garbage);
    if(self->token){
        free(self->token);
    }
    free(self);
}