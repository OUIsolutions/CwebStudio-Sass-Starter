


function main_interface(){


   let connected = interface.getPrimitiveState(CONNECTED).getValue()

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

        interface.text(null,"aaaaaaaa")
        interface.text(null,"aaaaa")
   


}