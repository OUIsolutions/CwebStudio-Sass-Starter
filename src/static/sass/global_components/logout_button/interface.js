
/**
 * @param {Element404} main_interface
 * @param {MainState} main_state
 * */
function render_logout_button(main_interface, main_state){
    main_interface.button(
        {click:()=>{efetuate_logout(main_interface,main_state)}},
        'logout'
    )
}