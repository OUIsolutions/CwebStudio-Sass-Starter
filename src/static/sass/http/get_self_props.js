
/**
 * @typedef {object} SelfProps
 * @property {string} username
 * @property {string} creation
 * @property {string} last_update
 * @property
 * */


/**
 * @param {string} token
 * @return {SelfProps}
 * */
async  function get_self_props(token){

    return await  make_authenticated_requisition(token,GET_SELF_PROPS_ROUTE);

}