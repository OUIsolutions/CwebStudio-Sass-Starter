let main_state;
function  main_loop(action,args=null){

    action(main_state,args);

    createElement404(
        (main_interface) => {
            generate_main_component(main_interface, main_state)
        },
        document.body
    ).render();

}

function main(){
    main_state = create_main_state();
    let token = sessionStorage.getItem(TOKEN_KEY);

    if(!token){
        main_loop(start_application);
    }



}


window.onload = ()=> main()
