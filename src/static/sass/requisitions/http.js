
function go_to_start_page(main_state){
    main_state.page = 'start';
    main_loop();
}

function go_to_main_page_removing_token(main_interface,main_state){
    sessionStorage.removeItem(TOKEN_KEY);
    go_to_start_page(main_interface,main_state);
}


function  make_authenticated_requisition(
    main_state,
    route,
    params,
    callback){
    let token =  sessionStorage.getItem(TOKEN_KEY);
    if(!token){
        go_to_start_page(main_state);
        return;
    }

    //fetch and cach any error 
    if(!params){
        params = {
        };
    }
    if(!params.headers){
        params.headers = {};
    }

    params.headers.token =token

    
    fetch(route,params)
    .then(response => {
        let invalid_responses = [500,404]
        if(invalid_responses.includes(response.code)){
            go_to_main_page_removing_token(main_state);
            return;
        }
        return response;
    })
    .then(response => response.json())
    .then(response => {
        if(response.code === INVALID_TOKEN){
            go_to_main_page_removing_token(main_state);
            return;
        }
        callback(response);
        main_loop();

    })
    
}