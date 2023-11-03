

CwebHttpResponse *root_download_database_route(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_root(request,entries,database);
    if(auth.error){
        return  auth.response_error;
    }

    DtwResource *user = auth.user;


    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }
    CTextStack *backup = newCTextStack_string_empty();
    stack.format(backup,"zip %s -r %s ",BACKUP_PATH,DATABASE_PATH);
    long error = system(backup->rendered_text);
    stack.free(backup);
    if(error){
        return send_error(
                request,
                INTERNAL_ERROR,
                UNABLE_TO_ZIP_BACKUP,
                UNABLE_TO_ZIP_BACKUP_MESSAGE
        );
    }

    return cweb.response.send_file(BACKUP_PATH,CWEB_AUTO_SET_CONTENT,200);
    
}
