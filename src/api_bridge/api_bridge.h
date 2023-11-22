

void private_parse_chash_to_cweb_dict(CHash *value,CwebDict *target);


typedef struct {
    UniversalGarbage *garbage;
}ApiBridge;


CwebHttpResponse * ApiBridge_call_server(ApiBridge *self,const char *route, CHash *params, CHash *headers);

CwebHttpResponse * ApiBridge_call_server_with_only_headders(ApiBridge*self,const char *route, CHash *headers);

