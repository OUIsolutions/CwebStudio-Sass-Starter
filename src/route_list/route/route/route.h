


typedef struct{
    char *route;
    Autentication (*autentication)(CwebHttpRequest *request, CHash *entries,DtwResource *database);
    CwebHttpResponse *(*callback)(CwebHttpRequest *request, CHashObject*entries, DtwResource *database);

    char *description;

}Route;

Route * create_route(
        const char *route,
        Autentication (*autentication)(CwebHttpRequest *request, CHash *entries,DtwResource *database),
        CwebHttpResponse *(*callback)(CwebHttpRequest *request, CHashObject*entries, DtwResource *database),
        char *description
);

void Route_set_description(Route *self, const char *description);


CwebHttpResponse *Route_create_response(Route *self,CwebHttpRequest *request,DtwResource *database);
