


Element404.prototype.getSimpleState = function(name,defaultValue){
    return new SimpleState(this,name,defaultValue)
}

Element404.prototype.getObjectState = function(name){
    return new ObjectState(this,name)
}


Element404.prototype.private_setState = function (name,state){
    this.state[name] = state;
    this.render()
}

