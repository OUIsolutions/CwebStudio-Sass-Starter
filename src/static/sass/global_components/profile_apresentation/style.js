

class ProfileApresentationStyle {

    profile_picture_div(){
        return {
            'text-align':'center',

            'margin-top':'3vw',
            'margin-left':'6.5vw',
            width:'7vw',
            height:'7vw',
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
            'margin-top':'2vw',
            'text-align':'center',
            color:'white',
            'font-size':'3vh'
        }
    }
}