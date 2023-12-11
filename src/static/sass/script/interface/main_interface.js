


/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function main_interface_generator(main_interface,main_state){



   let interface_style = {
        position:'fixed',
        width:'100vw',
        height: '100vh'
   }

    if(!main_state.connected){
        interface_style['background'] = `url('${assets['background']}')`;
        interface_style['background-size'] = 'cover';
        interface_style[' background-position'] = 'center center';
    }


    main_interface.div({style:interface_style},()=>{
       if(!main_state.connected){
           render_login_page(main_interface,main_state)
       }
   })



}