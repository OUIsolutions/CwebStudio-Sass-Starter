
 function Element404(generator){
        this.root = document.createDocumentFragment();
        this.generator = generator
        this.state = {}
        this.locked = false
 }


function  createElement404(generator){
     return new Element404(generator)
}

