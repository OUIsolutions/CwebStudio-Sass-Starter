
/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 */
function  render_login_page(main_interface){

    main_interface.div({"class":"row"},()=>{

        main_interface.input({
           'class':'u-full-width',
            placeholder:"username"
        })

        main_interface.input({placeholder:"password"})

    })

}
