



/**
 * Creates a token
 * @param {Element404} main_interface
 * @param {string} login
 * @param {string} password
 */
function create_token(main_interface, login,password){
    let headers = {
        login: login,
        password:password
    }
    fetch(CREATE_TOKEN,{headers:headers})
    .then(data => data.json())
    .then(data =>{
        console.log(data)
    })
}