
class LoginProps{

    /** @type {string} */
    username_or_email;
    /** @type {UsernameOrEmailError} */
    username_or_email_error;

    /** @type {string} */
    password;

    /** @returns {boolean} */
    able_to_create_token(){
        if(!this.username_or_email){
            return false;
        }

        if(!this.password){
            return  false;
        }

        if(this.username_or_email_error){
            if(this.username_or_email_error.username === this.username_or_email){
                return false;
            }
        }
        return  true;
    }



}