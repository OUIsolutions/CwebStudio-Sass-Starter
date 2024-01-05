
/**
 * @param {Element404} root_div
 * @param {SelfProps} user_props
 * */
function  create_common_internal_interface(root_div, user_props){
    let vertical_bar = root_div.div(()=>{


        let image_container = root_div.div(()=>{
            let image =  root_div.create('img');
            image.set_prop('APosition','$(0%,0%,100%,100%)');
            image.inline_style({
                'border-radius':'10vh'
            })
            let profile_picture_not_provided = !user_props.profile_picture;
            if(profile_picture_not_provided){
                image.set_prop('src',assets['snow'])
            }
        })


        image_container.set_prop('APosition','$(10vh,5%,10vw,10vw)');

        let username = root_div.p(user_props.username);

        username.inline_style({
            'font-size':'4vh'
        })

        username.set_prop('APosition','$(0%,+10vw,100%,10%)')

        let links_part = root_div.div();
        links_part.set_prop('APosition','$(0%,+10%,100%,50%)');

        let logout_button = root_div.button('Logout',()=>{

        })

        logout_button.set_prop('APosition','$(30%,+50%,40%,10%)');

    })
    vertical_bar.inline_style({
        'background-color':BLUE_BACKGROUND,
        'text-align':'center',
        'color':'white'
    })
    vertical_bar.set_prop('APosition','$16:9(0%,0%,20vw,100%)');
}