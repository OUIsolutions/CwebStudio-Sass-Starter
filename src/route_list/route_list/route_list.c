


RouteList *newRouteList(){
    RouteList *self = UniversalGarbage_create_empty_struct(self,RouteList);
    self->routes = (Route**) malloc(0);
}

void RouteList_add_route(RouteList *self,Route *route){
    self->routes = (Route**) realloc(
            self->routes,
            sizeof(Route**) * (self->size+1)
            );
    self->routes[self->size] = route;
}

void RouteList_free(RouteList *self){
    for(int i = 0; i < self->size; i++){
        private_Route_free(self->routes[i]);
    }
    free(self->routes);
    free(self);
}

