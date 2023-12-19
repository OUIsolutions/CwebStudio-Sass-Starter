


function generate_main_component_style(main_state) {
    let style ={
        position:'fixed',
        width:'100vw',
        height: '100vh'
    }


    if(main_state.page === START_PAGE){
        style['background'] = `url('${assets['background']}')`;
        style['background-size'] = 'cover';
        style[' background-position'] = 'center center';
    }
    return style;
}

function generate_main_component(main_interface, main_state){

    let style =generate_main_component_style(main_state);


    main_interface.div(()=>{

        if(main_state.page === START_PAGE){
            generate_start_page(main_interface,main_state)
        }

        if(main_state.page ===ROOT_LIST_USERS_PAGE){

            render_users_page(main_interface,main_state);
        }


    },{style:style})

}
