
/**
 * @typedef Element404
 * @type {object}
 * @property {HTMLElement} root - the root element
 * @property {started} bool - if its started or nt
 * @property {object} state - the state of the element
 */
 function Element404(generator){
        this.root = document.createDocumentFragment();
        this.started = false
        this.generator = generator
        this.state = {}
}

function  createElement404(generator){
     return new Element404(generator)
}

