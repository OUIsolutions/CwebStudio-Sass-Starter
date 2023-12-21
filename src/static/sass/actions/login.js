

async function  login_callback(session_data,interface_state){

    let login   = interface_state.username_or_email;
    let password = interface_state.password;


    if(!login){
        return  render_start_page(login,"username not provided",password);
    }

    if(!password){
        return render_start_page(login,null,password,"password not provided");
    }
    try{
        let token = create_token(login,password);
    }

    /**@type {HttpError}*/
    catch (error){
        if(error.code === USER_NOT_EXIST){
            return  render_start_page(login,error.message,password);
        }
        if(error.code === WRONG_PASSWORD){
            return render_start_page(login,null,password,error.message);
        }
    }

}