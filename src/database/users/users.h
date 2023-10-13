

DtwResource *find_user_by_username_or_email(DtwResource  *database,const char *username_or_email,bool lock);


void set_finity_token(DtwResource *user, char *token, bool allow_renew, int expiration);

void set_infinity_token(DtwResource *user, char *token);


bool  password_are_equal(DtwResource *user, char *entrie_passworld);