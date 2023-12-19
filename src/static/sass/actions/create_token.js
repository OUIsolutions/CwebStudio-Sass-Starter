
/**
 *
 * @param {MainState} state
 * */
async function create_token(state){

    let login_props = state.login_props;
    login_props.username_or_email_error = undefined;
    login_props.password_error = undefined;


    if(!login_props.username_or_email){
        login_props.username_or_email_error  = "user not provided"
        return;
    }

    if(!login_props.password){
        login_props.password_error = "password not provided"
        return;
    }

    let data = await http_create_token(login_props.username_or_email,login_props.password);

    if(data.code === USER_NOT_EXIST){
        login_props.username_or_email_error = data.message;
        return;
    }


    if(data.code === WRONG_PASSWORD){
        login_props.password_error = data.message;
        return;
    }

    sessionStorage.setItem(TOKEN_KEY,data.token);
    await  perform_login(main_state);
}