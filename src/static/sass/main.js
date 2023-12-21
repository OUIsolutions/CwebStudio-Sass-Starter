
 async function  render(callback,args,state){


    let token = sessionStorage.getItem(TOKEN_KEY);
    /**@type {Element404}*/
    let created_interface;

    if(!callback){
        created_interface = render_start_page();
    }

    created_interface.target = document.body;
    created_interface.render();

}




window.onload = ()=> render()
