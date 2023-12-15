


/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
function  change_self_props(main_interface, main_state) {
    let page_props = main_state.page_root_profile;
    let headers = {}
    let modified = false;
    if(page_props.password || page_props.new_password){
        if(page_props.password !== page_props.new_password){
            page_props.password_error = "Passwords are not equal"
            main_interface.render();
            return;
        }
        if(!page_props.old_password){
            page_props.old_password_error = 'old password its required';
            main_interface.render();
            return;
        }
        headers['password'] = page_props.old_password;
        headers['new_password'] = page_props.new_password;
        modified = true;
    }

    if(page_props.email !== page_props.new_email){
        headers['new_email'] = page_props.new_email;
        modified = true;

    }

    if(page_props.username !== page_props.new_username){
        headers['new_username'] = page_props.new_username;
        modified = true;

    }

    if(!modified){
        return;
    }



    make_autenticated_requisition(main_interface,main_state,MODIFY_SELF_PROPS_ROUTE, {headers:headers},(response)=>{
        console.log(response)

        if(response.code === 0){
            alert(response.message);
            main_state.profile.username = page_props.new_username;
            main_state.profile.email = page_props.new_email;
            main_interface.render();

        }
    })


}