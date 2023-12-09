

function main(){


    main_interface = new Element404(
        ()=>{main_interface_generator(main_interface)
        });

    let token = sessionStorage.getItem(TOKEN);

    if(!token){
        let connected = main_interface.getPrimitiveState(CONNECTED);
        connected.setValue(false);

        main_interface.render(document.body)
        return;
    }


}


window.onload = (undefined)=> main()
