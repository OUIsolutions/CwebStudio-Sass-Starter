


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
    }


}