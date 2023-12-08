

class ObjectState{

        constructor(father,name){
                this.father = father
                this.name = name
                this.state = this.father.state[this.name]
                if (this.state === undefined) {

                        this.state = {}
                        this.father.state[this.name] = this.state
                }
        }


        getPrimitiveState(name,defaultValue){
                return new PrimitiveState(this,name,defaultValue)
        }


        getObjectState(name){
                return new ObjectState(this,name)
        }

}

