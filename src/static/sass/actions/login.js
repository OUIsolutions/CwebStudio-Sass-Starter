
/**
 * @param {Element404} main_interface
 * @param {Element404} login_input
 * @param {Element404} password_input
 * @param {Element404} login_error
 * @param {Element404} password_error
 * */
async function  login_callback(main_interface,login_input,password_input,login_error,password_error){

    login_error.clear();
    password_error.clear();

    let login   = login_input.domElement.value;
    let password = password_input.domElement.value;


    if(!login){
        start_page_create_error(login_error,"login not provided")
        return;
    }


    if(!password){
        start_page_create_error(password_error,"password not provided")
        return;
    }

    let token = undefined;
    try{
         token = await create_token(login, password);
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

    await  home_callback(token,main_interface);


}