


void private_parse_chash_to_cweb_dict(CHash *value,CwebDict *target);


typedef struct {
    char *token;
    UniversalGarbage *garbage;


    CwebHttpResponse *last_response;
    long last_content_size;
    unsigned char *last_content;
    int last_status_code;
    CHash *last_hash;

}ApiBridge;

ApiBridge *newApiBridge();

void ApiBridge_set_token(ApiBridge *self,const char *token);



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



void ApiBridge_free(ApiBridge *self);