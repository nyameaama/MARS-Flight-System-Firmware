//GLOBAL VARS & EVENT LISTENERS
          var altitudeX = 0;
          var latE, longE, satE, altE, pitchE, rollE, yawE, velE;
          var gyX, gyY, gyZ, acX, acY, acZ, _wfr, _wfl, _wrl, _wrr;
          var _tmp, _pres, _thr;

          var mostRecentToken = "";

          const selectElement = document.getElementById('DRONE-STATE');
          selectElement.addEventListener('change', function() {
            const selectedIndex = selectElement.selectedIndex;
            //If state change is to ARMED we call arm request sequence else send other state
            // 0 -> STANDBY
            // 1 -> ARMED
            // 2 -> BYPASS
            if(selectedIndex != 1){
              sendstateData(selectedIndex + 1,0,0,0,0);
            }else{
              //Pop out the arming sequence UI
              var openmenuArm = document.getElementById("arm_seq_ui");
              openmenuArm.style.visibility = "visible";
              //Dont allow state to be switched yet
              selectElement.selectedIndex = 0;
            }
            
          });

          document.getElementById("BPnotification-button").addEventListener("click", function () {
            removeBPnotification();
          });

          document.getElementById("arm_seq_auth_req").addEventListener("click", function () {
            //Send token request
            requestToken();
            writeToArmTerminal("<b>TOKEN REQUEST SENT");
          });

          document.getElementById("arm_seq_auth_autofill").addEventListener("click", function () {
            var token_entry = document.getElementById("arm_seq_ui-input");
            token_entry.value = mostRecentToken;
          });

          document.getElementById("arm_seq_auth_ARM").addEventListener("click", function () {
            //Send token to be authorized
            var token_entry = document.getElementById("arm_seq_ui-input").value;
            handleAuth(token_entry);
            writeToArmTerminal("<b>AUTH SENT");
          });

          document.getElementById("firmware-push-button").addEventListener("click", function () {
            handleFileUpload();
          });

          document.getElementById("newWayPoint-button").addEventListener("click", function () {
            addNewWayPoint();
          });


    function deleteWayPoint() {
            var waypointContainer = document.getElementById("wayPointContainer");
            waypointContainer.parentNode.removeChild(waypointContainer);
          }
    function addNewWayPoint() {
      // Create a new div element with class draggable
      var newWayPoint = document.createElement("div");
      newWayPoint.className = "wayPointContainer draggable";
    
      // Add the close button and form elements to the div
      newWayPoint.innerHTML = `
        <button class="btn-close">&times;</button>
        <form id="container_text">
          <label for="latitude">Latitude:</label>
          <input type="number" class="pill" id="latitude" name="latitude">
          <br>
          <label for="longitude">Longitude:</label>
          <input type="number" class="pill" id="longitude" name="longitude">
          <br>
          <label for="altitude">Altitude:</label>
          <input type="number" class="pill" id="altitude" name="altitude">
        </form>
      `;
    
      // Add the new div element to the mission menu
      var missionMenu = document.getElementById("mission-menu");
      missionMenu.insertBefore(newWayPoint, missionMenu.childNodes[2]);
    
      // Add an event listener to the close button to remove the div when clicked
      newWayPoint.querySelector(".btn-close").addEventListener("click", function() {
        newWayPoint.remove();
      });
    
      makeDraggable(newWayPoint);
    }
    function makeDraggable(element) {
      var active = false;
      var currentX;
      var currentY;
      var initialX;
      var initialY;
      var xOffset = 0;
      var yOffset = 0;
    
      element.addEventListener("mousedown", dragStart, false);
      element.addEventListener("mouseup", dragEnd, false);
      element.addEventListener("mousemove", drag, false);
    
      element.addEventListener("touchstart", dragStart, false);
      element.addEventListener("touchend", dragEnd, false);
      element.addEventListener("touchmove", drag, false);
    
      function dragStart(e) {
        if (e.type === "touchstart") {
          initialX = e.touches[0].clientX - xOffset;
          initialY = e.touches[0].clientY - yOffset;
        } else {
          initialX = e.clientX - xOffset;
          initialY = e.clientY - yOffset;
        }
    
        if (e.target === element) {
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
    
          setTranslate(currentX, currentY, element);
        }
      }
    
      function setTranslate(xPos, yPos, el) {
        el.style.transform = "translate3d(" + xPos + "px, " + yPos + "px, 0)";
      }
    }
          ////////////////////////////
          class LiveDataGraph {
          constructor(canvasId, maxDataPoints = 100, updateInterval = 1000) {
              this.container = document.getElementById(canvasId).parentElement;
              this.canvas = document.getElementById(canvasId);
              this.ctx = this.canvas.getContext('2d');
              this.data = [0];
              this.maxDataPoints = maxDataPoints;
              this.updateInterval = updateInterval;
              this.maxDataValue = 100; // Assuming data range is 0 to 100
              this.resizeCanvas();
              window.addEventListener('resize', () => this.resizeCanvas());
          }

          resizeCanvas() {
              this.canvas.width = this.container.clientWidth;
              this.canvas.height = this.container.clientHeight;
              this.dataWidth = this.canvas.width / this.maxDataPoints;
              this.dataHeight = this.canvas.height / this.maxDataValue;
              this.drawGraph();
          }

          updateGraph(newDataPoint) {
              this.data.push(newDataPoint);
              while (this.data.length > this.maxDataPoints) {
                  this.data.shift();
              }
              this.drawGraph();
          }

          drawGraph() {
              this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
              this.ctx.fillStyle = 'white';
              this.ctx.font = '12px Arial';
              this.ctx.textAlign = 'left'; // Align labels to the left

              // Add some padding to the top and bottom
              const paddingTop = 30;
              const paddingBottom = 10;

              // Draw y-axis label on the bottom left
              const yLabelBottom = this.canvas.height - paddingBottom - 12; // Bottom padding for y-labels considering font size
              this.ctx.fillText('Value', 5, yLabelBottom);

              this.ctx.textAlign = 'right';
              for (let i = 0; i <= 100; i += 20) {
                  const y = this.canvas.height - i * this.dataHeight - paddingBottom - 12; // Add padding at the bottom considering font size
                  this.ctx.fillText(i.toString(), 35, y);
              }

              this.ctx.strokeStyle = 'white';
              this.ctx.lineWidth = 2;
              this.ctx.beginPath();
              for (let i = 0; i < this.data.length; i++) {
                  const x = i * this.dataWidth + 40; // Add padding on the left
                  const y = this.canvas.height - this.data[i] * this.dataHeight - paddingBottom - 12; // Subtract padding for the line considering font size
                  if (i === 0) {
                      this.ctx.moveTo(x, y);
                  } else {
                      this.ctx.lineTo(x, y);
                  }
                  if (i % 10 === 0) {
                      this.ctx.fillText(i.toString(), x, this.canvas.height - paddingBottom - 18); // Adjust the y-coordinate for labels considering font size
                  }
              }
              this.ctx.stroke();

              // Draw x-axis label on the bottom left
              const xLabelBottom = this.canvas.height - paddingBottom +10; // Bottom padding for x-label considering font size
              this.ctx.textAlign = 'left';
              this.ctx.fillText('Time', 5, xLabelBottom);

              // Draw y-axis label on the top left
              this.ctx.textAlign = 'left';
              this.ctx.fillText('Value', 5, paddingTop + 20); // Add padding to the top
          }

      }
      const sampleGraph = new LiveDataGraph('AltCanvas');

      function getRandomDataPoint() {
          return Math.random() * 100;
      }

      function sendBPnotification(){
        var setMenu = document.getElementById("BPnotification");
        setMenu.style.visibility = "visible";
        setMenu.style.pointerEvents = "auto";

        var Section0 = document.getElementById("config-menu");
        Section0.style.filter = "blur(4px)";
        Section0.style.pointerEvents = "none";

        var Section1 = document.getElementById("map-ind-area");
        Section1.style.filter = "blur(4px)";
        Section1.style.pointerEvents = "none";

        var Section2 = document.getElementById("terminal-area");
        Section2.style.filter = "blur(4px)";
        Section2.style.pointerEvents = "none";

        var Section3 = document.getElementById("data-area");
        Section3.style.filter = "blur(4px)";
        Section3.style.pointerEvents = "none";

        var Section4 = document.getElementById("stats-menu");
        Section4.style.filter = "blur(4px)";
        Section4.style.pointerEvents = "none";

        var Section5 = document.getElementById("attitude-ind-area");
        Section4.style.filter = "blur(4px)";
        Section4.style.pointerEvents = "none";
      }

      function removeBPnotification(){
        var setMenu = document.getElementById("BPnotification");
        setMenu.style.visibility = "hidden";
        setMenu.style.pointerEvents = "none";

        var Section0 = document.getElementById("config-menu");
        Section0.style.filter = "blur(0px)";
        Section0.style.pointerEvents = "auto";

        var Section1 = document.getElementById("map-ind-area");
        Section1.style.filter = "blur(0px)";
        Section1.style.pointerEvents = "auto";

        var Section2 = document.getElementById("terminal-area");
        Section2.style.filter = "blur(0px)";
        Section2.style.pointerEvents = "auto";

        var Section3 = document.getElementById("data-area");
        Section3.style.filter = "blur(0px)";
        Section3.style.pointerEvents = "auto";

        var Section4 = document.getElementById("stats-menu");
        Section4.style.filter = "blur(0px)";
        Section4.style.pointerEvents = "auto";

        var Section5 = document.getElementById("attitude-ind-area");
        Section4.style.filter = "blur(0px)";
        Section4.style.pointerEvents = "auto";
      }



      function updateGraph() {
          sampleGraph.updateGraph(altitudeX);
          setTimeout(updateGraph, sampleGraph.updateInterval);
      }

      ///////////////////////////////////////////////////////////////
      //UPDATE PAGE
      function updatePageContinuously(){
            updateGraph();
            updateW1();
            updateGPS();
            updateIMU1();
            updateIMU2();
            updateAMB();
            updateBATT();
            //updateNative();
          }

      setInterval(updatePageContinuously, 1000);

      ///////////////////////////////////////////////////////////////
      


        const terminalDiv = document.getElementById('terminal');
