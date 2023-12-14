



/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
function create_token(main_interface, main_state){

    let login_props = main_state.page_start.login_props;
    login_props.username_or_email_error = undefined;
    login_props.password_error = undefined;

    if(!login_props.username_or_email){
        login_props.username_or_email_error  = "user not provided"
        main_interface.render()
        return;
    }

    if(!login_props.password){
        login_props.password_error = "password not provided"
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
            login_props.username_or_email_error = data.mensage;
            main_interface.render()
            return;
        }


        if(data.code === WRONG_PASSWORD){
            login_props.password_error = data.mensage;
            main_interface.render()
            return;   
        }

        sessionStorage.setItem(TOKEN,data.token);
        efetuate_login(main_interface,main_state,data.token);

    })


}