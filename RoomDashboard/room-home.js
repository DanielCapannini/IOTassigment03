

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
            const w = {
                type: "light",
                state: "True",
                start: new Date().toLocaleTimeString([], {
                    hour: "2-digit",
                    minute: "2-digit",
                    second: "2-digit",
                }),
            }
            axios.post("room-date.php", w).then(response => {
                console.log(response)
            })
        }
        else if (lightSwitch.getAttribute("value") == "off" && isLightsOn) {
            const w = {
                type: "light",
                state: "False",
                start: new Date().toLocaleTimeString([], {
                    hour: "2-digit",
                    minute: "2-digit",
                    second: "2-digit",
                }),
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
        const w = {
            type: "window",
            state: parseInt(a),
            start: new Date().toLocaleTimeString([], {
                hour: "2-digit",
                minute: "2-digit",
                second: "2-digit",
            }),
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