
typedef struct {
     char *name;
    bool required;
    int expected_type;
    bool used_default;
    union {
        int default_int;
        double default_double;
        char*default_string;
        bool defualt_bool;
    };

}RouteEntre;

RouteEntre *private_newRouteEntre(const char *name,bool required,int expected_type);

void private_RouteEntre_free(RouteEntre  *self);


