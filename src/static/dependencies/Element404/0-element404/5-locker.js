
Element404.prototype.lock=function( ){
    this.locked = true
   
    document.onkeydown = function (e) {
        return false;
    }

    this.render()


}

Element404.prototype.unlock=function( ){

    this.locked = false
}