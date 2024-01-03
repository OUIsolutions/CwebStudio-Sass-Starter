
function  start_page_create_error(error,message){
    const error_style ={
        'font-size':'2vh',
        'color':'white'
    }

    error.p(message,{style:error_style});
}
function  clear_error(error){
    error.root.innerHTML= '';
}