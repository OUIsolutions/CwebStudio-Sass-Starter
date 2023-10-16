

typedef struct Autentication{
    bool error;
    union {
        DtwResource *user;
        CwebHttpResponse *response_error;
    };
}Autentication;

Autentication autenticate(CwebHttpRequest *request, CHash *entries,DtwResource *database);
