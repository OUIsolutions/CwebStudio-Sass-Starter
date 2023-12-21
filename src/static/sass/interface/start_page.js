
function generate_start_page_style(){
    let style = {};

    style.right_div_style ={

        position:'absolute',
        width:'30vw',
        height:'100%',
        left:'70vw',
        'background-color':BLUE_BACKGROUND

    }
    style.main_form_style ={
        position:'absolute',
        'text-align':'center',
        height:'30vh',
        left:'5vw',
        'top': '30vh'
    }

    style.title_style ={
        color:'white',
        'margin-right':'5vw',
        'font-size':'4vh'
    }
    style.input_style ={
        'background-color':'white',
        'border-radius':'1vh',
        width:'20vw',
        'margin-right':'5vw',
        'font-size':'3vh',
        height:'5vh',
        border:'0'
    }
    style.login_button ={
        'margin-right':'5vw',
        height:'5vh',
        width:'10vw'
    }
    style.error_style ={
        'font-size':'2vh',
        'color':'white'
    }
    return style;
}

function  generate_start_page(username,username_error,password,password_error){

    return createElement404(()=>{

        let page_style = generate_start_page_style();

        main_interface.div(()=>{

            main_interface.div(()=>{

                main_interface.h4("Enter in the Platform",{style:page_style.title_style})
                main_interface.br()

                main_interface.stateInput(
                    "username_or_email",
                    {
                        style:page_style.input_style,
                        placeholder:"username or email",
                        default_value:username
                    }
                )

                if(username_error){
                    main_interface.p(username_error,{style:page_style.error_style});
                }

                main_interface.stateInput(
                    "password",
                    {
                        style:page_style.input_style,
                        type:"password",
                        default_value:password,
                        placeholder:"password"
                    }
                )

                if(password_error){
                    main_interface.p(password_error,{style:page_style.error_style});

                }

                main_interface.button("Login",{
                    style:page_style.login_button
                });

            },{style:page_style.main_form_style})


        },{style:page_style.right_div_style})
    })
}