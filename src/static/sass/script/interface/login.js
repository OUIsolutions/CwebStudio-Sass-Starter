
/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 */
function  render_login_page(main_interface){

    const  LEFT_DIV_STYLE = {
        position:'absolute',
        width:'30vw',
        height:'100%',
        right:'0%',
        'background-color':'rgb(7, 15, 28)',
    }

    const MAIN_FORM_STYLE = {
        opacity:'100%',
        position:'absolute',
        'text-align':'center',
        height:'30%',
        left:'5%',
        'top': '30vh'
    }

    const INPUT_STYLE = {
        'background-color':'white',
        'border-radius':'5%',
        width:'20vw',
        height:'5vh',
        'border':'0'
    }
    const TITLE_STYLE ={
        'color':'white'
    }
    let page_props = main_interface.getObjectState(PAGE_PROPS);


    main_interface.div({style:LEFT_DIV_STYLE},()=>{
        main_interface.div({style:MAIN_FORM_STYLE},()=>{

            main_interface.h4({style:TITLE_STYLE},"Enter in the Plataform")
            main_interface.br()
            console.log(main_interface)
            
            //let login = page_props.getPrimitiveState(LOGIN);
            main_interface.input({
                style:INPUT_STYLE,
                //value:login,
                placeholder:"username or email"
            })

            main_interface.br()

            main_interface.input({
                style:INPUT_STYLE,
                type:'password',
                placeholder:"password"
            })
            main_interface.button(null,"Subscribe")

        })


    })

}
