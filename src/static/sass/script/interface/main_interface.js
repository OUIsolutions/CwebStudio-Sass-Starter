


function main_interface(){
   
   let connected = interface.getPrimitiveState(CONNECTED).getValue()
   if(!connected){
        render_login_page()
   }

}