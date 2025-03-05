let topic = [
    "Course Introduction",
    "Development Environment & What to Eat for Dinner",
    "Course Timetable",
    "Psychological Tests",
    "Psychological Tests - Python Version",
    "Classes Suspended - Professor on Business Trip",
    "Classes Suspended - YZU School Anniversary",
    "Simple RPG"
];

let inputMonth, inputDay;
let startDate = new Date();
console.log(startDate);

function setMonthAndDate( startMonth, startDay ){
    console.log("[setMonthAndDate] Being Called");
    console.log(startMonth, startDay);

    startDate.setMonth(startMonth - 1, startDay);
    startDate.setHours(0);
    startDate.setMinutes(0);
    startDate.setSeconds(0);

    console.log(startDate);
}

document.addEventListener('DOMContentLoaded', function() {
    const inputDate = document.getElementById('inputDate');

    inputDate.addEventListener('change', function() {
        console.log("[inputDate] Being Called");

        const dateValue = inputDate.value;
        const dateParts = dateValue.split('-');

        inputMonth = parseInt(dateParts[1], 10);
        inputDay = parseInt(dateParts[2], 10);

        setMonthAndDate( inputMonth, inputDay );

        const courseTable = document.getElementById('courseTable');
        courseTable.innerHTML = '<tr><th>Session</th><th>Time</th><th>Theme</th></tr>';

        for (let i = 0; i < topic.length; i++) {
            const tr = document.createElement('tr');
            const tdSession = document.createElement('td');
            const tdDate = document.createElement('td');
            const tdTopic = document.createElement('td');

            const currentDate = new Date(startDate);
            currentDate.setDate(startDate.getDate() + i);

            tdSession.textContent = i + 1;
            tdDate.textContent = currentDate.toLocaleDateString('en-US', { month: 'numeric', day: 'numeric' });
            tdTopic.textContent = topic[i];

            tr.appendChild(tdSession);
            tr.appendChild(tdDate);
            tr.appendChild(tdTopic);
            courseTable.appendChild(tr);
            
            if (topic[i].includes("Classes Suspended")) {
                tr.style.backgroundColor = "rgb(168, 168, 168)";
            }
        }
    });
});

