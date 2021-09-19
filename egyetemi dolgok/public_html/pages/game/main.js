import fw from './framework.js';
import Player from './player.js';
import Wall from './wall.js';
import Dialogue from './dialogue.js';
import gameContext from './gameContext.js';
import Coin from './coin.js';
import Spike from './spike.js';
import Maps from './maps.js';

const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
gameContext.ctx = ctx;


gameContext.music = {
    main: new Audio('sounds/main.mp3'),
    jump: new Audio('sounds/jump.mp3'),
    rope: new Audio('sounds/rope.mp3'),
    coin: new Audio('sounds/coin.mp3'),
    dead: new Audio('sounds/dead.mp3'),
}

gameContext.music.main.loop = true;
gameContext.music.main.volume = 0.2;


gameContext.maps = new Maps();




fw.load([
    Player.images.dead,
    Player.images.idle,
    Player.images.jump_l,
    Player.images.jump_r,
    Player.images.run_l,
    Player.images.run_r,
    Wall.image,
    Coin.image,
], () => {
    requestAnimationFrame(update);
});



function update() {


    for (var i in fw._pressedKeys) {
        if (fw._pressedKeys[i])
            gameContext.scene.fire('keyDown_' + i);
    }


    gameContext.index = fw.createIndex(gameContext.scene);
    gameContext.scene.fire('update', ctx);


    //ctx.fillStyle = "#CD853F";
    //ctx.fillRect(gameContext.Player.x - canvas.width / 2, gameContext.Player.y - canvas.height / 2, canvas.width, canvas.height);
    if (gameContext.Player) {
        let dx = gameContext.Player.lastX - gameContext.Player.x;
        let dy = gameContext.Player.lastY - gameContext.Player.y;
        gameContext.cameraX -= dx;
        gameContext.cameraY -= dy;
        gameContext.ctx.translate(dx, dy);
    }

    const BackGroundImage = fw.image('./sprites/bg/BG.png');
    //if(gameContext.currentLevel =="rm_menu")
    gameContext.ctx.drawImage(BackGroundImage, gameContext.cameraX - canvas.width / 2, gameContext.cameraY - canvas.height / 2, canvas.width, canvas.height);


    gameContext.scene.fire('draw', ctx);

    requestAnimationFrame(update);
}
