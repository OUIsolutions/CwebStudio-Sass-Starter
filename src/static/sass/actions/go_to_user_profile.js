

async function  go_to_user_profile_page( main_state){

    const  headers ={
        'include-tokens':true
    }
    let data = await make_authenticated_requisition(main_state,GET_SELF_PROPS_ROUTE, {headers:headers})
    let profile = main_state.profile;

    profile.username = data.username;
    profile.new_username = data.username;

    profile.email = data.email;
    profile.new_email = data.email;


    profile.is_root =data.is_root;
    profile.verified = data.verified;

    data.finite_tokens.forEach((token)=>{
        let new_token = new FiniteTokenState();
        new_token.allow_renew = token.allow_renew;
        new_token.creation = token.creation;
        new_token.expiration = token.expiration;
        new_token.last_update = token.last_update;
        new_token.token_id = token.token_id;
    })

    main_state.page = 'user_profile'






}