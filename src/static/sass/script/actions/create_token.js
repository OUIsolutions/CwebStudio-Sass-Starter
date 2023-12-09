



/**
 * Creates a token
 * @param {Element404} main_interface
 * @param {string} login
 * @param {string} password
 */
function create_token(main_interface, login,password){
    let headers = {
        login: login,
        password:password
    }
    fetch(CREATE_TOKEN,{headers:headers})
    .then(data => data.json())
    .then(data =>{

        let page_props =main_interface.getObjectState(PAGE_PROPS);

        if(data.code == USER_NOT_FOUND){
            let username_error =page_props.getPrimitiveState(USERNAME_ERROR)
            username_error.setValue(data.mensage);
        }



        main_interface.render()
    })


}