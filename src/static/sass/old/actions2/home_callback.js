



/**
 * @param {object} interface_state
 * */
async function  home_callback(interface_state){
    interface_state.user_props = await get_self_props();
    return render_list_users(interface_state);

}