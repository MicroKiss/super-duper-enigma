var dataService = {};
var defaultUser = { username: "Admin", password: "password" };
var loginToken = btoa(`${defaultUser.username}:${defaultUser.password}`);
var loggedInUser = false;

var loginInfo = { username: "Admin", password: "password" };

async function httpGet(url = '', loginInfo = { username: "Admin", password: "password" }) {
    const response = new Promise((resolutionFunc, rejectionFunc) => {
        resolutionFunc(mockdata[url]);
    })
    return await response // parses JSON response into native JavaScript objects
}

/// PageController:



// [POST] Felhasználó beléptetése : /users/login - Nyilvános Endpoint
dataService.Login = function (username, password) {
    loginToken = btoa(`${username}:${password}`);
    loggedInUser = !loggedInUser;
    return loggedInUser;
}


//  [GET] Alapvető információk az adatbázis tartalmáról : / - Publikus
dataService.GetInfo = function () {
    return httpGet("");
}

/// UserController:

//  [GET] Az összes felhasználó : /users - Admin joghoz kötött
dataService.GetUsers = function () {
    return httpGet("users");
}

/// GroupController:

//  [GET] Az összes Kategória : /groups - Admin/Manager joghoz kötött
dataService.GetGroups = function () {
    return httpGet("groups");
}
/// MapController:

//  [GET] Az összes Térkép : /maps - Admin/Manager joghoz kötött
dataService.GetMaps = function () {
    return httpGet("otherMaps");
}
//  [GET] Egy Térkép ID alapján : /map/{id} - Admin/Manager joghoz kötött
dataService.GetMapById = function (id) {
    return httpGet("maps/${id}");
}
//  [GET] Az összes Térkép Kategória ID alapján : /maps/{groupId} - Admin/Manager joghoz kötött
dataService.GetMapsByGroupId = function (groupId) {
    return httpGet("otherMaps");
    //return httpGet("maps/group/" + groupId);
}
//  [GET] Az elsó 10 Térkép lekérdezése : /maps/first10 - Admin/Manager joghoz kötött
dataService.GetMapsFirst10 = function () {
    return httpGet("otherMaps");
}

//  [GET] Egy térkép képfájljának lekérdezése mapId alapján
dataService.GetImageById = function (id) {
    return httpGet("imagesrc")
    //return httpGet(`/maps/image/${id}`);
}


//  [GET] az alap keresés, mely a  title,publisher,description,remarks propertikben keres szövegrészletet
dataService.GetMapsDefault = function (term) {
    return httpGet("otherMaps");
}

dataService.advancedSearch = function (term) {
    return httpGet("otherMaps");
}




async function httpPut(url = '', data = '') {
    const response = await fetch(config.dataServiceUrl + url, {
        method: 'PUT',
        headers: new Headers({
            'Authorization': 'Basic ' + btoa(`${loginInfo.username}:${loginInfo.password}`),
            'Content-Type': 'application/json'
        }),
        body: JSON.stringify(data),
    });
    return await response.json(); // parses JSON response into native JavaScript objects
}


dataService.PutMetaData = function (id, data) {
    return httpPut(`maps/${id}`, data);
}