

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
    .then(data => data.json())
    .then(data =>{
        console.log(data);
        if(data.code === USER_NOT_EXIST){
            login_props.username_or_email_error = data.message;
            return;
        }


        if(data.code === WRONG_PASSWORD){
            login_props.password_error = data.message;
            return;   
        }

        //sessionStorage.setItem(TOKEN_KEY,data.token);
        //efetuate_login(main_interface,main_state);

    })


}