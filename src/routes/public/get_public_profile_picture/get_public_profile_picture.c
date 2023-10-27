

CwebHttpResponse *get_public_profile_picture(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    char *user_id = obj.getString(entries,USER_ID_ENTRE);

    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    DtwResource *user = find_user_by_id(database,user_id);
    if(!user){
        return send_error(
                request,
                NOT_FOUND,
                USER_NOT_EXIST,
                USER_NOT_EXIST_MENSSAGE,
                user_id
        );
    }

    DtwResource *profile_picture = resource.sub_resource(user,PROFILE_PICTURE_PATH);

    char *extension = resource.get_string_from_sub_resource(profile_picture,EXTENSION_PATH);
    if(!extension){
        return send_error(
                request,
                NOT_FOUND,
                PROFILE_PICTURE_NOT_EXIST,
                PROFILE_PICTURE_NOT_EXIST_MESSAGE
        );

    }

    bool public = resource.get_bool_from_sub_resource(profile_picture,PUBLIC_PATH);
    if(!public){
        return send_error(
                request,
                FOREBIDEN,
                PROFILE_PICTURE_NOT_EXIST,
                PROFILE_PICTURE_ITS_NOT_PUBLIC_MESSAGE
        );
    }

    DtwResource  *file = resource.sub_resource(profile_picture,"%s.%s",PROFILE_PICTURE_BLOB_PATH,extension);
    return cweb.response.send_file(file->path,CWEB_AUTO_SET_CONTENT,HTTP_OK);

}