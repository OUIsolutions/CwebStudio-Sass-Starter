/**
 * @param {MainState} main_state
 * */
function go_to_start_page(main_state){
    main_state.page = 'start';
    throw "login error";
}
/**
 * @param {MainState} main_state
 * */
function go_to_main_page_removing_token(main_state){
    sessionStorage.removeItem(TOKEN_KEY);
    go_to_start_page(main_state);
}


/**
 *
 * @param {MainState} main_state
 * @param {string} route
 * @param {object} params
 * @returns  {object}
 * */
async function  make_authenticated_requisition(
    main_state,
    route,
    params=null){

    let token =  sessionStorage.getItem(TOKEN_KEY);
    if(!token){
        go_to_start_page(main_state);
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

    
    let response = await fetch(route,params);

    let invalid_responses = [500,404]
    if(invalid_responses.includes(response.code)){
        go_to_main_page_removing_token(main_state);
    }
    let data = await  response.json();

    if(data.code === INVALID_TOKEN){
        go_to_main_page_removing_token(main_state);
    }

    return data;
}