import fw from './framework.js';
import gameContext from './gameContext.js';
import Wall from './wall.js';
import Tombstone from './tombstone.js';

//npx http-server -c-1

var KeyEvent = {
    VK_SPACE: 32,
    VK_A: 65,
    VK_D: 68,
    VK_W: 87,
    VK_S: 83,
    VK_E: 69,
    VK_Q: 81,
    VK_R: 82,
};


var NORMALstate = function (hero) {
    this.player = hero;
    this.grappleDist = 320;
    this.player.spriteIndex = 0;

};
NORMALstate.prototype.frame = function () {
    if (this.player.lastX - this.player.x == 0 && this.player.lastY - this.player.y == 0)
        this.player.image = Player.images.idle;


    this.player.hsp = (fw.isDown(KeyEvent.VK_D) - fw.isDown(KeyEvent.VK_A)) * this.player.moveSpeed;

    if (this.player.place_meeting(this.player.getLeft(), this.player.getTop() + 1, Wall)) {
        //looking left-right n ground
        if (this.player.hsp < 0)
            this.player.image = Player.images.run_l;
        else if (this.player.hsp > 0)
            this.player.image = Player.images.run_r;
        //jumping
        if (fw.isDown(KeyEvent.VK_SPACE) && !this.player.jumpcd) {
            this.player.jumpcd = 30;
            gameContext.music.jump.cloneNode(true).play();

            this.player.spriteIndex = 0;
            this.player.image = (this.player.hsp < 0 ? Player.images.jump_l : Player.images.jump_r);
            this.player.vsp -= this.player.jumpSpeed;
        }
    }
    else  //not place meetinh wall
    {
        this.player.image = (this.player.hsp < 0 ? Player.images.jump_l : Player.images.jump_r);
        if (this.player.vsp < 10)
            this.player.vsp += this.player.grav;
    }
    this.player.grappleCD = Math.max(0, this.player.grappleCD - 1);
    this.player.jumpcd = Math.max(0, this.player.jumpcd - 1);



    if (fw.isDown(KeyEvent.VK_R) && this.player.grappleCD == 0 &&
        Math.sqrt(Math.pow((this.player.getLeft() + this.player.getWidth() / 2) - (fw.MouseX + gameContext.cameraX - canvas.width / 2), 2) + Math.pow(this.player.y - (fw.MouseY + gameContext.cameraY - canvas.height / 2), 2)) < this.grappleDist) {

        gameContext.music.rope.cloneNode(true).play();
        this.player.state = new SWINGstate(this.player);
    }



    this.player.spriteIndex = (this.player.spriteIndex + 1) % 50;

};

var SWINGstate = function (hero) {
    this.id = "SWINGstate";
    this.player = hero;
    this.player.vsp = 0;
    this.player.hsp = 0;
    this.GrappleX = fw.MouseX + gameContext.cameraX - canvas.width / 2;
    this.GrappleY = fw.MouseY + gameContext.cameraY - canvas.height / 2;
    this.RopeX = this.player.getLeft() + this.player.getWidth() / 2;
    this.RopeY = this.player.y;
    this.RopeAngle = Math.atan2(this.GrappleY - this.player.y, this.GrappleX - (this.player.getLeft() + this.player.getWidth() / 2));
    this.RopeLength = Math.sqrt(Math.pow(this.player.getLeft() + this.player.getWidth() / 2 - this.GrappleX, 2) + Math.pow(this.player.y - this.GrappleY, 2)) - 3;
    this.RopeOsc = 0;
    this.player.grappleCD = 100;
};

SWINGstate.prototype.frame = function () {
    this.player.jumpcd = Math.max(0, this.player.jumpcd - 1);
    this.RopeOsc -= Math.cos(this.RopeAngle) * 0.02;
    this.RopeAngle += this.RopeOsc;
    this.RopeOsc *= 0.96;
    this.RopeX = this.GrappleX - Math.cos(this.RopeAngle) * this.RopeLength;
    this.RopeY = this.GrappleY - Math.sin(this.RopeAngle) * this.RopeLength;
    this.player.hsp = this.RopeX - (this.player.getLeft() + this.player.getWidth() / 2);
    this.player.vsp = this.RopeY - this.player.y;

    //  this.RopeLength = Math.max(this.RopeLength + (fw.isDown(KeyEvent.VK_S) - fw.isDown(KeyEvent.VK_W)), 0.3);
    this.RopeOsc -= (fw.isDown(KeyEvent.VK_D) - fw.isDown(KeyEvent.VK_A)) * 0.005;

    if (fw.isDown(KeyEvent.VK_SPACE) && this.player.jumpcd == 0) {
        gameContext.music.rope.cloneNode(true).play();
        this.player.state = new NORMALstate(this.player);
        this.player.vsp = -this.player.jumpSpeed;
    }
}

var DEADstate = function (hero) {
    gameContext.music.dead.cloneNode(true).play();
    this.id = "DEADstate";
    this.player = hero;
    this.player.spriteIndex = 2;
    this.time = Date.now();
    this.player.deathcounter++;
    this.player.hsp = 0;
    this.player.vsp = 0;
    this.player.image = Player.images.dead;
};

