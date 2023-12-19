
/**
 *
 * @param {MainState} state
 * */
 async  function perform_login(state){

   state.profile = get_self_props(state);

     if(state.profile.root){
         await list_users(state);
         return;
     }

     let a  = 20;
 }