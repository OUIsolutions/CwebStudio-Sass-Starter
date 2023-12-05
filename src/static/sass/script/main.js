

function main(){


    createElement404(function (){
        this.div(null,'aaaaaaaa');

        this.p(null,"the value of state is: "+this.getSimpleState("num",0).getValue());

        this.button({click:()=>{
                let num = this.getSimpleState("num",0);
                num.setValue(num.getValue()+1);
                this.render()
            }},"add")


    }).render(document.getElementById("root"));

}


window.onload = (undefined)=> main()