DEADstate.prototype.frame = function () {
    this.player.spriteIndex = this.player.spriteIndex < 49 ? (this.player.spriteIndex + 1) % 50 : 49;

    if (Date.now() > this.time + 1500) {

        gameContext.scene.add(new Tombstone(this.player.x, this.player.y, this.player.deathcounter));
        this.player.x = this.player.SPAWNCOORDS[0];
        this.player.y = this.player.SPAWNCOORDS[1];



        let dx = gameContext.Player.lastX - gameContext.Player.x;
        let dy = gameContext.Player.lastY - gameContext.Player.y;
        gameContext.cameraX -= dx;
        gameContext.cameraY -= dy;
        gameContext.ctx.translate(dx, dy);

        this.player.hsp = 0;
        this.player.vsp = 0;

        this.player.state = new NORMALstate(this.player);
    }




}


export default class Player extends fw.EntityWithSprite {
    constructor(x, y) {
        super(x, y);
        this.SPAWNCOORDS = [x, y];
        this.deathcounter = 0;
        this.state = new NORMALstate(this);
        this.spriteIndex = 0;
        this.grappleCD = 0;

        //movement
        this.vsp = 0;
        this.hsp = 0;
        this.jumpSpeed = 20;
        this.moveSpeed = 6;
        this.grav = 2;
        this.jumpcd = 0;

        this.lastX = x;
        this.lastY = y;
        gameContext.Player = this;

        gameContext.cameraX = this.x;
        gameContext.cameraY = this.y;

    }

    getLeft() {
        return this.x + 12;
    }
    getTop() {
        return this.y + 6;
    }

    getWidth() {
        return 40;
    }

    getHeight() {
        return 56;
    }

    die() {
        if (this.state.id != "DEADstate")
            this.state = new DEADstate(this);
    }


    move() {
        // H Collisions
        if (this.place_meeting(this.getLeft() + this.hsp, this.getTop(), Wall)) {
            while (!this.place_meeting(this.getLeft() + Math.sign(this.hsp), this.getTop(), Wall)) {
                this.x += Math.sign(this.hsp);
            }
            this.hsp = 0;
            if (this.state.id == "SWINGstate") {
                this.state.RopeAngle = Math.atan2(this.state.GrappleY - this.y, this.state.GrappleX - (this.getLeft() + this.getWidth() / 2));
                this.state.RopeOsc = 0;
                console.log(this.state.RopeOsc);
            }
        }
        this.x += this.hsp;

        // V Collision
        if (this.place_meeting(this.getLeft(), this.getTop() + this.vsp, Wall)) {
            while (!this.place_meeting(this.getLeft(), this.getTop() + Math.sign(this.vsp), Wall)) {
                this.y += Math.sign(this.vsp);
            }
            this.vsp = 0;
            if (this.state.id == "SWINGstate") {
                this.state.RopeAngle = Math.atan2(this.state.GrappleY - this.y, this.state.GrappleX - (this.getLeft() + this.getWidth() / 2));
                this.state.RopeOsc = 0;
            }
        }
        this.y += this.vsp;
    }





    update() {

        this.state.frame();

        this.lastX = this.x;
        this.lastY = this.y;
        this.move();


    }//update

    draw(ctx) {

        //ctx.fillRect(this.getLeft(), this.getTop(), this.getWidth(), this.getHeight());


        if (this.state.id == "SWINGstate") {
            ctx.lineWidth = 2;
            ctx.strokeStyle = "rgba(139,69,19,1)";
            ctx.beginPath();       // Start a new path
            ctx.moveTo(this.state.GrappleX, this.state.GrappleY);    // Move the pen to (30, 50)
            ctx.lineTo(this.getLeft() + this.getWidth() / 2, this.y + this.getHeight() / 2);  // Draw a line to (150, 100)
            ctx.stroke();          // Render the path
        }
        //draw player
        ctx.drawImage(this.image, Math.floor(this.spriteIndex / 5) * 64, 0, 64, 64, this.x, this.y, 64, 64);

        //ui
        ctx.fillStyle = '#000000';
        ctx.font = "15px Comic Sans MS";
        ctx.textAlign = "left";
        ctx.fillText('Coins left to get: ' + gameContext.coinCounter, gameContext.cameraX - canvas.width / 2 + 20, gameContext.cameraY - canvas.height / 2 + 50);

        //loading bar for rope
        let ropedrawLength = Math.floor((100 - this.grappleCD) / 100 * 64) - 16;
        ctx.drawImage(Player.Ropeimage, 0, 0, 8, ropedrawLength, this.x, this.y + 60, 8, -Math.max(ropedrawLength, 0));

        //show hitbox
        // ctx.fillRect(this.getLeft(), this.getTop(), this.getWidth(), this.getHeight());
    }



}
Player.images = {
    idle: fw.image('./sprites/player/idle.png'),
    jump_r: fw.image('./sprites/player/jump_r.png'),
    jump_l: fw.image('./sprites/player/jump_l.png'),
    run_r: fw.image('./sprites/player/run_r.png'),
    run_l: fw.image('./sprites/player/run_l.png'),
    dead: fw.image('./sprites/player/dead.png'),
}


Player.Ropeimage = fw.image('./sprites/player/rope.png');
Player.image = Player.images.idle;
Player.events = ['update', 'draw'];
