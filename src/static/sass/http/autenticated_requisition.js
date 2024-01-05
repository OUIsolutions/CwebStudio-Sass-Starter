

/**
 * @param {string} token
 * @param {string} route
 * @param {object} props
 * @return {object}
 * */

async  function make_authenticated_requisition(token,route, props=undefined){
    let formatted_props ={};

    for( let key in props){
        formatted_props[key] =props[key];
    }
    if(!formatted_props.headers){
        formatted_props.headers = {};
    }
    formatted_props.headers[TOKEN_KEY] = token;


    let request = await  fetch(route,formatted_props)

    return await request.json();
}
