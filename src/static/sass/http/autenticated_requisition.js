

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

    /**@type {object}*/
    let parsed_in_json = await  request.json();



    if(parsed_in_json[CODE_KEY] !== INTERNAL_OK  && parsed_in_json[CODE_KEY]){
        /**@type {HttpError}*/
        throw  parsed_in_json
    }

    return parsed_in_json;
}
