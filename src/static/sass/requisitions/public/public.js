
/**
*   @param {string} login
 *  @param {string} password
 *  @returns {TokenAttribute}
* */
async function http_create_token(login,password){
    let headers = {
        login: login,
        password:password
    }
    let response = await  fetch(CREATE_TOKEN_ROUTE,{headers:headers});
    return await response.json();

}