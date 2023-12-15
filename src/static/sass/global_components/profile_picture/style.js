

class  ProfilePictureStyle{

    profile_picture_div(){
        return {
            'margin-top':'5vw',
            'margin-left':'5vw',
            width:'10vw',
            height:'10vw'
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