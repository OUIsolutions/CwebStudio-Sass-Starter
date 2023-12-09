

class UsernameOrEmailError{
    /** @type {boolean} */
    exist
    /** @type {string} */
    username;
    /** @type {string} */
    message;


    /** @param {string} username
     * @param {string} message
     * */
    constructor() {
        this.exist = false;
    }

}
