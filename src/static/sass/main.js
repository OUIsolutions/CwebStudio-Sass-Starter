
let session_data = {}

 async function  render(callback,state){


    let token = sessionStorage.getItem(TOKEN_KEY);
    /**@type {Element404}*/
    let created_interface;

    if(!callback){
        callback = start_callback;
    }

    created_interface = callback(session_data,state);
    created_interface.target = document.body;
    created_interface.render();


}




window.onload = ()=> render()
