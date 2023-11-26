typedef struct {
    privateRouteEntre **entries;
    int size;
}privateRouteEntries;

privateRouteEntries * private_newRouteEntres();

void privateRouteEntres_add_entre(privateRouteEntries *self, privateRouteEntre* entre);

void privateRouteEntries_free(privateRouteEntries *self);
