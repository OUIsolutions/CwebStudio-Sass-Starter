
const ABSOLUTE_POSITION_ATTRIBUTE = 'APosition';
const ABSOLUTE_POSITION_QUERY_SELECTOR = `[${ABSOLUTE_POSITION_ATTRIBUTE}]`

const ABSOLUTE_POSITION_DOM_LOAD = 'load';
//code assigns
const  ABSOLUTE_POSITION_START_CHAR = '$';
const  ABSOLUTE_POSITION_MEASURE_DIVIDER = ',';
const ABSOLUTE_POSITION_LEFT_PARENTESIS = '(';
const ABSOLUTE_POSITION_RIGHT_PARENTESIS = ')';
const  ABSOLUTE_POSITION_EMPTY_STRING = ''
const ABSOLUTE_POSITION_SPACE = ' '

const  ABSOLUTE_POSITION_VALID_NUMS = ['.','0','1','2','3','4','5','6','7','8','9'];

const ABSOLUTE_POSITION_ASPECT_RATION_SEPARATOR = ':'
//directions
const ABSOLUTE_POSITION_LEFT = 'left';
const ABSOLUTE_POSITION_TOP = 'top';
const ABSOLUTE_POSITION_WIDTH = 'width';
const ABSOLUTE_POSITION_HEIGHT = 'height';


//operators
const ABSOLUTE_POSITION_OPERATOR_PLUS = '+';
const ABSOLUTE_POSITION_OPERATOR_MIN = '-';
const ABSOLUTE_POSITION_OPERATOR_PLUS_FIRST = 'f';


const ABSOLUTE_POSITION_VALID_OPERATORS = [
    ABSOLUTE_POSITION_OPERATOR_PLUS,
    ABSOLUTE_POSITION_OPERATOR_MIN,
    ABSOLUTE_POSITION_OPERATOR_PLUS_FIRST
]

const ABSOLUTE_POSITION_HORIZONTAL_DIRECTIONS = [ABSOLUTE_POSITION_LEFT,ABSOLUTE_POSITION_WIDTH];
const ABSOLUTE_POSITION_VERTICAL_DIRECTIONS = [ABSOLUTE_POSITION_TOP,ABSOLUTE_POSITION_HEIGHT];

//measures
const ABSOLUTE_POSITION_VIEW_WIDTH = 'vw';
const ABSOLUTE_POSITION_VIEW_HEIGHT  = 'vh';
const ABSOLUTE_POSITION_PX = 'px';
const ABSOLUTE_POSITION_PERCENT = '%';

const ABSOLUTE_POSITION_VALID_DIMENSIONS = [
    ABSOLUTE_POSITION_VIEW_WIDTH,
    ABSOLUTE_POSITION_VIEW_HEIGHT,
    ABSOLUTE_POSITION_PX,
    ABSOLUTE_POSITION_PERCENT
]
//html tags
const ABSOLUTE_POSITION_RESIZE = 'resize';
const ABSOLUTE_POSITION_ABSOLUTE = 'absolute';


//errors
const ABSOLUTE_PARENTESIS_NOT_PROVIDED = ' char:"(" not provided at:';
const  ABSOLUTE_POSITION_MISSING_DIVIDER = '"," missing at';
const ABSOLUTE_POSITION_ARGS_NOT_PASSED = 'Args not passed at:';
const ABSOLUTE_POSITION_INVALID_DIMENSION = 'Invalid Dimensions at:'
const ABSOLUTE_POSITION_NOT_VALID_NUMBER = 'Not Valid Number at:';
let absolute_position_show_errors =true;

class AbsolutePositionError extends Error {
    constructor(message = "",) {
        super(message);
    }

    /**@param {HTMLElement} element*/
    show_error(element){
        if(absolute_position_show_errors){
            console.log(this.message)
            console.log(element)
        }
    }

}


/**
 * @typedef {object} AbsolutePositionAspectRatio
 * @property {number} width
 * @property {number} height
 * @property {boolean} is_horizontal
 * @property {boolean} is_vertical
 * */
/**
 * @param {number} width
 * @param {number} height
 * @return {AbsolutePositionAspectRatio}
 * */
