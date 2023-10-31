#define INTERNAL_OK 0
#define  ROUTE_NOT_FOUND 1
#define ENTRY_ERROR 2
#define USER_NOT_EXIST 3
#define  WRONG_PASSWORD 4
#define INVALID_EXPIRATION 5
#define INVALID_TOKEN 6
#define USER_NOT_ROOT 7
#define USER_ALREADY_EXIST 8
#define EMAIL_CANNOT_BE_EQUAL_TO_USERNAME 9
#define NOTHING_TO_MODIFY 10
#define PROFILE_PICTURE_NOT_PROVIDED 11
#define NOT_VALID_IMAGE_TYPE 12
#define PROFILE_PICTURE_NOT_EXIST 13
#define PROFILE_PICTURE_ITS_NOT_PUBLIC 14
#define USER_IS_ALREDY_VERIFIED 15
#define COULD_NOT_SEND_EMAIL 16
#define VERIFICATION_KEY_ITS_WRONG 17

#define NOT_VALID_EXPIRATION_MENSSAGE "param #reference# at headers/paramns is not a valid expiration time use -1 for infinity tokens or 1 or more for finite tokens"
#define NOT_VALID_TOKEN_MESSAGE "token: %s its invalid"
#define NOT_EXIST_TOKEN_MESSAGE  "token: %s not exist"
#define EXPIRED_TOKEN_MESSAGE  "token: %s its expired"
#define USER_NOT_ROOT_MESSAGE "you must be root to acess these route"
#define USER_ALREADY_MESSAGE "user %s already exist"
#define NOTHING_TO_MODIFY_MESSAGE "There is nothing to modify at headers/params"
#define NOT_VALID_IMAGE_TYPE_MESSAGE "param #image# its not an valid content type\n valids: #valids#"
#define PROFILE_PICTURE_ITS_NOT_PUBLIC_MESSAGE "profile picture its not public"


#define ROUTE_NOT_FOUND_MENSSAGE "route: %s its not valid"
#define USER_NOT_EXIST_MENSSAGE "user %s not found"
#define WRONG_PASSWORD_MENSSAGE "wrong password"
#define EMAIL_CANNOT_BE_EQUAL_TO_USERNAME_MESSAGE "email cannot be equal to username"
#define PROFILE_PICTURE_NOT_PROVIDED_MESSAGE "profile picture not provided"
#define PROFILE_PICTURE_NOT_EXIST_MESSAGE "profile picture not exist"
#define USER_IS_ALREDY_VERIFIED_MESSAGE "user is already verifyid"
#define  VERIFICATION_KEY_ITS_WRONG_MESSAGE  "verification key:%s its wrong"
#ifdef DEBUG
    #define COULD_NOT_SEND_EMAIL_MESSAGE "the system was unable to send the verification code "\
                                          "implement the send_email_verification function located in (email/email.c)"
#else
 #define COULD_NOT_SEND_EMAIL_MESSAGE "the system was unable to send the verification code"
#endif
