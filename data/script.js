/**
    Script pour le service WEB
    @file script.js
    @author Enzo Richard
    @version 1.3 09/12/22 
*/

setInterval(function getTemperature(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if(this.status == 200) {
        document.getElementById("temp").innerHTML = this.responseText + " °C";
        }
    };
    xhttp.open("GET", "lireTemp", true);
    xhttp.send();
   }, 5000);



let boisOptions = [];
let error = null;
const errorDiv = document.querySelector(".error");
let info = "";
const infoDiv = document.querySelector(".info");

function getBois() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        let responseParsed = JSON.parse(this.responseText);
        if (this.readyState == 4 && this.status == 200) {
            for(let i = 0; i < responseParsed.length; i++) {
                let currentWood = responseParsed[i].name;
                let currentId = responseParsed[i].id;
                var x = document.getElementById("dropDown_TypeBois");
                var option = document.createElement("option");
                option.value = currentId;
                option.text = currentWood;
                x.add(option);
            } 

            //Refresh le contenu
            var siteHeader = document.getElementById('dropDown_TypeBois');
            siteHeader.style.display='none';
            siteHeader.offsetHeight; // no need to store this anywhere, the reference is enough
            siteHeader.style.display='block';

            getDetailsBois(document.getElementById("dropDown_TypeBois"));
        }
    };
    xhttp.open("GET", "getNomBois", true);
    xhttp.send();
}

function getDetailsBois(selectedObject){
    id = selectedObject.options[selectedObject.selectedIndex].value;

    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        console.log(this.responseText);
        const responseParsed = JSON.parse(this.responseText.slice(1, -1));
        console.table(responseParsed);
        if (this.readyState == 4 && this.status == 200) {
            // setWoodTemperature(responseParsed.temperature);
            // setWoodTemps(responseParsed.temps);
            document.getElementById("nomBois").innerHTML = selectedObject.options[selectedObject.selectedIndex].text;
            document.getElementById("nomBois2").innerHTML = selectedObject.options[selectedObject.selectedIndex].text;
            document.getElementById("typeBois").innerHTML = responseParsed.type;
            document.getElementById("origineBois").innerHTML = responseParsed.origine;
            document.getElementById("tempSechBois").innerHTML = responseParsed.drying /*+ " secondes"*/;
            document.getElementById("tempSechBois2").innerHTML = responseParsed.drying;
            document.getElementById("tempMinBois").innerHTML = responseParsed.temp /*+ " °C"*/;
            document.getElementById("tempMinBois2").innerHTML = responseParsed.temp + " °C";

            setTempSechEtCible();
        }
    }

    xhttp.open("GET", "getDetailsBois?id=" + id, true);
    xhttp.send();

}

function setTempSechEtCible()
{
    var tempCible = 20;
    var tempSech = 20;
    var xhttp = new XMLHttpRequest();
    tempCible = document.getElementById("tempMinBois").innerHTML;
    tempSech = document.getElementById("tempSechBois").innerHTML;
    if(this.status == 200) {
        document.getElementById("tempMinBois").innerHTML = this.responseText;
        document.getElementById("tempSechBois").innerHTML = this.responseText;
        console.log(this.responseText);
    };
    xhttp.open("GET", "setTempSechEtCible?tempCible=" + tempCible + "&tempSech=" + tempSech, true);
    xhttp.send();
}

function demarrerFour(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if(this.status == 200) {
            console.log(this.responseText);
        }
        }   ;
    xhttp.open("GET", "demarrerFour", true);
    xhttp.send();
}

setInterval(function getCompteur(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if(this.status == 200) {
        document.getElementById("compteurLecture").innerHTML = this.responseText + "s";
        }
    };
    xhttp.open("GET", "lireCompteur", true);
    xhttp.send();
   }, 1000);
