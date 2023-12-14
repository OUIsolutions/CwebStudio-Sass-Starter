
function go_to_main_page(main_interface,main_state){
    main_state.turnOnPage(MainPage);
    main_interface.render();
}
function go_to_main_page_removing_token(main_interface,main_state){
    sessionStorage.removeItem(TOKEN);
    go_to_main_page(main_interface,main_state);
}

/**
 * Creates a token
 *
 * @param {Element404} main_interface
 * @param {MainState} main_state
 * @param {string} route
 *@param {object} params
 * @param {function} callback
 */
function  make_autenticated_requisition(
    main_interface,
    main_state,
    route,
    params,
    callback){
    let token =  sessionStorage.getItem(TOKEN);
    if(!token){
        go_to_main_page(main_interface,main_state);
        return;
    }
    //fetch and cach any error 
    if(!params){
        params = {};
    }
    params.headers = {
        token:token
    }
    
    fetch(route,params)
    .then(response => {
        let invalid_responses = [401,403,500]
        if(invalid_responses.includes(response.code)){
            go_to_main_page_removing_token(main_interface,main_state);
            return;
        }
        return response;
    })
    .then(response => response.json())
    .then(response => {

        if(response.code === INVALID_TOKEN){
            go_to_main_page_removing_token(main_interface,main_state);
            return;
        }

        callback(response);
        main_interface.render();
        
    })
    
}