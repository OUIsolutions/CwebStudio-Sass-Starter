

/**
 * @param {string} username_or_email
 * @param {string} password
 * @throws {HttpError}
 * @returns{string}
 * */
async function create_token(username_or_email,password){
      let request = await fetch(CREATE_TOKEN_ROUTE,{
          headers:{
              LOGIN:username_or_email,
              PASSWORD_ENTRE:password
          }
      });


      let parsed_in_json = await  request.json();
      if(parsed_in_json[CODE_KEY] !== INTERNAL_OK){
          /**@type {HttpError}*/
          throw  parsed_in_json
      }
      /**@type {string}*/
      return parsed_in_json[TOKEN_KEY];
}