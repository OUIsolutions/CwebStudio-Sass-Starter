
async function  logout_callback(token,root_div){
    let result = await http_remove_token(token);
    sessionStorage.removeItem(TOKEN_ENTRE);
    render_start_page(root_div);
}