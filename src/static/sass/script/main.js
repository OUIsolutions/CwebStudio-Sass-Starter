

function main(){


    createElement404(function (){
        this.div(null,'aaaaaaaa');

        this.p(null,"the value of state is: "+this.getPrimitiveState("num",0).getValue());

        this.button({click:()=>{
                this.increment(1);
                this.render();
            }},"add")

    }).render(document.getElementById("root"));

}


window.onload = (undefined)=> main()
