

function  generate_start_page(main_interface, main_state){

    let page_style = generate_start_page_style();

    main_interface.div(()=>{


        main_interface.div(()=>{

            main_interface.h4("Enter in the Platform",{style:page_style.title_style})
            main_interface.br()

            main_interface.stateInput(
                login_props,
                "username_or_email",
                {
                style:page_style.input_style,
                placeholder:"username or email"
            }
            )

            let username_or_email_error = login_props.username_or_email_error;
            if(username_or_email_error){
                main_interface.p(username_or_email_error,{style:page_style.error_style});
            }

            main_interface.stateInput(
                login_props,
                "password",
                {
                    style:page_style.input_style,
                    type:"password",
                    placeholder:"password"
                }
            )
            let password_error = login_props.password_error;
            if(password_error){
                main_interface.p(password_error,{style:page_style.error_style},);

            }

            main_interface.button("Login",{
                style:page_style.login_button,
                click:()=>create_token(main_interface,main_state)

            });
           


        },{style:page_style.main_form_style})


    },{style:page_style.right_div_style})

}
