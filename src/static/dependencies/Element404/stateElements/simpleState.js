

class State{
    
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

    getState(name,defaultValue){
        return new State(this.element404,name,defaultValue,this)
    }



    setValue(value){

        

        this.element404.state[this.name] =private_Element404_convert_values(value)
    }




}