

void reference_static_file(CTextStack *head,const char *filename){
    CTextStack *current_element = newCTextStack_string(filename);
    if(stack.ends_with(current_element,".css")){
        stack.only$open(head,CTEXT_LINK," rel='stylesheet' href='%sc'",
                        cweb_smart_static_ref(current_element->rendered_text)
        );
    }
    if(stack.ends_with(current_element,"js")){
        CText$Scope(head,CTEXT_SCRIPT," src='%sc'",
                    cweb_smart_static_ref(current_element->rendered_text)
        );
    }
    stack.free(current_element);
}


void reference_static_path(CTextStack *head,const char *path){
    UniversalGarbage *garbage = newUniversalGarbage();
    char *formated_path = dtw.concat_path(cweb_static_folder,path);
    UniversalGarbage_add_simple(garbage,formated_path);
    if(dtw.entity_type(formated_path) == DTW_FILE_TYPE){
        reference_static_file(head,formated_path);
        UniversalGarbage_free(garbage);
        return;
    }

    DtwStringArray *listage = dtw.list_files_recursively(formated_path,DTW_CONCAT_PATH);
    UniversalGarbage_add(garbage,dtw.string_array.free,listage);

    dtw.string_array.sort(listage);

    for(int i=0; i < listage->size;i++){
        reference_static_file(head,listage->strings[i]);
    }

    UniversalGarbage_free(garbage);
}

