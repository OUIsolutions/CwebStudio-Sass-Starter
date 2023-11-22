#include "../../../../src/imports.h"
#include "../../../../src/declaration.h"
#include "../../../../src/definition.h"
#undef DATABASE_PATH
#define DATABASE_PATH "tests/target"

int main(){
    start_namespaces();
    create_root_user_if_not_exist();
    ApiBridge *bridge = newApiBridge();
    ApiBridge_create_token(bridge,"root","root",-1);
    ApiBridge_represent(bridge);
    ApiBridge_free(bridge);
}
