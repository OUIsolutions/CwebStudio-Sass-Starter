
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

bool  password_are_equal(DtwResource *user, char *entrie_passworld){
    DtwResource  *password = resource.sub_resource(user,PASSWORD_PATH);
    char *password_str = resource.get_string(password);
    char *password_sha = dtw.generate_sha_from_string(password_str);

    char *entrie_sha = dtw.generate_sha_from_string(entrie_passworld);
    bool result = strcmp(password_sha,entrie_sha) == 0;
    free(password_sha);
    free(entrie_sha);
    return  result;
}
