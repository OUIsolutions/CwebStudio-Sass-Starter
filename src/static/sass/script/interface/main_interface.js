


/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 */
function main_interface_generator(main_interface){


   let connected = main_interface.getPrimitiveState(CONNECTED).getValue()

   let interface_style = {
        position:'absolute',
        width:'100vw',
        height: '100vh'
   }
   
   if(!connected){
       interface_style['background'] = `url('${BACKGROUND_IMAGE}')`;
       interface_style['background-size'] = 'cover'
       interface_style[' background-position'] = 'center center'
   }

    main_interface.div({},()=>{

        /*
       if(!connected){
           render_login_page()
       }
       */
        main_interface.text("aaaaaaaa")
        main_interface.text("aaaaa")
   })


}