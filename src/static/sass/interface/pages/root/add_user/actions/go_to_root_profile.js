

/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
function  go_to_add_user(main_interface, main_state){

    main_state.turnOnPage(NewUserState);
    main_interface.render();

}