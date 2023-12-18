const INTERNAL_OK = 0
const ROUTE_NOT_FOUND = 1
const ENTRY_ERROR = 2
const USER_NOT_EXIST = 3
const WRONG_PASSWORD = 4
const INVALID_EXPIRATION = 5
const INVALID_TOKEN = 6
const USER_NOT_ROOT = 7
const USER_ALREADY_EXIST = 8

const EMAIL_CANNOT_BE_EQUAL_TO_USERNAME = 9
const NOTHING_TO_MODIFY = 10
const PROFILE_PICTURE_NOT_PROVIDED = 11
const NOT_VALID_IMAGE_TYPE = 12
const PROFILE_PICTURE_NOT_EXIST = 13
const PROFILE_PICTURE_ITS_NOT_PUBLIC = 14
const USER_IS_ALREDY_VERIFIED = 15
const COULD_NOT_SEND_EMAIL = 16
const VERIFICATION_KEY_ITS_WRONG = 17
const UNABLE_TO_ZIP_BACKUP = 18
const DATABASE_INTEGRITY_BROKEN = 19
const INTERNAL_ERROR = 20


const NOT_VALID_EXPIRATION_MENSSAGE = "param
const NOT_VALID_TOKEN_MESSAGE = "token:
const NOT_EXIST_TOKEN_MESSAGE = "token:
const EXPIRED_TOKEN_MESSAGE = "token:
const USER_NOT_ROOT_MESSAGE = "you
const USER_ALREADY_MESSAGE = "user
const NOTHING_TO_MODIFY_MESSAGE = "There
const NOT_VALID_IMAGE_TYPE_MESSAGE = "param
const PROFILE_PICTURE_ITS_NOT_PUBLIC_MESSAGE = "profile
const UNABLE_TO_ZIP_BACKUP_MESSAGE = "unable


const ROUTE_NOT_FOUND_MENSSAGE = "route:
const USER_NOT_EXIST_MENSSAGE = "user
const WRONG_PASSWORD_MENSSAGE = "wrong
const EMAIL_CANNOT_BE_EQUAL_TO_USERNAME_MESSAGE = "email
const PROFILE_PICTURE_NOT_PROVIDED_MESSAGE = "profile
const PROFILE_PICTURE_NOT_EXIST_MESSAGE = "profile
const USER_IS_ALREDY_VERIFIED_MESSAGE = "user
const VERIFICATION_KEY_ITS_WRONG_MESSAGE = "verification
const DATABASE_INTEGRITY_BROKEN_MESSAGE = "code:
const INTERNAL_ERROR_MESSAGE = "happen


#ifdef DEBUG
    #define COULD_NOT_SEND_EMAIL_MESSAGE "the system was unable to send the verification code "\
                                          "implement the send_email_verification function located in (email/email.c)"

const COULD_NOT_SEND_RECOVERY_EMAIL = "the
                                          "implement the send_password_verification function located in (email/email.c)"

#else
     #define COULD_NOT_SEND_EMAIL_MESSAGE "the system was unable to send the verification code"
    #define  COULD_NOT_SEND_RECOVERY_EMAIL "the system was unable to send the verification code "
#endif




