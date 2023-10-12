

DtwResource *find_user_by_username_or_email(DtwResource  *database,const char *username_or_email,bool lock);

char * get_user_password(DtwResource *user);