const output = document.getElementById('output');
const input = document.getElementById('input');

let currentPage = 'main'; // Default current page is 'main'

input.addEventListener('keydown', (event) => {
    if (event.key === 'Enter') {
        event.preventDefault();
        const command = input.value.trim();
        input.value = '';
        executeCommand(command);
    }
});

function executeCommand(command) {
    //const response = '> ' + command + '\n';
    //input.value += response;
    
    if (currentPage === 'main') {
        handleMainPageCommand(command);
    } 
    else if (currentPage === 'fdpage1') {
      handleFDPage2Command(command)
    } 
    else if (currentPage === 'pfpage1') {
        handlePreflightPageCommand(command);
    } 
    else if (currentPage === 'hardwareConfig') {
      handlehardwareConfigPageCommand(command);
    }
    else if (currentPage === 'SWPpage') {
      handleSWPPageCommand(command);
    }
    else if (currentPage === 'MWPpage') {
      handleMWPPageCommand(command);
    }
    else if (currentPage === 'imuStat') {
      handleIMUPPageCommand(command);
    }
    else if (currentPage === 'gpsStat') {
      handleGPSPageCommand(command);
    }
    else if (currentPage === 'syspage1') {
      handleSYSPageCommand(command);
    }
    else if (currentPage === 'targetLatInput') {
      handleLatInputPageCommand(command);
    }
    else if (currentPage === 'targetLongInput') {
      handleLongInputPageCommand(command);
    }
    else if (currentPage === 'cruiseAltInput') {
      handleCAltInputPageCommand(command);
    }
    else if (currentPage === 'targetVelocityInput') {
      handleVelInputPageCommand(command);
    }
    else if (currentPage === 'targetAltInput') {
      handleTAltInputPageCommand(command);
    }
    else if (currentPage === 'FLInput') {
      handleFLInputPageCommand(command);
    }
    else if (currentPage === 'FRInput') {
      handleFRInputPageCommand(command);
    }
    else if (currentPage === 'RLInput') {
      handleRLInputPageCommand(command);
    }
    else if (currentPage === 'RRInput') {
      handleRRInputPageCommand(command);
    }
    else if (currentPage === 'THRInput') {
      handleTHRInputPageCommand(command);
    }
    terminalDiv.scrollTop = output.scrollHeight;
}

