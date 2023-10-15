

void set_finity_token(DtwResource *user, char *token, bool allow_renew, int expiration);

void set_infinity_token(DtwResource *user, char *token);


long count_infinite_token(DtwResource *user);

void remove_last_infinite_token(DtwResource *user);


long count_finite_token(DtwResource *user);


void remove_expired_tokens(DtwResource *user);




