/**
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function  render_user_profile_page(main_interface, main_state) {

    main_interface.div({style: left_bar_style()}, () => {
        render_profile_apresentation(main_interface,main_state);

        main_interface.div({style:letf_bar_pages_style()},()=>{

            create_left_bar_element(
                main_interface,
                main_state.page_root_profile,
                "Profile",
                ()=>{go_to_root_page(main_interface,main_state)}
            )

            render_logout_button(main_interface,main_state);
        })
    })

    let page_props = main_state.page_user_profile;
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
            main_interface.stateInput(page_props,"new_username",{style:input_style});


            if(page_props.username_error){
                main_interface.p({style:style_error},page_props.username_error);
            }

            main_interface.p({style:p_style},"email");
            main_interface.stateInput(page_props,"new_email",{style:input_style});
            if(page_props.email_error){
                main_interface.p({style:style_error},page_props.email_error);
            }


            main_interface.br()
            main_interface.br()
            main_interface.br()
            main_interface.br()
            main_interface.br()
            main_interface.br()

            main_interface.button({click:()=>change_user_self_props(main_interface,main_state)},"Change Props")
        })

        main_interface.div({style:{
                position: 'absolute',
                top:'5%',
                'left':'30vw',
            }},()=>{
            main_interface.p({style:p_style},"Old Passowrd");
            main_interface.stateInput(page_props,"old_password",{
                style:input_style,
                type:"password"
            });
            main_interface.br()
            if(page_props.old_password_error){
                main_interface.p({style:style_error},page_props.old_password_error);
            }

            main_interface.p({style:p_style},"new password");
            main_interface.stateInput(page_props,"password",{
                type:"password",
                style:input_style}

            );
            if(page_props.password_error){
                main_interface.p({style:style_error},page_props.password_error);
            }
            main_interface.p({style:p_style},"confirm new password",);
            main_interface.stateInput(page_props,"new_password",{
                type:"password",
                style:input_style}
            );

            if(page_props.password_error){
                main_interface.p({style:style_error},page_props.password_error);
            }
        })


    })

    


}