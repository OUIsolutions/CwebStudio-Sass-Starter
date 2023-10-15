

void set_finite_token(DtwResource *user, char *token, bool allow_renew, int expiration);

void set_infinite_token(DtwResource *user, char *token);


long count_infinite_token(DtwResource *user);

void remove_last_updated_infinite_token(DtwResource *user, int totals);

void remove_last_updated_finite_token(DtwResource *user, int totals);

void remove_expired_tokens(DtwResource *user);


long count_finite_token(DtwResource *user);


void remove_expired_tokens(DtwResource *user);




