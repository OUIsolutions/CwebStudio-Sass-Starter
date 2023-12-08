

function main(){


    main_interface = new Element404(
        ()=>{main_interface_generator(main_interface)
        });

    let token = sessionStorage.getItem(TOKEN);

    if(!token){
        main_interface.getPrimitiveState(CONNECTED).setValue(false);
        main_interface.render(document.body)
        return;
    }

}


window.onload = (undefined)=> main()
