
/**
 * @param {MainState} state
 * @returns {Profile}
 * */
async function get_self_props(state){
    return await make_authenticated_requisition(state,GET_SELF_PROPS_ROUTE);
}