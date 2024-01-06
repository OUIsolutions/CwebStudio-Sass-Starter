



/**
 * @param {string} token
 * @param {Element404} root_div
 * */
async function  home_callback(token,root_div){
     let user_props_or_error = await make_requisiton_and_redirect_to_home_if_expired_token(
         root_div,
         async ()=>  get_self_props(token)
     );

     if(user_props_or_error.were_redirect){
          return;
     }


     create_common_internal_interface(token,root_div,user_props_or_error.response);


}