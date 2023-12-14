

/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function  render_start_page(main_interface, main_state){

    let start_page = main_state.page_start
    let login_props =start_page.login_props
    let style = new StartPageStyle();

    main_interface.div({style:style.right_div_style()},()=>{


        main_interface.div({style:style.main_form_style()},()=>{

            main_interface.h4({style:style.title_style() },"Enter in the Plataform")
            main_interface.br()

            main_interface.stateInput(
                login_props,
                "username_or_email",
                {
                style:style.input_style(),
                placeholder:"username or email"
            })

            let username_or_email_error = login_props.username_or_email_error;
            if(username_or_email_error){
                main_interface.p({style:style.error_style()},username_or_email_error);
            }
            

            if(!username_or_email_error){
                main_interface.br()
            }

            main_interface.stateInput(
                login_props,
                "password",
                {
                    style:style.input_style(),
                    type:"password",
                    placeholder:"password"
                }
            )
            let password_error = login_props.password_error;
            if(password_error){
                main_interface.p({style:style.error_style()},password_error);
            }
            
            main_interface.button({
                click:()=>create_token(main_interface,main_state)
            },"Login"

            );
           


        })


    })

}
