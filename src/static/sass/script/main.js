

function main(){

    
    interface = new Element404(main_interface);

    let token = sessionStorage.getItem(TOKEN);

    if(!token){
        interface.getPrimitiveState(CONNECTED).setValue(false);
        interface.render(document.body)
        return;
    }

}


window.onload = (undefined)=> main()
