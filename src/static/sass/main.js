//let my_seed = 'hello my cold friend'
//tomato_start(my_seed);

 async function  main(){



    let token = sessionStorage.getItem(TOKEN_KEY);

     createElement404((main_interface)=>{


            let root = main_interface.div();


            if(!token){
                render_start_page(root);
                return;
            }
            home_callback(token,root)

        }, document.body).render();

}

window.addEventListener('load',main);
