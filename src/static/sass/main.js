
function  main_loop(action,args=null){

    action(state,args);

    createElement404(
        (main_interface) => {
            generate_main_component(main_interface, state)
        },
        document.body
    ).render();

}

function main(){

    let token = sessionStorage.getItem(TOKEN_KEY);

    if(!token){
        main_loop(start_application);
    }



}


window.onload = ()=> main()
