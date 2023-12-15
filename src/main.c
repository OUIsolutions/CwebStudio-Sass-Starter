

//never use these flag in production
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
    const char *static_folder = "static";
    if(dtw.entity_type(static_folder) == DTW_NOT_FOUND){
        static_folder = "src/static";
    }

    #ifdef DEBUG
        for(int i = 3000; i < 4000; i++){
            CwebServer server = newCwebSever(i, main_sever);
            server.single_process = true;
            server.static_folder = static_folder;
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
