

function  render_main_form_container(root_div){
    root_div.div((sub_element)=>{

        sub_element.inline_style({
            'background-color':BLUE_BACKGROUND
        })
        sub_element.set_prop("APosition",
            "$16:9(70%,0%,30%,100%)" +
            "$1:1(0%,30%,100%,50%)"
        );

        render_main_form(root_div);

    })
}