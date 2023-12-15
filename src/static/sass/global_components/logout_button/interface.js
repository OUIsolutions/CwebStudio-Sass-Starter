
/**
 * @param {Element404} main_interface
 * @param {MainState} main_state
 * */
function render_logout_button(main_interface, main_state){
    let logout_button_style= {
        position:'absolute',
        'top':'80%',
        'left':'30%'
    }

    main_interface.button(
        {
            click:()=>{efetuate_logout(main_interface,main_state)},
            style:logout_button_style

        },
        'logout'
    )
}