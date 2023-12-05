

function main(){


    createElement404(function (){
        this.div(null,'aaaaaaaa');

        this.p(null,"the value of state is: ");

        this.button({click:()=>{

                let num = this.getSimpleState("num",0);
                num.setValue(num.getValue()+1);

            }},"add")


    }).render(document.getElementById("root"));

}


window.onload = (undefined)=> main()
