
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
    
}