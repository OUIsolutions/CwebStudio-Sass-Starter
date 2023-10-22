

DtwResource *find_user_by_username_or_email(DtwResource  *database,const char *username_or_email);


DtwResource *find_user_by_id(DtwResource  *database,const char *id);

bool is_root(DtwResource *user);

CHash * describe_user(DtwResource *user, bool include_tokens);


CHash * describe_all_users(DtwResource *database,const char *start_path, bool include_tokens);


void database_remove_user(DtwResource *database, DtwResource *user);



void database_create_user( DtwResource  *database,const char *username,const char *email,const char *password,bool is_root);


bool  password_are_equal(DtwResource *user, char *entrie_passworld);