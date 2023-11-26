
void remove_max_finite_tokens(DtwResource *user);

void remove_max_ifinite_tokens(DtwResource *user);

Route * describe_create_token();

CwebHttpResponse *create_token(CwebHttpRequest *request, CHashObject*entries, DtwResource *database);
