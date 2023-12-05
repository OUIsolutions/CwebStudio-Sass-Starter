

class ObjectState {

    constructor(father,name){
        this.name = name
        this.father = father
    }

    getValue(){
        return  this.father.state[this.name]
    }

    setValue(value){
        let converted_value = value
        if(this.getValue()){
            value = value.value
        }
        this.father.private_setState(this.name,value)
    }

    private_setState = function (name,state){
        this.state[name] = state;
        this.father.private_setState(name,state)
    }

    
    getSimpleState = function(name,defaultValue){
        return new SimpleState(this,name,defaultValue)
    }

    getObjectState = function(name){
        return new ObjectState(this,name)
    }

}