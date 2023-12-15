/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function  render_users_page(main_interface, main_state) {
    let start_page = main_state.page_start
    let login_props = start_page.login_props
    main_interface.div({style: left_bar_style()}, () => {

        render_profile_picture(main_interface,main_state);

    })

}