#include "dependencies/CHashManipulator.h"
#include "dependencies/CWebStudio.h"
#include "dependencies/doTheWorld.h"

CwebNamespace cweb;
DtwNamespace dtw;
CHashNamespace hash;
CHashObjectModule obj;
CHashArrayModule array;
CHashValidatorModule validator;

#include "constants/all.h"
#include "database/declaration.h"
#include "extras/extras.h"
#include "errors/errors.h"
#include "api_routes/declaration.h"

#include "database/definition.h"
#include "extras/extras.c"
#include "errors/errors.c"
#include "api_routes/definition.h"

//never use these flag in production
#define DEBUG
CwebHttpResponse *main_sever(CwebHttpRequest *request ){

    #ifdef DEBUG
        if(!strcmp(request->route,END_ROUTE)){
            cweb_end_server = true;
        }
    #endif
    if(dtw_starts_with(request->route,CREATE_TOKEN)){
        return create_token(request);
    }

    return send_error(
            request,
            NOT_FOUND,
            ROUTE_NOT_FOUND,
            ROUTE_NOT_FOUND_MENSSAGE
            );

}

int main(int argc, char *argv[]){
    cweb = newCwebNamespace();
    dtw = newDtwNamespace();
    hash = newCHashNamespace();
    obj = hash.object;
    array = hash.array;
    validator = hash.validator;

    struct CwebServer server = newCwebSever(5000, main_sever);
    #ifdef DEBUG
        server.single_process = true;
    #endif

    cweb.server.start(&server);
    return 0;
}
