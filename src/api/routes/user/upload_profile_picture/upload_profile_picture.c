

CwebHttpResponse *upload_profile_picture(CwebHttpRequest *request, CHashObject*entries, DtwResource *database){
    Autentication  auth = autenticate(request,entries,database);
    DtwResource_catch(database){
        return NULL;
    }
    if(auth.error){
        return  auth.response_error;
    }
    DtwResource *user = auth.user;

    obj.set_default(entries, PUBLIC_ENTRE, hash.newBool(false));
    bool is_public = obj.getBool_converting(entries, PUBLIC_ENTRE);
    char *content_type = obj.getString(entries,CONTENT_TYPE_ENTRE);
    char *token = obj.getString(entries,TOKEN_ENTRE);
    char *host = obj.getString(entries,HOST_ENTRIE);


    UniversalGarbage *garbage = newUniversalGarbage();

    CHashObject *valid_extensions = newCHashObject(
            "image/png",hash.newString("png"),
            "image/jpg",hash.newString("jpg"),
            "image/jpeg",hash.newString("jpeg")
    );
    UniversalGarbage_add(garbage, CHash_free,valid_extensions);


    char *extension =NULL;

    CHash_protected(entries){
        extension =  obj.getString(valid_extensions,content_type);
    }

    CHash_catch(valid_extensions){
        validator.raise_error_by_key( entries,
              CONTENT_TYPE_ENTRE,
              NOT_VALID_IMAGE_TYPE,
              NOT_VALID_IMAGE_TYPE_MESSAGE,
              newCHashObject(
                      "image",hash.newString(content_type),
                      "valids", newCHashStringArray("image/png","image/jpg","image/jpeg")
              )
        );
    }

    CHash_catch(entries){
        UniversalGarbage_free(garbage);
        return send_entrie_error(request, entries);
    }

    unsigned char *body =  cweb.request.read_content(request, MAX_PROFILE_PICTURE);

    if(!body){
        UniversalGarbage_free(garbage);
        return send_error(
                request,
                NOT_FOUND,
                PROFILE_PICTURE_NOT_PROVIDED,
                PROFILE_PICTURE_NOT_PROVIDED_MESSAGE
        );
    }



    CHash *response_hash = newCHashObject(
            CODE_KEY, hash.newNumber(INTERNAL_OK),
            MESSAGE_KEY, hash.newString(PICTURE_UPLOADED),
            PROFILE_PICTURE_URL_KEY, hash.newStackString(construct_profile_picture_url(
            user->name,
            is_public,
            token,
            host
            ))
    );
    UniversalGarbage_add_return(garbage, CHash_free,response_hash);

    database_upload_profile_picture(user, extension, is_public, body, request->content_length);
    DtwResource_catch(database){
        UniversalGarbage_free_including_return(garbage);
        return NULL;
    }

    commit_transaction(database);

    UniversalGarbage_free(garbage);

    return send_chash_cleaning_memory(response_hash,HTTP_CREATED);

}