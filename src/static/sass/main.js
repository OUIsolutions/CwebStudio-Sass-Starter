




/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function main_interface_generator(main_interface,main_state){
    let interface_style = {
         position:'fixed',
         width:'100vw',
         height: '100vh'
    }

     if(main_state.page_start.current){
         interface_style['background'] = `url('${assets['background']}')`;
         interface_style['background-size'] = 'cover';
         interface_style[' background-position'] = 'center center';
     }
 
     main_interface.div({style:interface_style},()=>{
        if(main_state.page_start.current){
            render_start_page(main_interface,main_state)
        }

        //root pages
        if(main_state.page_root_users.current){
            render_users_page(main_interface,main_state);
        }

        if(main_state.page_root_profile.current){
            render_root_profile_page(main_interface,main_state);
        }

    })
 
 
 
 }

function main(){

    let main_state = new MainState();
    let token = sessionStorage.getItem(TOKEN);

    let main_interface =createElement404(
        (main_interface) => {
            main_interface_generator(main_interface, main_state)
        },
        
        document.body
    )

    if(!token){
        main_state.turnOnPage(StartPage);
        main_interface.render();
    }
    
    if(token){
        efetuate_login(main_interface, main_state, token)
    }


}


window.onload = ()=> main()
