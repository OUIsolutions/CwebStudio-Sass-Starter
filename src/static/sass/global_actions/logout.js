/**
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function  efetuate_logout(main_interface, main_state){

    function  go_to_main(response){
        go_to_main_page_removing_token(main_interface,main_state);
    }

    let token = sessionStorage.getItem(TOKEN);
    let paramns = {
        headers:{'token-to-remove': token}
    }

    make_autenticated_requisition(main_interface,main_state,REMOVE_TOKEN,paramns, go_to_main)

}