

function  render_start_page(main_interface){

        main_interface.div((sub_element)=>{

            sub_element.inline_style({
                'background': `url('${assets['background']}')`,
                'background-size':'cover',
                'background-position': 'center center'
            });
            sub_element.set_prop("APosition","$(0%,0%,100%,100%)")

            render_main_form_container(main_interface);

        });

    
}