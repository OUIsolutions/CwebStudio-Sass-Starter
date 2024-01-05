



/**
 * @param {string} token
 * @param {Element404} root_div
 * */
async function  home_callback(token,root_div){
     let user_props = undefined;

     try{
          user_props = await get_self_props(token);
     }
     catch (error){
         console.log(error);

     }

     create_common_internal_interface(root_div,user_props);


}