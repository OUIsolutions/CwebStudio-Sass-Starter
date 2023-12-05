

class ObjectState extends  SimpleState{

    constructor() {
        super();
        this.state ={}
    }

    private_setState = function (name,state){
        this.state[name] = state;
        this.father.private_setState()
    }



}