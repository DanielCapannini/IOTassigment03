

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
    console.log(datiGrafico);

    // Ordina gli oggetti per orario di inizio
    //datiGrafico.sort((a, b) => (a.start > b.start) ? 1 : -1);

    let tempoFalse = 0;
    let tempoTrue = 0;
    let lastEnd = null;

    datiGrafico.forEach(item => {
      if (lastEnd !== null) {
        console.log(item.start);
        console.log(new o(item.start));
        const durata = new Date(item.start) - new Date(lastEnd);
        if (item.status === 'False') {
          tempoFalse += durata;
        } else {
          tempoTrue += durata;
        }
      }
      lastEnd = item.start;
    });

    console.log('Tempo False:', tempoFalse);
    console.log('Tempo True:', tempoTrue);
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