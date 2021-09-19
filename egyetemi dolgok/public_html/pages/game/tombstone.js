import fw from './framework.js';
import gameContext from './gameContext.js';
import Player from './player.js';

export default class Tombstone extends fw.EntityWithSprite {

    constructor(x, y, ind) {
        super(x, y);
        this.image = Tombstone.image;
        this.ind = ind;
    }


    getLeft() {
        return this.x + 8;
    }
    getTop() {
        return this.y + 20;
    }

    getWidth() {
        return 64;
    }

    getHeight() {
        return 64;
    }


    draw(ctx) {
        // ctx.fillRect(this.getLeft(),this.getTop(),this.getWidth(),this.getHeight());

        ctx.drawImage(this.image, 0, 0, 64, 64, this.x, this.y, 64, 64);
        // ctx.fillRect(this.getLeft(), this.getTop(), this.getWidth(), this.getHeight());
        //ui
        ctx.fillStyle = '#FF0000';
        ctx.font = "15px Comic Sans MS";
        ctx.textAlign = "middle";
        ctx.fillText(this.ind, this.x + this.getWidth() / 2, this.y + this.getHeight() - 10);


    }

}
Tombstone.image = fw.image('./sprites/object/tombstone.png');
Tombstone.events = ['draw'];