// Helper function to show menu options
function showMenuOptions(options) {
    output.textContent += options.join('  ') + '\n';
}

// Helper function to handle navigation between pages
function changePage(pageName) {
    currentPage = pageName;
    clearOutput();
    switch (pageName) {
      case "main":
      outputOnInit();
      break;
    case "fdpage1":
      FDPAGE1();
      break;
    case "pfpage1":
      PFPAGE1();
      break;
    case "hardwareConfig":
      hardwarePage();
      break;
    case 'gpsStat':
      gpsStatPage();
      break;
    case 'imuStat':
      imuStatPage();
      break;
    case 'SWPpage':
      SWPpage();
      break;
    case 'MWPpage':
      MWPpage();
      break;
    case 'syspage1':
      SYSpage();
      break;
    case 'targetLatInput':
      targetLatInput();
      break;
    case 'targetLongInput':
      targetLongInput();
      break;
    case 'targetAltInput':
      targetAltInput();
      break;
    case 'cruiseAltInput':
      cruiseAltInput();
      break;
    case 'targetVelocityInput':
      targetVelocityInput();
      break;
    case 'FLInput':
      FLInput();
      break;
    case 'FRInput':
      FRInput();
      break;
    case 'RLInput':
      RLInput();
      break;
    case 'RRInput':
      RRInput();
      break;
    case 'THRInput':
      THRInput();
      break;
    default:
      //dayName = "Invalid Input";
  }
}

function outputOnInit() {
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\nFLIGHT DIRECTOR [1]',
    '              SYS MISC [2]',
    '\n\n\n\n\n\nPREFLIGHT [3]',
    '               CONFIGURATION [4]',
  ]);
  showMenuOptions(['\n\n\n\n\n< BACK', '                                 NEXT >']);
}

function PFPAGE1() {
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n             FIRMWARE: V1.0',
    '         \n\n             VEHICLE ID: 0001',
    '\n\n\n                ERROR DUMP',

  ]);
  showMenuOptions(['\n\n\n\n\n\n\n\n< BACK', '                            ']);
}

function FDPAGE1() {
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n\n               SINGLE WAYPOINT [1]',
    '\n\n\n\n\n\n               MULTI WAYPOINT [2]',
  ]);
  showMenuOptions(['\n\n\n\n\n\n< BACK', '                               NEXT >']);
}

// Clear the output
function clearOutput() {
    output.textContent = '';
}

// Function to handle commands on the main page
function handleMainPageCommand(command) {
    switch (command) {
        case '1':
            changePage('fdpage1');
            break;
        case '2':
            changePage('syspage1');
            break;
        case '3':
            changePage('pfpage1');
            break;
        case '4':
            changePage('hardwareConfig');
            break;
        default:
            // Handle unknown commands
            input.value += '> Invalid command';
            break;
    }
}

function handleFDPage2Command(command){
  switch (command) {
        case '1':
            changePage('SWPpage');
            break;
        case '2':
            changePage('MWPpage');
            break;
        case '<':
            changePage('main');
            break;
        case '>':
            changePage('SWPpage');
            break;
        default:
            // Handle unknown commands
            input.value += '> Invalid command';
            break;
    }
}
// Function to handle commands on the Preflight page
function handlePreflightPageCommand(command) {
  switch (command) {
        case '<':
          changePage('main');
            break;
        case '>':
            //changePage('imuStat');
            break;
        default:
            // Handle unknown commands
            input.value += '> Invalid command';
            break;
    }
}

function handleSYSPageCommand(command) {
  switch (command) {
        case '<':
          changePage('main');
            break;
        case '>':
            //changePage('imuStat');
            break;
        case '1':
            changePage('FLInput');
            break;
        case '2':
            changePage('FRInput');
            break;
        case '3':
            changePage('RLInput');
            break;
        case '4':
            changePage('RRInput');
            break;
        case '5':
            changePage('THRInput');
            break;
        default:
            // Handle unknown commands
            input.value += '> Invalid command';
            break;
    }
}

