




//===========================API============================================================
#define  API_START "/api"
//public
#define CREATE_TOKEN_ROUTE "/api/public/create_token"
#define GET_PUBLIC_PROFILE_PICTURE_ROUTE "/api/public/get_public_profile_picture"
#define VERIFY_EMAIL_ROUTE "/api/public/verify_email"
#define DESCRIBE_ROUTE "/api/public/describe"
#define SEND_RECOVERY_PASSWORD_ROUTE "/api/public/recover_password"
//public_point

//debug
#define END_ROUTE "/api/end"
#define STATIC_CHANGED "/api/changed"

//user
#define REMOVE_TOKEN_ROUTE "/api/user/remove_token"
#define REMOVE_ALL_FINITE_TOKENS_ROUTE "/api/user/remove_all_finite_tokens"
#define REMOVE_ALL_INFINITE_TOKENS_ROUTE "/api/user/remove_all_infinite_tokens"
#define REMOVE_ALL_TOKENS_ROUTE "/api/user/remove_all_tokens"
#define REMOVE_TOKEN_BY_ID "/api/user/remove_token_by_id"
#define GET_SELF_PROPS_ROUTE  "/api/user/get_self_props"
#define MODIFY_SELF_PROPS_ROUTE "/api/user/modify_self_props"
#define SELF_REMOVE_ROUTE "/api/user/self_remove"
#define UPLOAD_PROFILE_PICTURE_ROUTE "/api/user/upload_profile_picture"
#define GET_PRIVATE_PROFILE_PICTURE_ROUTE "/api/user/get_private_profile_picture"
#define SEND_VERIFICATION_EMAIL_ROUTE "/api/user/send_verification_email"
//user_point

//root
#define CREATE_USER_ROUTE "/api/root/create_user"
#define LIST_USERS_ROUTE "/api/root/list_users"
#define REMOVE_USER_ROUTE "/api/root/remove_user"
#define MODIFY_USER_PROPS_ROUTE "/api/root/modify_user_props"
#define GET_USER_PROPS_ROUTE "/api/root/get_user_props"
#define DOWNLOAD_DATABASE_ROUTE "/api/root/download_database"
//root_point