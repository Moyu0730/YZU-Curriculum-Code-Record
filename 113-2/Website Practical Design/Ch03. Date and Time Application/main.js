$(function(){
    $("#courseTable").append('<tr>' + '<th>Session</th>' + '<th>Time</th>' + '<th>Theme</th>' + '</tr>');

    var topicCount = topic.length;
    var millisecsPerDay = 24 * 60 * 60 * 1000;
    // console.log(topicCount);
    console.log("[main.js] Entered");

    for( let x = 0 ; x < topicCount ; ++x ){
        $("#courseTable").append(
            '<tr>' + 
            `<td> ${x+1} </td>` + 
            `<td> ${( new Date(startDate.getTime() + 7 * x * millisecsPerDay) ).toLocaleDateString('en-US', { month: 'numeric', day: 'numeric' }) } </td>` + 
            `<td> ${topic[x]} </td>` + 
            '</tr>'
        );
        
        var tr = document.getElementsByTagName("tr")[x+1];
        if (topic[x].includes("Classes Suspended")) {
            tr.style.backgroundColor = "rgb(168, 168, 168)";
        }
    }
})