

class ObjectState {
    
    constructor(element404,name,defaultValue,father){
        this.name = name
        this.element404 = element404
        this.father = father
        if(!this.getValue()&& defaultValue !== undefined){
            this.setValue(defaultValue)
        }


    }
    getValue(){
        return  this.element404.state[this.name]
    }

    subState(name,defaultValue){
        return new SimpleState(this.element404,name,defaultValue,this)
    }

    setValue(value){

        if(this.father){
            this.father.setValue(this.name,)
        }

        this.element404.state[this.name] =private_Element404_convert_values(value)
    }




}