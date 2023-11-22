

void private_parse_chash_to_cweb_dict(CHash *value,CwebDict *target);

CwebHttpResponse * call_server(const char *route, CHash *params, CHash *headers);

CwebHttpResponse * call_server_with_only_headders(const char *route,CHash *headers);

