



/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
function create_token(main_interface, main_state){

    let login_props = main_state.page.login_props;

    let headers = {
        login: login_props.username_or_email,
        password:login_props.password
    }

     fetch(CREATE_TOKEN,{headers:headers})
    .then(data => data.json())
    .then(data =>{

        if(data.code === USER_NOT_FOUND){
            console.log(data)
           login_props.username_or_email_error = new UsernameOrEmailError(
               login_props.username_or_email,
               data.mensage
           );
        }

        main_interface.render()
    })


}