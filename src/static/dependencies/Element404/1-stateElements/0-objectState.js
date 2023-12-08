

function ObjectState (father,name){
        this.name = name
        this.father = father
        if (!this.getValue() ) {
                this.state = {}
                father[name] = this.state
                this.setValue({})
        }

}



ObjectState.prototype.private_setState = function (name,state){
        this.state[name] = state;
        this.father.private_setState(name,state)
}


ObjectState.prototype.getPrimitiveState = function(name,defaultValue){
        return new PrimitiveState(this,name,defaultValue)
}

ObjectState.prototype.getObjectState = function(name){
        return new ObjectState(this,name)
}

