

/**
 * Creates an Primitive state
 * @param {string} name The name of the state
 * @param {any} defaultValue The the default value
 * @returns {PrimitiveState}
 */
Element404.prototype.getPrimitiveState = function(name,defaultValue){
    return new PrimitiveState(this,this,name,defaultValue)
}

/**
 * Creates a Object state
 * @param {string} name The name of the state
 * @returns {ObjectState}
 */
Element404.prototype.getObjectState = function(name){
    return new ObjectState(this,this,name)

}


Element404.prototype.private_setState = function (name,state){
    this.state[name] = state;


}

