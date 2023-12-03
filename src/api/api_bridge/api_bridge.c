

ApiBridge *newApiBridge(){
    ApiBridge *self = UniversalGarbage_create_empty_struct(self,ApiBridge);
    self->garbage = newUniversalGarbage();
    UniversalGarbage_add(self->garbage, CwebHttpResponse_free,self->last_response);
    UniversalGarbage_add(self->garbage, CHash_free,self->last_hash);
    UniversalGarbage_add_simple(self->garbage,self->token);
    UniversalGarbage_add_simple(self->garbage,self->password);

    self->host = "localhost:3000";
    return  self;
}

void ApiBridge_set_token(ApiBridge *self,const char *token){
    self->token = strdup(token);
    UniversalGarbage_resset(self->garbage,self->token);
}
void ApiBridge_set_password(ApiBridge *self,const char *password){
    self->password = strdup(password);
    UniversalGarbage_resset(self->garbage,self->password);
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

    //set default token
    if(self->token && !CwebDict_get(request->headers,TOKEN_ENTRE)){
        CwebDict_set(request->headers,TOKEN_ENTRE,self->token);
    }

    if(self->password && !CwebDict_get(request->headers,PASSWORD_ENTRE)){
        CwebDict_set(request->headers,PASSWORD_ENTRE,self->password);
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
CHash* ApiBridge_list_users(ApiBridge *self,const char *contains,bool include_root_props,bool include_tokens){
    CHash  *entries = newCHashObject(
            INCLUDE_TOKEN_ENTRE,hash.newBool(include_tokens),
            INCLUDE_ROOT_PROPS_ENTRE,hash.newBool(include_root_props)
   );
    if(contains){
        obj.set_string(entries,CONTAINS_ENTRE,contains);
    }

    int status = ApiBridge_call_server(
            self,
            LIST_USERS_ROUTE,
            entries
    );

    return self->last_hash;
}
CHash* ApiBridge_get_user_props(ApiBridge *self,const char *login){
    int status = ApiBridge_call_server(
            self,
            GET_USER_PROPS_ROUTE,
            newCHashObject(
                    LOGIN,hash.newString(login)
            )
    );

    return self->last_hash;
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
        ApiBridge_set_password(self,password);
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

int ApiBridge_remove_all_tokens(ApiBridge *self){
    return ApiBridge_call_server(self,REMOVE_ALL_TOKENS_ROUTE,NULL);
}

int ApiBridge_remove_all_infinite_tokens(ApiBridge *self){
    return ApiBridge_call_server(self,REMOVE_ALL_INFINITE_TOKENS_ROUTE,NULL);
}

int ApiBridge_remove_all_finite_tokens(ApiBridge *self){
    return ApiBridge_call_server(self,REMOVE_ALL_FINITE_TOKENS_ROUTE,NULL);
}


int ApiBridge_modify_self_props(ApiBridge *self,const char *new_username,const char *new_email,const char *new_password){
    CHashObject * entries = newCHashObjectEmpty();
    if(new_username){
        CHashObject_set_string(entries,NEW_USERNAME_ENTRE,new_username);
    }
    if(new_email){
        CHashObject_set_string(entries,NEW_EMAIL_ENTRE,new_email);
    }
    if(new_password){
        CHashObject_set_string(entries,NEW_PASSWORD_ENTRE,new_password);
    }
    return ApiBridge_call_server(self,MODIFY_SELF_PROPS_ROUTE,entries);
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
