

function create_left_bar_element(main_interface,page_props,text,callback){

    let  div_style ={
        'margin-top':'2vh',
         height:'5vh',
        'text-align':'center',
        'color':'white'

    }
    if(page_props.selected || page_props.current){
        div_style['background-color'] = 'rgb(36,58,93)';
    }

    let div_props = {
        style:div_style,
        click:callback,
    }
    if(page_props.selected){
        div_props['render_mouseleave'] =()=>{page_props.selected = false}
    }
    if(!page_props.selected){
        div_props['render_mouseenter'] =()=>{page_props.selected = true}
    }

    main_interface.div(div_props,text)


}