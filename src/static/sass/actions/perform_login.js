

 function perform_login(main_state){

    make_authenticated_requisition(main_state,GET_SELF_PROPS_ROUTE,null,(response) => {
        let profile = main_state.profile;
        profile.username = response.username;
        profile.email = response.email;
        profile.verified =response.verified;
        profile.is_root = response.root;
        if(profile.is_root){
            list_users(main_state);
            return;
        }
        go_to_user_profile_page(main_state);
    })


 }