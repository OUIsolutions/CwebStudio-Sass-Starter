
/**
 * @param {object} session_data
 * @param {StartPageProps} interface_state
 * */
async function  login_callback(session_data,interface_state){

    let login   = interface_state.login;
    let password = interface_state.password;

    let start_page_props = {
        login:login,
        password:password
    }

    if(!login){
        start_page_props.login_error ="username not provided";
        return  render_start_page(start_page_props);
    }


    if(!password){
        start_page_props.password_error ="password not provided";
        return render_start_page(start_page_props);
    }
    try{
        let token = await create_token(login,password);
    }
    /**@type {HttpError}*/
    catch (error){
        if(error.code === USER_NOT_EXIST){
            start_page_props.login_error =error.message
            return  render_start_page(start_page_props);
        }
        if(error.code === WRONG_PASSWORD){
            start_page_props.password_error =error.message
            return  render_start_page(start_page_props);
        }
    }

}