
/**
 * @typedef {object} TokenOrError
 * @property {string} token
 * @property {HttpError} error
 * @property {boolean} error_happen
 * */

/**
 * @param {string} username_or_email
 * @param {string} password
 * @returns{TokenOrError}
 * */
async function create_token(username_or_email,password){

    let request = await fetch(CREATE_TOKEN_ROUTE,{
          headers:{
              [LOGIN]:username_or_email,
              [PASSWORD_ENTRE]:password
          }
      });


      let parsed_in_json = await  request.json();

      let result = {
          token:undefined,
          error:undefined,
          error_happen:false
      };


      if(parsed_in_json[CODE_KEY] !== INTERNAL_OK){
          /**@type {HttpError}*/
          result.error = parsed_in_json;
          result.error_happen = true;
          return result;
      }
      result.token = parsed_in_json[TOKEN_KEY];

      return result;

}