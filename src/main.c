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
#include "token/token.h"
#include "database/declaration.h"
#include "extras/extras.h"

#include "errors/errors.h"
#include "routes/declaration.h"

#include "database/definition.h"
#include "token/token.c"
#include "extras/extras.c"
#include "errors/errors.c"
#include "routes/definition.h"

//never use these flag in production

#define DEBUG
CwebHttpResponse *main_sever(CwebHttpRequest *request ){


    #ifdef DEBUG

        if(!strcmp(request->route,END_ROUTE)){
             cweb_end_server = true;
             return cweb.response.send_text(APLICATION_TERMINATED,200);
        }
    #endif


    CHashObject * entries = join_headders_and_paramns(request);
    DtwResource *database = resource.newResource(DATABASE_PATH);
    CwebHttpResponse *response = NULL;

    if(!strcmp(request->route,CREATE_TOKEN)){
        response = create_token(request,entries,database);
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
        }
    #else
        CwebServer server = newCwebSever(80, main_sever);
        cweb.server.start(&server);
    #endif

    return 0;
}
