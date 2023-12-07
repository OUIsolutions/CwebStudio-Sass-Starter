
function main_interface(){
   
   let connected = this.getState(CONNECTED).getValue()
   if(!connected){
        render_login_page()
   }

}