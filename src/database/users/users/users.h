

DtwResource *find_user_by_username_or_email(DtwResource  *database,const char *username_or_email);


DtwResource *find_user_by_id(DtwResource  *database,const char *id);

bool is_root(DtwResource *user);

void database_remove_user(DtwResource *database, DtwResource *user);



void database_create_user( DtwResource  *database,const char *username,const char *email,const char *password,bool is_root);


bool  password_are_equal(DtwResource *user, char *entrie_passworld);