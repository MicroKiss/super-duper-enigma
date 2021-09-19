config.query.onclick = function (event) {
    let target = event.target; // where was the click?

    if (target.id == 'defaultSearchButton') {
        dataService.GetMapsDefault($("#defaultSearchInput").val()).then(data => {

            initContent(CONTENTMODES.table, data)
        });
    }


    // advanced search
    if (target.id == 'advancedSearchButton') {
        let validinput = false;

        let inputs = [];

        $('#advancedSearch').find('input').each(function () {
            if (!$(this).get(0).checkValidity()) {
                validinput = false;
                return false;
            }

            if ($(this).attr('id') == "year_is_na") {
                if ($(this).is(':checked')) {
                    validinput = true;
                    inputs.push(`${$(this).attr('id')}=true`);
                }
            }
            else {
                if ($(this).val()) {
                    inputs.push(`${$(this).attr('id')}=${$(this).val()}`);
                    validinput = true;
                }
            }
        });

        if (!validinput)
            return;


        if ($("#group_id").val())
            inputs.push(`${$("#group_id").attr('id')}=${$("#group_id").val()}`);

        dataService.advancedSearch(inputs.join("&")).then(data => {
            initContent(CONTENTMODES.table, data);
        });
    }

};


yearIsNAChange = function () {
    if ($("#year_is_na").is(':checked')) {
        $("#year_from").attr('disabled', 'disabled');
        $("#year_from").val("");
        $("#year_to").attr('disabled', 'disabled');
        $("#year_to").val("");
    }
    else {
        $("#year_from").removeAttr('disabled');
        $("#year_to").removeAttr('disabled');
    }

}

function InitQuery() {
    dataService.GetGroups().then((data) => {

        let categorySelectOptions = `<option value = "" ></option > `;
        for (let i = 0; i < data.length; i++) {
            categorySelectOptions += `<option value = "${data[i].id}" > ${data[i].category}</option> `
        }

        config.query.innerHTML =
            `
<div class= "row" >
    <div class="col-sm-8">
        <input id="defaultSearchInput" type="text" class="form-control" placeholder="default search like: 'Budapest'" id="geodata"></input>
    </div>
    <div class="col-sm-4">
        <button id="defaultSearchButton" class="btn btn-primary btn-block">
            Search
        </button>
    </div>
</div >

<button class="btn btn-secondary btn-block" data-toggle="collapse" data-target="#advancedSearch">Toggle Advanced Search</button>

<div id="advancedSearch" class="collapse">
    <form>
        <div class="form-group">
            <div class="row">
            <div class="col-sm-6">
            <label for="title">Title:</label>
                <input type="text" class="form-control" id="title">
                </div>
                <div class="col-sm-6">
            <label for="group_id">Category:</label>
                <select id="group_id" class="custom-select">
                    ${categorySelectOptions}
                </select>
            </div>
            </div>


            <div class="row">
            <div class="col-sm-6">
            <label for="publisher">Publisher:</label>
                <input type="text" class="form-control" id="publisher">
                </div>
                <div class="col-sm-6">
            <label for="theme">Theme:</label>
                <input type="text" class="form-control" id="theme">
                </div>
                </div>


            <label>Year :</label>
                <div class="row">
                    <div class="col-sm-12 text-center" >
                        <div class="custom-control custom-switch">
                            <input type="checkbox" onchange="yearIsNAChange()" class="custom-control-input" id="year_is_na">
                            <label class="custom-control-label" for="year_is_na">Year is not provided in the database</label>
                        </div>
                    </div>
                </div>
            
                <div class="row">
                    <div class="col-sm-1">
                        <p class="text-center">from:</p>
                    </div>
                    <div class="col-sm-5">
                        <input type="number" min="1000" max="9999" class="form-control" id="year_from">
                    </div>
                    <div class="col-sm-1">
                        <p class="text-center">to:</p>
                    </div>
                    <div class="col-sm-5">
                        <input type="number" min="1000" max="9999" class="form-control" id="year_to">
                    </div>
                </div>

                <div class="row">
                <div class="col-sm-6">
            <label for="description">Description:</label>
                <input type="text" class="form-control" id="description">
                </div>
                <div class="col-sm-6">
            <label for="language">Language:</label>
                <input type="text" class="form-control" id="language">
                </div>
                </div>
                
                <div class="row">
                <div class="col-sm-6">
            <label for="remarks">Remarks:</label>
            <input type="text" class="form-control" id="remarks">
            </div>
            <div class="col-sm-6">
            <p class="text-center">Scale:</p>
            <input type="text" class="form-control" id="scale">

            </div>
            </div>
            </br>
            <div class="row">
                <div class="col-sm-1">
                    <p class="text-center">Resolution:</p>
                </div>
                <div class="col-sm-5">
                    <input type="number" min="1" class="form-control" id="resolution">
                </div>
            </div>
        </div>
    </form>
    <button id="advancedSearchButton" class="btn btn-primary btn-block">
    Advanced Search
    </button>
</div>
                
`;

    });


}