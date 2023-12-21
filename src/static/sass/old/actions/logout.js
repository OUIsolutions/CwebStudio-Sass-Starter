
async function  perform_logout(main_state){

    let token = sessionStorage.getItem(TOKEN_KEY);
    let params = {
        headers:{'token-to-remove': token}
    }

    await make_authenticated_requisition(main_state,REMOVE_TOKEN_ROUTE,params)
    go_to_main_page_removing_token(main_state);

}