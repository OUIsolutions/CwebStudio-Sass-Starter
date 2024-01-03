

function  render_start_page(main_interface){

        main_interface.div((sub_element)=>{

            sub_element.inline_style({
                position:'fixed',
                width:'100vw',
                height: '100vh',
                'background': `url('${assets['background']}')`,
                'background-size':'cover',
                'background-position': 'center center'
            });

            render_main_form_container(main_interface);

        });

    
}