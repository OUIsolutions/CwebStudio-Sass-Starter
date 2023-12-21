

async function  login_callback(session_data,interface_state){

    let username_or_email   = interface_state.username_or_email;
    let password = interface_state.password;


    if(!username_or_email){
        return  render_start_page(username_or_email,"username not provided",password);
    }

    if(!password){
        return render_start_page(username_or_email,null,password,"password not provided");
    }
    try{
        let token = create_token(username_or_email,password);
    }

    /**@type {HttpError}*/
    catch (error){
        if(error.code === USER_NOT_EXIST){
            return  render_start_page(username_or_email,error.message,password);
        }
        if(error.code === WRONG_PASSWORD){
            return render_start_page(username_or_email,null,password,error.message);
        }
    }
    
}