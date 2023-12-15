/**
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function  render_root_profile_page(main_interface, main_state) {

    main_interface.div({style: left_bar_style()}, () => {
        render_profile_apresentation(main_interface,main_state);

        main_interface.div({style:letf_bar_pages_style()},()=>{

            create_left_bar_element(
                main_interface,
                main_state.page_root_profile,
                "Profile",
                ()=>{go_to_root_page(main_interface,main_state)}
            )

            create_left_bar_element(
                main_interface,
                main_state.page_root_users,
                "List Users",
                ()=>{go_to_users_page(main_interface,main_state)}
            )

            render_logout_button(main_interface,main_state);
        })
    })
    main_interface.div({style:rest_of_left_bar()},()=>{



    })

    


}