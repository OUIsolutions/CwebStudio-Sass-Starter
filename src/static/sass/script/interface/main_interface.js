


function main_interface(){


   let connected = interface.getPrimitiveState(CONNECTED).getValue()

   let interface_style = {
        position:'absolute',
        width:'100vw',
        height: '100vh'
   }
   if(!connected){
       interface_style['background'] = `url('${BACKGROUND_IMAGE}')`;
   }

   interface.div({style:interface_style},()=>{

       if(!connected){
           render_login_page()
       }

   })


}