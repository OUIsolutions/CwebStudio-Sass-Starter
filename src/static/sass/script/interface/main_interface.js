


/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 */
function main_interface_generator(main_interface){


   let connected = main_interface.getPrimitiveState(CONNECTED).getValue()

   
    /*
    if(!connected){
        interface_style['background'] = `url('${BACKGROUND_IMAGE}')`;
        interface_style['background-size'] = 'cover'
        interface_style[' background-position'] = 'center center'
    }
    */

    main_interface.div({'class':'container'},()=>{
       if(!connected){
           render_login_page(main_interface)
       }
   })


}