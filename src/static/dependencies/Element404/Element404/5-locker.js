
Element404.prototype.lock=function( ){
    this.locked = true
    this.root.innerHTML = ''
    this.render()


}

Element404.prototype.unlock=function( ){

    this.locked = false
    this.render()

}