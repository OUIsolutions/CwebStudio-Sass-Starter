USER = 'user'
ROOT = 'root'
PUBLIC = 'public'
POSSIBLE_ROUTES = [USER,ROOT,PUBLIC]


ROUTE_CONSTANTES_PATH = 'src/constants/routes.h'

def read_file(filename:str)->str:
    with open(filename,'r') as arq:
        return arq.read()

def replace_point_with_code(text:str, point:str,code:str)->str:
    if point not in text:
        raise Exception(f'point {point} not found')
    formated_text = code + '\n' + point
    return text.replace(text,formated_text)

def format_route_constant(routename:str):
    formated = routename.replace('  ',' ')
    formated = formated.replace(' ','_')
    return formated.upper()


def add_route_constant(type:str,route_name:str)->str:
    route_string = read_file(ROUTE_CONSTANTES_PATH)
    point = f'//{type}_point'
    code = format_route_constant(route_name)
    return replace_point_with_code(route_string,point,code)    
    

def main():
    
    route_name = input("type the route name")
    type_route = input(f"type the type of route {POSSIBLE_ROUTES}")
    
    if  type_route not in POSSIBLE_ROUTES:
        print(f"{type_route} not in {POSSIBLE_ROUTES}")
        return
    try:
        inertions = {
            ROUTE_CONSTANTES_PATH: add_route_constant(type,route_name)
        }
        for i in inertions:
            
    except Exception as e :
        print(e)
    


main()