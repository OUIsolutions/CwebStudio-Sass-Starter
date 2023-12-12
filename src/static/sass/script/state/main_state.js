

class MainState{

    /** @type {boolean} */
    connected = false;

    /** @type {StartPage} */
    start_page = new StartPage();

    turn_of_all_pages(){
        this.start_page.current = false;
    }

    tur_on_start_page(){
        this.turn_of_all_pages();
        this.start_page.current =true;
    }


}