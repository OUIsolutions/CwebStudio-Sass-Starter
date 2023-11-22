

CHash * describe_user_without_tokens(DtwResource *user, bool include_root_props, const char *token, const char *host){
    DtwResource_catch(user){
        return NULL;
    }

    UniversalGarbage *garbage = newUniversalGarbage();

    CHashObject * user_obj = newCHashObjectEmpty();
    UniversalGarbage_add_return(garbage, CHash_free,user_obj);

    char *username = resource.get_string_from_sub_resource(user,USERNAME_PATH);
    char *email = resource.get_string_from_sub_resource(user,EMAIL_PATH);
    long creation_data = resource.get_long_from_sub_resource(user,CREATION_PATH);
    long last_update_data = resource.get_long_from_sub_resource(user,LAST_UPDATE_PATH);
    bool verified = resource.get_bool_from_sub_resource(user,VERIFIED_PATH);
    bool is_root = resource.get_bool_from_sub_resource(user,IS_ROOT_PATH);

    DtwResource_catch(user){
        UniversalGarbage_free_including_return(garbage);
        return NULL;
    }

    obj.set_string(user_obj,USERNAME_KEY,username);


    char *converted_creation_data = dtw_convert_unix_time_to_string(creation_data);
    UniversalGarbage_add_simple(garbage,converted_creation_data);

    obj.set_string(user_obj,CREATION_KEY,converted_creation_data);

    char *converted_last_update = dtw_convert_unix_time_to_string(last_update_data);
    UniversalGarbage_add_simple(garbage,converted_last_update);
    obj.set_string(user_obj,LAST_UPDATE_PATH,converted_last_update);


    obj.set_string(user_obj,EMAIL_KEY,email);
    obj.set_bool(user_obj,VERIFIED_KEY,verified);


    if(include_root_props){

        if(verified){
            obj.set_any(user_obj, VERIFICATION_URL_ENTRE, hash.newNULL());
        }

        DtwResource *recovery_key = resource.sub_resource(user,RECOVERY_PASSWORD_PATH);
        if(resource.type(recovery_key) == DTW_COMPLEX_STRING_TYPE){
            char *reconvery_key_content = resource.get_string(recovery_key);
            DtwResource_catch(user){
                UniversalGarbage_free_including_return(garbage);
                return NULL;
            }
            obj.set_string(user_obj,RECOVERY_KEY,reconvery_key_content);
        }


        if(!verified){

            DtwResource *verification_resource = resource.sub_resource(user,VERIFICATION_PASSWORD_PATH);
            bool verification_exist = resource.type(verification_resource) == DTW_COMPLEX_STRING_TYPE;

            if(verification_exist){
                char *verification_password = resource.get_string(verification_resource);
                DtwResource_catch(user){
                    UniversalGarbage_free_including_return(garbage);
                    return NULL;
                }

                CTextStack  *verification_url = construct_verification_url(
                        user->name,
                        verification_password,
                        host
                );

                obj.set_Stack(user_obj, VERIFICATION_URL_ENTRE, verification_url);
            }

            if(!verification_exist){
                obj.set_any(user_obj, VERIFICATION_URL_ENTRE, hash.newNULL());
            }
        }

    }
    DtwResource *profile_picture = resource.sub_resource(user,PROFILE_PICTURE_PATH);
    bool exist_profile_picture = resource.type(profile_picture) == DTW_FOLDER_TYPE;

    if(exist_profile_picture){
        bool is_public = resource.get_bool_from_sub_resource(profile_picture, PUBLIC_PATH);
        DtwResource_catch(user){
            UniversalGarbage_free_including_return(garbage);
            return NULL;
        }
        CTextStack *profile_url = construct_profile_picture_url(user->name, is_public, token, host);
        obj.set_Stack(user_obj, PROFILE_PICTURE_URL_KEY, profile_url);
    }


    obj.set_bool(user_obj,IS_ROOT_KEY,is_root);
    UniversalGarbage_free(garbage);
    return user_obj;
}

