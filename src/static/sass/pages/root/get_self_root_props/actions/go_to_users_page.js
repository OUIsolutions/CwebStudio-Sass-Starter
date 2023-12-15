

/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
function  go_to_root_page(main_interface, main_state){

    const  headers ={
        'include-tokens':true
    }

    function response_callback(response){
        console.log(response);
    }
    make_autenticated_requisition(main_interface,main_state,GET_SELF_PROPS,
        {headers:headers},
                response_callback,
        )


}