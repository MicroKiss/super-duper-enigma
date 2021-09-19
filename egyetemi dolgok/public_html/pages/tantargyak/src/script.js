
$(document).ready(function () {





    $.getScript("config.js", () => {
        config.css.forEach(cssurl => {

            $('head').append($('<link rel="stylesheet" type="text/css" />').attr('href', cssurl));
        })

        let script_arr = [];

        if (config.useMockData) {
            script_arr.push('./assets/mock_data.js')
            script_arr.push('./services/mockdataservice.js')
        }
        else
            script_arr.push('./services/dataservice.js')

        $.getMultiScripts(script_arr).done(function () {
            script_arr = config.components;
            script_arr.concat(config.tools);

            $.getMultiScripts(script_arr).done(function () {
                Init();
            });
        });

    })

});

$.getMultiScripts = function (arr, path) {
    var _arr = $.map(arr, function (scr) {
        return $.getScript((path || "") + scr);
    });

    _arr.push($.Deferred(function (deferred) {
        $(deferred.resolve);
    }));

    return $.when.apply($, _arr);
}


function Init() {
    InitQuery();
}


