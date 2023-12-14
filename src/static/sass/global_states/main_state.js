


class MainState{


    /** @type {Profile} */
    profile = new Profile();

    /** @type {StartPage} */
    page_start= new StartPage();
    page_root_users = new UsersPageState();

    turnOnPage(page_class){
        for(let key in this){
            if(!key.startsWith("page")){
                continue;
            }
            let value = this[key];
            if(value instanceof (page_class)){
                value.current = true;
                continue
            }

            this[key].current = false;
        }
    }
}