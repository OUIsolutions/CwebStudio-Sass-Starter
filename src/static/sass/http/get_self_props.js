
/**
 * @typedef {object} SelfProps
 * @property {string} username
 * @property {string} creation
 * @property {string} last_update
 * @property
 * */
{"user_props":{"username":"rootRR","creation":"2023-12-15 07:25:57","last_update":"2023-12-22 05:37:37","email":"root","verified":true,"root":true}}
async  function get_self_props(){

    return await  make_autenticated_requisition(GET_SELF_PROPS_ROUTE);

}