

class ProfileApresentationStyle {

    aprsentation_div(){
        return {
            'position':'absolute',
            width:'100%',
            height:'20vh'
        }
    }
    profile_picture_div(){
        return {
            'position':'absolute',
            'top':'3vw',
            'left':'2vw',
            width:'5vw',
            height:'5vw',
           'border-radius': '50%',
            'overflow': 'hidden',
        }
    }
    profile_picture_img(url){
        if(!url){
            url = assets['snow'];
        }
        return {
            width:'100%',
            height:'100%',
            background: `url('${url}')`,
            'background-size': 'cover',
            ' background-position':'center center'
        }

    }
     profile_name_style(){
        return {
            'position':'absolute',
            'top':'5vw',
            'left':'10vw',
            border:'0vw',
            width:'5vw',
            height:'5vw',
            color:'white',
            'font-size':'3vh'
        }
    }


}