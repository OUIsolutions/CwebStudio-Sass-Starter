
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

char * get_user_password(DtwResource *user){
    DtwResource  *password = resource.sub_resource(user,PASSWORD_PATH);
    return resource.get_string(password);
}
