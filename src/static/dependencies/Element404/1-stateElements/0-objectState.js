

class ObjectState{

        constructor(element404,father,name){
                this.element404 = element404;
                this.father = father;
                this.name = name;
                this.state = this.father.state[this.name]
                if (this.state === undefined) {

                        this.state = {}
                        this.father.state[this.name] = this.state
                }
        }


        getPrimitiveState(name,defaultValue){
                return new PrimitiveState(this.element404,this,name,defaultValue)
        }


        getObjectState(name){
                return new ObjectState(this.element404,this,name)
        }

}

