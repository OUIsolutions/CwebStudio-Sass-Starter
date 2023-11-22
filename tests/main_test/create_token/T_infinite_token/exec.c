
#include "../../../../src/imports.h"
#include "../../../../src/declaration.h"
#undef DATABASE_PATH
#define DATABASE_PATH "tests/target"

#include "../../../../src/definition.h"


int main(){
    start_namespaces();
    #define API_TIME -1;

    create_root_user_if_not_exist();
    ApiBridge *bridge = newApiBridge();
    ApiBridge_create_token(bridge,"root","root",-1);
    ApiBridge_represent(bridge);
    ApiBridge_free(bridge);
}
