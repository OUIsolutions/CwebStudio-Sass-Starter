
/**
 *
 * @param {MainState} state
 * */
 async  function perform_login(state){

   let response = await make_authenticated_requisition(state,GET_SELF_PROPS_ROUTE);

     let profile = state.profile;
     profile.username = response.username;
     profile.email = response.email;
     profile.verified =response.verified;
     profile.is_root = response.root;
     if(profile.is_root){
         await list_users(state);
         return;
     }

 }