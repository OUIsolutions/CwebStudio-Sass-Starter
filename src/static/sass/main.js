

 async function  render(callback=null,interface_state={}){

    let token = sessionStorage.getItem(TOKEN_KEY);


    if(!callback && !token){
        callback = start_callback;
    }
    if(!callback && token){
        callback =home_callback;
    }


    let created_interface = await callback(interface_state);
    created_interface.target = document.body;
    created_interface.render();


}




window.onload = ()=> render()
