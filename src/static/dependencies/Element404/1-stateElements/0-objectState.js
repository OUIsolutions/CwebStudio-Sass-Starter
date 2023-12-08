

class ObjectState{

        constructor(father,name){
                this.name = name
                this.father = father
                this.state = this.father[this.name]

                if (!this.state) {
                        this.state = {}
                        father[name] = this.state
                }
        }


        getPrimitiveState(name,defaultValue){
                return new PrimitiveState(this,name,defaultValue)
        }


        getObjectState(name){
                return new ObjectState(this,name)
        }

}

