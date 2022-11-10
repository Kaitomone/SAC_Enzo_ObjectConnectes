setInterval(function getTemperature(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if(this.status == 200) {
        document.getElementById("temp").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "lireTemp", true);
    xhttp.send();
   }, 5000);



const title = document.querySelector(".title");
const boisSelect = document.getElementById("bois");
const BASE_URL = "http://51.79.84.135:9999/api";
let boisOptions = [];
let error = null;
const errorDiv = document.querySelector(".error");
let info = "";
const infoDiv = document.querySelector(".info");
//const authorization = eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImFsYSIsImlhdCI6MTY2MTUxNjAzNX0.4eGrq5XuJM1AcFnrxsRLHZp7e7E6v_u8lh6gEVAoU0Q;

function getBois() {
    return new Promise((resolve, reject) => {
    fetch(`${BASE_URL}/woodlist/authorization=${authorization}`)
        .then(data => data.json())
        .then(woodlist => {
        resolve(woodlist);
        })
        .catch(err => {
        reject(err);
        });
    });
}

getBois().then(data => {
    let option;
    console.log(data);
    Object.entries(data).forEach(bois => {
    option = document.createElement("option");
    option.text = bois[1].name;
    boisSelect.add(option);
    });
});


