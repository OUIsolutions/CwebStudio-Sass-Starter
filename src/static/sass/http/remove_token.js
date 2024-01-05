
async function http_remove_token(token){
    return await make_authenticated_requisition(token,REMOVE_TOKEN_ROUTE,{
        TOKEN_ENTRE:token
    });
}