void describe_finite_tokens(CHash *user_obj,DtwResource *user){
    DtwResource_catch(user){
        return ;
    }

    UniversalGarbage *garbage = newUniversalGarbage();

    CHashArray * finite_tokens = newCHashArrayEmpty();
    obj.set_any(user_obj,FINITE_TOKENS_KEY,finite_tokens);


    DtwResource  *finite_tokens_resource = resource.sub_resource(user,FINITE_TOKENS_PATH);
    DtwStringArray *finite_tokens_list = resource.list_names(finite_tokens_resource);
    UniversalGarbage_add(garbage, DtwStringArray_free,finite_tokens_list);

    DtwResource_catch(user){
        UniversalGarbage_free(garbage);
        return ;
    }

    for(int i = 0; i < finite_tokens_list->size; i ++){
        UniversalGarbage *internal_garbage = newUniversalGarbage();

        CHashObject *current_token_obj = newCHashObjectEmpty();
        array.append_any(finite_tokens,current_token_obj);
        char *token_id = finite_tokens_list->strings[i];

        DtwResource *current_token_resource = resource.sub_resource(
                finite_tokens_resource,
                token_id
        );

        obj.set_string(current_token_obj,TOKEN_ID,token_id);
        long creation = resource.get_long_from_sub_resource(current_token_resource,CREATION_PATH);
        bool allow_renew = resource.get_bool_from_sub_resource(current_token_resource,ALLOW_RENEW_PATH);
        long expiration = resource.get_long_from_sub_resource(current_token_resource,EXPIRATION_PATH);
        long last_update = resource.get_long_from_sub_resource(current_token_resource,LAST_UPDATE_PATH);


        DtwResource_catch(user){
            UniversalGarbage_free(garbage);
            UniversalGarbage_free(internal_garbage);
            return;
        }

        char *converted_creation = dtw_convert_unix_time_to_string(creation);
        UniversalGarbage_add_simple(internal_garbage,converted_creation);
        obj.set_string(current_token_obj,CREATION_KEY,converted_creation);


        obj.set_bool(current_token_obj,ALLOW_RENEW_KEY,allow_renew);



        char *last_update_in_str = dtw_convert_unix_time_to_string(last_update);
        UniversalGarbage_add_simple(internal_garbage,last_update_in_str);
        obj.set_string(current_token_obj,LAST_UPDATE_KEY,last_update_in_str);


        long expiration_time = last_update + expiration;
        bool is_expired = time(NULL) >=  expiration_time;
        if(is_expired){
            obj.set_string(current_token_obj,EXPIRATION_KEY,EXPIRED_RESPONSE);
        }
        bool its_valid = !is_expired;
        if(its_valid){
            char *expiration_string = dtw_convert_unix_time_to_string(expiration_time);
            obj.set_string(current_token_obj,EXPIRATION_KEY,expiration_string);
            UniversalGarbage_add_simple(internal_garbage,expiration_string);
        }

        UniversalGarbage_free(internal_garbage);

    }

    UniversalGarbage_free(garbage);
}

void describe_infinite_tokens(CHash *user_obj,DtwResource *user){
    DtwResource_catch(user){
        return ;
    }

    UniversalGarbage *garbage = newUniversalGarbage();

    CHashArray *infinite_tokens = newCHashArrayEmpty();
    obj.set_any(user_obj,INFINITE_TOKENS_KEY,infinite_tokens);
    DtwResource * infinite_tokens_resource = resource.sub_resource(user,INFINITE_TOKENS_PATH);

    DtwStringArray * infinite_tokens_list = resource.list_names(infinite_tokens_resource);
    UniversalGarbage_add(garbage, DtwStringArray_free,infinite_tokens_list);


    DtwResource_catch(user){
        UniversalGarbage_free(garbage);
        return ;
    }

    for(int i = 0; i < infinite_tokens_list->size; i ++){
        UniversalGarbage *internal_garbage = newUniversalGarbage();
        CHashObject *current_token_obj = newCHashObjectEmpty();
        array.append_any(infinite_tokens,current_token_obj);

        char *token_id = infinite_tokens_list->strings[i];

        DtwResource *current_token_resource = resource.sub_resource(
                infinite_tokens_resource,
                token_id
        );
        obj.set_string(current_token_obj,TOKEN_ID,token_id);

        long creation = resource.get_long_from_sub_resource(current_token_resource,CREATION_PATH);
        long last_update = resource.get_long_from_sub_resource(current_token_resource,LAST_UPDATE_PATH);

        DtwResource_catch(user){
            UniversalGarbage_free(garbage);
            UniversalGarbage_free(internal_garbage);
            return;
        }

        char *converted_creation = dtw_convert_unix_time_to_string(creation);
        UniversalGarbage_add_simple(internal_garbage,converted_creation);
        obj.set_string(current_token_obj,CREATION_KEY,converted_creation);


        char *last_update_in_str = dtw_convert_unix_time_to_string(last_update);
        UniversalGarbage_add_simple(internal_garbage,last_update_in_str);
        obj.set_string(current_token_obj,LAST_UPDATE_KEY,last_update_in_str);


        UniversalGarbage_free(internal_garbage);
    }

    UniversalGarbage_free(garbage);

}
CHash * describe_user(DtwResource *user, bool include_tokens, bool include_root_props, const char *token, const char *host){
    DtwResource_catch(user){
        return NULL;
    }

    CHash *user_obj = describe_user_without_tokens(user, include_root_props, token, host);

    if(!include_tokens){
        return user_obj;
    }
    describe_finite_tokens(user_obj,user);
    describe_infinite_tokens(user_obj,user);

    return user_obj;
}



