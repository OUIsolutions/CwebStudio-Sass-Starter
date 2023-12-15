

class  ProfilePictureStyle{

    profile_picture_div(){
        return {

            'margin-top':'3vw',
            'margin-left':'6vw',
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

}