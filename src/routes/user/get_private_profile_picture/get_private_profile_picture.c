

CwebHttpResponse *get_private_profile_picture(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    Autentication  auth = autenticate_sub_token_or_token(request,entries,database,PROFILE_PICTURE_PATH);
    DtwResource_catch(database){
        return NULL;
    }
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource_catch(database){
        return NULL;
    }
    DtwResource *user = auth.user;

    DtwResource *profile = resource.sub_resource(user,PROFILE_PICTURE_PATH);
    DtwResource *extenson_resource = resource.sub_resource(profile,EXTENSION_PATH);

    if(resource.type(extenson_resource) == DTW_NOT_FOUND){
        return send_error(
                request,
                NOT_FOUND,
                PROFILE_PICTURE_NOT_EXIST,
                PROFILE_PICTURE_NOT_EXIST_MESSAGE
        );
    }
    char *extension = resource.get_string(extenson_resource);
    DtwResource_catch(database){
        return NULL;
    }

    DtwResource  *file = resource.sub_resource(profile,"%s.%s",PROFILE_PICTURE_BLOB_PATH,extension);
    commit_transaction(database);

    return cweb.response.send_file(file->path,CWEB_AUTO_SET_CONTENT,HTTP_OK);
}