CHash * describe_all_users_contains_not_case_sensitive(DtwResource *database, const char *contains, bool include_tokens,bool include_root_props, const char *token, const char *host){
    DtwResource_catch(database){
        return NULL;
    }
    UniversalGarbage *garbage = newUniversalGarbage();
    DtwResource * all_users;
    all_users = resource.sub_resource(database, USERS_PATH);
    all_users = resource.sub_resource(all_users,ELEMENTS_PATH);


    DtwStringArray * all_users_ids = resource.list_names(all_users);
    UniversalGarbage_add(garbage, DtwStringArray_free,all_users_ids);
    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return NULL;
    }
    CHashArray  *all_users_hash = array.newArrayEmpty();
    UniversalGarbage_add_return(garbage, CHash_free,all_users_hash);

    CTextStack *formated_contains= stack.newStack_string(contains);
    UniversalGarbage_add(garbage,stack.free,formated_contains);
    stack.self_lower(formated_contains);


    for(long i = 0; i < all_users_ids->size; i++){
        UniversalGarbage *internal_garbage = newUniversalGarbage();

        char *current = all_users_ids->strings[i];
        DtwResource *current_user  = resource.sub_resource(all_users,"%s",current);

        char *email =  resource.get_string_from_sub_resource(current_user,EMAIL_PATH);
        DtwResource_catch(database){
            UniversalGarbage_free_including_return(garbage);
            UniversalGarbage_free(internal_garbage);
            return NULL;
        }
        CTextStack *email_stack = stack.newStack_string(email);
        UniversalGarbage_add(internal_garbage,stack.free,email_stack);
        stack.self_lower(email_stack);

        bool email_in_search = stack.index_of(email_stack,formated_contains->rendered_text) != -1;
        if(email_in_search){
            CHashObject *description =  describe_user(current_user, include_tokens, include_root_props, token, host);
            DtwResource_catch(database){
                UniversalGarbage_free_including_return(garbage);
                UniversalGarbage_free(internal_garbage);
                return NULL;
            }
            array.append_any(all_users_hash,description);
            UniversalGarbage_free(internal_garbage);
            continue;
        }


        char *username = resource.get_string_from_sub_resource(current_user,USERNAME_PATH);
        DtwResource_catch(database){
            UniversalGarbage_free_including_return(garbage);
            UniversalGarbage_free(internal_garbage);
            return NULL;
        }
        CTextStack *username_stack = stack.newStack_string(username);
        UniversalGarbage_add(internal_garbage,stack.free,username_stack);
        stack.self_lower(username_stack);
        bool username_in_search = stack.index_of(username_stack,formated_contains->rendered_text) != -1;

        if(username_in_search){
            CHashObject *description =  describe_user(current_user,include_tokens,include_root_props,token,host);
            DtwResource_catch(database){
                UniversalGarbage_free_including_return(garbage);
                UniversalGarbage_free(internal_garbage);
                return NULL;
            }
            array.append_any(all_users_hash,description);
        }


        UniversalGarbage_free(internal_garbage);
    }

    UniversalGarbage_free(garbage);
    return all_users_hash;

}

