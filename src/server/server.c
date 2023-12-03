


CwebHttpResponse *main_sever(CwebHttpRequest *request ){



    char *route = request->route;
    if(cweb_starts_with(route,API_START)){
        return api_handler(request);
    }

    return interface_handler(request);

}
