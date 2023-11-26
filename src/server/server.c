
RouteList * create_route_list(){
    RouteList  *list = newRouteList();
    RouteList_add_route(list,describe_create_token());
    RouteList_add_route(list,describe_get_public_profile_picture());

    return list;
}


CwebHttpResponse *main_sever(CwebHttpRequest *request ){


#ifdef DEBUG
    create_root_user_if_not_exist();
    //WARNING: THESE WILL KILL THE ENTIRE APPLICATION IF YOU ACCESS /end
    if(!strcmp(request->route,END_ROUTE)){
         cweb_end_server = true;
         return cweb.response.send_text(TERMINATED_APLICATION,HTTP_OK);
    }

#endif
    UniversalGarbage  *garbage = newUniversalGarbage();

    CHashObject * entries = join_headders_and_paramns(request);
    UniversalGarbage_add(garbage, hash.free,entries);

    DtwResource *database = resource.newResource(DATABASE_PATH);
    UniversalGarbage_add(garbage, resource.free,database);

    database->use_locker_on_unique_values = false;

    CwebHttpResponse *response = NULL;



    if(strings_equal(request->route, CREATE_TOKEN_ROUTE)){
        response = create_token(request,entries,database);
    }

    if(strings_equal(request->route,REMOVE_TOKEN_ROUTE)){
        response = remove_token(request,entries,database);
    }

    if(strings_equal(request->route, REMOVE_ALL_FINITE_TOKENS_ROUTE)){
        response = remove_all_finite_tokens(request,entries,database);
    }

    if(strings_equal(request->route,REMOVE_ALL_INFINITE_TOKENS_ROUTE)){
        response = remove_all_infinite_tokens(request,entries,database);
    }

    if(strings_equal(request->route,REMOVE_ALL_TOKENS_ROUTE)){
        response = remove_all_tokens(request,entries,database);
    }

    if(strings_equal(request->route,REMOVE_TOKEN_BY_ID)){
        response = remove_token_by_id(request,entries,database);
    }


    if(strings_equal(request->route,GET_SELF_PROPS_ROUTE)){
        response = get_self_props(request,entries,database);
    }

    if(strings_equal(request->route, CREATE_USER_ROUTE)){
        response = create_user(request,entries,database);
    }

    if(strings_equal(request->route, LIST_USERS_ROUTE)){
        response = list_users(request,entries,database);
    }

    if(strings_equal(request->route,REMOVE_USER_ROUTE)){
        response = remove_user(request,entries,database);
    }

    if(strings_equal(request->route, MODIFY_SELF_PROPS_ROUTE)){
        response = modify_self_props(request,entries,database);
    }

    if(strings_equal(request->route,SELF_REMOVE_ROUTE)){
        response = self_remove(request,entries,database);
    }

    if(strings_equal(request->route,MODIFY_USER_PROPS_ROUTE)){
        response = modify_user_props(request,entries,database);
    }

    if(strings_equal(request->route, GET_USER_PROPS_ROUTE)){
        response = get_user_props(request,entries,database);
    }

    if(strings_equal(request->route, UPLOAD_PROFILE_PICTURE_ROUTE)){
        response = upload_profile_picture(request,entries,database);
    }

    if(strings_equal(request->route,GET_PRIVATE_PROFILE_PICTURE_ROUTE)){
        response = get_private_profile_picture(request,entries,database);
    }

    if(strings_equal(request->route,GET_PUBLIC_PROFILE_PICTURE_ROUTE)){
        response = get_public_profile_picture(request,entries,database);
    }


    if(strings_equal(request->route,SEND_VERIFICATION_EMAIL_ROUTE)){
        response = send_email_verification_route(request,entries,database);
    }



    if(strings_equal(request->route,VERIFY_EMAIL_ROUTE)){
        response = public_verify_email_route(request,entries,database);
    }


    if(strings_equal(request->route,DESCRIBE_ROUTE)){
        response = public_describe_route(request,entries,database);
    }

    if(strings_equal(request->route, SEND_RECOVERY_PASSWORD_ROUTE)){
        response = send_recovery_password_route(request, entries, database);
    }

    if(strings_equal(request->route,DOWNLOAD_DATABASE_ROUTE)){
        response = root_download_database_route(request,entries,database);
    }
    //route_insertion


    DtwResource_catch(database){


#ifdef DEBUG
        int error_code = DtwResource_get_error_code(database);
            char *error_message = DtwResource_get_error_message(database);
           response = send_error(
                    request,
                    CWEB_INTERNAL_SERVER_ERROR,
                    DATABASE_INTEGRITY_BROKEN,
                    DATABASE_INTEGRITY_BROKEN_MESSAGE,
                    error_code,
                    error_message
            );
#else

        response = send_error(
                request,
                CWEB_INTERNAL_SERVER_ERROR,
                INTERNAL_ERROR,
                INTERNAL_ERROR_MESSAGE
        );

#endif
    }

    UniversalGarbage_free(garbage);


    if(response){
        return  response;
    }

    return send_error(
            request,
            NOT_FOUND,
            ROUTE_NOT_FOUND,
            ROUTE_NOT_FOUND_MENSSAGE,
            request->route
    );

}
