

class UsernameOrEmailError{
    /** @type {string} */
    username;
    /** @type {string} */
    message;


    /** @param {string} username
     * @param {string} message
     * */
    constructor(username,message) {
        this.username = username
        this.message = message
    }
}
