


/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
function  add_user(main_interface, main_state) {
    let page_props = main_state.page_add_user;
    page_props.email_error = undefined;
    page_props.password_error = undefined;
    page_props.username_error= undefined;

    if(!page_props.username){
        page_props.username_error = 'username must be provided';
        main_interface.render();
        return;
    }
    if(!page_props.email){
        page_props.email_error = 'email must be provided';
        main_interface.render();
        return;
    }

    if(page_props.email.length <=10){
        page_props.email_error = 'email must be higher than 10'
        main_interface.render();
        return;
    }



    if(!page_props.password || !page_props.new_password){
        page_props.password_error = 'password must be provided';
        main_interface.render();
        return;
    }


    if(page_props.password.length <=10){
        page_props.password_error = 'password must be higher than 10';
        main_interface.render();
        return;
    }

    if(page_props.password !== page_props.new_password){
        page_props.password_error = 'password must be equal';
        main_interface.render();
        return;
    }


    let headers = {
        username:page_props.username,
        email:page_props.email,
        password:page_props.password
    }


    make_autenticated_requisition(main_interface,main_state,'/api/root/create_user', {headers:headers},(response)=>{
       alert(response.message);
       if(response.code === 0){
           go_to_users_page(main_interface,main_state);
       }
    })


}