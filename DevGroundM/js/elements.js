var cPage = 1;

document.getElementById("emi-select").addEventListener("click", function () {
    utilitySwitcher(4);
});

document.getElementById("actions-select").addEventListener("click", function () {
    utilitySwitcher(2);
});

document.getElementById("logs-select").addEventListener("click", function () {
    utilitySwitcher(3);
});

document.getElementById("stats-select").addEventListener("click", function () {
    utilitySwitcher(1);
});

document.getElementById("mission-select").addEventListener("click", function () {
    utilitySwitcher(5);
});

document.getElementById("emi-mpopup").addEventListener("click", function () {
    var menu = document.getElementById("ECV-menu");
    menu.style.visibility = "visible";
});

document.getElementById("ECV-menu-close").addEventListener("click", function () {
    var closemenu = document.getElementById("ECV-menu");
    closemenu.style.visibility = "hidden";
});

document.getElementById("arm_seq_ui_close").addEventListener("click", function () {
    var closemenuArm = document.getElementById("arm_seq_ui");
    closemenuArm.style.visibility = "hidden";
});

document.getElementById("supdater-menu-button").addEventListener("click", function () {
    var menusupdater = document.getElementById("supdater-menu");
    menusupdater.style.visibility = "visible";
});

document.getElementById("supdater-menu-close").addEventListener("click", function () {
    var closemenusupdater = document.getElementById("supdater-menu");
    closemenusupdater.style.visibility = "hidden";
});

function hideStatsMenu(){
    var smnu = document.getElementById("initStat-menu");
    //Set no visibility
    smnu.style.visibility = "hidden";
}

function showStatsMenu(){
    var smnu = document.getElementById("initStat-menu");
    //Set no visibility
    smnu.style.visibility = "visible";
}

function hideActionsMenu(){
    var smnu = document.getElementById("actions-menu");
    //Set no visibility
    smnu.style.visibility = "hidden";
}

function showActionsMenu(){
    var smnu = document.getElementById("actions-menu");
    //Set no visibility
    smnu.style.visibility = "visible";
}

function hideLogsMenu(){
    var smnu = document.getElementById("mainTelem-menu");
    //Set no visibility
    smnu.style.visibility = "hidden";
}

function showLogsMenu(){
    var smnu = document.getElementById("mainTelem-menu");
    //Set no visibility
    smnu.style.visibility = "visible";
}

function hideEMIMenu(){
    var smnu = document.getElementById("emi-menu");
    //Set no visibility
    smnu.style.visibility = "hidden";
}

function showEMIMenu(){
    var smnu = document.getElementById("emi-menu");
    //Set no visibility
    smnu.style.visibility = "visible";
}

function showMissionMenu(){
    var smnu = document.getElementById("mission-menu");
    //Set no visibility
    smnu.style.visibility = "visible";
}

function hideMissionMenu(){
    var smnu = document.getElementById("mission-menu");
    //Set no visibility
    smnu.style.visibility = "hidden";
}

function utilitySwitcher(pageFlag){
    /*
        1 -> Stats Menu
        2 -> Actions Menu
        3 -> Logs Menu
        4 -> EMI Menu
        5 -> Mission Menu
    */
   //Hide previous page
   switch(cPage){
    case 1:
        hideStatsMenu();
        document.getElementById("stats-select").className = "nonactive";
        break;
    case 2:
        hideActionsMenu();
        document.getElementById("actions-select").className = "nonactive";
        break;
    case 3:
        hideLogsMenu();
        document.getElementById("logs-select").className = "nonactive";
        break;
    case 4:
        hideEMIMenu();
        document.getElementById("emi-select").className = "nonactive";
        break;
    case 5:
        hideMissionMenu();
        document.getElementById("mission-select").className = "nonactive";
        break;
}
   //Switch current page flag
    switch(pageFlag){
        case 1:
            showStatsMenu();
            document.getElementById("stats-select").className = "active";
            break;
        case 2:
            showActionsMenu();
            document.getElementById("actions-select").className = "active";
            break;
        case 3:
            showLogsMenu();
            document.getElementById("logs-select").className = "active";
            break;
        case 4:
            showEMIMenu();
            document.getElementById("emi-select").className = "active";
            break;
        case 5:
            showMissionMenu();
            document.getElementById("mission-select").className = "active";
            break;    
    }
    //Set new current page
    cPage = pageFlag;
}

var dragItem = document.querySelector("#wayPointContainer");
var container = document.querySelector("#mission-menu");

var active = false;
var currentX;
var currentY;
var initialX;
var initialY;
var xOffset = 0;
var yOffset = 0;

container.addEventListener("touchstart", dragStart, false);
container.addEventListener("touchend", dragEnd, false);
container.addEventListener("touchmove", drag, false);

container.addEventListener("mousedown", dragStart, false);
container.addEventListener("mouseup", dragEnd, false);
container.addEventListener("mousemove", drag, false);

function dragStart(e) {
  if (e.type === "touchstart") {
    initialX = e.touches[0].clientX - xOffset;
    initialY = e.touches[0].clientY - yOffset;
  } else {
    initialX = e.clientX - xOffset;
    initialY = e.clientY - yOffset;
  }

  if (e.target === dragItem) {
    active = true;
  }
}

function dragEnd(e) {
  initialX = currentX;
  initialY = currentY;

  active = false;
}

function drag(e) {
  if (active) {
  
    e.preventDefault();
  
    if (e.type === "touchmove") {
      currentX = e.touches[0].clientX - initialX;
      currentY = e.touches[0].clientY - initialY;
    } else {
      currentX = e.clientX - initialX;
      currentY = e.clientY - initialY;
    }

    xOffset = currentX;
    yOffset = currentY;

    setTranslate(currentX, currentY, dragItem);
  }
}

function setTranslate(xPos, yPos, el) {
  el.style.transform = "translate3d(" + xPos + "px, " + yPos + "px, 0)";
}


class Node{
    constructor(latitude, longitude, altitude){
        this.latitude = latitude;
        this.longitude = longitude;
        this.altitude = altitude;
        this.next = null;
    }
}

class Waypoint{
    constructor(){
        this.top = null;
        this.tail =null;
        this.id = 0;
    }

     addWayPoint(latitude,longitude,altitude){
        newNode = new Node(latitude,longitude,altitude);

        if(this.top == null){
            this.head = newNode;
            this.tail = newNode;
        }else{
            this.tail.next = newNode;
            this.tail= newNode;
        }
        id++;
    }

    deleteWayPoint(id){
    tempNode = top;
    parentNode = null;
    while(tempNode != null){
        if(tempNode.id == id){
            parentNode.next = tempNode.next;
        }
        parentNode = tempNode;
        tempNode = tempNode.next;
    }
    }
}
