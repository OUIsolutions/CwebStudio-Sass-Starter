

CwebHttpResponse *main_route(CwebHttpRequest *request ){

    CTextStack * s = newCTextStack(CTEXT_LINE_BREAKER,CTEXT_SEPARATOR);
    stack.text(s,"<!DOCTYPE html>");
    CText$Scope(s,CTEXT_HTML,"lang=%s",LANG){
        CTextScope(s,CTEXT_HEAD){
            stack.only$open(s,CTEXT_META,"charset='UTF-8'");
            stack.only$open(s,CTEXT_META,"name='viewport' content='width=device-width, initial-scale=1.0'");
            CTextScope(s,CTEXT_TITLE){
                stack.segment_text(s,MAIN_TITLE);
            }
            reference_static_path(s,ELEMENT404);
            reference_static_path(s,SASS);
            reference_static_path(s,EXTRA_STATIC);
            CTextScope(s,CTEXT_SCRIPT){
                stack.format(s,
                             "const BACKGROUND_IMAGE = '%sc'",
                             cweb_smart_static_ref("background.jpg")
                );
            }


        }
        CTextScope(s,CTEXT_BODY){

        }
    }

    return cweb.response.send_rendered_CTextStack_cleaning_memory(s,CWEB_OK);

}
