


#include "../../../../src/imports.h"
#include "../../../../src/declaration.h"

#undef DATABASE_PATH
#define DATABASE_PATH "tests/target/content"
#undef TRANSACTION_PATH
#define TRANSACTION_PATH  "tests/target/transactions"

#include "../../../../src/definition.h"


int main(){
    start_namespaces();
    dtw_now = 0;

    create_root_user_if_not_exist();
    ApiBridge *bridge = newApiBridge();
    ApiBridge_remove_all_tokens(bridge);
    ApiBridge_represent(bridge);

    ApiBridge_free(bridge);
}
