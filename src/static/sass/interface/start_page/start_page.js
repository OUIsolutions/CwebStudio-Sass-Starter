

function  render_start_page(root_div){
    root_div.clear();


    root_div.inline_style({
        'background': `url('${assets['background']}')`,
        'background-size':'cover',
        'background-position': 'center center',

        position:'absolute',
        width:"100%",
        height:"100%",
        left:"0%",
        top:"0%"
    });

    render_main_form_container(root_div);


    
}