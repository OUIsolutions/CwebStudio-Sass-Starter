

function main(){

    let main_state = new MainState();
    let token = sessionStorage.getItem(TOKEN);


    let main_interface =createElement404(
        (main_interface) => {
            main_interface_generator(main_interface, main_state)
        },
        
        document.body
    )


    if(!token){
        main_state.tur_on_start_page();
        main_interface.render();
    }
    
    if(token){
        efetuate_login(main_interface, main_state, token)
    }


}


window.onload = (undefined)=> main()
