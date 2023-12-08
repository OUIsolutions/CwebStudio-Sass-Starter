
/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 */
function  render_login_page(main_interface){

    const  LEFT_DIV_STYLE = {
        position:'fixed',
        width:'30%',
        height:'100%',
        right:'0%',
        opacity:'50%',
        'background-color':'rgb(14, 15, 18)',
    }

    main_interface.div({style:LEFT_DIV_STYLE},()=>{

        main_interface.input({
            placeholder:"username"
        })

        main_interface.input({
            placeholder:"password"
        })
        main_interface.button(null,"submit")
    })

}
