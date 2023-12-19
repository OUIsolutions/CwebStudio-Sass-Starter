


function  list_users(main_state){
    function list_users(response){
       main_state.page_root_users = {
           users:[]
       };

       response.forEach((user)=>{
            let created_user = {}
           created_user.username =user.username;
           created_user.email = user.email;
           created_user.last_update = user.last_update;
           created_user.root = user.root;
           created_user.verified = user.verified;
           main_state.page_root_users.users.unshift(created_user);
       })

        main_state.page = 'users';
    }

    make_authenticated_requisition(main_state,LIST_USERS_ROUTE,null,list_users)


}