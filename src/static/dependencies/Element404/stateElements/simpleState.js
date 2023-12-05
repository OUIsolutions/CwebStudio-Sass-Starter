

function SimpleState (father,name,defaultValue) {

    this.name = name
    this.father = father

    if (!this.getValue() && defaultValue !== undefined) {
        this.setValue(defaultValue)
    }

}