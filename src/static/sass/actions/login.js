
/**
 * @param {Element404} main_interface
 * @param {Element404} login_error
 * @param {Element404} password_error
 * */
async function  login_callback(main_interface,login_error,password_error){

    let login   = main_interface.getStateValue("login");
    let password = main_interface.getStateValue("password");
    clear_error(login_error);
    clear_error(password_error);

    if(!login){
        start_page_create_error(login_error,"login not provided")
        return;
    }


    if(!password){
        start_page_create_error(password_error,"password not provided")
        return;
    }
    try{
        let token = await create_token(login, password);
        sessionStorage.setItem(TOKEN_KEY,token);

        //return home_callback(new_interface_state);
    }
    /**@type {HttpError}*/
    catch (error){
        if(error.code === USER_NOT_EXIST){
            start_page_create_error(login_error,error.message)

        }
        if(error.code === WRONG_PASSWORD){
            start_page_create_error(password_error,error.message)
        }
    }

}