// Function to handle commands on the Wing Configuration page
function handlehardwareConfigPageCommand(command) {
  switch (command) {
        case '1':
            changePage('imuStat');
            break;
        case '2':
            changePage('gpsStat');
            break;
        case '<':
            changePage('main');
            break;
        case '>':
            changePage('imuStat');
            break;
        default:
            // Handle unknown commands
            input.value += '> Invalid command';
            break;
    }
}

function handleIMUPPageCommand(command) {
  switch (command) {
        case '<':
            changePage('hardwareConfig');
            break;
        case '>':
            //changePage('imuStat');
            break;
        default:
            // Handle unknown commands
            input.value += '> Invalid command';
            break;
    }
}

function handleGPSPageCommand(command) {
  switch (command) {
        case '<':
            changePage('hardwareConfig');
            break;
        case '>':
            //changePage('imuStat');
            break;
        default:
            // Handle unknown commands
            input.value += '> Invalid command';
            break;
    }
}

function handleSWPPageCommand(command) {
  switch (command) {
        case '<':
            changePage('fdpage1');
            break;
        case '>':
            //changePage('imuStat');
            break;
          case '1':
            changePage('targetLatInput');
            break;
          case '2':
            changePage('targetLongInput');
            break;
          case '3':
            changePage('targetAltInput');
            break;
          case '4':
            changePage('cruiseAltInput');
            break;
          case '5':
            changePage('targetVelocityInput');
            break;
        default:
            // Handle unknown commands
            input.value += '> Invalid command';
            break;
    }
}

function handleMWPPageCommand(command) {
  switch (command) {
        case '<':
          changePage('fdpage1');
            break;
        case '>':
            //changePage('imuStat');
            break;
        default:
            // Handle unknown commands
            input.value += '> Invalid command';
            break;
    }
}

function handleLatInputPageCommand(command) {
  if (isValidLatitude(command)) {
    // Send Data
    sendFLIGHTDIRECTORSWP(command,0,0,0,0);
    // Move page step back
    changePage('SWPpage');
  } else if(command == '<') {
    changePage('SWPpage');
  }else{
    // Handle invalid input
    input.value += '> Invalid Target Latitude';
  }
}

function handleLongInputPageCommand(command) {
  if (isValidLongitude(command)) {
    // Send Data
    sendFLIGHTDIRECTORSWP(0,command,0,0,0);
    // Move page step back
    changePage('SWPpage');
  } else if(command == '<') {
    changePage('SWPpage');
  }else{
    // Handle invalid input
    input.value += '> Invalid Target Longitude';
  }
}

function handleTAltInputPageCommand(command) {
  if (isValidAltitude(command)) {
    // Send Data
    sendFLIGHTDIRECTORSWP(0,0,command,0,0);
    // Move page step back
    changePage('SWPpage');
  } else if(command == '<') {
    changePage('SWPpage');
  }else{
    // Handle invalid input
    input.value += '> Invalid Target Altitude';
  }
}

function handleCAltInputPageCommand(command) {
  if (isValidAltitude(command)) {
    // Send Data
    sendFLIGHTDIRECTORSWP(0,0,0,command,0);
    // Move page step back
    changePage('SWPpage');
  } else if(command == '<') {
    changePage('SWPpage');
  }else{
    // Handle invalid input
    input.value += '> Invalid Cruise Altitude';
  }
}

function handleVelInputPageCommand(command) {
  if (isValidVelocity(command)) {
    // Send Data
    sendFLIGHTDIRECTORSWP(0,0,0,0,command);
    // Move page step back
    changePage('SWPpage');
  } else if(command == '<') {
    changePage('SWPpage');
  }else{
    // Handle invalid input
    input.value += '> Invalid Target Velocity';
  }
}

function handleFLInputPageCommand(command) {
  if (isValidWingAngle(command)) {
    // Send Data
    sendSYSMISC(command,0,0,0,0);
    // Move page step back
    changePage('syspage1');
  } else if(command == '<') {
    changePage('syspage1');
  }else{
    // Handle invalid input
    input.value += '> Invalid Wing Value';
  }
}

function handleFRInputPageCommand(command) {
  if (isValidWingAngle(command)) {
    // Send Data
    sendSYSMISC(0,command,0,0,0);
    // Move page step back
    changePage('syspage1');
  } else if(command == '<') {
    changePage('syspage1');
  }else{
    // Handle invalid input
    input.value += '> Invalid Wing Value';
  }
}

function handleRLInputPageCommand(command) {
  if (isValidWingAngle(command)) {
    // Send Data
    sendSYSMISC(0,0,command,0,0);
    // Move page step back
    changePage('syspage1');
  } else if(command == '<') {
    changePage('syspage1');
  }else{
    // Handle invalid input
    input.value += '> Invalid Wing Value';
  }
}

function handleRRInputPageCommand(command) {
  if (isValidWingAngle(command)) {
    // Send Data
    sendSYSMISC(0,0,0,command,0);
    // Move page step back
    changePage('syspage1');
  } else if(command == '<') {
    changePage('syspage1');
  }else{
    // Handle invalid input
    input.value += '> Invalid Wing Value';
  }
}

