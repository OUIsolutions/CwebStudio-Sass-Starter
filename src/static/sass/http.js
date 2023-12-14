
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
        main_state.turnOnPage(StartPage);
        main_interface.render();
    }
    //fetch and cach any error 
    fetch(route,params)
    .then(response => {
        let invalid_responses = [401,403,500]
        if(invalid_responses.includes(response.code)){
            sessionStorage.removeItem(TOKEN);
            main_state.turnOnPage(StartPage);
            main_interface.render();
        }
        return response;
    })
    .then(response => response.json())
    .then(response => {

        if(response.code === INVALID_TOKEN){
            sessionStorage.removeItem(TOKEN);
            main_state.turnOnPage(StartPage);
            main_interface.render();
            return;
        }
        callback(response);
        main_interface.render();
        
    })
    
}