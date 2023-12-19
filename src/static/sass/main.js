let main_state;
function  main_loop(props=null){


    props.action(main_state,props.args);

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
            action:start_application
        });
    }

}


window.onload = ()=> main()
