
/**
 *
 * @param {MainState} state
 * */
 async  function perform_login(state){

   state.profile = await get_self_props(state);
     if(state.profile.root){
         await list_users(state);
         return;
     }

     let a  = 20;
 }