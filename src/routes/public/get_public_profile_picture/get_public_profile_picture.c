Route *describe_get_public_profile_picture(){
    Route  * route = newRoute(
            GET_PUBLIC_PROFILE_PICTURE_ROUTE,
            NULL,
            get_public_profile_picture
     );
    return route;


}

CwebHttpResponse *get_public_profile_picture(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){

    char *user_id = obj.getString(entries,USER_ID_ENTRE);

    CHash_catch(entries){
        return send_entrie_error(request, entries);
    }

    DtwResource *user = find_user_by_id(database,user_id);
    DtwResource_catch(database){
        return NULL;
    }

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
    DtwResource *extenson_resource = resource.sub_resource(profile_picture,EXTENSION_PATH);

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


    bool is_public = resource.get_bool_from_sub_resource(profile_picture,PUBLIC_PATH);
    DtwResource_catch(database){
        return NULL;
    }

    if(!is_public){
        return send_error(
                request,
                FOREBIDEN,
                PROFILE_PICTURE_ITS_NOT_PUBLIC,
                PROFILE_PICTURE_ITS_NOT_PUBLIC_MESSAGE
        );
    }

    DtwResource  *file = resource.sub_resource(profile_picture,"%s.%s",PROFILE_PICTURE_BLOB_PATH,extension);
    return cweb.response.send_file(file->path,CWEB_AUTO_SET_CONTENT,HTTP_OK);

}