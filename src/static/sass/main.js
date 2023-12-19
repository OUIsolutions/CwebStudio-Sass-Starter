let main_state;
 function  main_loop(props=null){

    let action = props['action'];
    let action_args = props['args'];
    if(action){
         action(main_state,action_args)
    }

    console.log("terminou a açao");


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
        main_loop({
            action: start_application
        })
    }

}


window.onload = ()=> main()
