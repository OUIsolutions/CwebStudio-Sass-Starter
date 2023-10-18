

DtwResource *find_user_by_username_or_email(DtwResource  *database,const char *username_or_email);


DtwResource *find_user_by_id(DtwResource  *database,const char *id);

bool is_root(DtwResource *user);

CHash * describe_user(DtwResource *user, bool include_tokens);

bool  password_are_equal(DtwResource *user, char *entrie_passworld);