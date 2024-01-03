
function  render_main_form(main_interface){
    main_interface.div((sub_element)=>{

        sub_element.inline_style({
            'text-align':'center'
        });

        sub_element.set_prop("APosition","$16:9(15%,30%,70%,30%)" +
            "$1:1(5%,15%,90%,30%)");

        let title = main_interface.h4("Enter in the Platform");
        title.inline_style({
            color:'white'
        });

        main_interface.br();

        const  state_input_style = {
            'background-color':'white',
            'border-radius':'1vh',
            width:'100%',
            'font-size':'3vh',
            height:'5vh',
            border:'0'
        }

        let login = main_interface.input({
                inline_style:state_input_style,
                placeholder:"username or email"
        })

        let login_error_fragment = main_interface.div();

        let password = main_interface.input({
                inline_style:state_input_style,
                type:"password",
                placeholder:"password",
                render_keyup:false
        })


        let password_fragment = main_interface.div();

        main_interface.button("Login",{
            click:()=> login_callback(
                main_interface,
                login,
                password,
                login_error_fragment,
                password_fragment
            )
        });

    })
}