
/**
 * @param {object} session_data
 * @param {StartPageProps} interface_state
 * */
async function  login_callback(session_data,interface_state){

    let login   = interface_state.login;
    let password = interface_state.password;

    if(!login){
        interface_state.login_error ="username not provided";
        return  render_start_page(interface_state);
    }


    if(!password){
        interface_state.password_error ="password not provided";
        return render_start_page(interface_state);
    }
    try{
        let token = await create_token(login,password);
    }
    /**@type {HttpError}*/
    catch (error){
        if(error.code === USER_NOT_EXIST){
            interface_state.login_error =error.message
            return  render_start_page(interface_state);
        }
        if(error.code === WRONG_PASSWORD){
            interface_state.password_error =error.message
            return  render_start_page(interface_state);
        }
    }

}