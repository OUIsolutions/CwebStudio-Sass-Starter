

class  ProfilePictureStyle{

    profile_picture_div(){
        return {
            'margin-top':'5vw',
            'margin-left':'2vw',
            width:'5vw',
            height:'5vw',
           'border-radius': '50%',
            'overflow': 'hidden',
        }
    }
    profile_picture_img(){
        return{
            width:'100%',
            height:'100%',
            background: `url('${assets['snow']}')`,
            'background-size': 'cover',
            ' background-position':'center center'
        }
    }

}