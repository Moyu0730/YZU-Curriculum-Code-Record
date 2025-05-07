let twd_jpy_line = document.getElementById('jpy-line-chart');
let twd_jpy_data = JSON.parse(document.getElementById('exchangeData').innerHTML);
let usd_twd_line = document.getElementById('usd-line-chart');
let usd_twd_data = JSON.parse(document.getElementById('exchangeData').innerHTML);

// console.log(twd_jpy_data);
draw(twd_jpy_line, twd_jpy_data, 'twd-jpy', 'JPY');
draw(usd_twd_line, usd_twd_data, 'usd-twd', 'USD');

function draw( inputLine, inputData, type, title ){
    let trace = {};
    trace.type = "scatter";
    trace.mode = "lines";
    trace.name = "Team A";
    
    trace.text = [];
    
    trace.x = [];
    trace.y = [];
    
    for (let i = 0; i < inputData.length; i++) {
        trace.x[i] = inputData[i].date;
        trace.y[i] = inputData[i][type];
    }
    
    let resultData = [];
    resultData.push(trace);
    
    let layout = {
        margin: {
            t: 0
        },
        xaxis:{
            showline: true
        },
        yaxis:{
            showline: true
        },
        annotations:[
            {
                xref: 'paper',
                yref: 'paper',
                x: 0.5,
                y: 0.1,
                text: `${title} Exchange ${trace.x[0]} ~ ${trace.x.slice(-1)}`,
                showarrow:false,
                xanchor:'center',
                yanchor:'top',
                font:{
                    size:15,
                    color:'gray'
                }
            }
        ]
    };

    Plotly.newPlot(inputLine, resultData, layout);
}