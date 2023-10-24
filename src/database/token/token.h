

void set_finite_token(DtwResource *user, char *token, bool allow_renew, int expiration);

DtwResource *get_finite_token(DtwResource *user, char *token);

DtwResource *get_ifinite_token(DtwResource *user, char *token);

void create_infinite_token(DtwResource *user,const char *sha);

long count_infinite_token(DtwResource *user);

void remove_last_updated_infinite_token(DtwResource *user, int totals);

void remove_last_updated_finite_token(DtwResource *user, int totals);

void remove_expired_tokens(DtwResource *user);

int database_remove_token(DtwResource *user,Token *token);

long count_finite_token(DtwResource *user);


void remove_expired_tokens(DtwResource *user);




