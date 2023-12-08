


/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 */
function main_interface_generator(main_interface){


   let connected = main_interface.getPrimitiveState(CONNECTED).getValue()

   let interface_style = {
        position:'fixed',
        width:'100vw',
        height: '100vh',
   }

    if(!connected){
        interface_style['background'] = `url('${BACKGROUND_IMAGE}')`;
        interface_style['background-size'] = 'cover'
        interface_style[' background-position'] = 'center center'
    }


    main_interface.div({style:interface_style},()=>{
       if(!connected){
           render_login_page(main_interface)
       }
   })


}