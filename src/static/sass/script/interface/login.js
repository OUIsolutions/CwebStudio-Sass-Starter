

/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 * @param {StartPage} start_page
 */
function  render_login_page(main_interface,start_page){

    const  LEFT_DIV_STYLE = {
        position:'absolute',
        width:'30vw',
        height:'100%',
        right:'0%',
        'background-color':'rgb(7, 15, 28)',
    }

    const MAIN_FORM_STYLE = {
        position:'absolute',
        'text-align':'center',
        height:'30vh',
        left:'5vw',
        'top': '30vh'
    }

    const INPUT_STYLE = {
         'background-color':'white',
         'border-radius':'1vh',
         width:'20vw',
         'font-size':'2vh',
         height:'5vh',
         'border':'0'
    }

    const TITLE_STYLE ={
        'color':'white',
        'font-size':'4vh',
    }
    const ERROR_STYLE = {
        'font-size':'1vh',
        'color':'white'
    }

    main_interface.div({style:LEFT_DIV_STYLE},()=>{
        main_interface.div({style:MAIN_FORM_STYLE},()=>{

            main_interface.h4({style:TITLE_STYLE},"Enter in the Plataform")
            main_interface.br()

            main_interface.stateInput(
                start_page.login_props,
                "username_or_email",
                {
                style:INPUT_STYLE,
                placeholder:"username or email"
            })

            main_interface.br()

            main_interface.stateInput(
                start_page.login_props,
                "password",
                {
                    style:INPUT_STYLE,
                    type:"password",
                    placeholder:"password"
                }
            )



        })


    })

}
