/**
 * @param {Element404} main_interface
 * @param {MainState} main_state
 * */
function render_profile_apresentation(main_interface, main_state){
    let profile = main_state.profile;
    let profile_picture_style = new ProfileApresentationStyle()

    main_interface.div({style:profile_picture_style.aprsentation_div()},()=>{
        main_interface.div({style:profile_picture_style.profile_picture_div()},()=>{
            main_interface.div({
                    style:profile_picture_style.profile_picture_img(profile.profile_picture_url)
                },
                null
            )
        })
        main_interface.div({style:profile_picture_style.profile_name_style()},()=>{
            main_interface.p(null,profile.username);
        })

    })

}