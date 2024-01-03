
function render_start_page_style(){
    let style = {};

    style.global = {
        position:'fixed',
        width:'100vw',
        height: '100vh',
        'background': `url('${assets['background']}')`,
        'background-size':'cover',
        'background-position': 'center center'
    }
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
 
    return style;
}

/**
 * @typedef {object} StartPageProps
 * @property {string || undefined} login
 * @property {string || undefined} login_error
 * @property {string || undefined} password
 * @property {string || undefined} password_error
 * * */

/**
 * @returns {Element404}
 * */
function  render_start_page(main_interface){

        let page_style = render_start_page_style();
        main_interface.div((sub_element)=>{

            sub_element.inline_style(page_style.global);


            main_interface.div((sub_element)=>{

                sub_element.inline_style(page_style.right_div_style);

                
                main_interface.div((sub_element)=>{

                    sub_element.inline_style(page_style.main_form_style);


                    main_interface.h4("Enter in the Platform",{inline_style:page_style.title_style})
                    main_interface.br()

                    main_interface.stateInput(
                        "login",
                        {
                            inline_style:page_style.input_style,
                            placeholder:"username or email"
                        }
                    )
                    let login_error_fragment = main_interface.div();



                    main_interface.stateInput(
                        "password",
                        {
                            inline_style:page_style.input_style,
                            type:"password",
                            placeholder:"password",
                            render_keyup:false
                        }
                    )

                    let password_fragment = main_interface.div();

                    main_interface.button("Login",{
                        style:page_style.login_button,
                        click:()=> login_callback(main_interface,login_error_fragment,password_fragment)
                    });

                })
            })

        });

    
}