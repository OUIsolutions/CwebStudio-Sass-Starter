

class PrimitiveState {

    /**
     * @param {Element404} element404
     * @param {Element404 | ObjectState} father
     * @param {string} name
     * @param {any} defaultValue
     */
    constructor(element404,father, name, defaultValue) {
        this.element404 = element404;
        this.father = father;

        this.name = name;
        if (!this.getValue() && defaultValue !== undefined) {
            this.setValue(defaultValue)
        }
    }
    /**
     * @returns {any}
     */
    getValue(){
        return this.father.state[this.name];
    }

    /**
     * @param {any} value
     */
    setValue(value){
        if(!value){
            return
        }

        let converted_value = value;
        if(value.value){
            converted_value = value.value
        }


        this.father.state[this.name] = converted_value;
    }
    /**
     * @param {number} value
     */
    increment (value){
        let old = this.getValue();
        this.setValue(old+value)
    }
    /**
     * @param {number} value
     */
    decrement (value){
        let old = this.getValue();
        this.setValue(old-value)
    }


    /**
     * @param {object} props
     */
    stateInput(props){
        let formated_props = {
            render_focusout:(value)=>{
                this.setValue(value)

            }
        }
        let value = this.getValue();
        if(value){
            formated_props['value'] = value
        }

        if(props){
           for(const key  in props){
               formated_props[key] = props[key];
           }
        }


        this.element404.input(formated_props)
    }
}