

function main_interface_loop(){

    
    let token = main_interface.getStateValue("token");
    
    if(!token){
        start_page_component();
        return;
    }
    

}