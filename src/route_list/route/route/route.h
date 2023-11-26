


typedef struct{
    char *route;
    Autentication (*autentication)(CwebHttpRequest *request, CHash *entries,DtwResource *database);
    CwebHttpResponse *(*callback)(CwebHttpRequest *request, CHashObject*entries, DtwResource *database);

    char *description;

}Route;

Route * newRoute(
        const char *route,
        Autentication (*autentication)(CwebHttpRequest *request, CHash *entries,DtwResource *database),
        CwebHttpResponse *(*callback)(CwebHttpRequest *request, CHashObject*entries, DtwResource *database),
);

void Route_set_description(Route *self, const char *description);


void private_Route_free(Route *self);
