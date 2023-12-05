

function PrimitiveState (father, name, defaultValue) {

    this.name = name
    this.father = father

    if (!this.getValue() && defaultValue !== undefined) {
        this.setValue(defaultValue)
    }
}


PrimitiveState.prototype.increment = function (value){
    let old = this.getValue();
    this.setValue(old+value)
}



PrimitiveState.prototype.decrement = function (value){
    let old = this.getValue();
    this.setValue(old-value)
}
