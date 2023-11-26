

Route * create_route(const char *route){
    Route  *self = UniversalGarbage_create_empty_struct(self,Route);
    self->route = strdup(route);
    return self;
}