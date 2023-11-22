

void private_parse_chash_to_cweb_dict(CHash *value,CwebDict *target);


typedef struct {

    UniversalGarbage *garbage;
}ApiBridge;


CwebHttpResponse * ApiBridge_call_server_full(
        ApiBridge *self,
        const char *route,
        CHash *params,
        CHash *headers,
        const char *content_type,
        unsigned  char *content,
        long content_size
        );

CwebHttpResponse * ApiBridge_call_server(ApiBridge*self, const char *route, CHash *entries);

