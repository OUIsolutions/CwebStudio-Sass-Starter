
class LoginProps{

    /** @type {string} */
    username_or_email= undefined;
    /** @type {LoginElementError} */
    username_or_email_error =new LoginElementError();

    /** @type {string} */
    password;
    /** @type {LoginElementError} */
    password_error =new LoginElementError();


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
        if(this.password_error){
            if(this.password_error.password === this.password){
                return false;
            }
        }
        
        return  true;
    }

}