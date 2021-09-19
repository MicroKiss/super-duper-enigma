
var config = {
    components: ['./components/content.js',
        './components/query.js',
        './components/top_bar.js'],
    tools: [],
    css: ['./css/style.css'
        , './css/drift-basic.css'],
    query: document.querySelector("#query"),
    top_bar: document.querySelector("#top-bar"),
    content: document.querySelector("#content"),

    dataServiceUrl: 'https://editke.herokuapp.com/',
    //dataServiceUrl:"http://localhost:8080/",
    useMockData: false,
};

