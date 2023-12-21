
/**
 *
 * @param {Element404} main_interface
 * @param {MainState} main_state
 * @param {string} page_name
 * @param {string} text
 * @param {function} callback
 * */
function left_bar_component(
    main_interface,
    main_state,
    page_name,
    text,
    callback){

    let  div_style ={
        'margin-top':'2vh',
         height:'5vh',
        'text-align':'center',
        'color':'white'

    }

    let is_selected = main_state.selected_page === page_name;
    let is_current_page = main_state.page === page_name;
    if(is_selected || is_current_page){
        div_style['background-color'] = 'rgb(36,58,93)';
    }

    let div_props = {
        style:div_style,
        click:callback,
    }
    if(is_selected){
        div_props['render_mouseleave'] =()=>{
            if(main_state.selected_page === page_name){
                main_state.selected_page = undefined;
            }
        }
    }
    if(!is_selected){
        div_props['render_mouseenter'] =()=>{
            main_state.selected_page = page_name;
        }
    }

    main_interface.div(text,div_props)


}