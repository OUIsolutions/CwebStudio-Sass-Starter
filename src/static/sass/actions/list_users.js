

/**
 *
 * @param {MainState} state
 * */
async function  list_users(state){

    let data = await make_authenticated_requisition(state,LIST_USERS_ROUTE);
    state.users =[]

    data.forEach((user)=>{
        let created_user = {}
        created_user.username =user.username;
        created_user.email = user.email;
        created_user.last_update = user.last_update;
        created_user.root = user.root;
        created_user.verified = user.verified;
        main_state.users.unshift(created_user);
    })
    state.page = 'users';


}