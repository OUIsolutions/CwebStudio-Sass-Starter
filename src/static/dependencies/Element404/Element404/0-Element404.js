/**
 * @param {function} generator 
 */
 function Element404(generator){
        /** @type {DocumentFragment} */
        this.root = document.createDocumentFragment();
        /** @type {function} */
        this.generator = ()=>{generator(this)}
        /** @type {boolean} */ 
        this.locked = false
 }

 
/**
 * @param {function} generator
 */
function  createElement404(generator){
     return new Element404(generator)
}

