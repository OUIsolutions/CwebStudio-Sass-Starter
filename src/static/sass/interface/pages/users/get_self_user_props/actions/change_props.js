


/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
function  change_user_self_props(main_interface, main_state) {
    let page_props = main_state.page_user_profile;
    let headers = {}
    let modified = false;
    let requires_password = false;
    page_props.old_password_error =undefined;
    page_props.email_error = undefined;
    page_props.password_error = undefined;
    page_props.username_error= undefined;
    if(page_props.password || page_props.new_password){
        if(page_props.password !== page_props.new_password){
            page_props.password_error = "Passwords are not equal"
            main_interface.render();
            return;
        }

        if(page_props.new_password.length <=10){
            page_props.password_error = 'password is lower than 10';
            main_interface.render();
            return;
        }
        headers['new_password'] = page_props.new_password;
        modified = true;
        requires_password = true;
    }


    if(page_props.email !== page_props.new_email){
        if(page_props.new_email.length <= 10){
            page_props.email_error = 'email is lower than 10';
            main_interface.render();
            return;
        }

        headers['new_email'] = page_props.new_email;
        modified = true;
        requires_password = true;
    }

    if(page_props.username !== page_props.new_username){
        headers['new_username'] = page_props.new_username;
        modified = true;

    }

    if(requires_password){
        if(!page_props.old_password){
            page_props.old_password_error = 'old password its required';
            main_interface.render();
            return;
        }
        headers['password'] = page_props.old_password;
    }


    if(!modified){
        return;
    }



    make_authenticated_requisition(main_interface,main_state,MODIFY_SELF_PROPS_ROUTE, {headers:headers},(response)=>{

        if(response.code === 0){
            alert(response.message);
            main_state.profile.username = page_props.new_username;
            main_state.profile.email = page_props.new_email;
            main_interface.render();
            return
        }

       alert(response.message);
    })


}