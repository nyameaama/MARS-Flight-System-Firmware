var Xconnected = true

window.addEventListener("gamepadconnected", (event) => {
    handleConnectDisconnect(event, true);
    updateSticks();
});
  
window.addEventListener("gamepaddisconnected", (event) => {
    handleConnectDisconnect(event, false);
});

function handleConnectDisconnect(event, connected){
    if(connected == true){
        //Hide conntroller loading UI
        document.getElementById("controller-stat-check").style.visibility = "hidden";
        document.getElementById("emi-loading").style.visibility = "hidden";

        //Show controller connected UI
        document.getElementById("controller-screen1-connected").style.visibility = "visible";

        //Modify contrller status text in control viewer
        document.getElementById("controller-status").innerHTML = "Controller Connected";
    }else{
        //Hide controller connected UI
        document.getElementById("controller-screen1-connected").style.visibility = "hidden";

        //Show conntroller loading UI
        document.getElementById("controller-stat-check").style.visibility = "visible";
        document.getElementById("emi-loading").style.visibility = "visible";

        //Modify contrller status text in control viewer
        document.getElementById("controller-status").innerHTML = "No Controller Detected";
    }
    
}

function updateSticks() {
    setInterval(() => {
        const myGamepad = navigator.getGamepads()[0]; // use the first gamepad
    
        const lstick = document.getElementById("left-stick");
        lstick.innerHTML = `(${myGamepad.axes[0].toFixed(4)}, ${myGamepad.axes[1].toFixed(4)})`;

        const rstick = document.getElementById("right-stick");
        rstick.innerHTML = `(${myGamepad.axes[2].toFixed(4)}, ${myGamepad.axes[3].toFixed(4)})`;

        const rtrig = document.getElementById("right-trigger");
        rtrig.innerHTML = `(${myGamepad.buttons[7].value.toFixed(4)})`;
        
    }, 50) // update axes 5 times per second
  }

  