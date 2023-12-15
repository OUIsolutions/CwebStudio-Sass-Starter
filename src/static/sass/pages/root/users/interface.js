/**
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function  render_users_page(main_interface, main_state) {
    main_interface.div({style: left_bar_style()}, () => {
        render_profile_apresentation(main_interface,main_state);
        render_logout_button(main_interface,main_state);
    })



}