
class BackendBridge{

    constructor(){
        this.session_timeout = 30;
        this.token = sessionStorage.getItem(TOKEN)
        this.conected = false
        if(this.token){
            
        }
    }

    update_session(){
        fetch(UPDATE_SESSION,{
            headders:{
                TOKEN:this.token
            }
        })
        .then(data => data.json())
        .then(response => {
            if(response.code == )
        })
    }

    create_session(username,password){

    }



}