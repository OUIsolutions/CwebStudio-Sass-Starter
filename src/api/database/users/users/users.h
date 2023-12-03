





DtwResource *find_user_by_username_or_email(DtwResource  *database,const char *username_or_email);


DtwResource *find_user_by_id(DtwResource  *database,const char *id);

bool is_root(DtwResource *user);

void database_remove_user(DtwResource *database, DtwResource *user);


void database_create_user( DtwResource  *database,const char *username,const char *email,const char *password,bool is_root,bool verified);


void database_modify_user( DtwResource  *database,DtwResource *user,const char *new_username,const char *new_email,const char *new_password,bool set_is_root, bool is_root);

void database_upload_profile_picture(DtwResource *user, const char *extension, bool is_public, unsigned char *value, long size);

bool  password_are_equal(DtwResource *user, char *entrie_passworld);

bool  password_are_equal_if_password_provided(DtwResource *user, char *entrie_passworld);

#define NEW_VALUE_NOT_PROVIDED -1
#define USER_NOT_EXIST_INTERNAL 0
#define USER_HAVE_THE_SAME_NAME_INTERNAL 1
#define USER_ALREADY_EXIST_INTERNAl 2

short get_user_index_status_if_new_value_provided(DtwResource *database, DtwResource *user, const char *value_path, char *new_value);