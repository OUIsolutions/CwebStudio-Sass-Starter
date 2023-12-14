

class LoginError {
    /** @type {boolean} */
    exist = false

    /** @type {string} */
    message = undefined;

    resset(){
        this.exist = false;
        this.message = false;
    }
}
