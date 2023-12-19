


function generate_main_component_style() {
    let style ={
        position:'fixed',
        width:'100vw',
        height: '100vh'
    }


    if(state.page === 'start'){
        style['background'] = `url('${assets['background']}')`;
        style['background-size'] = 'cover';
        style[' background-position'] = 'center center';
    }
    return style;
}

function generate_main_component(main_interface, state){
    let style =generate_main_component_style();
    main_interface.div(()=>{

        if(state.page === 'start'){
            generate_start_page(main_interface,state)
        }

    },{style:style})

}
