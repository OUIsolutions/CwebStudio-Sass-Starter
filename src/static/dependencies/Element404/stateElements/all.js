
function  private_StateElements_getValue(){
    return  this.father.state[this.name]
}

ObjectState.prototype.getValue = private_StateElements_getValue
PrimitiveState.prototype.getValue = private_StateElements_getValue

function  private_StateElements_setValue(value){
    let converted_value = value
    if(value.value){
        converted_value = value.value
    }

    this.father.private_setState(this.name,converted_value)
}

ObjectState.prototype.setValue = private_StateElements_setValue
PrimitiveState.prototype.setValue = private_StateElements_setValue


