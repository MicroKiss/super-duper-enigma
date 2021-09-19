
function searchButton() {
    //console.log($("#mapselect option:selected").val());
    initContent(CONTENTMODES.table, $("#mapselect option:selected").val());

};

function InitQuery(data) {

    let html = `
    <div class="limiter">
    <div class="container-table100">
        <div class="wrap-table100">
            <div class="table100">
                <table>
                    <tr>
                        <th align="left">
                            <select id="mapselect">`;
    for (let i = 0; i < data.length; i++) {
        html += `<option value="${data[i].id}">${data[i].category}</option>`
    }
    html += `
                        </th>
                        <th>
                            <button onclick="searchButton()">Search</button>
                        </th>
                    </tr>
                </table>
            </div>
        </div>
    </div>
</div>
    `;


    global.query.innerHTML = html;

}