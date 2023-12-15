

function create_left_bar_element(main_interface,page_props,text,callback){

    const  div_style ={
        'margin-top':'2vh',
         height:'5vh',
        'text-align':'center',
        'color':'white'

    }

    main_interface.div({
        style:div_style,
        click:callback
    },text)


}