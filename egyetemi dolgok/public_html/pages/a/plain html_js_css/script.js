import mockdata from './assets/mock_data.js';
global.mockdata = mockdata;




function Init() {
    InitQuery(mockdata.groups);
}





$(document).ready(function () {
    Init();
});



