

function main(){

    let main_state = new MainState();
    console.log(main_state);
    return ;
    let token = sessionStorage.getItem(TOKEN);

    if(!token){
        main_state.tur_on_start_page();
    }


    createElement404(
        (main_interface) => {
            main_interface_generator(main_interface, main_state)
        }
    ).render(document.body)

}


window.onload = (undefined)=> main()
