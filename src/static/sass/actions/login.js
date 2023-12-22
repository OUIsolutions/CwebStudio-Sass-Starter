
/**
 * @param {StartPageProps} interface_state
 * */
async function  login_callback(interface_state){

    let login   = interface_state.login;
    let password = interface_state.password;


    let new_interface_state = {
        login:login,
        password:password
    }

    if(!login){
        new_interface_state.login_error ="username not provided";
        return  render_start_page(new_interface_state);
    }


    if(!password){
        new_interface_state.password_error ="password not provided";
        return render_start_page(new_interface_state);
    }
    try{
        new_interface_state.token = await create_token(login, password);
        //return home_callback(new_interface_state);
    }
    /**@type {HttpError}*/
    catch (error){
        if(error.code === USER_NOT_EXIST){
            new_interface_state.login_error =error.message
            return  render_start_page(new_interface_state);
        }
        if(error.code === WRONG_PASSWORD){
            new_interface_state.password_error =error.message
            return  render_start_page(new_interface_state);
        }
    }

}