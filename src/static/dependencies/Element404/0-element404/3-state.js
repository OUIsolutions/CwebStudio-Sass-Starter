


Element404.prototype.getPrimitiveState = function(name,defaultValue){
    return new PrimitiveState(this,name,defaultValue)

}

Element404.prototype.getObjectState = function(name){
    return new ObjectState(this,this,name)

}


Element404.prototype.private_setState = function (name,state){
    this.state[name] = state;


}

