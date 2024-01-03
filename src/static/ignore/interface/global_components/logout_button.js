

function logout_button(main_interface, main_state){
    let logout_button_style= {
        position:'absolute',
        'top':'80%',
        'left':'30%'
    }

    main_interface.button(
        'logout',
        {
            click:()=>{main_loop({action:perform_logout})},
            style:logout_button_style

        }
   )
}