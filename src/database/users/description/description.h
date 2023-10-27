

CHash * describe_user(DtwResource *user, bool include_tokens, bool include_verification_link, const char *token, const char *host);

CHash * describe_all_users_contains_not_case_sensitive(DtwResource *database, const char *contains, bool include_tokens, const char *token, const char *host);


CHash * describe_all_users_with_contains_case_sensitive(DtwResource *database, const char *contains, bool include_tokens, const char *token, const char *host);


CHash * describe_all_without_contains_start(DtwResource *database, bool include_tokens, const char *token, const char *host);


CHash * describe_all_users(DtwResource *database, const char *contains, bool case_sensitive, bool include_tokens, const char *token, const char *host);