CHash * describe_all_users_with_contains_case_sensitive(DtwResource *database, const char *contains, bool include_tokens,bool include_root_props,const char *token, const char *host){
    DtwResource_catch(database){
        return NULL;
    }

    UniversalGarbage *garbage = newUniversalGarbage();

    DtwResource * all_users;
    all_users = resource.sub_resource(database, USERS_PATH);
    all_users = resource.sub_resource(all_users,ELEMENTS_PATH);

    DtwStringArray * all_users_ids = resource.list_names(all_users);
    UniversalGarbage_add(garbage, DtwStringArray_free,all_users_ids);

    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return NULL;
    }
    CHashArray  *all_users_hash = array.newArrayEmpty();
    UniversalGarbage_add_return(garbage, CHash_free,all_users_hash);


    for(long i = 0; i < all_users_ids->size; i++){
        UniversalGarbage *internal_garbage = newUniversalGarbage();
        char *current = all_users_ids->strings[i];
        DtwResource *current_user  = resource.sub_resource(all_users,"%s",current);

        char *email =  resource.get_string_from_sub_resource(current_user,EMAIL_PATH);
        DtwResource_catch(database){
            UniversalGarbage_free_including_return(garbage);
            UniversalGarbage_free(internal_garbage);
            return NULL;
        }
        CTextStack *email_stack = stack.newStack_string(email);
        UniversalGarbage_add(internal_garbage,stack.free,email_stack);


        bool email_in_search = stack.index_of(email_stack,contains) != -1;
        if(email_in_search){
            CHashObject *description =  describe_user(current_user,include_tokens,include_root_props,token,host);
            array.append_any(all_users_hash,description);
            DtwResource_catch(database){
                UniversalGarbage_free_including_return(garbage);
                UniversalGarbage_free(internal_garbage);
                return NULL;
            }
            UniversalGarbage_free(internal_garbage);
            continue;
        }

        char *username = resource.get_string_from_sub_resource(current_user,USERNAME_PATH);
        DtwResource_catch(database){
            UniversalGarbage_free_including_return(garbage);
            UniversalGarbage_free(internal_garbage);
            return NULL;
        }
        CTextStack *username_stack = stack.newStack_string(username);
        UniversalGarbage_add(internal_garbage,stack.free,username_stack);

        if(stack.index_of(username_stack,contains) != -1){
            CHashObject *description = describe_user(current_user,include_tokens,include_root_props,token,host);
            DtwResource_catch(database){
                UniversalGarbage_free_including_return(garbage);
                UniversalGarbage_free(internal_garbage);
                return NULL;
            }
            array.append_any(all_users_hash,description );
        }

        UniversalGarbage_free(internal_garbage);
    }

    UniversalGarbage_free(garbage);
    return all_users_hash;
}


CHash * describe_all_without_contains_start(DtwResource *database, bool include_tokens,bool include_root_props,const char *token, const char *host){
    DtwResource_catch(database){
        return NULL;
    }

    UniversalGarbage *garbage = newUniversalGarbage();

    DtwResource * all_users;
    all_users = resource.sub_resource(database, USERS_PATH);
    all_users = resource.sub_resource(all_users,ELEMENTS_PATH);

    DtwStringArray * all_users_ids = resource.list_names(all_users);
    UniversalGarbage_add(garbage, DtwStringArray_free,all_users_ids);


    DtwResource_catch(database){
        UniversalGarbage_free(garbage);
        return NULL;
    }

    CHashArray  *all_users_hash = array.newArrayEmpty();
    UniversalGarbage_add_return(garbage, CHash_free,all_users_hash);

    for(long i = 0; i < all_users_ids->size; i++){
        char *current = all_users_ids->strings[i];
        DtwResource *current_user  = resource.sub_resource(all_users,"%s",current);
        CHashObject *description = describe_user(current_user,include_tokens,include_root_props,token,host);
        DtwResource_catch(database){
            UniversalGarbage_free_including_return(garbage);
            return NULL;
        }

        array.append_any(all_users_hash,description);

    }
    UniversalGarbage_free(garbage);
    return all_users_hash;
}


CHash * describe_all_users(DtwResource *database,const char *contains,bool case_sensitive, bool include_tokens,bool include_root_props,const char *token, const char *host){
    DtwResource_catch(database){
        return NULL;
    }


    if(!contains){
        return describe_all_without_contains_start(database, include_tokens,include_root_props,token,host);
    }

    if(case_sensitive){
        return describe_all_users_with_contains_case_sensitive(database, contains, include_tokens,include_root_props,token,host);
    }

    return describe_all_users_contains_not_case_sensitive(database, contains, include_tokens,include_root_props,token,host);

}
