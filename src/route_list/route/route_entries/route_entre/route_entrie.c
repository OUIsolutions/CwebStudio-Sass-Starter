

privateRouteEntre *private_newRouteEntre(const char *name, bool required, int expected_type){
    privateRouteEntre  *self = UniversalGarbage_create_empty_struct(self, privateRouteEntre);
    self->name = strdup(name);
    self->required = required;
    self->expected_type = expected_type;
}

void private_RouteEntre_free(privateRouteEntre  *self){
    free(self->name);
    if(self->expected_type == CHASH_STRING && self->used_default){
        free(self->default_string);
    }
}

