

function main(){

    let root_element = new Element404();

    root_element.div(null,"aaaaaaa")
    //let page_state = root_element.getSimpleState(CURRENT_PAGE,LOGIN_PAGE);
    //let page_value = page_state.getValue()

   // if(page_value === LOGIN_PAGE){
       // render_login_page(root_element)
    //}

    root_element.render(document.getElementById("root"));

}


window.onload = (undefined)=> main()
