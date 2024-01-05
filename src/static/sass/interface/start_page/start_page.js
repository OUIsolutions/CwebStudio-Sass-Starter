

function  render_start_page(root_div){


    root_div.inline_style({
                'background': `url('${assets['background']}')`,
                'background-size':'cover',
                'background-position': 'center center',

    });

    render_main_form_container(root_div);


    
}