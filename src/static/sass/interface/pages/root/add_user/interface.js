/**
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function  render_add_user_page(main_interface, main_state) {

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
                ()=>{go_to_list_users_page(main_interface,main_state)}
            )

            logout_button(main_interface,main_state);
        })
    })
    let page_props = main_state.page_add_user;
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

                border:'none'

        }
        let p_style ={
            'margin-top':0,
            color: 'grey',
            'text-align':'center'
        }
        let style_error={
            color:'red'
        }
        main_interface.div({style:div_style},()=>{

            main_interface.p({style:p_style},"username");
            main_interface.stateInput(page_props,"username",{style:input_style});

            if(page_props.username_error){
                main_interface.p({style:style_error},page_props.username_error);
            }

            main_interface.p({style:p_style},"email");
            main_interface.stateInput(page_props,"email",{style:input_style});
            if(page_props.email_error){
                main_interface.p({style:style_error},page_props.email_error);
            }

            main_interface.p({style:p_style},"password");
            main_interface.stateInput(page_props,"password",{
                type:"password",
                style:input_style}

            );
            if(page_props.password_error){
                main_interface.p({style:style_error},page_props.password_error);
            }
            main_interface.p({style:p_style},"confirm password",);
            main_interface.stateInput(page_props,"new_password",{
                type:"password",
                style:input_style}
            );
            if(page_props.password_error){
                main_interface.p({style:style_error},page_props.password_error);
            }

            main_interface.br()
            main_interface.br()

            main_interface.button({click:()=>add_user(main_interface,main_state)},"Add User")
        })



    })

    


}