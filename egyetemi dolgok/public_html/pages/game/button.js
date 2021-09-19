import fw from './framework.js';
import gameContext from './gameContext.js';

export default class Button extends fw.EntityWithSprite{
    
    constructor(x,y,spritename) {
        super(x, y);

        this.type = spritename;
        this.image = fw.image('./sprites/buttons/'+spritename+'.png');
    }

    click()
    {
        // console.log(
        //     fw.MouseX + " " + fw.MouseY +"\n"+ 
        //     this.x+" "+ this.y
        // );



        if(fw.MouseX+ gameContext.cameraX-canvas.width/2 < this.x || fw.MouseX+ gameContext.cameraX-canvas.width/2 > this.x+64 ||
             fw.MouseY+ gameContext.cameraX-canvas.height/2 < this.y || fw.MouseY+ gameContext.cameraX-canvas.height/2 > this.y+64)
            return;

        switch (this.type) {
            case "play":
            gameContext.music.main.play();
                gameContext.maps.setMap("rm_1");
                break;
            case "help":
                gameContext.maps.setMap("rm_help");
                break;
        
            default:
                break;
        }
    

    }
    draw(ctx){

       //ctx.fillText(fw.MouseX+" "+fw.MouseY,fw.MouseX-canvas.width/2,fw.MouseY-canvas.height/2);

        ctx.drawImage(this.image, this.x, this.y);

    }





}
Button.events = ['draw','click'];
