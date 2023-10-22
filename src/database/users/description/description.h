

CHash * describe_user(DtwResource *user, bool include_tokens);


CHash * describe_all_users_with_start_path_not_case_sensitive(DtwResource *database, const char *start_path, bool include_tokens);


CHash * describe_all_users_with_start_path_case_sensitive(DtwResource *database, const char *start_path, bool include_tokens);

CHash * describe_all_without_start_path(DtwResource *database,bool include_tokens);


CHash * describe_all_users(DtwResource *database,const char *start_path,bool case_sensitive, bool include_tokens);

