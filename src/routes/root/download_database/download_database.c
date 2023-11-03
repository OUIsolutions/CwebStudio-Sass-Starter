

CwebHttpResponse *root_download_database_route(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_root(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    DtwResource *user = auth.user;


    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }
    UniversalGarbage *garbage = newUniversalGarbage();
    CTextStack *backup = stack.newStack_string_empty();
    UniversalGarbage_add(garbage,stack.free,backup);
    stack.format(backup,"./zip %s -r %s ",BACKUP_PATH,DATABASE_PATH);
    long error = system(backup->rendered_text);
    if(error){
        UniversalGarbage_free(garbage);
        return send_error(
                request,
                INTERNAL_ERROR,
                UNABLE_TO_ZIP_BACKUP,
                UNABLE_TO_ZIP_BACKUP_MESSAGE
        );
    }
    CTextStack * backup_zip =stack.newStack_string_empty();
    UniversalGarbage_add(garbage,stack.free,backup_zip);

    stack.format(backup_zip,"%s.zip",BACKUP_PATH);

    CwebHttpResponse *response = cweb.response.send_file(backup_zip->rendered_text,CWEB_AUTO_SET_CONTENT,200);
    UniversalGarbage_free(garbage);
    return response;

}
