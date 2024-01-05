



/**
 * @param {string} token
 * @param {Element404} main_interface
 * */
async function  home_callback(token,main_interface){

     let user_props = await get_self_props(token);
     console.log(user_props);
}