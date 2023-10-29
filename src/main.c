#include "imports.h"
#include "namespaces.h"
#include "declaration.h"
#include "definition.h"



//never use these flag in production
#define DEBUG

CwebHttpResponse *main_sever(CwebHttpRequest *request ){



    #ifdef DEBUG
    create_root_user_if_not_exist();
    //WARNING: THESE WILL KILL THE ENTIRE APPLICATION IF YOU ACCESS /end
    if(!strcmp(request->route,END_ROUTE)){
         cweb_end_server = true;
         return cweb.response.send_text(TERMINATED_APLICATION,HTTP_OK);
    }

    #endif

    CHashObject * entries = join_headders_and_paramns(request);
    DtwResource *database = resource.newResource(DATABASE_PATH);
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

    if(strings_equal(request->route,LIST_USERS)){
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
    
//route_insertion

    hash.free(entries);
    resource.free(database);

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

int main(){
    cweb = newCwebNamespace();
    dtw = newDtwNamespace();
    resource = dtw.resource;
    hash = newCHashNamespace();
    obj = hash.object;
    array = hash.array;
    validator = hash.validator;
    stack = newCTextStackModule();
    create_root_user_if_not_exist();

    //define these flag to reconstruct database, if integrity brokes
#define RELOAD_ALL_TRANSACTIONS

#ifdef RELOAD_ALL_TRANSACTIONS
        reload_all_transactions();
    #endif


     #ifdef DEBUG
        for(int i = 3000; i < 4000; i++){
            CwebServer server = newCwebSever(i, main_sever);
            server.single_process = true;
            cweb.server.start(&server);
            if(cweb_end_server){
                break;
            }
        }
    #else
        CwebServer server = newCwebSever(DEFAULT_PRODUCTION_PORT, main_sever);
        cweb.server.start(&server);
    #endif

    return 0;
}
