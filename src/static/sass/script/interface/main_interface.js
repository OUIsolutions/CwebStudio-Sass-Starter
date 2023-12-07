
function main_interface(){
   
   let connected = interface.getState(CONNECTED).getValue()
   if(!connected){
        render_login_page()
   }

}