from os.path import isdir
from os import mkdir

USER = 'user'
ROOT = 'root'
PUBLIC = 'public'
POSSIBLE_ROUTES = [USER,ROOT,PUBLIC]
MAIN_IF = 'main_if.c'


MODELS_PATH  = "build/models"
ROUTE_CONSTANTES_PATH = 'src/constants/routes.h'
ROUTES_PATH = "src/routes"
MAIN_PATH = 'src/main.c'

def read_file(filename:str)->str:
    with open(filename,'r') as arq:
        return arq.read()
    
def write_file(filename:str,value:str):
    with open(filename,'w') as arq:
        arq.write(value)

def replace_point_with_code(text:str, point:str,code:str)->str:
    if point not in text:
        raise Exception(f'point {point} not found')
    formated_text = code + '\n' + point
    return text.replace(point,formated_text)

def format_route_constant(routename:str)->str:
    formated = routename.replace('  ',' ')
    formated = formated.replace(' ','_')
    return formated.upper() + '_ROUTE'

def format_route_dir_or_file_name(routename:str)->str:
    formated = routename.replace('  ',' ')
    formated = formated.replace(' ','_')
    return formated.lower()

def create_function_name(routename:str)->str:
    formated = routename.replace('  ',' ')
    formated = formated.replace(' ','_')
    return formated.lower() + '_route'

def add_route_constant(type_element:str,route_name:str)->str:
    route_string = read_file(ROUTE_CONSTANTES_PATH)
    point = f'//{type_element}_point'
    route_constant = format_route_constant(route_name)
    code = f'#define {route_constant} "/{type_element}/{route_name}"'
    return replace_point_with_code(route_string,point,code)    

def add_route_declaration_import(type_element:str,route_name:str)->str:
    route_declaration_path = f'{ROUTES_PATH}/{type_element}/declaration.h'
    content = read_file(route_declaration_path)
    dir = format_route_dir_or_file_name(route_name)
    filename = format_route_dir_or_file_name(route_name)
    content+=f'\n#include "{dir}/{filename}.h"'
    return content

def add_route_definition_import(type_element:str,route_name:str)->str:
    route_declaration_path = f'{ROUTES_PATH}/{type_element}/definition.h'
    content = read_file(route_declaration_path)
    dir = format_route_dir_or_file_name(route_name)
    filename = format_route_dir_or_file_name(route_name)
    content+=f'\n#include "{dir}/{filename}.c"'
    return content


def create_function_declaration(route_name:str)->str:
    model = load_model('function_declaration.h')
    return model.replace('function_name',create_function_name(route_name))

def create_function_definition(type_route:str,route_name:str)->str:
    model = load_model(f'{type_route}_function.c')
    return  model.replace('function_name',create_function_name(route_name))

def load_model(model_name:str)->str:
    return read_file(f'{MODELS_PATH}/{model_name}')

def create_main_if(route_name:str)->str:
    content = read_file(MAIN_PATH)
    main_if = load_model(MAIN_IF)
    main_if = main_if.replace('ROUTE',format_route_constant(route_name))
    main_if = main_if.replace('route_name',create_function_name(route_name))
    content = replace_point_with_code(content,'//route_insertion',main_if)
    return content

def create_insertions(type_route:str,route_name:str):
    route_function_dir = f'{ROUTES_PATH}/{type_route}/{format_route_dir_or_file_name(route_name)}'
    route_function_name = format_route_dir_or_file_name(route_name)
    return {
        ROUTE_CONSTANTES_PATH: add_route_constant(type_route,route_name),
        f'{ROUTES_PATH}/{type_route}/declaration.h':add_route_declaration_import(type_route,route_name),
        f'{ROUTES_PATH}/{type_route}/definition.h':add_route_definition_import(type_route,route_name),
        f'{route_function_dir}/{route_function_name}.h':create_function_declaration(route_name),
        f'{route_function_dir}/{route_function_name}.c':create_function_definition(route_name),
        MAIN_PATH:create_main_if(route_name)

    }

def main():
    
    route_name = input("type the route name:")
    type_route = input(f"type the type of route {POSSIBLE_ROUTES}:")
    
    if  type_route not in POSSIBLE_ROUTES:
        print(f"{type_route} not in {POSSIBLE_ROUTES}")
        return
    try:
        route_function_dir = f'{ROUTES_PATH}/{type_route}/{format_route_dir_or_file_name(route_name)}'
        if isdir(route_function_dir):
            raise Exception('function already exist')
        mkdir(route_function_dir)
        insertions = create_insertions(type_route,route_name)
        
        for path in insertions:
            write_file(path, insertions[path])


    except Exception as e :
        print(e)
    


main()