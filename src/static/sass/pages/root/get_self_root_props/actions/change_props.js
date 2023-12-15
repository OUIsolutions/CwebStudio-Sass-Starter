


/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
function  change_self_props(main_interface, main_state) {
    let page_props = main_state.page_root_profile;
    let headders = {}

    if(page_props.password || page_props.new_password){
        if(page_props.password !== page_props.new_password){
            page_props.password_error = "Passwords are not equal"
            main_interface.render();
            return;
        }
        headders['new_password'] = page_props.new_password;
    }
    if(page_props.email !== page_props.new_email){
        headders['new_email'] = page_props.new_email;
    }

    if(page_props.username !== page_props.new_username){
        headders['new_username'] = page_props.new_email;
    }



}