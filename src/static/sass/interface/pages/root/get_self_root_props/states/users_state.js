
class RootProfileState {

    /** @type {boolean} */
    current = false;
    /** @type {boolean} */

    /** @type {boolean} */
    is_root;
    /** @type {boolean} */
    verified;
    /** @type {string} */

    username;
    /** @type {string} */
    new_username;
    /** @type {string} */
    username_error;


    /** @type {string} */
    email;
    /** @type {string} */
    new_email;
    /** @type {string} */
    email_error;

    /** @type {string} */
    old_password;
    /** @type {string} */
    old_password_error;
    /** @type {string} */
    password;
    /** @type {string} */
    new_password;
    /** @type {string} */
    password_error;

    /** @type {string} */
    profile_picture_url;

    /** @type {Array<FiniteTokenState>} */
    finite_tokens =[]

}