
/**
 * Returns the sum of all numbers passed to the function.
 * @param {string } tag The tag of element
 * @param {object} props The object props
 * @param {fuction | string} content the internal content
 */
Element404.prototype.create=function(tag,props,content){


    if (this.started === false){

        this.generator = () => {         
            
            let element = document.createElement(tag)
            this.root = element
            this.generate_component_reference(element,props,content)
        } 
        this.started = true
        return
    }


    this.sub_component(tag,props,content)
    
}


/**
 * Returns the sum of all numbers passed to the function.
* @param {HTMLElement=} target The target to render
*/
Element404.prototype.render= function(target=null){
    if(target){
        this.target = target
    }

    if(!this.target){
        return;
    }

    this.target.innerHTML = ''
    this.generator()
    this.target.appendChild(this.root)
}

