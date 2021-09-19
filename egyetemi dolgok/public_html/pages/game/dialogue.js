import fw from './framework.js';
import gameContext from './gameContext.js';


//TODO : a szöveg karakterenként hoszabbodjon, ne egyből jelenjen meg az egész. DONE

export default class Dialogue extends fw.Entity {

    constructor() {
        super(0, 0);
        this.textArray = [""];
        this.start = Date.now();
        this.showLength = 0;
        this.showTime = 0;
        this.showLengthtimer = 2;
        gameContext.Dialogue = this;
        

        this.updateText([""]);


    }




    update() {
        if(!gameContext.Player)
            return;

        
        this.x = gameContext.Player.x - this.text.length * 17 / 2;
        this.y = gameContext.Player.y - 60;

        if ((Date.now() - this.start) / 1000 > this.showTime) 
        {
            this.showLength = 0;
            this.start = Date.now();
            this.textIndex++;
            if(this.textArray.length > this.textIndex)
            {
                this.text = this.textArray[this.textIndex];
                this.showTime = this.textArray[this.textIndex].length*0.15+1;
            }
            else
            {
                this.textArray = ["",]
                this.text = "";
                Dialogue.events = [];
            }
        }

        if(this.showLength < this.text.length && this.showLengthtimer < 0)
            {
            this.showLength++;
            this.showLengthtimer = 2;
            
            }
            this.showLengthtimer--;
    }

    updateText(str_array)
    {
        this.showLength = 0;
        this.showTime = 0;
        this.textArray = str_array;
        this.start = Date.now();
        this.textIndex = 0;
        this.text = this.textArray[this.textIndex];
        this.showTime = this.textArray[this.textIndex].length*0.15+1;
        Dialogue.events = ['draw', 'update'];
    }

    draw(ctx) {
        ctx.font = "30px Comic Sans MS";
        ctx.fillStyle = "rgba(0, 0, 0, 0.7)";
        ctx.textAlign = "center";

        for (let i = 0; i < this.showLength; ++i) {
            ctx.fillText(this.text.substring(i, i + 1), this.x + i * 17, this.y + 10 * Math.sin(Date.now() / 200 + i * 0.2));


        }

    }

}

Dialogue.events = ['update','draw'];

