

/**
 * @param {object} page_props
 * @returns {Element404}
 * */

function  render_list_users(page_props) {
    return createElement404((main_interface)=> {
            main_interface.p(JSON.stringify(page_props));
    })

}