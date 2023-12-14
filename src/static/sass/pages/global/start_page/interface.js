

/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function  render_start_page(main_interface, main_state){

    let start_page = main_state.page_start
    let login_props =start_page.login_props

    const  RIGTH_DIV_STYLE = {
        position:'absolute',
        width:'30vw',
        height:'100%',
        left:'70vw',
        'background-color':'rgb(7, 15, 28)',
    }

    main_interface.div({style:RIGTH_DIV_STYLE},()=>{

        const MAIN_FORM_STYLE = {
            position:'absolute',
            'text-align':'center',
            height:'30vh',
            left:'5vw',
            'top': '30vh'
        }
        main_interface.div({style:MAIN_FORM_STYLE},()=>{

            const TITLE_STYLE ={
                'color':'white',
                'font-size':'4vh',
            }

            main_interface.h4({style:TITLE_STYLE},"Enter in the Plataform")
            main_interface.br()

            const INPUT_STYLE = {
                'background-color':'white',
                'border-radius':'1vh',
                width:'20vw',
                'font-size':'2vh',
                height:'5vh',
                'border':'0'
            }

            const ERROR_STYLE = {
                'font-size':'2vh',
                'color':'white'
            }

            main_interface.stateInput(
                login_props,
                "username_or_email",
                {
                style:INPUT_STYLE,
                placeholder:"username or email"
            })

            let username_or_email_error = login_props.username_or_email_error;
            if(username_or_email_error){
                main_interface.p({style:ERROR_STYLE},username_or_email_error);
            }
            

            if(!username_or_email_error){
                main_interface.br()
            }

            main_interface.stateInput(
                login_props,
                "password",
                {
                    style:INPUT_STYLE,
                    type:"password",
                    placeholder:"password"
                }
            )
            let password_error = login_props.password_error;
            if(password_error){
                main_interface.p({style:ERROR_STYLE},password_error);
            }

            
            main_interface.button({
                click:()=>create_token(main_interface,main_state)
            },"Login"

            );
           


        })


    })

}
