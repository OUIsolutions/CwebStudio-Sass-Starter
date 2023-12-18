
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