function handleTHRInputPageCommand(command) {
  if (isValidThrottle(command)) {
    // Send Data
    sendSYSMISC(0,0,0,0,command);
    // Move page step back
    changePage('syspage1');
  } else if(command == '<') {
    changePage('syspage1');
  }else{
    // Handle invalid input
    input.value += '> Invalid Throttle Value';
  }
}

// Function to check if a number is a valid latitude
function isValidLatitude(latitude) {
  const latitudeFloat = parseFloat(latitude);
  if (!isNaN(latitudeFloat) && latitudeFloat >= -90 && latitudeFloat <= 90) {
    return true;
  }
  return false;
}

// Function to check if a number is a valid longitude
function isValidLongitude(longitude) {
  // Longitude ranges from -180 to 180 degrees
  return !isNaN(longitude) && Math.abs(longitude) <= 180;
}

// Function to check if a number is a valid altitude
function isValidAltitude(altitude) {
  // Altitude can be any real number (positive, negative, or zero)
  return !isNaN(altitude);
}

// Function to check if a number is a valid velocity
function isValidVelocity(velocity) {
  // Velocity should be non-negative (assuming it represents speed)
  return !isNaN(velocity) && velocity >= 0;
}

// Function to check if a wing angle is valid
function isValidWingAngle(angle) {
  // Velocity should be non-negative (assuming it represents speed)
  if(angle >= 0 && angle <= 180){
    return true;
  }
  return false;
}

// Function to check if throttle value is valid
function isValidThrottle(value) {
  // Velocity should be non-negative (assuming it represents speed)
  if(value >= 0 && value <= 100){
    return true;
  }
  return false;
}


function SWPpage(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n SINGLE WAYPOINT',
    '\n\n\n           Target Latitude [1]: 0.000',
    '\n\n          Target Longitude [2]: 0.000',
    '\n\n           Target Altitude [3]: 0.000',
    '\n\n           Cruise Altitude [4]: 0.000',
    '\n\n                  Velocity [5]: 0.000',
  ]);
  showMenuOptions(['\n\n< BACK', '                                NEXT >']);
}

function MWPpage(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n MULTI WAYPOINT',
    '\n\n\n\n\n                   NO DATA'
  ]);
  showMenuOptions(['\n\n\n\n\n\n\n\n< BACK', '                            NEXT >']);
}

function hardwarePage(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n\n\n\n\nIMU[1]',
    '                             GPS[2]',
  ]);
  showMenuOptions(['\n\n\n\n\n\n\n\n< BACK', '                            NEXT >']);
}

function imuStatPage(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n IMU DATA',
    '\n\n                   VX: ' + gyX,
    '\n\n                   VY: ' + gyY,
    '\n\n                   VZ: ' + gyZ,
    '\n\n                 ACCX: ' + acX,
    '\n\n                 ACCY: ' + acY,
    '\n\n                 ACCZ: ' + acZ,
  ]);
  showMenuOptions(['\n< BACK', '                           ']);
}

function gpsStatPage(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n GPS DATA',
    '\n\n                LATITUDE: ' + latE,
    '\n\n               LONGITUDE: ' + longE,
    '\n\n                ALTITUDE: ' + altitudeX,
    '\n\n              SATELLITES: ' + satE,
    '\n\n                VELOCITY: ' + velE,
  ]);
  showMenuOptions(['\n\n\n< BACK', '                            ']);
}

function SYSpage(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\nSample the full command of the four wing servos and motor, providing precise control over their movements and operations. The vehicle must be in STANDBY mode',
    '\n\n            FRONT-LEFT WING [1]: ' + _wfl,
    '\n\n           FRONT-RIGHT WING [2]: ' + _wfr,
    '\n\n             REAR-LEFT WING [3]: ' + _wrl,
    '\n\n            REAR-RIGHT WING [4]: ' + _wrr,
    '\n\n         THROTTLE (0 - 100) [5]: ' + _thr,
  ]);
  showMenuOptions(['\n\n< BACK', '                            ']);
}

function targetLatInput(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n\n           ENTER TARGET LATITUDE',
    '\n\n\nTarget Latitude is the desired latitude coordinate where your HIVE 2 vehicle will navigate to during the Single Waypoint mission. It specifies the north-south position on the surface of the earth',
  ]);
  showMenuOptions(['\n\n\n\n\n\n< BACK', '                            ']);
}

function targetLongInput(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n\n           ENTER TARGET LONGITUDE',
    '\n\n\nTarget Longitude is the desired longitude coordinate where your HIVE 2 vehicle will navigate to during the Single Waypoint mission. It specifies the east-west position on the surface of the earth',
  ]);
  showMenuOptions(['\n\n\n\n\n\n< BACK', '                            ']);
}

function targetAltInput(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n\n           ENTER TARGET ALTITUDE',
    '\n\n\nTarget Altitude is the approximate altitude at which your HIVE 2 vehicle will complete the Single Waypoint mission. It specifies the height above the ground level at the destination point',
  ]);
  showMenuOptions(['\n\n\n\n\n\n< BACK', '                            ']);
}

function cruiseAltInput(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n\n           ENTER CRUISE ALTITUDE',
    '\n\n\nCruise Altitude is the altitude at which your HIVE 2 vehicle will maintain during the cruise phase of the Single Waypoint mission. After reaching the target altitude, the vehicle will fly at this height until the mission completes'
  ]);
  showMenuOptions(['\n\n\n\n\n\n< BACK', '                            ']);
}

