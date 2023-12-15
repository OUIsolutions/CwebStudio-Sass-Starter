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
    let page_props = main_state.page_root_profile;
    main_interface.div({style:rest_of_left_bar()},()=>{
        let div_style = {
            position:"absolute",
            top:'5%',
            left:"5%"
        }

        let input_style={
            'margin-top':0,

            'border-radius':'1vh',
                'background-color':SOFT_GREY,
                'color':'white',
                width:'15vw',
                'font-size':'2vh',
                height:'3vh',
                border:0

        }
        let p_style ={
            'margin-top':0,
            color: 'grey',
            'text-align':'center'
        }
        main_interface.div({style:div_style},()=>{
            main_interface.p({style:p_style},"username");
            main_interface.stateInput(page_props,"new_username",{style:input_style});

            main_interface.p({style:p_style},"email");
            main_interface.stateInput(page_props,"email",{style:input_style});

            main_interface.p({style:p_style},"new password");
            main_interface.stateInput(page_props,"password",{
                type:"password",
                style:input_style}

            );

            main_interface.p({style:p_style},"new password",);
            main_interface.stateInput(page_props,"new_password",{
                type:"password",
                style:input_style}
            );
            main_interface.br()
            main_interface.br()

            main_interface.button(null,"Change Props")
        })

    })

    


}