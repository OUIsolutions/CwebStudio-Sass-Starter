

CwebHttpResponse *get_private_profile_picture(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_sub_token_or_token(request,entries,database,PROFILE_PICTURE_PATH);
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource *user = auth.user;

    DtwResource *profile = resource.sub_resource(user,PROFILE_PICTURE_PATH);
    char *extension = resource.get_string_from_sub_resource(profile,EXTENSION_PATH);
    if(!extension){

            return send_error(
                    request,
                    NOT_FOUND,
                    PROFILE_PICTURE_NOT_EXIST,
                    PROFILE_PICTURE_NOT_EXIST_MESSAGE
            );

    }

    DtwResource  *file = resource.sub_resource(profile,"%s.%s",PROFILE_PICTURE_BLOB_PATH,extension);
    commit_transaction(database);

    return cweb.response.send_file(file->path,CWEB_AUTO_SET_CONTENT,HTTP_OK);
}