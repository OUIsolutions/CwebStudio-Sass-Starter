
class LoginProps{

    /** @type {string} */
    username_or_email= undefined;
    /** @type {UsernameOrEmailError} */
    username_or_email_error =new UsernameOrEmailError();

    /** @type {string} */
    password;
    /** @type {PasswordError} */
    password_error =new PasswordError();


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