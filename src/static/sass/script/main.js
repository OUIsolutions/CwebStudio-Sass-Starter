

function main(){


    createElement404(function (){
        this.div(null,'aaaaaaaa');
        let numState = this.getPrimitiveState("num",0);
        let numValue = numState.getValue()
        this.p(null,"the value of state is: "+numValue);

        let input = this.getPrimitiveState('input','');

        this.input({
            value:input.getValue(),
            render_focusout:(v)=> {
                this.getPrimitiveState('input').setValue(v);
            }
     
        })

        if(input.getValue('input') === 'mateus'){
            this.p(null,'aaaaaaaaaaaaaaaaaaaaa');
        }
        
        this.button({render_click:()=>numState.increment(1)},"add")
        this.button({render_click:()=>numState.decrement(1)},"remove")

    }).render(document.getElementById("root"));

}


window.onload = (undefined)=> main()
