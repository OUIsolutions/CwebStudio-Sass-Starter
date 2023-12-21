
 async function  render(callback,args,state){


    let token = sessionStorage.getItem(TOKEN_KEY);
    /**@type {Element404}*/
    let created_interface;

    if(!callback){
        created_interface = await start_callback();
    }

    created_interface.target = document.body;
    created_interface.render();

}




window.onload = ()=> render()
