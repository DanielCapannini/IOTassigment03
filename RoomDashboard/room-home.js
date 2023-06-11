

let isLightsOn = false
let slider = document.getElementById("slider")
let lightSwitch = document.getElementById("switch")

window.onload = function () {
    lightSwitch = document.getElementById("switch")
    slider = document.getElementById("slider")
    setupSlicer()
    setupLight()
    lightSwitch.addEventListener("click", function () {
        console.log(lightSwitch.getAttribute("value"))
        console.log(isLightsOn)
        if (lightSwitch.getAttribute("value") == "on" && !isLightsOn) {
          const now = new Date();
          const year = now.getFullYear();
          const month = (now.getMonth() + 1).toString().padStart(2, '0');
          const day = now.getDate().toString().padStart(2, '0');
          const hours = now.getHours().toString().padStart(2, '0');
          const minutes = now.getMinutes().toString().padStart(2, '0');
          const seconds = now.getSeconds().toString().padStart(2, '0');
            const w = {
                type: "light",
                state: "True",
                start: `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`,
            }
            axios.post("room-date.php", w).then(response => {
                console.log(response)
            })
        }
        else if (lightSwitch.getAttribute("value") == "off" && isLightsOn) {
          const now = new Date();
          const year = now.getFullYear();
          const month = (now.getMonth() + 1).toString().padStart(2, '0');
          const day = now.getDate().toString().padStart(2, '0');
          const hours = now.getHours().toString().padStart(2, '0');
          const minutes = now.getMinutes().toString().padStart(2, '0');
          const seconds = now.getSeconds().toString().padStart(2, '0');
            const w = {
                type: "light",
                state: "False",
                start: `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`,
            }
            axios.post("room-date.php", w).then(response => {
                console.log(response)
            })
        }
    })
    slider.addEventListener("mousedown", function () {
        slider.addEventListener("mousemove", function () {
            slideRollerBlinds(this.value)
        })
    })
    slider.addEventListener("mouseup", function () {
        slider.removeEventListener("mousemove", function () {
            slideRollerBlinds(this.value)
        })
        updateWindow(this.value)
    })
    slider.addEventListener("click", function () {
        slideRollerBlinds(this.value)
    })

    fetch('lights.json')
  .then(response => response.json())
  .then(data => {
    let durations = {
        "accensione": 0,
        "spegnimento": 0
      };
      
      data.lights.forEach(light => {
        if(light.end != undefined){
        let start = parseDateTime(light.start);
        let end = parseDateTime(light.end);
        let duration = end.getTime() - start.getTime();
      
        if (light.state === "True") {
          durations.accensione += duration;
        } 
        if (light.state === "False") {
          durations.spegnimento += duration;
        }}
      });
      
      let totalTime = durations.accensione + durations.spegnimento;
      let ctx = document.getElementById('myChart').getContext('2d');
let myChart = new Chart(ctx, {
  type: 'pie',
  data: {
    labels: ['acceso', 'spento'],
    datasets: [{
      data: [durations.accensione, durations.spegnimento],
      backgroundColor: ['#07ff03', '#ed0707']
    }]
  },
  options: {
    title: {
      display: true,
      text: `Totale tempo di accensione e spegnimento: ${totalTime} ms`
    }
  }
});
  });

  fetch('lights.json')
  .then(response => response.json())
  .then(data => {
    let accensioniPerOra = Array(24).fill(0);

data.lights.forEach(light => {
    if(light.end != undefined){
  let start = parseDateTime(light.start);
  let end = parseDateTime(light.end);
  let duration = end.getTime() - start.getTime();

  if (light.state === "True") {
    let startHour = start.getHours();
    let endHour = end.getHours();

    if (startHour === endHour) {
      accensioniPerOra[startHour] += duration;
    } else {
      for (let h = startHour; h <= endHour; h++) {
        if (h === startHour) {
          accensioniPerOra[h] += (3600000 - start.getMinutes() * 60000 - start.getSeconds() * 1000 - start.getMilliseconds());
        } else if (h === endHour) {
          accensioniPerOra[h] += (end.getMinutes() * 60000 + end.getSeconds() * 1000 + end.getMilliseconds());
        } else {
          accensioniPerOra[h] += 3600000;
        }
      }
    }
  }}
});
let ctx = document.getElementById('myChart2').getContext('2d');
let myChart = new Chart(ctx, {
  type: 'bar',
  data: {
    labels: Array.from(Array(24), (_, i) => i.toString()),
    datasets: [{
      label: 'Durata accensione luce per ora',
      data: accensioniPerOra,
      backgroundColor: 'rgba(54, 162, 235, 0.2)',
      borderColor: 'rgba(54, 162, 235, 1)',
      borderWidth: 1
    }]
  },
  options: {
    scales: {
      yAxes: [{
        ticks: {
          beginAtZero: true
        }
      }]
    },
    title: {
      display: true,
      text: 'Durata accensione luce per ora'
    }
  }
});
  });
  console.log("ciao")
}

function parseDateTime(dateTimeString) {
    let dateTimeParts = dateTimeString.split(' ');
    let dateParts = dateTimeParts[0].split('-');
    let timeParts = dateTimeParts[1].split(':');
    return new Date(dateParts[0], dateParts[1] - 1, dateParts[2], timeParts[0], timeParts[1], timeParts[2]);
  }

function slideRollerBlinds(value) {
    
}

function updateWindow(value) {
    let a = parseInt(value)
    const now = new Date();
    const year = now.getFullYear();
    const month = (now.getMonth() + 1).toString().padStart(2, '0');
    const day = now.getDate().toString().padStart(2, '0');
    const hours = now.getHours().toString().padStart(2, '0');
    const minutes = now.getMinutes().toString().padStart(2, '0');
    const seconds = now.getSeconds().toString().padStart(2, '0');
      const w = {
          type: "window",
          state: parseInt(a),
          start: `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`,
      }
        console.log(w)
        axios.post("room-date.php", w).then(response => {
            console.log(response)
        })
}

function setupSlicer() {
    return axios.get("window.json").then((response) => {
        console.log(response)
        let windowData = response.data["window"]
        slider.setAttribute("value", windowData[windowData.length - 1].state)
    })
}

function setupLight(){
    return axios.get("lights.json").then((response) => {
        let lightData = response.data["lights"]
        isLightsOn = lightData[lightData.length - 1].state == "True" ? true : false
        lightSwitch.setAttribute("value", !isLightsOn ? "on" : "off")
    })
}