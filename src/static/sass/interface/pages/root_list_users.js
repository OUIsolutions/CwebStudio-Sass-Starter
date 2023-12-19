
function  render_users_page(main_interface, main_state) {

        main_interface.div( () => {
        profile_apresentation(main_interface,main_state);
        main_interface.div(()=>{
            /*
                left_bar_component(
                    main_interface,
                    main_state.profile,
                    "Profile",
                    ()=>{main_loop({action:go_to_root_page})}
                )

                left_bar_component(
                    main_interface,
                    main_state.profile,
                    "List Users",
                    ()=>{list_users(main_interface,main_state)}
                )
            */
                //logout_button(main_interface,main_state);
        },{style:letf_bar_pages_style()})
    },{style: left_bar_style()});

    main_interface.div(()=>{

        main_interface.br()
        const button_style = {
            'margin-left':'10%'
        }
        main_interface.button(
            "Create New User",
        {style:button_style,
            click:()=>go_to_add_user(main_interface,main_state)
        }
        )

        const table_style = {
            width:'80%',
            'margin-left':'10%',
            'margin-right':'10%',
        }


        main_interface.table(()=>{

            main_interface.tr(null,()=>{
                main_interface.th(null,'Username')
                main_interface.th(null,'Creation')
                main_interface.th(null,"Email")
                main_interface.th(null,"Last update")
                main_interface.th(null,"Is Root")
                main_interface.th(null,"Is Verified")
                main_interface.th(null,null)

            },{style:table_style})

            function  convert_boolean(value){
                if(value){
                    return "yes"
                }
                return "no"
            }
            main_state.users.forEach(current_user => {
                main_interface.tr(null,()=>{
                    console.log(current_user)
                    main_interface.td(String(current_user.username))
                    main_interface.td(String(current_user.creation))
                    main_interface.td(String(current_user.email))
                    main_interface.td(String(current_user.last_update))
                    main_interface.td(convert_boolean(current_user.root))
                    main_interface.td(convert_boolean(current_user.verified))
                    main_interface.td(()=>{
                            main_interface.button(null,"Edit")
                    })

                })
            })
        })

    },{style:rest_of_left_bar()})

    


}