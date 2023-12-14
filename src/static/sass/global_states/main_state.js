


class MainState{


    /** @type {Profile} */
    profile = new Profile();

    /** @type {StartPage} */
    page_start= new StartPage();


    /*
    * @param {class} page
    * */
    turnOnPage(page){
        for(let key in this){
            if(!key.startsWith("page")){
                continue;
            }
            let value = this[key];
            if(value instanceof (page)){
                value.current = true;
                continue
            }

            this[key].current = false;
        }
    }
}