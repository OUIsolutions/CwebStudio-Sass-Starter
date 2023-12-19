/**
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function  render_users_page(main_interface, main_state) {
    main_interface.div({style: left_bar_style()}, () => {
        profile_apresentation(main_interface,main_state);

        main_interface.div({style:letf_bar_pages_style()},()=>{

            left_bar_component(
                main_interface,
                main_state.page_root_profile,
                "Profile",
                ()=>{go_to_root_page(main_interface,main_state)}
            )

            left_bar_component(
                main_interface,
                main_state.page_root_users,
                "List Users",
                ()=>{go_to_users_page(main_interface,main_state)}
            )

            logout_button(main_interface,main_state);
        })
    })
    main_interface.div({style:rest_of_left_bar()},()=>{

        main_interface.br()
        const button_style = {
            'margin-left':'10%'
        }
        main_interface.button({style:button_style,click:()=>go_to_add_user(main_interface,main_state)},"Create New User")

        const table_style = {
            width:'80%',
            'margin-left':'10%',
            'margin-right':'10%',
        }


        main_interface.table({style:table_style},()=>{

            main_interface.tr(null,()=>{
                main_interface.th(null,'Username')
                main_interface.th(null,'Creation')
                main_interface.th(null,"Email")
                main_interface.th(null,"Last update")
                main_interface.th(null,"Is Root")
                main_interface.th(null,"Is Verified")
                main_interface.th(null,null)

            })

            function  convert_boolean(value){
                if(value){
                    return "yes"
                }
                return "no"
            }
            main_state.page_root_users.users.forEach(current_user => {
                main_interface.tr(null,()=>{
                    console.log(current_user)
                    main_interface.td(null,String(current_user.username))
                    main_interface.td(null,String(current_user.creation))
                    main_interface.td(null,String(current_user.email))
                    main_interface.td(null,String(current_user.last_update))
                    main_interface.td(null,convert_boolean(current_user.root))
                    main_interface.td(null,convert_boolean(current_user.verified))
                    main_interface.td(null,()=>{
                            main_interface.button(null,"Edit")
                    })

                })
            })
        })

})

    


}