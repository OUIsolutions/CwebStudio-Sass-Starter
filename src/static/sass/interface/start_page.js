
function render_start_page_style(){
    let style = {};

    style.global = {
        position:'fixed',
        width:'100vw',
        height: '100vh',
        'background': `url('${assets['background']}')`,
        'background-size':'cover',
        'background-position': 'center center'
    }
    style.right_div_style ={

        position:'absolute',
        width:'30vw',
        height:'100%',
        left:'70vw',
        'background-color':BLUE_BACKGROUND

    }
    style.main_form_style ={
        position:'absolute',
        'text-align':'center',
        height:'30vh',
        left:'5vw',
        'top': '30vh'
    }

    style.title_style ={
        color:'white',
        'margin-right':'5vw',
        'font-size':'4vh'
    }
    style.input_style ={
        'background-color':'white',
        'border-radius':'1vh',
        width:'20vw',
        'margin-right':'5vw',
        'font-size':'3vh',
        height:'5vh',
        border:'0'
    }
    style.login_button ={
        'margin-right':'5vw',
        height:'5vh',
        width:'10vw'
    }
    style.error_style ={
        'font-size':'2vh',
        'color':'white'
    }
    return style;
}

/**
 * @typedef {object} StartPageProps
 * @property {string || undefined} login
 * @property {string || undefined} login_error
 * @property {string || undefined} password
 * @property {string || undefined} password_error
 * * */

/**
 * @param {StartPageProps} start_state
 * @returns {Element404}
 * */
function  render_start_page(start_state){

    return createElement404((main_interface)=>{
        main_interface.stored_state = start_state;
        let page_style = render_start_page_style();
        main_interface.div(()=>{

            main_interface.div(()=>{

                main_interface.div(()=>{

                    main_interface.h4("Enter in the Platform",{style:page_style.title_style})
                    main_interface.br()

                    main_interface.stateInput(
                        "login",
                        {
                            style:page_style.input_style,
                            placeholder:"username or email"
                        }
                    )

                    if(start_state.login_error){
                        main_interface.p(start_state.login_error,{style:page_style.error_style});
                    }


                    main_interface.stateInput(
                        "password",
                        {
                            style:page_style.input_style,
                            type:"password",
                            placeholder:"password",
                            render_keyup:false
                        }
                    )

                    if(start_state.password_error){
                        main_interface.p(start_state.password_error,{style:page_style.error_style});

                    }

                    main_interface.button("Login",{
                        style:page_style.login_button,
                        click:()=> render(
                            login_callback,
                            main_interface.getFullState()
                        )
                    });

                },{style:page_style.main_form_style})


            },{style:page_style.right_div_style})

        },{style:page_style.global});

    })
}