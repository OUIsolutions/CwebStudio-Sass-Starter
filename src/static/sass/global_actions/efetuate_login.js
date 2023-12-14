
/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
 function efetuate_login(main_interface, main_state){


    make_autenticated_requisition(main_interface,main_state,GET_SELF_PROPS,null,(response) => {
        let profile = main_state.profile;
        profile.username = response.username;
        profile.email = response.email;
        profile.verified =response.verified;
        
    })



 }