function absolute_position_convert_aspect_ratio(width, height){
    //convert 1920x1080 to 16x9
    let aspect_ratio = width/height;
    let width_ratio = 1;
    let height_ratio = 1;
    if(aspect_ratio > 1){
        width_ratio = aspect_ratio;
    }
    if(aspect_ratio < 1){
        height_ratio = 1/aspect_ratio;
    }
    return {
        is_horizontal:aspect_ratio >= 1,
        is_vertical:aspect_ratio < 1,
        width:width_ratio,
        height:height_ratio
    };
}

/**
 * @param {number} element1
 * @param {number} element2
 * @return {number}
 */
function absolute_position_returns_difference(element1, element2){
   if(element1 >= element2) {
       return element1 - element2;
   }
   return  element2 - element1;
}

/**
 * @param {Array<AbsolutePositionProp>} measures
 * @param {number}browser_width
 * @param {number}browser_height
 * @return {AbsolutePositionProp}
 * **/
function absolute_position_find_closest_measure(measures, browser_width, browser_height) {
    let closest = undefined;
    let closest_dif = undefined;
    let browser_ratio = absolute_position_convert_aspect_ratio(browser_width, browser_height);
    for(let measure of measures){
        let measure_ratio = absolute_position_convert_aspect_ratio(measure.horizontal_ratio, measure.vertical_ratio);
        let width_dif = absolute_position_returns_difference(measure_ratio.width,browser_ratio.width);
        let highest_dif = absolute_position_returns_difference(measure_ratio.height,browser_ratio.height);
        let dif = width_dif+highest_dif;
        if(closest_dif=== undefined){
            closest = measure;
            closest_dif = dif;
        }

        if(dif <= closest_dif){
            closest = measure;
            closest_dif = dif;
        }

    }

    return closest;
}

/**
 * @typedef SantosDummontDimension
 * @property {number} value
 * @property {string} measure
 * @property {string} operator
 * */


/**
 *@typedef {object} AbsolutePositionDimensions
 * @property {SantosDummontDimension} left
 * @property {SantosDummontDimension} heigth
 * @property {SantosDummontDimension} width
 * @property {SantosDummontDimension} height
 * */


/**
 * @typedef {object} AbsolutePositionProp
 * @property {number} horizontal_ratio
 * @property {number} vertical_ratio
 * @property {AbsolutePositionDimensions} dimensions
 * */


/**
 * @param {Array} element
 * @param {number} horizontal_ratio
 * @param {number} vertical_ratio
 * @return {AbsolutePositionProp}
 * */
function absolute_position_find_or_create_dimension(element, horizontal_ratio, vertical_ratio){
    for(let current of element){
        if(current.width === horizontal_ratio && current.height === vertical_ratio){
            return current;
        }
    }
    let created = {
        horizontal_ratio:horizontal_ratio,
        vertical_ratio:vertical_ratio,
        dimensions:undefined
    };

    element.unshift(created);
    return created;


}
/**
 @param {string} value

 @return {SantosDummontDimension}
 */
function absolute_position_generate_divided_number(value){


    if(value === ABSOLUTE_POSITION_EMPTY_STRING){
        throw new AbsolutePositionError(ABSOLUTE_POSITION_ARGS_NOT_PASSED);
    }


    let num_string = ABSOLUTE_POSITION_EMPTY_STRING;
    let operator = undefined;

    let passed_operator = ABSOLUTE_POSITION_VALID_OPERATORS.includes(value[0]);


    if(passed_operator){
        operator = value[0];
        num_string = value.substring(1);
    }

    if(!passed_operator){
        num_string = value;
    }


    //revert num_string
    let reverted_num_string = num_string.split(ABSOLUTE_POSITION_EMPTY_STRING).reverse();
    let dimensions_list = [];
    let new_num_string = [];
    let num_found = false;
    for(let current of reverted_num_string){

        
        if(ABSOLUTE_POSITION_VALID_NUMS.includes(current)){
            num_found = true;
        }

        if(!num_found){
            dimensions_list.unshift(current);
        }
        if(num_found){
            new_num_string.unshift(current);
        }

    }

    let dimensions = dimensions_list.join(ABSOLUTE_POSITION_EMPTY_STRING);


    if(dimensions === ABSOLUTE_POSITION_EMPTY_STRING){
        dimensions = ABSOLUTE_POSITION_PERCENT;
    }
    if(!ABSOLUTE_POSITION_VALID_DIMENSIONS.includes(dimensions)){
        throw new  AbsolutePositionError(ABSOLUTE_POSITION_INVALID_DIMENSION);
    }

    
    

    let final_string_num = new_num_string.join(ABSOLUTE_POSITION_EMPTY_STRING);


    let num = Number(final_string_num);
    if(num === undefined){
        throw  new AbsolutePositionError(ABSOLUTE_POSITION_NOT_VALID_NUMBER);
    }

    return {
        measure:dimensions,
        value:num,
        operator:operator
    }
        

}


