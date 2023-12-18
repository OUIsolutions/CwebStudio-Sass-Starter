




/**
 * Creates an H3
 * @param {MainState} main_state
 */
function create_main_interface_style(main_state){
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

    return interface_style;

}



/**
 * Creates an H3
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function main_interface_generator(main_interface,main_state){
    let interface_style = create_main_interface_style(main_state);

     main_interface.div(()=>{
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

        if(main_state.page_add_user.current){
            render_add_user_page(main_interface,main_state);
        }

        if(main_state.page_user_profile.current){
            render_user_profile_page(main_interface,main_state);
        }

    },{style:interface_style})

 
}


function main(){

    let main_state = new MainState();
    let token = sessionStorage.getItem(TOKEN_KEY);

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
        efetuate_login(main_interface, main_state)
    }


}


window.onload = ()=> main()
