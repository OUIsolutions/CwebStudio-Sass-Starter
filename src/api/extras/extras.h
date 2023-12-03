

CwebHttpResponse  *send_chash_cleaning_memory(CHash *element,int status_code);

CHashObject *join_headders_and_paramns(CwebHttpRequest *request);


bool strings_equal(const char *string_a ,const char *string_b);

CTextStack  *construct_profile_picture_url(const char *user_id, bool is_public, const char *token, const char *host);


CTextStack  * construct_verification_url(const char *user_id,const char *verification_key,const char *host);

