let main_state;

async function  handle_props(props){
    let action = props['action'];
    let action_args = props['args'];
    if(action){
       try{
           await action(main_state,action_args)
       } catch (error){}
    }
}
 async function  main_loop(props=null){


    if(props){
        await handle_props(props)
    }

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
        }).then( )
    }

}


window.onload = ()=> main()
