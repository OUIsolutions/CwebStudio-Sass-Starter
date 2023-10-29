

DtwResource *find_element_by_id(DtwResource *folder,const char *id);

DtwResource * find_element_by_index(DtwResource *folder, const char *index_name,const char *value);

void create_index(DtwResource *folder, const char *id, const char *index_name, const char *value);

void destroy_index(DtwResource *folder,const char *index_name,const  char *value);
