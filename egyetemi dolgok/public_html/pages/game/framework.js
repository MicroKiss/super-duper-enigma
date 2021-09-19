
import gameContext from './gameContext.js';

var fw = {};


onmousemove = function (e) { fw.MouseX = e.clientX; fw.MouseY = e.clientY; }
onmousedown = function(e) {
    if(e.button == 0) 
    gameContext.scene.fire('click', gameContext.ctx);
}


fw._pressedKeys = {}; //asszociatív tömbben tároljuk, hogy egy gomb le van-e nyomva
document.onkeydown = function(e) {
    fw._pressedKeys[e.which] = true;
};

document.onkeyup = function(e) {
    fw._pressedKeys[e.which] = false;
};

fw.isDown = function(key) {
    return fw._pressedKeys[key] === true;
};

fw.image = function(src) {
    var img = document.createElement('img');
    img.src = src;
    return img;
};

fw.load = function(images, onLoad, onProgress) {
    var loaded = 0;

    function checkLoaded() {
        if (onProgress) {
            onProgress(loaded / images.length * 100);
        }
        if (loaded === images.length) { //ha minden kép be volt töltve, akkor visszahívunk
            onLoad();
        }
    }

    for (var i = 0; i < images.length; i++) {
        if (images[i].width > 0) { //a kép be van töltve
            loaded++;
        } else { //eseménykezelõt rakunk a képre, ha nincs betöltve
            images[i].addEventListener('load', function() {
                loaded++;
                checkLoaded();
            });
        }
    }
    checkLoaded();
};

fw.rectIntersect = function(x1, y1, w1, h1, x2, y2, w2, h2) { //egyszerû metszés vizsgálat
    return x2 < x1 + w1 && x2 + w2 > x1 && y2 < y1 + h1 && y2 + h2 > y1;
};



fw.createIndex = function(scene, size) { //bin index készítés
    if (!size) {
        size = 64;
    }
    var grid = {};
    scene.entities.forEach(entity => {

        //entitás szélének meghatározása (cella szélek)
        var left = entity.getLeft();
        var top = entity.getTop();
        var cellLeft = Math.floor(left / size);
        var cellTop = Math.floor(top / size);
        var cellRight = Math.floor((left + entity.getWidth()) / size);
        var cellBottom = Math.floor((top + entity.getHeight()) / size);

        //végig megyünk az összes cellán, amit érint az entitás
        for (var x = cellLeft; x <= cellRight; x++) {
            for (var y = cellTop; y <= cellBottom; y++) {
                var cellKey = key(x, y);
                var cellData = grid[cellKey]; //az adott koordinátához tartozó cella infó lekérése
                if (!cellData) { //a cella üres volt
                    grid[cellKey] = [entity]; //a cella mostantól egy elemet tartalmaz: az entitást
                } else {
                    cellData.push(entity); //a cellához hozzáadunk még egy elemet
                }
            }
        }
    });

    function key(x, y) {
        return x + ',' + y;
    }

    return {
        query: function(left, top, width, height) {
            var cellLeft = Math.floor(left / size);
            var cellTop = Math.floor(top / size);
            var cellRight = Math.floor((left + width) / size);
            var cellBottom = Math.floor((top + height) / size);

            var result = [];
            for (var x = cellLeft; x <= cellRight; x++) {
                for (var y = cellTop; y <= cellBottom; y++) {
                    var cellKey = key(x, y);
                    var cellData = grid[cellKey]; //az adott koordinátához tartozó cella infó lekérése
                    if (!cellData) { //a cellában nincs elem
                        continue;
                    }
                    for (var j = 0; j < cellData.length; j++) { //a cella minden elemét belerakjuk, ha még nem volt benne
                        var entity = cellData[j];
                        if (result.indexOf(entity) !== -1) { //már benne van az eredmény tömbben
                            continue;
                        }
                        if (!fw.rectIntersect(left, top, width, height, entity.getLeft(), entity.getTop(), entity.getWidth(), entity.getHeight())) {
                            continue; //ha ugyan a cella stimmel, de mégsem metszik egymást
                        }
                        result.push(entity);
                    }
                }
            }
            return result;
        }
    };
};

fw.Entity = class Entity {
    constructor(x, y) {
        this.x = x;
        this.y = y;

        this._events = new Map();
    }

    getLeft() {
        return this.x;
    }

    getTop() {
        return this.y;
    }

    getWidth() {
        return 0;
    }

    getHeight() {
        return 0;
    }
};

fw.EntityWithSprite = class EntityWithSprite extends fw.Entity {
    constructor(x, y) {
        super(x, y);
        this.image = null;
    }

    draw(ctx) {
        //  if (!this.image) {
        //      return;
        //  }
        //  ctx.drawImage(this.image, this.x, this.y);
    }

    getWidth() {
        return this.image ? this.image.width : 0;
    }

    getHeight() {
        return this.image ? this.image.height : 0;
    }

    place_meeting(x, y, obj) {

        const entities = gameContext.index.query(
            x,
            y,
            this.getWidth(),
            this.getHeight()
        );

        for (let entity of entities)
            if (entity instanceof obj && entity != this)
                return true;
        return false;
    }
};
fw.EntityWithSprite.events = ['draw'];

fw.Scene = class Scene {
    constructor() {
        this.entities = new Set();
        this.entitiesByEvents = new Map();

        this.add.apply(this, arguments);
    }


    empty()
    {
        for(let entity of this.entities)
            this.remove(entity);

    }

    add() {
        for (const entity of arguments) {
            this.entities.add(entity);

            const events = this.getEvents(entity.constructor);
            events.forEach((listeners, ev) => {
                const data = {entity, listeners};
                if (this.entitiesByEvents.has(ev)) {
                    this.entitiesByEvents.get(ev).add(data);
                } else {
                    this.entitiesByEvents.set(ev, new Set([data]));
                }
            });
        }
    }

    remove(entity) {
        this.entities.delete(entity);
        const events = this.getEvents(entity.constructor);
        events.forEach((listeners, ev) => {
            let evs = this.entitiesByEvents.get(ev);
            evs.forEach(data => {
                if (data.entity === entity) {
                    evs.delete(data);
                }
            });
        });
    }

    fire(event, payload) {
        if (!this.entitiesByEvents.has(event)) {
            return;
        }

        const entities = this.entitiesByEvents.get(event);
        entities.forEach(data => {
            const entity = data.entity;
            for (const listener of data.listeners) {
                listener.call(entity, payload);
            }
        });
    }

    getEvents(constructor) {
        if (fw.Scene._eventsByClass.has(constructor)) {
            return fw.Scene._eventsByClass.get(constructor);
        }

        const events = new Map();
        fw.Scene._eventsByClass.set(constructor, events);
        while (true) {
            if (constructor.events) {
                for (const event of constructor.events) {
                    const listener = constructor.prototype[event];
                    if (events.has(event)) {
                        events.get(event).push(listener)
                    } else {
                        events.set(event, [listener]);
                    }
                }
            }

            let parent = Object.getPrototypeOf(constructor.prototype);
            if (!parent) {
                break;
            }
            constructor = parent.constructor;
        }
        return events;
    }
};
fw.Scene._eventsByClass = new Map();

export default fw;