import fw from './framework.js';
import Wall from './wall.js';
import gameContext from './gameContext.js';
import Player from './player.js';

export default class Coin extends fw.EntityWithSprite {

    constructor(x, y) {
        super(x, y);
        this.image = Coin.image;
        gameContext.coinCounter += 1;
        this.spriteIndex = Math.floor(Math.random() * 30);
    }


    getLeft() {
        return this.x + 10;
    }
    getTop() {
        return this.y + 10;
    }

    getWidth() {
        return 44;
    }

    getHeight() {
        return 44;
    }


    update() {

        this.spriteIndex = (this.spriteIndex + 1) % 30;


        if (this.place_meeting(this.getLeft(), this.getTop(), Player)) {
            gameContext.music.coin.cloneNode(true).play();
            gameContext.coinCounter -= 1;
            gameContext.scene.remove(this);



            if (gameContext.coinCounter == 0)
                gameContext.maps.setMap(gameContext.nextLevel);

        }
    }

    draw(ctx) {
        // ctx.fillRect(this.getLeft(),this.getTop(),this.getWidth(),this.getHeight());

        ctx.drawImage(this.image, Math.floor(this.spriteIndex / 3) * 64, 0, 64, 64, this.x, this.y, 64, 64);


    }

}
Coin.image = fw.image('./sprites/object/coin.png');
Coin.events = ['update', 'draw'];

