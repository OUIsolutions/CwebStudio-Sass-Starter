
DtwResource *find_user_by_username_or_email(const char *username_or_email){
    DtwResource *database = resource.newResource(DATABASE_PATH);
    DtwResource *users = resource.sub_resource(database, USERS_PATH);

    DtwResource *possible_user = find_element_by_index(
            users,
            EMAIL_PATH,
            username_or_email,
            true
            );
    if(possible_user){
        return  possible_user;
    }
    possible_user = find_element_by_index(
            users,
            USERNAME_PATH,
            username_or_email,
            true
    );
    return possible_user;
}
