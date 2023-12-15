


/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
function  add_user(main_interface, main_state) {
    let page_props = main_state.page_root_profile;

    page_props.email_error = undefined;
    page_props.password_error = undefined;
    page_props.username_error= undefined;

    if(!page_props.password || !page_props.new_password){
        page_props.password_error = 'password must be provided';
        main_interface.render();
        return;
    }

    if(!page_props.email){
        page_props.email_error = 'email must be provided';
        main_interface.render();
        return;
    }


    if(!page_props.username){
        page_props.username = 'username must be provided';
        main_interface.render();
        return;
    }

    if(page_props.password.length <=10){
        page_props.password_error = 'password is higher than 10';
        main_interface.render();
        return;
    }

    if(page_props.email.length <=10){
        page_props.email_error = 'email must be higher than 10'
    }
    let headers = {
        username:page_props.username,
        email:page_props.email,
        password:page_props.password
    }

    /*
    make_autenticated_requisition(main_interface,main_state,MODIFY_SELF_PROPS_ROUTE, {headers:headers},(response)=>{

        if(response.code === 0){
            alert(response.message);
            main_state.profile.username = page_props.new_username;
            main_state.profile.email = page_props.new_email;
            main_interface.render();
            return
        }

       alert(response.mensage);
    })

*/
}