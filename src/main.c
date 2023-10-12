#include "dependencies/CHashManipulator.h"
#include "dependencies/CWebStudio.h"
#include "dependencies/doTheWorld.h"

CwebNamespace cweb;

#include "constants/all.h"
#include "database/declaration.h"
#include "database/definition.h"

CwebHttpResponse *main_sever(CwebHttpRequest *request ){


    return cweb.response.send_text("Hello World", 200);

}
int main(){

}
/*
int main(int argc, char *argv[]){
    cweb = newCwebNamespace();
    struct CwebServer server = newCwebSever(5000, main_sever);
    cweb.server.start(&server);
    return 0;
}
 */