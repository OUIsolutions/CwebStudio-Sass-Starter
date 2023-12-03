

CwebHttpResponse *main_route(CwebHttpRequest *request ){

    CTextStack * s = newCTextStack(CTEXT_LINE_BREAKER,CTEXT_SEPARATOR);
    CText$Scope(s,)

    return cweb.response.send_rendered_CTextStack_cleaning_memory(s);

}
