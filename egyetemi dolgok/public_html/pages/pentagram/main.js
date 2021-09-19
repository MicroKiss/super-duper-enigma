var nevem = "Jani";
console.log(`Hello, ${nevem}, ${2019-1997} éves vagy!`);


const canvas=document.getElementById('canvas');

const ctx= canvas.getContext('2d');


const keys = new Set();
document.body.addEventListener('keydown',(e)=>{keys.add(e.which)}   );
document.body.addEventListener('keyup'  ,(e)=>{keys.delete(e.which)});


class Entity {
    constructor(image, x,y) {
      this.x = x;
      this.y = y;
      this.image_index = document.createElement('img');
      this.image_index.src= image;
      this.image_index.onload = () =>{requestAnimationFrame(update);};
      this.sprite_index = 0;
      this.dir = 0;
      this.speed = 4;

    }
  }


 penta = new Entity("penta.png",400,400);
 inner = new Entity("inner.png",400,400);
 outer = new Entity("outer.png",400,400);

 let degrees = 0;
 let degrees2 = 0;
 let degrees3 = 0;

function logic()
{
degrees+= 0.05;
degrees2-= 0.2;
degrees3-= 0.08;

}

function draw()
{
    ctx.fillStyle = "#611704";
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    ctx.save();
    ctx.translate(canvas.width/2,canvas.height/2);
    ctx.rotate(degrees  *Math.PI/180);
    ctx.drawImage(penta.image_index,-canvas.width/2,-canvas.height/2);
     ctx.restore();
     ctx.save();    
     ctx.translate(canvas.width/2,canvas.height/2);
     ctx.rotate(degrees2  *Math.PI/180);
     ctx.drawImage(inner.image_index,-canvas.width/2,-canvas.height/2);
     ctx.restore();
     ctx.save();    
     ctx.translate(canvas.width/2,canvas.height/2);
     ctx.rotate(degrees3  *Math.PI/180);
     ctx.drawImage(outer.image_index,-canvas.width/2,-canvas.height/2);
    ctx.restore();
}

function update()
{
    logic();
    draw();

    requestAnimationFrame(update);
}

