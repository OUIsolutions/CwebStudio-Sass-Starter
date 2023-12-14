



/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
function create_token(main_interface, main_state){

    let login_props = main_state.start_page.login_props;
    let password_error = login_props.password_error;
    password_error.resset();

    let username_or_email_error = login_props.username_or_email_error
    username_or_email_error.resset();


    if(!login_props.username_or_email){
        username_or_email_error.exist = true;
        username_or_email_error.message = "user not provided"
        main_interface.render()
        return;
    }

    if(!login_props.password){
        password_error.exist = true;
        password_error.message = "password not provided"
        main_interface.render()
        return;
    }

        let headers = {
        login: login_props.username_or_email,
        password:login_props.password
    }

     fetch(CREATE_TOKEN,{headers:headers})
    .then(data => data.json())
    .then(data =>{
        if(data.code === USER_NOT_FOUND){
            username_or_email_error.exist = true;
            username_or_email_error.message = data.mensage
            main_interface.render()
            return;
        }


        if(data.code === WRONG_PASSWORD){
            password_error.exist = true;
            password_error.message = data.mensage
            main_interface.render()
            return;   
        }

        sessionStorage.setItem(TOKEN,data.token);
        efetuate_login(main_interface,main_state,data.token);

    })


}