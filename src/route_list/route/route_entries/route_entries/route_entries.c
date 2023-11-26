

privateRouteEntries * private_newRouteEntres(){
    privateRouteEntries *self = UniversalGarbage_create_empty_struct(self,privateRouteEntries);
    self->entries = (privateRouteEntre**) malloc(0);
    return self;
}

void privateRouteEntres_add_entre(privateRouteEntries *self, privateRouteEntre* entre){
    self->entries = (privateRouteEntre**)realloc(
            self->entries,
            sizeof (privateRouteEntre**) * (self->size+1)
     );
    self->entries[self->size] =entre;
    self->size+=1;
}

void privateRouteEntries_free(privateRouteEntries *self){
    for(int i =0; i < self->size;i++){
        free(self->entries[i]);
    }
    free(self->entries);
    free(self);
}

