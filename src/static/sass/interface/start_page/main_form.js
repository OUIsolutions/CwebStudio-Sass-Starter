
function  render_main_form(root_div){
    root_div.div((sub_element)=>{

        sub_element.inline_style({
            'text-align':'center'
        });


        sub_element.set_prop("APosition",
            "$16:9(15%,30%,70%,30%)" +
            "$1:1(5%,15%,90%,30%)"
        );


        let title = root_div.h4("Enter in the Platform");
        title.inline_style({
            color:'white'
        });

        root_div.br();

        const  input_style = {
            'background-color':'white',
            'border-radius':'1vh',
            width:'100%',
            'font-size':'3vh',
            height:'5vh',
            border:'0'
        }

        let login = root_div.input({
                inline_style:input_style,
                placeholder:"username or email"
        })

        let login_error_fragment = root_div.div();

        let password = root_div.input({
                inline_style:input_style,
                type:"password",
                placeholder:"password",
                render_keyup:false
        })


        let password_fragment = root_div.div();

        root_div.button("Login",{
            click:()=> login_callback(
                root_div,
                login,
                password,
                login_error_fragment,
                password_fragment
            )
        });

    })
}