


async  function make_autenticated_requisition(route,props){
    let formated_props ={};

    for( let key in props){
        formated_props[key] =props[key];
    }
    if(!formated_props.headers){
        formated_props.headers = {};
    }
    formated_props.headers[TOKEN_KEY] = sessionStorage.getItem(TOKEN_KEY);


    let request = await  fetch(route,formated_props)

    /**@type {object}*/
    let parsed_in_json = await  request.json();



    if(parsed_in_json[CODE_KEY] !== INTERNAL_OK  && parsed_in_json[CODE_KEY]){
        /**@type {HttpError}*/
        throw  parsed_in_json
    }

    return parsed_in_json;
}