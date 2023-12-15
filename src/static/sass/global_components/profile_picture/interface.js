/**
 * @param {Element404} main_interface The object props
 * @param {MainState} main_state
 */
function render_profile_picture(main_interface, main_state){
    let profile = main_state.profile;
    let profile_picture_style = new ProfilePictureStyle()
    main_interface.div({style:profile_picture_style.profile_picture_div()},()=>{
            main_interface.div({
                    style:profile_picture_style.profile_picture_img(profile.profile_picture_url)
                },
                null
            )
    })

}