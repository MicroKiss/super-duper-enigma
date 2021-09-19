import fw from './framework.js';
import gameContext from './gameContext.js';


var SPAWNState = function (wall) {
    this.wall = wall;
    this.startTime = Date.now();
};
SPAWNState.prototype.frame = function () {
    var count = 0;
    var nUp = this.wall.place_meeting(this.wall.x, this.wall.y - this.wall.getHeight(), Wall);
    var nDown = this.wall.place_meeting(this.wall.x, this.wall.y + this.wall.getHeight(), Wall);
    var nRight = this.wall.place_meeting(this.wall.x + this.wall.getWidth(), this.wall.y, Wall);
    var nLeft = this.wall.place_meeting(this.wall.x - this.wall.getWidth(), this.wall.y, Wall);


    if (nUp) count += 1;
    if (nRight) count += 2;
    if (nDown) count += 4;
    if (nLeft) count += 8;
    var imageName = './sprites/wall/' + count + '.png';
    this.wall.image = fw.image(imageName);

    if ((Date.now() - this.startTime) / 1000.0 > 0.5)
        this.wall.state = null;
}




export default class Wall extends fw.EntityWithSprite {

    constructor(x, y) {
        super(x, y);
        this.state = new SPAWNState(this);
        //this.image = Wall.image;
    }

    getWidth() {
        return 64;
    }

    getHeight() {
        return 64;
    }


    update() {
        if (this.state)
            this.state.frame();
    }
    draw(ctx) {

        ctx.drawImage(this.image, this.x, this.y);


        // ctx.fillRect(this.x,this.y-this.getHeight(),10,10);
        // ctx.fillRect(this.x,this.y+this.getHeight(),10,10);
        // ctx.fillRect(this.x+this.getWidth(),this.y,10,10);
        // ctx.fillRect(this.x-this.getWidth(),this.y,10,10);
    }





}
Wall.image = fw.image('wall.png');
Wall.events = ['draw', 'update'];

