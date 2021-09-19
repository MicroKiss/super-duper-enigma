import fw from './framework.js';
import Wall from './wall.js';
import gameContext from './gameContext.js';
import Player from './player.js';

export default class Spike extends fw.EntityWithSprite {

    constructor(x, y) {
        super(x, y);
        this.image = Spike.image;
    }


    getLeft() {
        return this.x + 8;
    }
    getTop() {
        return this.y + 20;
    }

    getWidth() {
        return 50;
    }

    getHeight() {
        return 40;
    }


    update() {



        if (this.place_meeting(this.getLeft(), this.getTop(), Player))
            gameContext.Player.die();



    }

    draw(ctx) {
        // ctx.fillRect(this.getLeft(),this.getTop(),this.getWidth(),this.getHeight());

        ctx.drawImage(this.image, 0, 0, 64, 64, this.x, this.y, 64, 64);
        // ctx.fillRect(this.getLeft(), this.getTop(), this.getWidth(), this.getHeight());


    }

}
Spike.image = fw.image('./sprites/object/spike.png');
Spike.events = ['update', 'draw'];

