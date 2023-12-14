
class StartPageStyle{

    /** @returns {object} */
    right_div_style(){return{
        position:'absolute',
        width:'30vw',
        height:'100%',
        left:'70vw',
        'background-color':BLUE_BACKGROUND,
    }}

    /** @returns {object} */
    main_form_style(){return{
        position:'absolute',
        'text-align':'center',
        height:'30vh',
        left:'5vw',
        'top': '30vh'
    }}
    /** @returns {object} */

    title_style(){return {
        color:'white',
        'margin-right':'5vw',

        'font-size':'4vh',
    }}

    /** @returns {object} */
    input_style(){return {
        'background-color':'white',
        'border-radius':'1vh',
        width:'20vw',
        'margin-right':'5vw',
        'font-size':'3vh',
        height:'5vh',
        border:'0'
    }}
    login_button() {return {
        'margin-right':'5vw',
        height:'5vh',

        width:'10vw',

    }}

    /** @returns {object} */
    error_style(){return{
        'font-size':'2vh',
        'color':'white'
    }}

}
