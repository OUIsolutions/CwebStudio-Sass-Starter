

 async function  main(){

    let token = sessionStorage.getItem(TOKEN_KEY);

     createElement404((main_interface)=>{


            let root = main_interface.div();

            root.outline_style({
                position:'absolute',
                width:"100%",
                height:"100%",
                left:"0%",
                top:"0%"
            });


            if(!token){
                render_start_page(root);
                return;
            }
            home_callback(token,root)

        }, document.body).render();

}

window.addEventListener('load',main);
