
let main_interface;
let states = {};

 async function  main(){

    let token = sessionStorage.getItem(TOKEN_KEY);

    states = {
        token:token
    }
    
    main_interface = createElement404(main_interface_loop, document.body);
    
    main_interface.stored_state = states;
    main_interface.render();


}
window.onload = ()=> main()
