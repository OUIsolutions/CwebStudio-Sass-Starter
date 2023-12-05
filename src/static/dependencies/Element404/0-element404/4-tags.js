




Element404.prototype.input=function(props){
    this.create('input',props,null)
}


/**
 * Creates an Div
 * @param {object} props The object props
 * @param {fuction | string} content the internal content
 */
Element404.prototype.div=function(props,content){
    this.create('div',props,content)
}


/**
 * Creates an paragraph
 * @param {fuction | string} content the internal content
 */
Element404.prototype.p=function(props,content){
    this.create('p',props,content)
}


/**
 * Creates an h1
 * @param {object} props The object props
 * @param {fuction | string} content the internal content
 */
Element404.prototype.h1=function(props,content){
    this.create('h1',props,content)
}



/**
 * Creates an g2
 * @param {object} props The object props
 * @param {fuction | string} content the internal content
 */
Element404.prototype.h2=function(props,content){
    this.create('h2',props,content)
}



/**
 * Creates an H3
 * @param {object} props The object props
 * @param {fuction | string} content the internal content
 */
Element404.prototype.h3=function(props,content){
    this.create('h3',props,content)
}

Element404.prototype.h4=function(props,content){
    this.create('h4',props,content)
}

Element404.prototype.h5=function(props,content){
    this.create('h5',props,content)
}



Element404.prototype.text=function(message){
    this.create(null,null,message)
}


Element404.prototype.button=function(props,content){
    this.create('button',props,content)
}

Element404.prototype.br=function(){
    this.create('br')
}
