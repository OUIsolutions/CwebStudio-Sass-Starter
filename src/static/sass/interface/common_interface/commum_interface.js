
/**
 * @param {Element404} root_div
 * @param {SelfProps} user_props
 * */
function  create_common_internal_interface(root_div, user_props){
    let vertical_bar = root_div.div(()=>{

        let username = root_div.p(user_props.username);

        username.inline_style({
            'font-size':'4vh'
        })

        username.set_prop('APosition','$(0%,10%,100%,10%)')

        let image =  root_div.create('img');
        image.set_prop('APosition','$(5vh,+10%,15vw,15vw)')

        let profile_picture_not_provided = !username.profile_picture;
        if(profile_picture_not_provided){
        }
    })
    vertical_bar.inline_style({
        'background-color':BLUE_BACKGROUND,
        'text-align':'center',
        'color':'white'
    })
    vertical_bar.set_prop('APosition','$16:9(0%,0%,20vw,100%)');
}