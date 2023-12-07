

function main(){

    
    interface = main_interface();
    
    let token = sessionStorage.getItem(TOKEN);

    if(!token){
        interface.getState(CONNECTED).setValue(false);
        interface.render(document.getElementById("root"))
        return;
    }

    
}


window.onload = (undefined)=> main()