/**
 * @param {Array<AbsolutePositionProp>} final_array
 * @param {string} current

 * */
function  absolute_position_generate_measure(final_array, current){


    let division = current.split(ABSOLUTE_POSITION_LEFT_PARENTESIS);

    if(division.length <= 1){
        throw new AbsolutePositionError(ABSOLUTE_PARENTESIS_NOT_PROVIDED);
    }


    let dimensions_raw = division[0];
    let divided_dimensions = dimensions_raw.split(ABSOLUTE_POSITION_ASPECT_RATION_SEPARATOR);

    let  horizontal_ration = window.innerWidth;
    let  vertical_ratio =window.innerHeight;

    if(divided_dimensions.length === 2){
        horizontal_ration = Number(divided_dimensions[0]);
        vertical_ratio = Number(divided_dimensions[1]);
    }

    let numbers = division[1];
    numbers = numbers
        .replaceAll(ABSOLUTE_POSITION_LEFT_PARENTESIS,ABSOLUTE_POSITION_EMPTY_STRING)
        .replaceAll(ABSOLUTE_POSITION_RIGHT_PARENTESIS,ABSOLUTE_POSITION_EMPTY_STRING);


    let divided_numbers = numbers.split(ABSOLUTE_POSITION_MEASURE_DIVIDER);

    if(divided_numbers.length !== 4){
        throw new AbsolutePositionError(ABSOLUTE_POSITION_MISSING_DIVIDER);
    }

    let left =absolute_position_generate_divided_number(divided_numbers[0]);
    let top =absolute_position_generate_divided_number(divided_numbers[1]);
    let width =absolute_position_generate_divided_number(divided_numbers[2]);
    let height =absolute_position_generate_divided_number(divided_numbers[3])

    let created = absolute_position_find_or_create_dimension(final_array,horizontal_ration,vertical_ratio);
    created.dimensions = {
        left:left,
        top:top,
        width:width,
        height:height
    }


}


/**
 * @param {HTMLElement} element
 * @param {string} value
 * @return {Array<AbsolutePositionProp>}
 * */
function  absolute_position_parser(element,value){
        /**@type {Array<AbsolutePositionProp>}*/
        let final_array = [];
        let formatted_value = value.replaceAll(ABSOLUTE_POSITION_SPACE,ABSOLUTE_POSITION_EMPTY_STRING);
        let elements = formatted_value.split(ABSOLUTE_POSITION_START_CHAR);
        elements = elements.filter(v => v !== ABSOLUTE_POSITION_EMPTY_STRING);

        elements.forEach(current=>{
            try{
                absolute_position_generate_measure(final_array,current)
            }
            /**@type {AbsolutePositionError}*/
            catch (error){
               error.show_error(element);
            }

        })
        return final_array;
}

let absolute_position_macros = {

}

/**
 * @param {string} name
 * @param {string} value
 * */
function  APosition_define_macro(name,value){
    absolute_position_macros[name] = value;
}
/**
 * @param {string} attribute
 * @return {string}
 * */
function  Absolute_position_replace_macros(attribute){
    let result = attribute;
    for(let key in absolute_position_macros){
        let value = absolute_position_macros[key];
        result = attribute.replaceAll(key,value);
    }
    return  result;
}

/**
 * @param {HTMLElement} element
 * @param {AbsolutePositionDimensions} measures
 * @param {string} name
 * @param {HTMLElement} previews_element
 * @param {number} browser_width
 * @param {number} browser_height
 *
 * */
