

function main(){


    createElement404(function (){
        this.div(null,'aaaaaaaa');

        this.p(null,"the value of state is: "+this.getPrimitiveState("num",0).getValue());

        let input = this.getPrimitiveState('input','');

        this.input({
            value:input.getValue(),
            focusout:(v)=> {
                this.getPrimitiveState('input').setValue(v);
                this.render();;
            }
     
        })
        if(input.getValue('input') === 'mateus'){
            this.p(null,'aaaaaaaaaaaaaaaaaaaaa');

        }



        this.button({click:()=>{
                this.getPrimitiveState("num",0).increment(1);
                this.render();
            }},"add")

        this.button({click:()=>{
                this.getPrimitiveState("num",0).decrement(1);
                this.render();
            }},"remove")

    }).render(document.getElementById("root"));

}


window.onload = (undefined)=> main()
