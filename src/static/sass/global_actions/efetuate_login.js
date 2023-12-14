
/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
 function efetuate_login(main_interface, main_state,token){


    
    make_autenticated_requisition(main_interface,main_state,GET_SELF_PROPS,null,(response) => {
        main_state.setSelfProps(response);
        sessionStorage.setItem(TOKEN,token);
    })


 }