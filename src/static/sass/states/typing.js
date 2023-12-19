


/**
 *   @typedef {Object} LoginProps
 *   @property {string || undefined} username_or_email
 *   @property {string || undefined} username_or_email_error
 *   @property {string || undefined} password
 *   @property {string || undefined} password_error
 * */


/**
 * @typedef {Object} User
 * @property {string || undefined} username;
 * @property {string || undefined} email;
 * @property {boolean || undefined} verified;
 * @property {boolean || undefined} last_update;
 * @property {boolean || undefined} is_root
 * */


/**
 * @typedef {Object} MainState
 * @property {LoginProps} login_props
 * @property {Profile || undefined} profile
 * @property {string || undefined} page
 * @property {Array<User>} users
 * */
