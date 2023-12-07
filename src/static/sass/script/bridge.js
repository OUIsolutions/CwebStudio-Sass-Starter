
class BackendBridge{

    constructor(){
    }

    

    get_self_props(){
        let token = sessionStorage.getItem(TOKEN);
        if(!token){
            throw 
        }
    }

    create_session(username,password){

    }



}