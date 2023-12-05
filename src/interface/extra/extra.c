

void reference_static_path(CTextStack *head,const char *path){
    UniversalGarbage *garbage = newUniversalGarbage();
    char *formated_path = dtw.concat_path(cweb_static_folder,path);
    UniversalGarbage_add_simple(garbage,formated_path);
    DtwStringArray *listage = dtw.list_files_recursively(formated_path,DTW_CONCAT_PATH);
    UniversalGarbage_add(garbage,dtw.string_array.free,listage);
    CTextStack *current_element = NULL;
    UniversalGarbage_add(garbage,stack.free,current_element);
    for(int i=0; i < listage->size;i++){
        current_element = stack.newStack_string( listage->strings[i]);
        UniversalGarbage_resset(garbage,current_element);
        if(stack.ends_with(current_element,".css")){
            stack.only$open(head,CTEXT_LINK,"'stylesheet' href='%sc'",
                            cweb_smart_static_ref(current_element->rendered_text)
                            );
        }
        if(stack.ends_with(current_element,"js")){
            CText$Scope(head,CTEXT_SCRIPT," src='%sc'",
                        cweb_smart_static_ref(current_element->rendered_text)
            );
        }
    }
    UniversalGarbage_free(garbage);
}

