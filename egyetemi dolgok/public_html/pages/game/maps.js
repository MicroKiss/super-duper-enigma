import fw from './framework.js';
import Player from './player.js';
import Wall from './wall.js';
import Button from './button.js';
import Dialogue from './dialogue.js';
import gameContext from './gameContext.js';
import Coin from './coin.js';
import Spike from './spike.js';



const W = Wall;
const _ = null;
const P = Player;
const C = Coin;
const S = Spike;

export default class Maps {

    constructor() {


        var scene = new fw.Scene();


        gameContext.scene = scene;

        this.setMap("rm_menu");

    };




    setMap(map)  //you can switch between gamerooms with this function
    {
        gameContext.currentLevel = map;
        gameContext.Player = null;
        gameContext.cameraX = 0;
        gameContext.cameraY = 0;
        gameContext.scene.empty();

        gameContext.scene.add(new Dialogue());

        var palya = [];


        switch (map) {
            case "rm_menu":

                gameContext.scene.add(new Button(canvas.width / 2 - 64 - canvas.width / 4, canvas.height / 2 - 64, "play"));
                gameContext.scene.add(new Button(0 - canvas.width / 2 + canvas.width / 4, canvas.height / 2 - 64, "help"));
                gameContext.scene.add(new Button(0 - canvas.width / 2 + 340, 0 - canvas.height / 2 + 100, "title"));
                break;
            case "rm_1":

                palya = [
                    [W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, P, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, W, W, W, C, _, _, _, S, _, _, _, _, _, S, S, _, _, _, _, _, _, _, _, _, _, _, _, C, W],
                    [W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, _, _, W, W, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W, _, _, _, _, _, _, _, _, C, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W, _, W, _, _, W, _, _, W, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W, _, _, _, _, _, W, _, _, _, W, _, _, _, _, W],
                    [W, _, _, C, C, _, _, _, _, _, _, _, _, _, W, _, _, C, W, _, _, _, _, _, _, _, _, _, _, _, W, _, _, W],
                    [W, W, W, W, W, W, W, W, W, W, _, _, _, _, W, W, W, W, W, W, W, W, _, _, W, W, W, W, W, W, W, W, W, W],
                    [W, W, W, W, W, W, W, W, W, W, _, _, _, _, _, _, _, _, _, _, _, _, _, W, W, W, W, W, W, W, W, W, W, W],
                    [W, W, W, W, W, W, W, W, W, W, S, _, _, _, _, _, _, _, _, _, _, _, W, W, W, W, W, W, W, W, W, W, W, W],
                    [W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W],
                ];
                gameContext.nextLevel = "rm_2";

                gameContext.Dialogue.updateText(["Oh I see I'm in a game",
                    "Seems like I have a rope ",
                    "I can use it with R ",
                    "All right let's go "]);


                break;
            case "rm_2":

                palya = [
                    [W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, C, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W, _, _, _, _, _, _, W],
                    [W, _, _, _, P, _, _, _, _, W, _, _, _, W, _, _, _, W, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, W, _, W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, W, W, W, W, W, _, W, W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, W, W, _, _, _, _, _, _, _, _, S, _, S, _, S, _, S, _, S, _, S, _, S, _, S, _, W],
                    [W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W],
                ];
                gameContext.nextLevel = "rm_3";
                gameContext.Dialogue.updateText(["Wow there is even a second level for this game",]);
                break;
            case "rm_3":

                palya = [
                    [W, W, W, W, W, W, W, W, W, W, W, W, W, W, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, P, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, W, _, _, _, _, _, C, _, _, W],
                    [W, _, W, W, W, W, _, _, _, _, _, S, _, _, W],
                    [W, _, _, _, _, _, W, W, W, W, W, W, W, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, W, W, W, W, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, S, S, _, _, _, _, W],
                    [W, _, _, _, _, _, W, W, W, W, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, C, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, W, W, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, W, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, W, W, _, _, _, _, _, _, _, W, _, _, W],
                    [W, _, _, _, _, _, W, W, W, _, _, W, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, W, _, _, W],
                    [W, C, _, _, _, _, _, _, _, S, S, W, _, C, W],
                    [W, W, W, W, W, W, W, W, W, W, W, W, W, W, W],
                ];
                gameContext.nextLevel = "rm_menu";
                gameContext.Dialogue.updateText(["All right last level",]);
                break;
            case "rm_help":

                palya = [
                    [W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, W],
                    [W, _, S, _, S, _, _, _, P, _, _, _, _, _, _, _, _, W],
                    [W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W],


                ];
                gameContext.Dialogue.updateText(
                    [
                        "In the game you can move via A/D buttons",
                        "You can jump with the spacebar",
                        "And you can throw a rope with the R button",
                        "This Game was made by MicroKiss for his university lesson",
                        "Hope you enjoyed it at least a little bit",
                        "Press ctrl+ R to return to the main menu"
                    ]
                );
                break;

            default:
                break;
        }




        for (let i = 0; i < palya.length; i++) {
            const row = palya[i];
            for (let j = 0; j < row.length; j++) {
                const type = row[j];
                if (!type) {
                    continue;
                }
                gameContext.scene.add(new type(j * 64, i * 64));
            }
        }



        gameContext.ctx.setTransform(1, 0, 0, 1, 0, 0);
        gameContext.ctx.translate(canvas.width / 2 - gameContext.cameraX, canvas.height / 2 - gameContext.cameraY);

    }//setmap

}//Maps

