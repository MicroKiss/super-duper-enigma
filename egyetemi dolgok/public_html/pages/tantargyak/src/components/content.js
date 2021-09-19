

var CONTENTMODES = {
    table: "table",
    image: "image"
}



let templateTableRow = (item) => `<tr>${item}</tr>`;
let templateTableHeadRow = (item) => `<tr>${item}</tr>`;
let templateTableHeadCell = (item) => `<th>${item}</th>`;
let templateTableCell = (item) => `<td>${item}</td>`;
let templateInputField = (name, value) => `<label for="${name}">"${name}": </label>
<input type="text" class="form-control" value="${value}" id="${name}">`;

function generateRow(...args) {
    let cells = [];
    args.forEach(element => {
        cells.push(templateTableCell(element));
    });

    return (templateTableRow(cells.join("")))
}
function generateHeadRow(...args) {
    let cells = [];
    args.forEach(element => {

        cells.push(templateTableHeadCell(element));
    });

    return (templateTableHeadRow(cells.join("")))
}




config.content.onclick = function (event) {

    let target = event.target; // where was the click?

    if (target.id == 'editDataButton') {

        let bodydata = { group: {}, groupId: 0, groupCategory: "" };

        $('#EditModal').find('input').each(function () {
            bodydata[$(this).attr('id')] = $(this).val();
        });
        bodydata["group"].id = bodydata.groupId;
        bodydata["group"].category = bodydata.groupCategory;
        delete bodydata.groupId;
        delete bodydata.groupCategory;

        dataService.PutMetaData(bodydata.mapId, bodydata);

        $("#EditModal").modal("hide");
    };

};



//This is the pop up window where we can update our map info
EditModal = function (data) {
    data.groupId = data.group.id;
    data.groupCategory = data.group.category;
    delete data.group;

    let fields = "";

    Object.keys(data).forEach((key) => {
        fields += templateInputField(key, data[key])
            ;
    });



    return `
<!-- Trigger the modal with a button -->
<button type="button" class="btn btn-info btn-lg" data-toggle="modal" data-target="#EditModal">Update metadata</button>

<!-- Modal -->
<div id="EditModal" class="modal fade" role="dialog">
  <div class="modal-dialog">

    <!-- Modal content-->
    <div class="modal-content">
      <div class="modal-header">
        <h4 class="modal-title">Metadata</h4>
      </div>
      <div class="modal-body">
          ${fields}

      <button id="editDataButton" type="submit" class="btn btn-primary">Submit</button>

      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
      </div>
    </div>

  </div>
</div>
`};





function initTable(datas) {


    let rows = "";

    datas.forEach((data) => {
        rows += generateRow(`<p onclick='initImage(${JSON.stringify(data)})'>${data.title}.</p>`,
            data.publisher, data.scale);
    })


    config.content.innerHTML = `	

    <input class="form-control" id="localSearchInput" onkeyup="localSearch()" type="text" placeholder="Filter result...">
            <div class="table-responsive">
                <table class="table table-striped table-hover table-condensed">
                    <thead class="thead-dark">
                        <tr>
                            <th>Title</th>
                            <th>Publisher</th>
                            <th>scale</th>
                        </tr>
                    </thead>
                    <tbody id="myTable"> 
                        ${rows}
                    </tbody>
                </table>
            </div>

`;
}


function localSearch() {
    var value = $("#localSearchInput").val().toLowerCase();
    $("#myTable tr").filter(function () {
        $(this).toggle($(this).text().toLowerCase().indexOf(value) > -1)
    });
}



var Drift;

function DriftZoom(level) {
    Drift.zoomFactor = Math.round(level);
}

function initImage(data) {

    let datacopy = JSON.parse(JSON.stringify(data));

    delete data.group;
    delete data.grFormat;
    delete data.regNumber;

    dataService.GetImageById(data.mapId).then(url => {
        delete data.mapId;


        config.content.innerHTML = `	
            <button data-toggle="collapse" data-target="#metadata" class="btn btn-info btn-block">Toggle metadata</button>


            <div id="metadata" class="collapse">

                <div class="table-responsive">
                    <table class="table table-striped table-hover">
                        <thead>
                            ${generateHeadRow(...Object.keys(data))}
                        </thead>
                        <tbody>
                            ${generateRow(...Object.values(data))}
                        </tbody>
                    </table>
                </div>

            ${EditModal(datacopy)}

            </div>

            <div class= "row" style="text-align: center">
            <div class="col-sm-6" >
            <h3>${data.title} </h3>
            </div>
            <div class="col-sm-6" >
            Zoom level: 
            <input type="range" class="form-control-range" min="2" max="10" onchange="DriftZoom(this.value)">
            </div>
            
                <div class="col-sm-12" >
                    <img src="${url}" width="100%" class="drift-trigger" data-zoom="${url}"  alt = "Couldn't load image">
                    <div id="drift-details" >

                </div>  
            </div>  
           
            `;

        Drift = new Drift(document.querySelector('.drift-trigger'), {
            paneContainer: document.querySelector('#drift-details'),
            // boundingBoxContainer: document.querySelector('#drift-details'),
            showWhitespaceAtEdges: false,
            inlinePane: 900,
            zoomFactor: 3,
            hoverBoundingBox: true,
            hoverDelay: 500,
        });


    }).catch(e => {
        console.error("sikertelen képlekérés", e);

        config.content.innerHTML = `	
        <button data-toggle="collapse" data-target="#metadata" class="btn btn-info btn-block">Toggle metadata</button>


        <div id="metadata" class="collapse">

            <div class="table-responsive">
                <table class="table table-striped table-hover">
                    <thead>
                        ${generateHeadRow(...Object.keys(data))}
                    </thead>
                    <tbody>
                        ${generateRow(...Object.values(data))}
                    </tbody>
                </table>
            </div>

        ${EditModal(datacopy)}

        </div>
        <img src="${'./assets/error_get_image.jpg'}" width="100%" alt="error image">
        `;

    })


}



function initContent(mode, data) {
    if (mode === CONTENTMODES.table)
        initTable(data);
    if (mode === CONTENTMODES.image)
        initImage(data);

}