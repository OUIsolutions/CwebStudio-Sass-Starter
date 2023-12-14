
class LoginProps{

    /** @type {string} */
    username_or_email= undefined;
    /** @type {LoginError} */
    username_or_email_error =new LoginError();

    /** @type {string} */
    password;
    /** @type {LoginError} */
    password_error =new LoginError();


}