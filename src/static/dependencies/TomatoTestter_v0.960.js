
const TOMATO_DEFAULT_SEED = 'hello my cold friend';
let tomato_last_generation = undefined;
let  tomato_min_rgb = 60;
let  tomato_max_rgb = 220;
let  tomato_minimum_difference = 50;
let tomato_total_generations = 0;


/**
 * @param {number} seed
 * @param {number} current_color
 * @return {number}
 */
function tomato_get_rgb_number(seed,current_color){

    let multiplication =  seed * (current_color +1) * tomato_total_generations;
    let pseudo_random_rgb = (multiplication % (tomato_max_rgb - tomato_min_rgb)) + tomato_min_rgb;

    if(!tomato_last_generation){
        return pseudo_random_rgb;
    }
    let last_rgb = tomato_last_generation[current_color];

    let MAX_TRYS = 100;
    for(let i =1; i < MAX_TRYS;i++){

        let difference = Math.abs(pseudo_random_rgb - last_rgb);

        if(difference > tomato_minimum_difference){
            break;
        }
        multiplication =  seed * (current_color +1 + i) * tomato_total_generations;
        pseudo_random_rgb = (multiplication % (tomato_max_rgb - tomato_min_rgb)) + tomato_min_rgb;



    }


    return pseudo_random_rgb;

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
    
    tomato_total_generations+=1;
    let red =  tomato_get_rgb_number(seed,0);
    let green = tomato_get_rgb_number(seed,1);
    let blue =  tomato_get_rgb_number(seed,2);

    tomato_last_generation = [red,green,blue];

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

