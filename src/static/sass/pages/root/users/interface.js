/**
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function  render_users_page(main_interface, main_state) {
    main_interface.div({style: left_bar_style()}, () => {
        render_profile_apresentation(main_interface,main_state);
        main_interface.div({style:letf_bar_pages_style()},()=>{
            render_logout_button(main_interface,main_state);
        })
    })
    main_interface.div({style:rest_of_left_bar()},()=>{

        main_state.table(null,()=>{
            
            main_state.page_root_users.users.forEach(user => {
            
            })
        })

})

    


}