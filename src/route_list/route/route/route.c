

Route * create_route(
        const char *route,
        Autentication (*autentication)(CwebHttpRequest *request, CHash *entries,DtwResource *database),
        CwebHttpResponse *(*callback)(CwebHttpRequest *request, CHashObject*entries, DtwResource *database),
        char *description
){
    Route  *self = UniversalGarbage_create_empty_struct(self,Route);
    self->route = strdup(route);
    self->autentication = autentication;
    self->callback = callback;
    return self;
}

void Route_set_description(Route *self, const char *description){
    if(self->description){
        free(self->description);
    }
    self->description = strdup(description);
}

void private_Route_free(Route *self){
    if(self->description){
        free(self->description);
    }
    free(self);
}