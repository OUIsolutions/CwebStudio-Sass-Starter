

 function create_token(state){

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

    let headers = {
        login: login_props.username_or_email,
        password:login_props.password
    }
    fetch(CREATE_TOKEN_ROUTE,{headers:headers})
    .then(response =>response.json())
    .then(response =>{
        console.log(response);
        if(response.code === USER_NOT_EXIST){
            login_props.username_or_email_error = response.message;
            main_loop();
            return;
        }


        if(response.code === WRONG_PASSWORD){
            login_props.password_error = response.message;
            main_loop();
            return;
        }

        sessionStorage.setItem(TOKEN_KEY,response.token);
        efetuate_login(main_state);
    })







}