
typedef struct{
    Route  **routes;
    long size;

}RouteList;

RouteList *newRouteList();

void RouteList_add_route(RouteList *self,Route *route);

void RouteList_free(RouteList *self);
