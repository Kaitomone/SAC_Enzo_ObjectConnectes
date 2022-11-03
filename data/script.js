function getTemp()
{
    var temperature = 20;
    var xhttp = new XMLHttpRequest();
    temperature = document.getElementById("temp").value;
    xhttp.onreadystatechange = function() {
        if(this.status == 200) {
            document.getElementById("temp").innerHTML = this.responseText;
            console.log(this.responseText);
        }
    };
    xhttp.open("GET", "getTemp?temp=" + temperature, true);
    xhttp.send();
    alert("La température cible a été changé pour " + temperature)
}