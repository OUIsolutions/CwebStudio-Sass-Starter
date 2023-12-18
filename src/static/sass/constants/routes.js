




//===========================API============================================================
const API_START "/api"
//public
const CREATE_TOKEN_ROUTE "/api/public/create_token"
const GET_PUBLIC_PROFILE_PICTURE_ROUTE "/api/public/get_public_profile_picture"
const VERIFY_EMAIL_ROUTE "/api/public/verify_email"
const DESCRIBE_ROUTE "/api/public/describe"
const SEND_RECOVERY_PASSWORD_ROUTE "/api/public/recover_password"
//public_point

//debug
const END_ROUTE "/api/end"
const STATIC_CHANGED "/api/changed"

//user
const UPDATE_TOKEN_ROUTE "/api/user/update_token"
const REMOVE_TOKEN_ROUTE "/api/user/remove_token"
const REMOVE_ALL_FINITE_TOKENS_ROUTE "/api/user/remove_all_finite_tokens"
const REMOVE_ALL_INFINITE_TOKENS_ROUTE "/api/user/remove_all_infinite_tokens"
const REMOVE_ALL_TOKENS_ROUTE "/api/user/remove_all_tokens"
const REMOVE_TOKEN_BY_ID "/api/user/remove_token_by_id"
const GET_SELF_PROPS_ROUTE "/api/user/get_self_props"
const MODIFY_SELF_PROPS_ROUTE "/api/user/modify_self_props"
const SELF_REMOVE_ROUTE "/api/user/self_remove"
const UPLOAD_PROFILE_PICTURE_ROUTE "/api/user/upload_profile_picture"
const GET_PRIVATE_PROFILE_PICTURE_ROUTE "/api/user/get_private_profile_picture"
const SEND_VERIFICATION_EMAIL_ROUTE "/api/user/send_verification_email"
//user_point

//root
const CREATE_USER_ROUTE "/api/root/create_user"
const LIST_USERS_ROUTE "/api/root/list_users"
const REMOVE_USER_ROUTE "/api/root/remove_user"
const MODIFY_USER_PROPS_ROUTE "/api/root/modify_user_props"
const GET_USER_PROPS_ROUTE "/api/root/get_user_props"
const DOWNLOAD_DATABASE_ROUTE "/api/root/download_database"
//root_point