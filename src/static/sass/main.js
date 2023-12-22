

 async function  render(callback,interface_state){


    let token = sessionStorage.getItem(TOKEN_KEY);
    /**@type {Element404}*/

    if(!token){
        callback = start_callback;
    }

    if(!callback && token){
        callback = home_callback
    }
   if(!interface_state ){
      interface_state = {
         token:token
      }
   }

    let created_interface = await callback(interface_state);
    created_interface.target = document.body;
    created_interface.render();


}




window.onload = ()=> render()
