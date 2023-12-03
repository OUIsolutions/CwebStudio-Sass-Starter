

CHash * describe_user_without_tokens(DtwResource *user, bool include_root_props, const char *token, const char *host);

void describe_finite_tokens(CHash *user_obj,DtwResource *user);

void describe_infinite_tokens(CHash *user_obj,DtwResource *user);

CHash * describe_user(DtwResource *user, bool include_tokens, bool include_root_props, const char *token, const char *host);

CHash * describe_all_users_contains_not_case_sensitive(DtwResource *database, const char *contains, bool include_tokens,bool include_root_props, const char *token, const char *host);


CHash * describe_all_users_with_contains_case_sensitive(DtwResource *database, const char *contains, bool include_tokens,bool include_root_props, const char *token, const char *host);


CHash * describe_all_without_contains_start(DtwResource *database, bool include_tokens, bool include_root_props, const char *token, const char *host);


CHash * describe_all_users(DtwResource *database,const char *contains,bool case_sensitive, bool include_tokens,bool include_root_props,const char *token, const char *host);
