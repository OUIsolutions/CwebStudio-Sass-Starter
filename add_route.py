USER = 'user'
ROOT = 'root'
PUBLIC = 'public'
POSSIBLE_ROUTES = [USER,ROOT,PUBLIC]


def read_file(filename:str)->str:
    with open(filename,'r') as arq:
        return arq.read()
    


def add_route_constant(type:str,route_name:str)->str:
    
    pass 

def main():
    
    route_name = input("type the route name")
    type_route = input(f"type the type of route {POSSIBLE_ROUTES}")
    
    if  type_route not in POSSIBLE_ROUTES:
        print(f"{type_route} not in {POSSIBLE_ROUTES}")
        return
    


main()