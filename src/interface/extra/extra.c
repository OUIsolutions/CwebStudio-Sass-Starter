
void reference_static_images(CTextStack *head){

    UniversalGarbage *garbage = newUniversalGarbage();

    DtwTree *listage = newDtwTree();
    UniversalGarbage_add(garbage, DtwTree_free,listage);
    dtw.tree.add_tree_from_hardware(listage,cweb_static_folder,&(DtwTreeProps){
            .content = DTW_HIDE,
            .hadware_data=DTW_HIDE,
            .path_atributes=DTW_INCLUDE
    });

    CTextScope(head,CTEXT_SCRIPT){
        stack.text(head,"let = assets = {};\n");
        for(int i=0; i < listage->size;i++){
            DtwTreePart *part = listage->tree_parts[i];
            DtwPath *path = part->path;
            char *name = dtw.path.get_name(path);
            char *extension = dtw.path.get_extension(path);
            bool implement = false;
            if(strings_equal(extension,"jpg")){
                implement = true;
            }

            if(strings_equal(extension,"png")){
                implement = true;
            }
            if(!implement){
                continue;
            }
            stack.format(head,"assets['%s'] = '%sc';\n",
                         name,
                         cweb_smart_static_ref(dtw.path.get_path(path))
           );
        }
    }
    UniversalGarbage_free(garbage);

}
void reference_static_path(CTextStack *head,const char *path){
    UniversalGarbage *garbage = newUniversalGarbage();
    char *formated_path = dtw.concat_path(cweb_static_folder,path);
    UniversalGarbage_add_simple(garbage,formated_path);
    DtwStringArray *listage = dtw.list_files_recursively(formated_path,DTW_CONCAT_PATH);
    UniversalGarbage_add(garbage,dtw.string_array.free,listage);

    dtw.string_array.sort(listage);
    CTextStack *current_element = NULL;
    UniversalGarbage_add(garbage,stack.free,current_element);
    for(int i=0; i < listage->size;i++){
        current_element = stack.newStack_string( listage->strings[i]);
        UniversalGarbage_resset(garbage,current_element);
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
    }
    UniversalGarbage_free(garbage);
}

