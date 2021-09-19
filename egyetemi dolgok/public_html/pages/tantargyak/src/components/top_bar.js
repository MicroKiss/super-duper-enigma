
config.top_bar.onclick = function (event) {

    if (event.target.id == 'loginButton') {
        console.log("clicked on loginbutton");

        //bejelentkezes
        dataService.Login($("#username").val(), $("#password").val()).then((result) => {
            if (result) {
                console.log("sikeres bejelentkezés");
                loggedInUser = true;
            }
            else {
                loggedInUser = false;
                console.log("sikertelen bejelentkezés");
            }
            initTopBar();
        })

    }
    else if (event.target.id == 'logOutButton') {
        console.log("clicked on logOutbutton");
        //kijelentkezes
        loginToken = btoa(`${defaultUser.username}:${defaultUser.password}`);
        loggedInUser = false;
        console.log("sikeres kijelentkezés");
        initTopBar();
    }
};


function initTopBar() {

    let loginform = ``;
    if (!loggedInUser) {
        loginform = `        
        <div class="input-group mb-3">
            <input type="text" class="form-control" value="Admin" name="username" id="username" placeholder="username">
            <input type="password" class="form-control" value ="password" name="password" id="password" placeholder="password">
            <div class="input-group-append">
                <button id="loginButton" class="btn btn-success">Login</button>
            </div>
        </div>`}
    else {
        loginform = `        
        <div class="input-group mb-3">
            <input type="text" disabled="disabled" class="form-control" name="username" id="username" placeholder="logged in">
            <input type="password" disabled="disabled" class="form-control" name="password" id="password" placeholder="********">
            <div class="input-group-append">
                <button id="logOutButton" class="btn btn-danger">Logout</button>
            </div>
        </div>`
    }

    config.top_bar.innerHTML = `
<div class="jumbotron text-center">
    <div class ="row">
        <div class="col-sm-4">
            ${loginform}
        </div>
        <div class="col-sm-4">
            <h1>Digitális Térképtár</h1>
        </div>
        <div class="col-sm-4">
           
        </div>
    </div>
</div>
`
}

initTopBar();
