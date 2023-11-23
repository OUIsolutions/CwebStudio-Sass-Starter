

//never use these flag in production
#define DEBUG

#include "imports.h"
#include "declaration.h"
#include "definition.h"


int main(){



    start_namespaces();
    create_root_user_if_not_exist();
    //define these flag to reconstruct database, if integrity brokes
    #ifdef RECONSTRUCT_DATABASE_FROM_START
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
