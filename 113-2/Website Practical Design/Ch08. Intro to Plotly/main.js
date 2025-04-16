/* Session 1 */
// // Plotly element structure
// // HTML Element, Trace, Layout
// Plotly.newPlot("myGraph", [{
//     // The data for the graph
//     // x = x-axis, y = y-axis
//     x: [1, 2, 3, 4, 5],
//     y: [1, 2, 4, 8, 16]
// }], {
//     // Remove margins to make the graph fit the screen
//     // t = top, b = bottom, l = left, r = right
//     margin: { t: 25, b: 25, l: 25, r: 25 },
// });

/* Session 2 */
// Import the data from outside link
d3.csv('https://raw.githubusercontent.com/ryanchung403/dataset/refs/heads/main/harry_potter.csv').then(res =>{
    // Mke sure the data is in the correct format
    console.log(res);

    // Draw the graph after the data is loaded
    drawGraph(res);
});

// Unpack the data
function unpack(rows, key) {
    return rows.map(function (row) {
        return row[key];
    });
}

// Draw the graph using Plotly - Lab Work
function drawGraph(res){
    let year = unpack(res, "release_year");
    let budget = unpack(res, "budget");
    let revenue = unpack(res, "revenue");

    let BudgetLine = {
        // The type and mode of the graph
        type: "scatter", // "bar" for bar graph, "scatter" for line graph
        // mode: "lines+markers", "lines", "markers"
        mode: "lines+markers", // "lines" for line graph, "markers" for scatter plot
    
        // The name of the graph
        name: "Budget", // Name of the first set of data
        // The color of the graph
        marker: {
            color: "orange", // Color of the first set of data
            size: 10 // Size of the markers
        },
    
        // The data for the graph
        // x = x-axis, y = y-axis
        x: year,
        y: budget
    }
    
    let RevenueLine = {
        // The type and mode of the graph
        type: "scatter", // "bar" for bar graph, "scatter" for line graph
        // mode: "lines+markers", "lines", "markers"
        mode: "lines+markers", // "lines" for line graph, "markers" for scatter plot
    
        // The name of the graph
        name: "Revenue", // Name of the first set of data
        // The color of the graph
        marker: {
            color: "blue", // Color of the first set of data
            size: 10 // Size of the markers
        },
    
        // The data for the graph
        // x = x-axis, y = y-axis
        x: year,
        y: revenue
    }
    
    // The data for the graph
    let data = [BudgetLine, RevenueLine];
    
    // The Layout for the graph
    let layout = {
        // Remove margins to make the graph fit the screen
        // t = top, b = bottom, l = left, r = right
        margin: {
            t: 50,
            b: 50,
            l: 50,
            r: 50
        },
    
        // The title of the graph
        title: {
            text: "Harry Potter Movie Budget and Revenue",
        }
    };
    
    // Plotly element structure
    // HTML Element, Trace, Layout
    Plotly.newPlot("myGraph", data, layout);
}

// Draw the graph using Plotly - Class Work
// function drawGraph(res){
//     console.log(res);

//     let trace1 = {
//         // The type and mode of the graph
//         type: "scatter", // "bar" for bar graph, "scatter" for line graph
//         // mode: "lines+markers", "lines", "markers"
//         mode: "markers", // "lines" for line graph, "markers" for scatter plot
    
//         // The name of the graph
//         name: "Set 1", // Name of the first set of data
//         // The color of the graph
//         marker: {
//             color: "blue", // Color of the first set of data
//             size: 10 // Size of the markers
//         },
    
//         // The data for the graph
//         // x = x-axis, y = y-axis
//         x: [],
//         y: []
//     }
    
//     let trace2 = {
//         // The type and mode of the graph
//         type: "scatter", // "bar" for bar graph, "scatter" for line graph
//         // mode: "lines+markers", "lines", "markers"
//         mode: "lines+markers", // "lines" for line graph, "markers" for scatter plot
    
//         // The name of the graph
//         name: "Set 2", // Name of the first set of data
//         // The color of the graph
//         marker: {
//             color: "orange", // Color of the first set of data
//             size: 10 // Size of the markers
//         },
    
//         // The data for the graph
//         // x = x-axis, y = y-axis
//         x: [],
//         y: []
//     }
    
//     // Transform Data from data.js
//     for( let i = 0; i < set1.length; i++ ) {
//         trace1.x.push(set1[i][0]);
//         trace1.y.push(set1[i][1]);
//     }
    
//     for( let i = 0; i < set2.length; i++ ) {
//         trace2.x.push(set2[i][0]);
//         trace2.y.push(set2[i][1]);
//     }
    
//     // The data for the graph
//     let data = [trace1, trace2];
    
//     // The Layout for the graph
//     let layout = {
//         // Remove margins to make the graph fit the screen
//         // t = top, b = bottom, l = left, r = right
//         margin: {
//             t: 50,
//             b: 30,
//             l: 30,
//             r: 20
//         },
    
//         // The title of the graph
//         title: {
//             text: "My Plotly Graph",
//         }
//     };
    
//     // Plotly element structure
//     // HTML Element, Trace, Layout
//     Plotly.newPlot("myGraph", data, layout);
// }