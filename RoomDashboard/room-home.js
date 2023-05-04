

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
    const datiGrafico = data.lights;

    const labels = datiGrafico.map(item => item.start);
    const dati = datiGrafico.map((item, index) => ({
      x: item.start,
      y: item.status === 'True' ? 1 : 0,
      end: index < datiGrafico.length - 1 ? datiGrafico[index+1].start : null
    }));

    const canvas = document.getElementById('grafico');
    const ctx = canvas.getContext('2d');

    const chart = new Chart(ctx, {
      type: 'line',
      data: {
        labels: labels,
        datasets: [{
          label: 'Stato luci',
          data: dati,
          backgroundColor: 'rgba(255, 99, 132, 0.2)',
          borderColor: 'rgba(255, 99, 132, 1)',
          borderWidth: 1,
          fill: false
        }]
      },
      options: {
        scales: {
          xAxes: [{
            type: 'time',
            time: {
              unit: 'second'
            }
          }],
          yAxes: [{
            ticks: {
              beginAtZero: true,
              max: 1,
              callback: function(value, index, values) {
                return value == 1 ? 'Acceso' : 'Spento';
              }
            }
          }]
        },
        tooltips: {
          callbacks: {
            label: function(tooltipItem, data) {
              const dato = data.datasets[tooltipItem.datasetIndex].data[tooltipItem.index];
              return dato.y == 1 ? 'Acceso' : 'Spento';
            }
          }
        },
        plugins: {
          filler: {
            propagate: true
          }
        }
      }
    });
  })
  .catch(error => {
    console.error(error);
  });
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