function targetVelocityInput(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n\n           ENTER TARGET VELOCITY',
    '\n\n\nTarget Velocity is the desired speed at which your HIVE 2 vehicle will travel during the Single Waypoint mission. It determines how fast the vehicle will move towards the target coordinates'
  ]);
  showMenuOptions(['\n\n\n\n\n\n< BACK', '                            ']);
}

function FLInput(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n\n     ENTER FRONT LEFT WING TRANSLATE VALUE',
    '\n\n\n     This is the angle the wing will move to',
    '\n\n\n                    (0 - 180)',
  ]);
  showMenuOptions(['\n\n\n\n\n\n< BACK', '                            ']);
}

function FRInput(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n\n     ENTER FRONT RIGHT WING TRANSLATE VALUE',
    '\n\n\n     This is the angle the wing will move to',
    '\n\n\n                    (0 - 180)',
  ]);
  showMenuOptions(['\n\n\n\n\n\n< BACK', '                            ']);
}

function RLInput(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n\n      ENTER REAR LEFT WING TRANSLATE VALUE',
    '\n\n\n     This is the angle the wing will move to',
    '\n\n\n                    (0 - 180)',
  ]);
  showMenuOptions(['\n\n\n\n\n\n< BACK', '                            ']);
}

function RRInput(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n\n      ENTER REAR RIGHT WING TRANSLATE VALUE',
    '\n\n\n     This is the angle the wing will move to',
    '\n\n\n                    (0 - 180)',
  ]);
  showMenuOptions(['\n\n\n\n\n\n< BACK', '                            ']);
}

