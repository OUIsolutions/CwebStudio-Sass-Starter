

function main(){


    createElement404(function (){
        this.div(null,'aaaaaaaa');

        this.p(null,"the value of state is: "+this.getSimpleState("num",0).getValue());


    }).render(document.getElementById("root"));

}


window.onload = (undefined)=> main()
