
function make_requisition(route,props){

    /**@type {object}*/
    let result = undefined;
    fetch(route,props)
        .then(response => response.json())
            .then(data => result =data)
    while (!result){}
    return result;

}