function THRInput(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n\n                ENTER THROTTLE VALUE',
    '\n\n\n     This is the power the motor will be set to',
    '\n\n\n                    (0 - 100)',
  ]);
  showMenuOptions(['\n\n\n\n\n\n< BACK', '                            ']);
}

        // Call the function on webpage load
        window.addEventListener('load', outputOnInit);
            // Add an event listener to the task button
          document.getElementById("DRONE-STATE").addEventListener("click", function() {
            var text = ""
            executeCommand("DRONE-STATE");
            // Send an AJAX request to the ESP32 server
            var xhttp = new XMLHttpRequest();
            xhttp.open("GET", "/perform-task", true);
            xhttp.send();
          });

          ////////////////////////////////////////////////////////////////
          function unpackData(packed_data) {
            const dataParts = packed_data.split('_');
            const pack1 = dataParts[0].match(/([A-Z]+)([\d.]+)/).slice(1);
            const pack2 = dataParts[1].match(/([A-Z]+)([\d.]+)/).slice(1);
            const pack3 = dataParts[2].match(/([A-Z]+)([\d.]+)/).slice(1);
            const pack4 = dataParts[3].match(/([A-Z]+)([\d.]+)/).slice(1);
            
            return [pack1, pack2, pack3, pack4];
        }
          
        function packData(id1,val1,id2,val2,id3,val3,id4,val4,id5,val5){
          const formattedValues = `${id1}${val1}_${id2}${val2}_${id3}${val3}_${id4}${val4}_${id5}${val5}`;
          return formattedValues;
        }

          function updateNative(){
            //Get state element
            // Get the <select> element
            const selectElement = document.getElementById('DRONE-STATE');
            // Get the index of the selected option
            const selectedIndex = selectElement.selectedIndex;
            //sendstateData(selectedIndex,0,0,0,0);
          }

          function updateGPS(){
            //Call API
            //Send backend request
            var xhr = new XMLHttpRequest();
            var url = "/GET_GPS"; // Replace with your ESP32 server URL

            xhr.open("POST", url, true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

            xhr.onreadystatechange = function () {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    if (xhr.status === 200) {
                        // Request successful, handle the response here
                        var response = xhr.responseText;
                        const unpackedData = unpackData(response);
                        //LAT
                        var _lat = parseFloat(unpackedData[0][1]);
                        document.getElementById('Lat-num').innerHTML = _lat;
                        latE = _lat;
                        //LONG
                        var _long = parseFloat(unpackedData[1][1]);
                        document.getElementById('Long-num').innerHTML = _long;
                        longE = _long;
                        //SAT
                        var _sat = parseFloat(unpackedData[2][1]);
                        document.getElementById('Sat-num').innerHTML = _sat;
                        satE = _sat;
                        //ALT
                        var _alt = parseFloat(unpackedData[3][1]);
                        document.getElementById('TAvar').innerHTML = "Altitude<br>" + _alt;
                        altitudeX = _alt;

                        //Update TRGT Element
                        document.getElementById('label10').innerHTML = "TRGT: " + _lat + " DEG " + _long + " DEG" ;
                    } else {
                        // Request failed, handle the error here
                        //var errorResponse = "Error: " + xhr.status + " - " + xhr.statusText;
                        //document.getElementById('Lat-num').innerHTML = errorResponse;
                    }
                }
            };

            // You can add any data you want to send in the request body
            var data = "key1=value1&key2=value2"; // Replace with your data
            xhr.send(data);
          }

          function updateIMU1(){
            //Call API
            //Send backend request
            var xhr = new XMLHttpRequest();
            var url = "/GET_IMU1"; 

            xhr.open("POST", url, true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

            xhr.onreadystatechange = function () {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    if (xhr.status === 200) {
                        // Request successful, handle the response here
                        var response = xhr.responseText;
                        const unpackedData = unpackData(response);
                        
                        var pitch = parseFloat(unpackedData[0][1]);
                        document.getElementById('pitch-num').innerHTML = pitch;
                        pitchE = pitch;
                        
                        var roll = parseFloat(unpackedData[1][1]);
                        document.getElementById('roll-num').innerHTML = roll;
                        rollE = roll;
                        
                        var yaw = parseFloat(unpackedData[2][1]);
                        document.getElementById('yaw-num').innerHTML = yaw;
                        yawE = yaw;

                        //Piggyback gyroY data through this uri_handler to save memory
                        var gyroY = parseFloat(unpackedData[3][1]);
                        document.getElementById('gyroY-num').innerHTML = gyroY;
                        gY = gyroY
                        
                    } else {
                        // Request failed, handle the error here
                        //var errorResponse = "Error: " + xhr.status + " - " + xhr.statusText;
                        //document.getElementById('Lat-num').innerHTML = errorResponse;
                    }
                }
            };

            // You can add any data you want to send in the request body
            var data = "key1=value1&key2=value2"; // Replace with your data
            xhr.send(data);
          }

          function updateIMU2(){
            //Call API
            //Send backend request
            var xhr = new XMLHttpRequest();
            var url = "/GET_IMU2"; 

            xhr.open("POST", url, true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

            xhr.onreadystatechange = function () {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    if (xhr.status === 200) {
                        // Request successful, handle the response here
                        var response = xhr.responseText;
                        const unpackedData = unpackData(response);
                        
                        var accX = parseFloat(unpackedData[0][1]);
                        document.getElementById('accX-num').innerHTML = accX;
                        acX = accX;
                        
                        var accY = parseFloat(unpackedData[1][1]);
                        document.getElementById('accY-num').innerHTML = accY;
                        acY = accY;
                        
                        var accZ = parseFloat(unpackedData[2][1]);
                        document.getElementById('accZ-num').innerHTML = accZ;
                        acZ = accZ;
                        //--
                        var gyroX = parseFloat(unpackedData[3][1]);
                        document.getElementById('gyroX-num').innerHTML = gyroX;
                        gyX = gyroX;

                    } else {
                        // Request failed, handle the error here
                        //var errorResponse = "Error: " + xhr.status + " - " + xhr.statusText;
                        //document.getElementById('Lat-num').innerHTML = errorResponse;
                    }
                }
            };

            // You can add any data you want to send in the request body
            var data = "key1=value1&key2=value2"; // Replace with your data
            xhr.send(data);
          }

          function updateW1(){
            //Call API
            //Send backend request
            var xhr = new XMLHttpRequest();
            var url = "/GET_W1"; // Replace with your ESP32 server URL

            xhr.open("POST", url, true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

            xhr.onreadystatechange = function () {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    if (xhr.status === 200) {
                        // Request successful, handle the response here
                        var response = xhr.responseText;
                        const unpackedData = unpackData(response);
                        //WFL
                        var wfl = parseFloat(unpackedData[0][1]);
                        document.getElementById('label1').innerHTML = 'WingFL<br>' + wfl;
                        _wfl = wfl;
                        //WFR
                        var wfr = parseFloat(unpackedData[1][1]);
                        document.getElementById('label2').innerHTML = 'WingFR<br>' + wfr;
                        _wfr = wfr;
                        //WRL
                        var wrl = parseFloat(unpackedData[2][1]);
                        document.getElementById('label3').innerHTML = 'WingRL<br>' + wrl;
                        _wrl = wrl;
                        //WRR
                        var wrr = parseFloat(unpackedData[3][1]);
                        document.getElementById('label4').innerHTML = 'WingRR<br>' + wrr;
                        _wrr = wrr;

                    } else {
                        // Request failed, handle the error here
                        //var errorResponse = "Error: " + xhr.status + " - " + xhr.statusText;
                        //document.getElementById('Lat-num').innerHTML = errorResponse;
                    }
                }
            };

            // You can add any data you want to send in the request body
            var data = "key1=value1&key2=value2"; // Replace with your data
            xhr.send(data);
          }

          function updateAMB(){
            //Call API
            //Send backend request
            var xhr = new XMLHttpRequest();
            var url = "/GET_AMB";

            xhr.open("POST", url, true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

            xhr.onreadystatechange = function () {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    if (xhr.status === 200) {
                        // Request successful, handle the response here
                        var response = xhr.responseText;
                        const unpackedData = unpackData(response);
                        //LAT
                        var OTA = parseFloat(unpackedData[0][1]);
                        document.getElementById("TATemp").innerHTML = 'OAT<br>' + OTA;
                        _tmp = OTA;
                        //LONG
                        var PRESS = parseFloat(unpackedData[1][1]);
                        document.getElementById("TAPressure").innerHTML = 'Pressure<br>' + PRESS;
                        _pres = PRESS;
                        //Piggyback gyroZ data through this uri_handler to save memory
                        var gyroZ = parseFloat(unpackedData[2][1]);
                        document.getElementById('gyroZ-num').innerHTML = gyroZ;
                        gyZ = gyroZ;
                        //Piggyback throttle data through this uri_handler to save memory
                        var throttle = parseFloat(unpackedData[2][1]);
                        document.getElementById('label8').innerHTML = "THROTTLE: " + throttle;
                        _thr = throttle;

                    } else {
                        // Request failed, handle the error here
                        //var errorResponse = "Error: " + xhr.status + " - " + xhr.statusText;
                        //document.getElementById('Lat-num').innerHTML = errorResponse;
                    }
                }
            };

            // You can add any data you want to send in the request body
            var data = "key1=value1&key2=value2"; // Replace with your data
            xhr.send(data);
          }

          function updateBATT(){
            //Call API
            //Send backend request
            var xhr = new XMLHttpRequest();
            var url = "/GET_BATT";

            xhr.open("POST", url, true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

            xhr.onreadystatechange = function () {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    if (xhr.status === 200) {
                        // Request successful, handle the response here
                        var response = xhr.responseText;
                        const unpackedData = unpackData(response);
                        //Voltage
                        var Voltage = parseFloat(unpackedData[0][1]);
                        //Current
                        var Current = parseFloat(unpackedData[1][1]);
                        //Percent
                        var Percent = parseFloat(unpackedData[2][1]);
                        document.getElementById('label5').innerHTML = "BATTERY : " + Percent + "% " + Voltage + "V " + Current + "mA";

                    } else {
                        // Request failed, handle the error here
                        //var errorResponse = "Error: " + xhr.status + " - " + xhr.statusText;
                        //document.getElementById('Lat-num').innerHTML = errorResponse;
                    }
                }
            };

            // You can add any data you want to send in the request body
            var data = "key1=value1&key2=value2"; // Replace with your data
            xhr.send(data);
          }

          function sendFLIGHTDIRECTORSWP(lat,long,Talt,Calt,vel){
            //Call API
            //Send backend request
            var xhr = new XMLHttpRequest();
            var url = "/INC_SWP";

            xhr.open("POST", url, true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

            var pkg = packData("LAT",lat,"LONG",long,"TALT",Talt,"CALT",Calt,"VEL",vel);
            xhr.send(pkg);
          }

          function sendSYSMISC(fl,fr,rl,rr,thr){
            //Call API
            //Send backend request
            const selectElement = document.getElementById('DRONE-STATE');
            const selectedIndex = selectElement.selectedIndex;
            if(selectedIndex != 2){
              sendBPnotification();
            }
            var xhr = new XMLHttpRequest();
            var url = "/INC_SYS";

            xhr.open("POST", url, true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

            var pkg = packData("FL",fl,"FR",fr,"RL",rl,"RR",rr,"THR",thr);
            xhr.send(pkg);
          }

          function sendstateData(st,fr,rl,rr,thr){
            //Call API
            //Send backend request
            var xhr = new XMLHttpRequest();
            var url = "/INC_STATE";

            xhr.open("POST", url, true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

            var pkg = packData("ST",st,"XX",fr,"XX",rl,"XX",rr,"XX",thr);
            xhr.send(pkg);
          }

          function handleAuth(token){
            //Call API
            //Send backend request
            var xhr = new XMLHttpRequest();
            var url = "/INC_AUTH";

            xhr.open("POST", url, true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

            var pkg = token;
            xhr.send(pkg);

            xhr.onreadystatechange = function () {
              if (xhr.readyState === XMLHttpRequest.DONE) {
                  if (xhr.status === 200) {
                      // Request successful, handle the response here
                      var response = xhr.responseText;
                      if(response == "STATE-CHANGE-SUCCESS"){
                        //Send confirmation to terminal
                        writeToArmTerminal("> " + response);
                        //Modify state element
                        selectElement.selectedIndex = 1;
                      }else{
                        //Send failure notice to terminal and do not modify state element
                        writeToArmTerminal("> " + response);
                      }
                  } else {
                      // Request failed, handle the error here
                      writeToArmTerminal("> DEV-FAIL-REQUEST");
                  }
              }
          };
          }

          function requestToken(){
            //Call API
            //Send backend request
            var xhr = new XMLHttpRequest();
            var url = "/GET_TOKEN";

            xhr.open("POST", url, true);
            xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

            xhr.onreadystatechange = function () {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    if (xhr.status === 200) {
                        // Request successful, handle the response here
                        var response = xhr.responseText;
                        //Send to terminal
                        writeToArmTerminal("> " + response);
                        //Save to buffer
                        mostRecentToken = response;
                    } else {
                        // Request failed, handle the error here
                        writeToArmTerminal("> DEV-FAIL-REQUEST");
                    }
                }
            };

            // You can add any data you want to send in the request body
            var data = "key1=value1&key2=value2"; // Replace with your data
            xhr.send(data);
          }

          function writeToArmTerminal(text) {
            const terminal = document.getElementById('arm_seq_terminal');
            terminal.innerHTML += `<div>${text}</div>`;
            // Scroll to the bottom to show the latest output
            terminal.scrollTop = terminal.scrollHeight;
        }

        function handleFileUpload() {
          const fileInput = document.getElementById('file-input');
          var otafile = document.getElementById('file-input').files;
          const fileName = fileInput.value.split(/(\\|\/)/g).pop(); // Extract file name from the path
          alert(`File "${fileName}" has been selected.`);
          //further logic to handle the uploaded file here
          var file = otafile[0];
					var xhr = new XMLHttpRequest();

					xhr.onreadystatechange = function() {
						if (xhr.readyState == 4) {
							if (xhr.status == 200) {
								document.open();
								document.write(xhr.responseText);
								document.close();
							} else if (xhr.status == 0) {
								alert("Server closed the connection abruptly!");
								location.reload()
							} else {
								alert(xhr.status + " Error!\n" + xhr.responseText);
								location.reload()
							}
						}
					};

					xhr.upload.onprogress = function (e) {
						var progress = document.getElementById("advanced-menu-text3");
						progress.textContent = "Progress: " + (e.loaded / e.total * 100).toFixed(0) + "%";
					};
					xhr.open("POST", "/INC_OTA", true);
					xhr.send(file);

        }