function  absolute_position_generate_measures(element, measures, name, previews_element, browser_width, browser_height){
        /**@type {SantosDummontDimension}*/
        let current_measure = measures[name];
        let value  =current_measure.value;
        let measure = current_measure.measure;
        let operator = current_measure.operator;

        if(!previews_element && operator === ABSOLUTE_POSITION_OPERATOR_PLUS_FIRST){
                element.style[name] = 0 + ABSOLUTE_POSITION_PX;
                return;
        }


        if(!previews_element || !operator){
                element.style[name] = value + measure;
                return;
        }

        let previews_rect = previews_element.getBoundingClientRect();
        /**@type {number}*/
        let previews_value = previews_rect[name];

        let father = element.parentElement;
        let father_rect = father.getBoundingClientRect();


        let pixel_value = value;
        if(measure === ABSOLUTE_POSITION_PERCENT){

                let father_value = undefined;

                if(ABSOLUTE_POSITION_HORIZONTAL_DIRECTIONS.includes(name)){
                        father_value = father_rect.width;
                }

                if(ABSOLUTE_POSITION_VERTICAL_DIRECTIONS.includes(name)){
                        father_value = father_rect.height;
                }

                let fraction =(father_value/100);
                pixel_value = (fraction * pixel_value);

        }

        if(measure === ABSOLUTE_POSITION_VIEW_HEIGHT){
                pixel_value = (pixel_value/100)*browser_height;
        }

        if(measure === ABSOLUTE_POSITION_VIEW_WIDTH){
                pixel_value = (pixel_value/100)*browser_width;
        }

        let father_value = 0;
        if(name === ABSOLUTE_POSITION_LEFT || name === ABSOLUTE_POSITION_TOP){
                father_value = father_rect[name];
        }


        //get the width of the brother
        if(operator === ABSOLUTE_POSITION_OPERATOR_PLUS || operator === ABSOLUTE_POSITION_OPERATOR_PLUS_FIRST){
                pixel_value+= previews_value - father_value;
        }

        if(operator === ABSOLUTE_POSITION_OPERATOR_MIN){

                pixel_value = previews_value - pixel_value + father_value;
        }


        element.style[name] = pixel_value + ABSOLUTE_POSITION_PX ;



}
function absolute_position_processElements() {
        let elementosRefer = document.querySelectorAll(ABSOLUTE_POSITION_QUERY_SELECTOR);

        elementosRefer.forEach(element => {


                let attribute = element.getAttribute(ABSOLUTE_POSITION_ATTRIBUTE);
                attribute = Absolute_position_replace_macros(attribute);


                let browser_width = window.innerWidth;
                let browser_height = window.innerHeight;
        
                
                let measures  = absolute_position_parser(element,attribute);

                if(measures.length === 0){
                        return;
                }

                let closest = absolute_position_find_closest_measure(measures,browser_width,browser_height);


                let dimensions = closest.dimensions;
                let previews_element = element.previousElementSibling;
                element.style.position = ABSOLUTE_POSITION_ABSOLUTE;

                absolute_position_generate_measures(element, dimensions,ABSOLUTE_POSITION_LEFT,previews_element,browser_width,browser_height);
                absolute_position_generate_measures(element,dimensions,ABSOLUTE_POSITION_TOP,previews_element,browser_width,browser_height);
                absolute_position_generate_measures(element,dimensions,ABSOLUTE_POSITION_WIDTH,previews_element,browser_width,browser_height);
                absolute_position_generate_measures(element,dimensions,ABSOLUTE_POSITION_HEIGHT,previews_element,browser_width,browser_height);

        });

}


function  absolute_position_start(){
        absolute_position_processElements();
        //set an  listener for change dimensions
        window.addEventListener(ABSOLUTE_POSITION_RESIZE, absolute_position_processElements);
        const observer = new MutationObserver(absolute_position_processElements);
        const config = { childList: true, subtree: true };
        observer.observe(document, config);

}

//add an document listener for window laod 
window.addEventListener(ABSOLUTE_POSITION_DOM_LOAD,absolute_position_start);
