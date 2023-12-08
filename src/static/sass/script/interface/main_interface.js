


function main_interface(){


   let connected = interface.getPrimitiveState(CONNECTED).getValue()

   let interface_style = {}
   if(!connected){
       interface_style['backgroundImage'] = `url("${BACKGROUND_IMAGE}")`;
   }

   interface.div({style:interface_style},()=>{

       if(!connected){
           render_login_page()
       }

   })


}