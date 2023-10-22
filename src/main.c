#include "dependencies/CHashManipulator.h"
#include "dependencies/CWebStudio.h"
#include "dependencies/doTheWorld.h"

CwebNamespace cweb;
DtwNamespace dtw;
DtwResourceModule resource;
CHashNamespace hash;
CHashObjectModule obj;
CHashArrayModule array;
CHashValidatorModule validator;
CTextStackModule stack;

#include "constants/all.h"
#include "autentication/declaration.h"
#include "database/declaration.h"
#include "observability/observability.h"
#include "extras/extras.h"

#include "errors/errors.h"
#include "routes/declaration.h"

#include "database/definition.h"
#include "observability/observability.c"
#include "autentication/definition.h"
#include "extras/extras.c"
#include "errors/errors.c"
#include "routes/definition.h"

//never use these flag in production
#define DEBUG



CwebHttpResponse *main_sever(CwebHttpRequest *request ){


    #ifdef DEBUG

    if(!strcmp(request->route,END_ROUTE)){
         cweb_end_server = true;
         return cweb.response.send_text(TERMINATED_APLICATION,HTTP_OK);
    }

    #endif


    CHashObject * entries = join_headders_and_paramns(request);
    DtwResource *database = resource.newResource(DATABASE_PATH);

    CwebHttpResponse *response = NULL;

    if(!strcmp(request->route, CREATE_TOKEN_ROUTE)){
        response = create_token(request,entries,database);
    }
    if(!strcmp(request->route,REMOVE_TOKEN_ROUTE)){
        response = remove_token(request,entries,database);
    }

    if(!strcmp(request->route,GET_SELF_PROPS_ROUTE)){
        response = get_self_props(request,entries,database);
    }

    if(!strcmp(request->route, CREATE_USER_ROUTE)){
        response = create_user(request,entries,database);
    }

    if(!strcmp(request->route,LIST_USERS)){
        response = list_users(request,entries,database);
    }

    if(!strcmp(request->route,REMOVE_USER_ROUTE)){
        response = remove_user(request,entries,database);
    }

    if(!strcmp(request->route, GET_USER_PROPS_ROUTE)){
        response = get_user_props(request,entries,database);
    }

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

int main(int argc, char *argv[]){
    cweb = newCwebNamespace();
    dtw = newDtwNamespace();
    resource = dtw.resource;
    hash = newCHashNamespace();
    obj = hash.object;
    array = hash.array;
    validator = hash.validator;
    stack = newCTextStackModule();


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
        CwebServer server = newCwebSever(80, main_sever);
        cweb.server.start(&server);
    #endif

    return 0;
}
