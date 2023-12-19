

/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
function  go_to_root_page(main_interface, main_state){

    const  headers ={
        'include-tokens':true
    }

    function response_callback(response){
        main_state.page_root_profile = new RootProfileState();
        let root_profile_state = main_state.page_root_profile;

        root_profile_state.username = response.username;
        root_profile_state.new_username = response.username;

        root_profile_state.email = response.email;
        root_profile_state.new_email = response.email;


        root_profile_state.is_root =response.is_root;
        root_profile_state.verified = response.verified;

        response.finite_tokens.forEach((token)=>{
            let new_token = new FiniteTokenState();
            new_token.allow_renew = token.allow_renew;
            new_token.creation = token.creation;
            new_token.expiration = token.expiration;
            new_token.last_update = token.last_update;
            new_token.token_id = token.token_id;
        })

        main_state.turnOnPage(RootProfileState);
        main_interface.render();

    }
    make_authenticated_requisition(main_interface,main_state,GET_SELF_PROPS,
        {headers:headers},
                response_callback,
        )


}