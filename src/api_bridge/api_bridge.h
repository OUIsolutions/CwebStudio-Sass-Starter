


void private_parse_chash_to_cweb_dict(CHash *value,CwebDict *target);


typedef struct {
    char *token;
    char *password;
    const char *host;
    UniversalGarbage *garbage;


    CwebHttpResponse *last_response;
    long last_content_size;
    unsigned char *last_content;
    int last_status_code;
    CHash *last_hash;

}ApiBridge;

ApiBridge *newApiBridge();

void ApiBridge_set_token(ApiBridge *self,const char *token);

void ApiBridge_set_password(ApiBridge *self,const char *password);



int ApiBridge_call_server_full(
        ApiBridge *self,
        const char *route,
        CHash *params,
        CHash *headers,
        const char *content_type,
        unsigned  char *content,
        long content_size
        );


int  ApiBridge_call_server(ApiBridge*self, const char *route, CHash *entries);

char * ApiBridge_create_token(ApiBridge*self,const char *username,const char *password,long  expiration);

//root routes
int ApiBridge_create_user(ApiBridge *self,const char *username,const char *email, const char *password,bool is_root,bool verified);

CHash* ApiBridge_get_user_props(ApiBridge *self,const char *login);


CHash* ApiBridge_list_users(ApiBridge *self,const char *contains,bool include_root_props,bool include_tokens);


//user data
CHash *ApiBridge_get_self_props(ApiBridge *self,bool include_tokens,bool include_root_props);

int ApiBridge_modify_self_props(ApiBridge *self,const char *new_username,const char *new_email,const char *new_password);


int ApiBridge_remove_all_tokens(ApiBridge *self);

int ApiBridge_remove_all_infinite_tokens(ApiBridge *self);

int ApiBridge_remove_all_finite_tokens(ApiBridge *self);


void ApiBridge_represent(ApiBridge *self);

void ApiBridge_free(ApiBridge *self);