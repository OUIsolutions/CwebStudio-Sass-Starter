

ApiBridge *newApiBridge(){
    ApiBridge *self = UniversalGarbage_create_empty_struct(self,ApiBridge);
    self->garbage = newUniversalGarbage();
    UniversalGarbage_add(self->garbage, CwebHttpResponse_free,self->last_response);
    UniversalGarbage_add(self->garbage, CHash_free,self->last_hash);
    UniversalGarbage_add_simple(self->garbage,self->token);
    self->host = "localhost:3000";
    return  self;
}

void ApiBridge_set_token(ApiBridge *self,const char *token){
    self->token = strdup(token);
    UniversalGarbage_resset(self->garbage,self->token);
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
    UniversalGarbage *internal_garbage = newUniversalGarbage();
    CwebHttpRequest * request = newCwebHttpRequest(-1);
    UniversalGarbage_add(internal_garbage, CwebHttpRequest_free,request);
    UniversalGarbage_add(internal_garbage, CHash_free,params);
    UniversalGarbage_add(internal_garbage, CHash_free,headers);
    UniversalGarbage_add_simple(internal_garbage, content);

    request->route = strdup(route);
    private_parse_chash_to_cweb_dict(params,request->params);
    private_parse_chash_to_cweb_dict(headers,request->headers);
    if(content){
        CwebDict_set(request->headers,"Content-type",content_type);
        request->content_length = content_size;
        request->content = content;
    }
    CwebDict_set(request->headers,HOST_ENTRIE,self->host);
    if(self->token){
        CwebDict_set(request->headers,TOKEN_ENTRE,self->token);
    }

    self->last_response  = main_sever(request);
    UniversalGarbage_resset(self->garbage,self->last_response );
    if(!self->last_response){
        self->last_response = NULL;
        self->last_content = NULL;
        self->last_content_size = -1;
        self->last_status_code = -1;
        self->last_hash = NULL;
        UniversalGarbage_free(internal_garbage);
        return -1;
    }
    self->last_content = self->last_response->content;
    self->last_content_size =  self->last_response->content_length;
    self->last_status_code =  self->last_response->status_code;

    self->last_response->content[self->last_content_size] ='\0';

    self->last_hash = CHash_load_from_json_strimg((char*)self->last_content);
    UniversalGarbage_resset(self->garbage,self->last_hash);

    UniversalGarbage_free(internal_garbage);

    if(self->last_status_code == 200 || self->last_status_code == 202){
        return 0;
    }

    return -1;
}



int ApiBridge_call_server(ApiBridge*self, const char *route, CHash *entries){
    return ApiBridge_call_server_full(self, route, NULL, entries,NULL,NULL,-1);
}

int ApiBridge_create_user(ApiBridge *self,const char *username,const char *email, const char *password,bool is_root,bool verified){
    return  ApiBridge_call_server(
            self,
            CREATE_USER_ROUTE,
            newCHashObject(
                    USERNAME_ENTRE,hash.newString(username),
                    EMAIL_ENTRE,hash.newString(email),
                    PASSWORD_ENTRE,hash.newString(password),
                    IS_ROOT_ENTRE,hash.newBool(is_root),
                    VERIFIED_ENTRE,hash.newBool(verified)
            )
    );

}
char * ApiBridge_create_token(ApiBridge*self,const char *username,const char *password,long  expiration){
    int response = ApiBridge_call_server(
            self,
            CREATE_TOKEN_ROUTE,
            newCHashObject(
                    LOGIN,hash.newString(username),
                    PASSWORD_ENTRE,hash.newString(password),
                    EXPIRATION_ENTRE,hash.newNumber((double )expiration)
                    )
            );


    if(response ==0){
        char *token = obj.getString(self->last_hash,TOKEN_KEY);
        ApiBridge_set_token(self,token);
        return token;
    }
    return  NULL;
}

CHash *ApiBridge_get_self_props(ApiBridge *self,bool include_tokens,bool include_root_props){
    int status = ApiBridge_call_server(
            self,
            GET_SELF_PROPS_ROUTE,
            newCHashObject(
                    INCLUDE_TOKEN_ENTRE,hash.newBool(include_tokens),
                    INCLUDE_ROOT_PROPS_ENTRE,hash.newBool(include_root_props)
            )
    );

    return self->last_hash;

}

void ApiBridge_represent(ApiBridge *self){
    printf("status-code: %d\n",self->last_status_code);
    printf("headers:\n");
    CwebDict_represent(self->last_response->headers);
    printf("content: %s\n",(char*)self->last_content);
}

void ApiBridge_free(ApiBridge *self){
    UniversalGarbage_free(self->garbage);

    free(self);
}
