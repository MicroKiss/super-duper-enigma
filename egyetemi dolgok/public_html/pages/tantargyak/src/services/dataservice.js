var dataService = {};
var defaultUser = { username: "Admin", password: "password" };
var loginToken = btoa(`${defaultUser.username}:${defaultUser.password}`);
var loggedInUser = false;

//example for usage : 
// dataService.GetSomething().then((data) => {
//     console.log(data);
// })

async function http(method, url = '', data = '') {
    console.log(config.dataServiceUrl + url);
    console.log(data);

    const response = await fetch(config.dataServiceUrl + url, {
        method: method,
        headers: new Headers({
            'Authorization': 'Basic ' + loginToken,
            'Content-Type': 'application/json',
            "Access-Control-Allow-Origin": "*"
        }),
        body: JSON.stringify(data),
    });
    return await response.json(); // parses JSON response into native JavaScript objects
}

async function httpGET(url = '') {


    const response = await fetch(config.dataServiceUrl + url, {
        method: 'GET',
        headers: new Headers({
            'Authorization': 'Basic ' + loginToken,
            'Content-Type': 'application/json',
            "Access-Control-Allow-Origin": "*"
        }),
    });
    return await response.json(); // parses JSON response into native JavaScript objects
}

///Login
// [POST] Felhasználó beléptetése : /users/login - Nyilvános Endpoint
dataService.Login = async function (username, password) {
    loginToken = btoa(`${username}:${password}`);
    try {
        const response = await fetch(config.dataServiceUrl + "users/login", {
            method: 'POST',
            headers: new Headers({
                'Authorization': 'Basic ' + loginToken,
                'Content-Type': 'application/json'
            }),
        });
        await response.json();
        return true;
    } catch (error) {
        console.error("sikertelen bejelentkezés");
        return false;
    }
}

/// PageController:

//  [GET] Alapvető információk az adatbázis tartalmáról : / - Publikus
dataService.GetInfo = function () {
    return httpGET("");
}

/// UserController:

//  [GET] Az összes felhasználó : /users - Admin joghoz kötött
dataService.GetUsers = function () {
    return httpGET("users");
}

/// GroupController:

//  [GET] Az összes Kategória : /groups - Admin/Manager joghoz kötött
dataService.GetGroups = function () {
    return httpGET("groups");
}

/// MapController:

//  [GET] Az összes Térkép : /maps - Admin/Manager joghoz kötött
dataService.GetMaps = function () {
    return httpGET("maps");
}
//  [GET] Egy Térkép ID alapján : /map/{id} - Admin/Manager joghoz kötött
dataService.GetMapById = function (id) {
    return httpGET(`maps/${id}`);
}
//  [GET] Az összes Térkép Kategória ID alapján : /maps/{groupId} - Admin/Manager joghoz kötött
dataService.GetMapsByGroupId = function (groupId) {
    return httpGET(`maps/group/${groupId}`);
}
//  [GET] Az elsó 10 Térkép lekérdezése : /maps/first10 - Admin/Manager joghoz kötött
dataService.GetMapsFirst10 = function () {
    return httpGET("maps/frist10");
}
//  [GET] Egy térkép képfájljának lekérdezése mapId alapján
dataService.GetImageById = function (id) {
    return httpGET(`images/${id}`);
}
//  [GET] az alap keresés, mely a  title,publisher,description,remarks propertikben keres szövegrészletet
dataService.GetMapsDefault = function (term) {
    return httpGET(`maps/defaultFilter?query=${term}`);
}
//  [GET] advancedSearch
dataService.advancedSearch = function (term) {
    return httpGET(`maps/advancedFilter?${term}`);
}

// [PUT] Egy térkép módosítása/frissítése ID alapján : /maps/{id} - Admin/Manager joghoz kötött

dataService.PutMetaData = function (id, data) {

    return http('PUT', `maps/${id}`, data);


}