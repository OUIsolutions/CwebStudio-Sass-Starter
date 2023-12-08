

class PrimitiveState {


    constructor(father, name, defaultValue) {
        this.name = name
        this.father = father

        if (!this.getValue() && defaultValue !== undefined) {
            this.setValue(defaultValue)
        }
    }
    getValue(){
        return this.father[this.name];
    }

    setValue(value){
        this.father[this.name] = value;
    }
    increment (value){
        let old = this.getValue();
        this.setValue(old+value)
    }

    decrement (value){
        let old = this.getValue();
        this.setValue(old-value)
    }
}