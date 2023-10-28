


def main():
    
    route_name = input("type the route name")
    POSSIBLE_ROUTES = ['user','root','public']
    type_route = input(f"type the type of route {POSSIBLE_ROUTES}")
    
    if  type_route not in POSSIBLE_ROUTES:
        print(f"{type_route} not in {POSSIBLE_ROUTES}")
        return
    
    

main()