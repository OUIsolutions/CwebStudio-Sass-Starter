
/**
 * Creates a token
 * @param {Element404} main_interface
 *@param {MainState} main_state
 */
 function efetuate_login(main_interface, main_state,token){

    fetch(GET_SELF_PROPS,{headers:{token:token}})
    .then(data => data.json())
    .then(data =>{
        console.log(data)
    })
    
 }