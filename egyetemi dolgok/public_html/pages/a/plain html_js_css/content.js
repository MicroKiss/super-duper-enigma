CONTENTMODES = {
    table: "table",
    image: "image"
}


function initTable(category) {
    let data;
    if (category !== "3") {
        global.content.innerHTML = "";
        return;
    }


    data = global.mockdata.otherMaps;

    let html = `	<div class="limiter">
    <div class="container-table100">
        <div class="wrap-table100">
            <div class="table100">
                <table>
                    <thead>
                        `;
    html += `    
    <tr class="table100-head">
        <th>Title</th>
        <th>Publisher</th>
        <th>scale</th>
    </tr>
    </thead>
    <tbody>`;

    for (let i = 0; i < data.length; i++) {
        html += `<tr>`;
        html += `<td>`
        html += `<p onclick='initImage(${JSON.stringify(data[i])})'>${data[i].title}.</p>`;
        html += `</td>`;
        html += `<td>${data[i].publisher}</td>`;
        html += `<td>${data[i].scale}</td>`;
        html += `</tr >`;
    }
    html += `</tbody>
    </table>				</div>
    </div>
</div>
</div>`;


    global.content.innerHTML = html;
}

function initImage(data) {
    console.log(data);

    let imagesrc = global.mockdata.imagesrc;//get image src for data.mapId;



    let html = `<table align="center" >`;
    html += `    
    <tr>
        <th>Title</th>
        <th>Publisher</th>
        <th>scale</th>
    </tr>`;
    html += `    
    <tr>
        <td>${data.title}</th>
        <td>${data.publisher}</th>
        <td>${data.scale}</th>
    </tr>`;
    html += `</table >`;

    html += `<img src = "${imagesrc}"  class="center"   alt="Couln't load image"/>`;




    global.content.innerHTML = html;
}


function initContent(mode, data) {
    if (mode === CONTENTMODES.table)
        initTable(data);
    if (mode === CONTENTMODES.image)
        initImage(data);

}