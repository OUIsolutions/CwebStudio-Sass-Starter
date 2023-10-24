

CwebHttpResponse  *send_chash_cleaning_memory(CHash *element,int status_code);

CHashObject *join_headders_and_paramns(CwebHttpRequest *request);


void aply_path_protection(CHashObject *element,const  char *key);

bool strings_equal(const char *string_a ,const char *string_b);
