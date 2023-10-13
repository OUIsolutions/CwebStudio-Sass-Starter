
DtwResource *find_user_by_username_or_email(DtwResource  *database,const char *username_or_email,bool lock){
    DtwResource *users = resource.sub_resource(database, USERS_PATH);

    DtwResource *possible_user = find_element_by_index(
            users,
            EMAIL_PATH,
            username_or_email,
            lock
            );
    if(possible_user){
        return  possible_user;
    }
    possible_user = find_element_by_index(
            users,
            USERNAME_PATH,
            username_or_email,
            lock
    );
    return possible_user;
}
void set_finity_token(DtwResource *user, char *token, bool allow_renew, int expiration){

    //user/token/
    DtwResource  *all_tokens = resource.sub_resource(user, FINITE_TOKEN_PATH);
    //user/token/akspdih3u2ju223j2j3j2
    DtwResource  *token_resource = resource.sub_resource(all_tokens,token);
    //user/token/akspdih3u2ju223j2j3j2/allow_renew
    DtwResource *allow_reenew_resource = resource.sub_resource(token_resource, ALLOW_RENEW_PATH);
    resource.set_bool(allow_reenew_resource,allow_renew);

    DtwResource *expiration_resource = resource.sub_resource(token_resource, EXPIRATION_PATH);
    long now = time(NULL);
    resource.set_long(expiration_resource,now + (expiration * 60));

    DtwResource  *creation_resource =resource.sub_resource(token_resource,CREATION_PATH);
    resource.set_long(creation_resource,now);

}

void set_infinity_token(DtwResource *user, char *token){

    //user/token/
    DtwResource  *all_tokens = resource.sub_resource(user, FINITE_TOKEN_PATH);
    //user/token/akspdih3u2ju223j2j3j2
    DtwResource  *token_resource = resource.sub_resource(all_tokens,token);
    long now = time(NULL);
    DtwResource  *creation_resource =resource.sub_resource(token_resource,CREATION_PATH);
    resource.set_long(creation_resource,now);

}
bool  password_are_equal(DtwResource *user, char *entrie_passworld){
    DtwResource  *password = resource.sub_resource(user,PASSWORD_PATH);
    char *password_sha = resource.get_string(password);
    char *entrie_sha = dtw.generate_sha_from_string(entrie_passworld);
    bool result = strcmp(password_sha,entrie_sha) == 0;
    free(entrie_sha);
    return  result;
}
