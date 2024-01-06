
/**
 * @typedef ResponseOrRedirect
 * @property {object} response
 * @property {boolean} were_redirect
 * */

/**
 * @param {Element404} root_div
 * @param {function} requisiton_function
 * @returns ResponseOrRedirect
 * */
async function make_requisiton_and_redirect_to_home_if_expired_token(root_div,requisiton_function){
    let result = {
        response:undefined,
        were_redirect:false
    }

    result.response = await requisiton_function();


    if(result.response.code === INVALID_TOKEN){
        sessionStorage.removeItem(TOKEN_ENTRE);
        render_start_page(root_div);
        result.were_redirect = true;
    }

    return result;

}