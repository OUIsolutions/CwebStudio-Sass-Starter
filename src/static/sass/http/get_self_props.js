
/**
 * @typedef {object} SelfProps
 * @property {string} username
 * @property {string} creation
 * @property {string} last_update
 * @property
 * */
async  function get_self_props(){

    return await  make_autenticated_requisition(GET_SELF_PROPS_ROUTE);

}