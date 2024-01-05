
const TOMATO_DEFAULT_SEED = 'hello my cold friend';

let  tomato_min_rgb = 50;
let  tomato_max_rgb = 230;
let  tomato_minimum_difference = 60;
let tomato_total_generations = 0;

/**
 * @param {number} seed
 * @param {number}total_generation
 * */
function  tomato_get_rgb_pure(seed,total_generation){

    let multiplication =
        (seed + total_generation + tomato_max_rgb)*
        (total_generation + tomato_max_rgb);


    let result =  multiplication % tomato_max_rgb;
    if(result < tomato_min_rgb){
        result = tomato_min_rgb;
    }

    return result;
}

/**
 * @param {number} seed
 * @return {number}
 */
function tomato_get_rgb_number(seed){

    let last_rgb =  tomato_get_rgb_pure(seed,tomato_total_generations-1);
    const LIMIT_TRYS = 100;

    let max_try = LIMIT_TRYS + tomato_total_generations;

    let rgb = 0;
    tomato_total_generations+=1;

    for(;tomato_total_generations < max_try; tomato_total_generations++){

        rgb = tomato_get_rgb_pure(seed,tomato_total_generations);
        let difference = rgb - last_rgb;
        let positive_difference = difference *1;
        if(positive_difference > tomato_minimum_difference){
            break;
        }
    }

    return rgb


}

/**
 * @param {string} seed
 * @return {number}
 * */

function tomato_create_tomato_num_seed(seed){
    let chars =  seed.split('');
    let result = 1;
    const ONE_MILLION_LIMIT = 1000000;

    chars.forEach(char => {
        let ascci_value = char.charCodeAt(0);
        result = (result * ascci_value) + 1;

        if(result > ONE_MILLION_LIMIT){
            result = result % ONE_MILLION_LIMIT;
        }

    });

    return result;

}

/**
 * @typedef {object} TomatoPseudoRamdomColors
 * @property {string} rgb
 * @property {string} color
 */

/**
 * @param {number} seed
 * @return  {TomatoPseudoRamdomColors}*/
function tomato_generate_pseudo_random_colors(seed){
    //determine Math seed


    let red =  tomato_get_rgb_number(seed);
    let green = tomato_get_rgb_number(seed);
    let blue =  tomato_get_rgb_number(seed);


    let color = 'black';
    if(red + green + blue < 300){
        color = 'white';
    }

    return {
        rgb: `rgb(${red},${green},${blue})`,
        color: color
    };

}

/**@param {number}seed */
function tomato_process_elements(seed){

    let all_elements = document.body.querySelectorAll('*');


    all_elements.forEach(element => {
        //set the tomato attribute
        if(element.getAttribute('tomato')){
            return;
        }
        element.setAttribute('tomato', 'true');

        if(element.style){
            let tomato_colors = tomato_generate_pseudo_random_colors(seed);
            element.style.backgroundColor = tomato_colors.rgb;
            element.style.color = tomato_colors.color;
        }
    });
}




function tomato_start(seed){

    let tomato_numerical_seed = 0;
    if(seed){
        tomato_numerical_seed = tomato_create_tomato_num_seed(seed);
    }
    else {
        tomato_numerical_seed = tomato_create_tomato_num_seed(TOMATO_DEFAULT_SEED);
    }



    window.addEventListener('load', ()=>{
        tomato_process_elements(tomato_numerical_seed);
        const observer = new MutationObserver( ()=>tomato_process_elements(tomato_numerical_seed));
        const config = { childList: true, subtree: true };
        observer.observe(document.body, config);
    });

}
