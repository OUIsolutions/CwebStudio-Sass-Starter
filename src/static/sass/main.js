

 async function  main(){

    let token = sessionStorage.getItem(TOKEN_KEY);

     createElement404((main_interface)=>{

            if(!token){
                start_callback(main_interface);
                return;
            }

            home_callback(main_interface)

        }, document.body).render();

}

window.addEventListener('load',main);
