

class SimpleState {

    constructor(father,name,defaultValue){
        this.name = name
        this.father = father
        if(!this.getValue()&& defaultValue !== undefined){
            this.setValue(defaultValue)
        }
    }

    getValue(){
        return  this.father.state[this.name]
    }

    setValue(value){
        let converted_value = value
        if(this.getValue()){
            value = value.value
        }
        this.father.private_setState(this.name)
    }


}