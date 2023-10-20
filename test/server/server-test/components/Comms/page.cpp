#include "page.h"

extern const char* responseXX =R"html(<!DOCTYPE html>
    <html>
      <head>
        <title>HIVE 2</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
          html { font-family: sans-serif; text-align: center; background-color: rgb(0, 0, 0);}
          body { display: inline-flex; flex-direction: column;overflow: hidden; }
          .table-container {
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            background-color: black;
            left: 20%;
        }
        table {
            width: 80%; /* Set the width of the table to 80% of the container */
            border-collapse: collapse;
            color: white;
            font-size: 110%;
        }
        table, th, td {
            border: 1px solid rgb(174, 174, 174);
            padding: 2%; /* Use percentage-based padding for cells */
        }
        th {
            background-color: #222;
        }
          #unit-title{
            color: #fff;
            left: 2%;
            top: 2%;
          }

          canvas { border: 1px solid #ccc; display: block; }

          #config-menu{
            position: absolute;
            width: 29.5%;
            height: 70%;
            border-radius: 5px;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left: 0.5%;
            top: 0%;
            background-color: rgb(35, 35, 35);
          }
          #terminal-area{
            position: absolute;
            width: 29.5%;
            height: 28.5%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left: 0.5%;
            top: 70.5%;
            background-color: rgb(35, 35, 35);
          }
          #attitude-ind-area{
            position: absolute;
            width: 34%;
            height: 48%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left: 30.5%;
            top: 0%;
            background-color: rgb(35, 35, 35);
          }
          #map-ind-area{
            position: absolute;
            width: 34%;
            height: 48%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left:65%;
            top: 0%;
            background-color: rgb(0, 0, 0);
            overflow: hidden;
          }
          #stats-menu{
            position: absolute;
            width: 50.5%;
            height: 50%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left:30.5%;
            top: 49%;
            background-color: rgb(35, 35, 35);
          }

          #data-area{
            position: absolute;
            width: 18%;
            height: 50%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left:81.5%;
            top: 49%;
            background-color: rgb(35, 35, 35);
            
          }
          #HIVE-IMG{
            position: absolute;
            width: 80%;
            height:30%;
            left:10%;
            top:15%;
            background-color: rgb(0, 0, 0);
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            overflow: hidden;
          }

          #HIVE-PIC{
            position: absolute;
            width: 200%;
            height:180%;
            left: -57%;
            top:-50%;
            object-fit: contain;
            border-radius: 15px;
            z-index: 5000;
            overflow: hidden;
            z-index: 50;
          }
          #DRONE-STATE{
            position: absolute;
            width: 30%;
            height:10%;
            left:35%;
            top:50%;
            border-radius: 30px;
            box-shadow: 0px 5px 15px 0px rgba(0, 0, 0, 0.5);
            color: rgb(0, 0, 0);
            text-align: center;
            font-size: larger;
            font-weight: bolder;
            justify-content: center;
            align-items: center;
            display: flex;
            background-color: #fff;
          }
          #terminal-panel{
            position: absolute;
            width: 90%;
            height:80%;
            left:5%;
            top:10%;
            background-color: rgb(0, 0, 0);
            border-radius: 15px;
            border-style: none;
            box-shadow: 0px 5px 15px 0px rgba(0, 0, 0, 0.5);
            color: rgb(255, 255, 255);

          }
          #Raw-Data{
            color: #fff;
            padding-bottom: 10%;
          }
          #Config{
            position: absolute;
            width: 80%;
            height:30%;
            left:10%;
            top:65%;
            background-color: rgb(35, 35, 35);
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
          }
          #config-title{
            color: #fff;
          }

          #AltGraphTitle{
            position: absolute;
            width: 10%;
            height:5%;
            left:45%;
            top:7%;
            color: #ffffff;
            z-index: 1000;
            font-weight: bolder;
          }

          /* Add a black background color to the top navigation */
            .topnav {
            background-color: #333;
            overflow: hidden;
            }

            /* Style the links inside the navigation bar */
            .topnav a {
            float: left;
            color: #f2f2f2;
            text-align: center;
            padding: 14px 16px;
            text-decoration: none;
            font-size: 17px;
            }

            /* Change the color of links on hover */
            .topnav a:hover {
            background-color: #ddd;
            color: black;
            }

            /* Add a color to the active/current link */
            .topnav a.active {
            background-color: #04AA6D;
            color: white;
            }

            #actions-menu{
                position: absolute;
                width:96%;
                height:85%;
                background-color: rgb(35, 35, 35);
                left:2%;
                top:12%;
                z-index: 100;
                
            }

            #opt-menu{
                position: absolute;
                width:48%;
                height:100%;
                left:0%;
                top:0%;
                z-index: 100;
                border-width: 1px;
                border-style: solid;
            }

            #configSWP{
                position: absolute;
                width:50%;
                height:100%;
                left:50%;
                top:0%;
                z-index: 100;
                border-width: 1px;
                border-style: solid;
            }
            
            #SWP-menuitem{
                position: absolute;
                width: 70%;
                height:11.5%;
                left:15%;
                top:5%;
                box-shadow: 0px 5px 15px 0px rgba(0, 0, 0, 0.5);
                color: rgb(0, 0, 0);
                text-align: center;
                font-size:medium;
                justify-content: center;
                align-items: center;
                display: flex;
                background-color: #ddd;
            }

            #MWP-menuitem{
                position: absolute;
                width: 70%;
                height:11.5%;
                left:15%;
                top:20%;
                box-shadow: 0px 5px 15px 0px rgba(0, 0, 0, 0.5);
                color: rgb(0, 0, 0);
                text-align: center;
                font-size:medium;
                justify-content: center;
                align-items: center;
                display: flex;
                background-color: #ddd;
            }

            #VehicleConfig{
                position: absolute;
                width: 70%;
                height:11.5%;
                left:15%;
                top:35%;
                color: rgb(0, 0, 0);
                text-align: center;
                font-size:medium;
                justify-content: center;
                align-items: center;
                display: flex;
                background-color: #ddd;
            }

            .numField{
                position: absolute;
                width: 30%;
                height:10%;
            }

            #LAT-f{
                left:15%;
                top:5%;
                background-color: #000000;
                color: #ffffff;
                border-style: none;
            }
            #LAT-set{
                position: absolute;
                width: 40%;
                height:11.5%;
                left:46%;
                top:5%;
            }

            #LNG-f{
                left:15%;
                top:25%;
                background-color: #000000;
                color: #ffffff;
                border-style: none;
            }
            #LNG-set{
                position: absolute;
                width: 40%;
                height:11.5%;
                left:46%;
                top:25%;
            }

            #ALT-f{
                position: absolute;
                width: 30%;
                height:10%;
                left:15%;
                top:45%;
                background-color: #000000;
                color: #ffffff;
                border-style: none;
            }
            #Alt-set{
                position: absolute;
                width: 40%;
                height:11.5%;
                left:46%;
                top:45%;
            }

            .terminal {
            width: 95%;
            height: 95%;
            border: 0.5px solid #fff;
            border-radius: 8px;
            padding: 10px;
            overflow: hidden;
            background-color: #000;
        }

        #output {
          white-space: pre-wrap;
            overflow-y: scroll;
            height: calc(100% - 35px); /* Adjust the height to leave space for the input field */
            margin: 0;
            padding: 0; /* Remove default padding */
            border-bottom: 1px solid #fff;
            text-align: left; /* Set text alignment to left */
            color: #fff;
            font-size:large;
        }
        /* New CSS style for menu options */
        .menu-options {
          display: grid;
          grid-template-columns: 1fr 1fr; /* Two equal columns */
          gap: 5px; /* Gap between grid items */
          text-align: center; /* Center the text within the grid items */
        }

        /* Style the scrollbar for Webkit (Chrome, Safari, Edge) */
        #output::-webkit-scrollbar {
            width: 8px; /* Set the width of the scrollbar */
        }

        #output::-webkit-scrollbar-thumb {
            background-color: #ffffff; /* Set the color of the scrollbar thumb */
            border-radius: 10px; /* Round the corners of the thumb */
        }

        #output::-webkit-scrollbar-thumb:hover {
            background-color: #ffffff; /* Set the color of the scrollbar thumb on hover */
        }

        /* Style the scrollbar for Firefox */
        #output::-moz-scrollbar {
            width: 8px; /* Set the width of the scrollbar */
        }

        #output::-moz-scrollbar-thumb {
            background-color: #ffffff; /* Set the color of the scrollbar thumb */
            border-radius: 10px; /* Round the corners of the thumb */
        }

        #output::-moz-scrollbar-thumb:hover {
            background-color: #ffffff; /* Set the color of the scrollbar thumb on hover */
        }


        #input {
            width: 100%;
            height:10%;
            margin-bottom: 0%;
            border: none;
            outline: none;
            background-color: rgb(255, 255, 255);
            color: #000000;

            font-size: 16px;
        }
        /* Style for the text label */
        /* WING */
        #label1 {
            position: absolute;
            top:20%;
            left: 17%;
            transform: translateX(-50%);
            background-color: rgba(0, 0, 0, 0.7);
            color: #fff;
            padding: 5px;
            border-radius: 3px;
            font-size: 14px;
            z-index: 100;
            font-weight: bolder;
        }
        /* WING */
        #label2 {
            position: absolute;
            top:19%;
            left: 85%;
            transform: translateX(-50%);
            background-color: rgba(0, 0, 0, 0.7);
            color: #fff;
            padding: 5px;
            border-radius: 3px;
            font-size: 14px;
            z-index: 100;
            font-weight: bolder;
        }
        /* WING */
        #label3 {
            position: absolute;
            top:52%;
            left: 17%;
            transform: translateX(-50%);
            background-color: rgba(0, 0, 0, 0.7);
            color: #fff;
            padding: 5px;
            border-radius: 3px;
            font-size: 14px;
            z-index: 100;
            font-weight: bolder;
        }
        /* WING */
        #label4 {
            position: absolute;
            top:52%;
            left: 85%;
            transform: translateX(-50%);
            background-color: rgba(0, 0, 0, 0.7);
            color: #fff;
            padding: 5px;
            border-radius: 3px;
            font-size: 14px;
            z-index: 100;
            font-weight: bolder;
        }
        /* BATTERY */
        #label5 {
            position: absolute;
            top:80%;
            left: 17%;
            transform: translateX(-50%);
            background-color: rgba(0, 0, 0, 0.7);
            color: #15ff00;
            padding: 5px;
            border-radius: 3px;
            font-size: 14px;
            z-index: 100;
            font-weight: bolder;
        }
        /* CAM BOOT */
        #label6 {
            position: absolute;
            top:90%;
            left: 17%;
            transform: translateX(-50%);
            background-color: rgba(0, 0, 0, 0.7);
            color: #15ff00;
            padding: 5px;
            border-radius: 3px;
            font-size: 14px;
            z-index: 100;
            font-weight: bolder;
        }
        /* THROTTLE */
        #label8 {
            position: absolute;
            top:90%;
            left: 70%;
            transform: translateX(-50%);
            background-color: rgba(0, 0, 0, 0.7);
            color: #15ff00;
            padding: 5px;
            border-radius: 3px;
            font-size: 14px;
            z-index: 100;
            font-weight: bolder;
        }
        #label7 {
            position: absolute;
            top:33%;
            left: 70%;
            transform: translateX(-50%);
            background-color: rgba(0, 0, 0, 0.7);
            color: #c91414;
            padding: 5px;
            border-style: solid;
            border-radius: 3px;
            font-size: 14px;
            z-index: 100;
            font-weight: bolder;
        }

        #label9 {
            position: absolute;
            top:5%;
            left: 15%;
            transform: translateX(-50%);
            background-color: rgba(0, 0, 0, 0.7);
            color: #c91414;
            padding: 5px;
            border-style: solid;
            border-radius: 3px;
            font-size: 10px;
            z-index: 100;
            font-weight: bolder;
        }

        #label10{
          position: absolute;
            top:80%;
            left: 66%;
            transform: translateX(-50%);
            background-color: rgba(0, 0, 0, 0.7);
            color: #15ff00;
            padding: 5px;
            border-radius: 3px;
            font-size: 14px;
            z-index: 100;
            font-weight: bolder;
        }

        #AltCanvas {
          position: absolute;
          top: 1%;
          left: 1.5%;
          width: 100%;
          height: 100%;
          z-index: 500;
          background-color: #000;
        }
        
        #initStat-menu {
            position: relative;
            width: 97%;
            height: 85%;
        }

        #MV-Button{
          position: absolute;
          top: 30%;
          left: 65%;
          z-index: 500;
          width: 30%;
          height: 60%;
          background-color: rgb(0, 0, 0);
          border-radius: 15px;
          box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
          color: #fff;
          font-weight: bolder;
          border-style: none;
        }
        #MV-Button:hover{
          background-color: rgb(255, 255, 255);
          color: #000;
        }

        #VHSN{
          position: absolute;
          top: 25%;
          left: 5%;
          color:#fff;
          font-weight: 400;
          font-size: small;
        }

        #VHTME{
          position: absolute;
          top: 40%;
          left: 5%;
          color:#fff;
          font-weight: 400;
          font-size: small;
        }

        #TATemp{
          position: absolute;
          top: 65%;
          left: 5%;
          width:25%;
          height:25%;
          color:#fff;
          font-weight: 400;
          font-size: small;
          border-style: solid;
          border-radius: 5px;
          border-color: #ccc;
        }

        #TAPressure{
          position: absolute;
          top: 65%;
          left: 37.5%;
          width:25%;
          height:25%;
          color:#fff;
          font-weight: 400;
          font-size: small;
          border-style: solid;
          border-radius: 5px;
          border-color: #ccc;
        }

        #TAvar{
          position: absolute;
          top: 65%;
          left: 70%;
          width:25%;
          height:25%;
          color:#ffffff;
          font-weight: 400;
          font-size: small;
          border-style: solid;
          border-radius: 5px;
          border-color: #ccc;
        }

        #PayloadStat{
          position: absolute;
          top: 9%;
          left:30%;
          width:40%;
          height:20%;
          color: #15ff00;
          font-weight: bolder;
          font-size: medium;
        }

        #Tline{
          position: absolute;
          top: 35%;
          left:17.5%;
          width: 64.25%;
        }

        #VL1{
          border-left: 1px solid rgb(255, 255, 255);
          height: 20%;
          position: absolute;
          left: 17.5%;
          top: 40%;
        }

        #VL2{
          border-left: 1px solid rgb(255, 255, 255);
          height: 20%;
          position: absolute;
          left: 50%;
          top: 40%;
        }

        #VL3{
          border-left: 1px solid rgb(255, 255, 255);
          height: 20%;
          position: absolute;
          left: 82.5%;
          margin-left: -3px;
          top: 40%;
          
        }

        #VL4{
          border-left: 1px solid rgb(255, 255, 255);
          height: 20%;
          position: absolute;
          left: 50%;
          top: 20%;
        }
        </style>
      </head>

      <body>
        
        <div id = "config-menu">
            <h1 id = "unit-title">HIVE 2 UNIT</h1>
            <div id = "HIVE-IMG">
              <img id = "HIVE-PIC" src="data:image/png;base64,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" />
            </div>
    
            <select id="DRONE-STATE">
              <option value="standby">STANDBY</option>
              <option value="armed">ARMED</option>
              <option value="bypass">BYPASS</option>
            </select>

            <div id = "Config"> 
              <h3 id = "config-title"> Configuration</h3>
              <h4 id = "VHSN"> Vehicle SN: 0001x </h4>
              <h4 id = "VHTME"> Vehicle Time: --</h4>
              <button id = "MV-Button"> Mission Viewer</button>
            </div>
        </div>
        
        <div id = "attitude-ind-area">
          <div class="terminal" id="terminal">
        <pre id="output"></pre>
        <input type="text" id="input" autofocus>
    </div>
        </div>

        <div id = "map-ind-area">
          <img alt="" id = "HIVE-PIC" src="data:image/jpeg;base64,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AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH//xAAUAQEAAAAAAAAAAAAAAAAAAAAA/9oACAECEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAP/EABQBAQAAAAAAAAAAAAAAAAAAAAD/2gAIAQMQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA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" />
          <div class="line"></div>
          <div id="label1">Wing FL</div>
          <div id="label2">Wing FR</div>
          <div id="label3">Wing RL</div>
          <div id="label4">Wing RR</div>
          <div id="label5">BATTERY : -</div>
          <div id="label6">NO NAV SET </div>
          <div id="label7">FAIL 84</div>
          <div id="label8">THROTTLE:</div>
          <div id="label9">NO DATA RESPONSE</div>
          <div id="label10">TRGT: </div>
        </div>

        <div id = "terminal-area">
            <div id="terminal-panel">
              <div id = "PayloadStat">NO PAYLOAD</div>
              <div id = "TAvar">ALT<br> -</div>
              <div id = "TAPressure"> Pressure<br> -</div>
              <div id = "TATemp"> OAT<br> -</div>
              <hr id = "Tline">
              <div id = VL1></div>
              <div id = VL2></div>
              <div id = VL3></div>
              <div id = VL4></div>

            </div>
        </div>

        <div id = "stats-menu">
            <div class="topnav">
                <a class="active">Stats</a>
                <a>Actions</a>
                <a>Logs</a>
            </div>

            <div id = "initStat-menu">
              <div id = "AltGraphTitle">Altitude</div>
              <canvas id="AltCanvas"></canvas>
            </div>

            <div id = "mainTelem-menu">

            </div>
            <div id = "actions-menu">
                <!--<div id = "opt-menu">
                    <button id = "SWP-menuitem"> SWP-Configuration</button>
                    <button id = "MWP-menuitem"> MWP-Configuration</button>
                    <button id = "VehicleConfig"> Vehicle-Setup</button>
                </div>
                <div id = "configSWP">
                    <input id = "LAT-f" type="number" class = "numField">
                    <button id = "LAT-set"> Set LAT</button>
                    <input  id = "LNG-f" type="number" class = "numField">
                    <button id = "LNG-set"> Set LNG</button>
                    <input  id = "ALT-f"type="number" class = "numField" min="1" max="9" step="1" value="1">
                    <button id = "Alt-set"> Set ALT</button>
                </div>-->

            </div>
        </div>

        <div class="table-container" id = "data-area">
          <table id = "Raw-Data">
            <thead>
              <tr>
                <th>Variable</th>
                <th>Value</th>
              </tr>
            </thead>
            <tbody>
              <tr>
                <td>Latitude</td>
                <td id = "Lat-num">-</td>
              </tr>
              <tr>
                <td>Longitude</td>
                <td id = "Long-num">-</td>
              </tr>
              <tr>
                <td>Satellites</td>
                <td id = "Sat-num">-</td>
              </tr>
              <tr>
                <td>Pitch</td>
                <td id = "pitch-num">-</td>
              </tr>
              <tr>
                <td>Roll</td>
                <td id = "roll-num">-</td>
              </tr>
              <tr>
                <td>Yaw</td>
                <td id = "yaw-num">-</td>
              </tr>
              <tr>
                <td>accX</td>
                <td id = "accX-num">-</td>
              </tr>
              <tr>
                <td>accY</td>
                <td id = "accY-num">-</td>
              </tr>
              <tr>
                <td>accZ</td>
                <td id = "accZ-num">-</td>
              </tr>
              <tr>
                <td>gyroX</td>
                <td id = "gyroX-num">-</td>
              </tr>
              <tr>
                <td>gyroY</td>
                <td id = "gyroY-num">-</td>
              </tr>
              <tr>
                <td>gyroZ</td>
                <td id = "gyroZ-num">-</td>
              </tr>
            </tbody>
          </table>
        </div>


        <script type="text/javascript">
          //GLOBAL VARS & EVENT LISTENERS
          altitudeX = 0;

          const selectElement = document.getElementById('DRONE-STATE');
          selectElement.addEventListener('change', function() {
            const selectedIndex = selectElement.selectedIndex;
            sendstateData(selectedIndex + 1,0,0,0,0);
          });


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

      function updateGraph() {
          sampleGraph.updateGraph(altitudeX);
          setTimeout(updateGraph, sampleGraph.updateInterval);
      }

      ///////////////////////////////////////////////////////////////
      //UPDATE PAGE
      function updatePageContinuously(){
            updateGraph();
            updateGPS();
            updateIMU1();
            updateIMU2();
            updateW1();
            updateAMB();
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
    '\n\n                   VX: 0.000',
    '\n\n                   VY: 0.000',
    '\n\n                   VZ: 0.000',
    '\n\n                 ACCX: 0.000',
    '\n\n                 ACCY: 0.000',
    '\n\n                 ACCZ: 0.000',
  ]);
  showMenuOptions(['\n< BACK', '                            NEXT >']);
}

function gpsStatPage(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\n\n GPS DATA',
    '\n\n               LATITUDE: 0.000',
    '\n\n              LONGITUDE: 0.000',
    '\n\n               ALTITUDE: 0.000',
    '\n\n             SATELLITES: 0.000',
    '\n\n               VELOCITY: 0.000',
  ]);
  showMenuOptions(['\n\n\n< BACK', '                            NEXT >']);
}

function SYSpage(){
  const initialText = '>        --- FLIGHT MANAGEMENT SYSTEM ---\n';
  output.textContent += initialText;
  showMenuOptions([
    '\nSample the full command of the four wing servos and motor, providing precise control over their movements and operations. The vehicle must be in STANDBY mode',
    '\n\n            FRONT-LEFT WING [1]: 0.000',
    '\n\n           FRONT-RIGHT WING [2]: 0.000',
    '\n\n             REAR-LEFT WING [3]: 0.000',
    '\n\n            REAR-RIGHT WING [4]: 0.000',
    '\n\n         THROTTLE (0 - 100) [5]: 0.000',
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
                        //LONG
                        var _long = parseFloat(unpackedData[1][1]);
                        document.getElementById('Long-num').innerHTML = _long;
                        //SAT
                        var _sat = parseFloat(unpackedData[2][1]);
                        document.getElementById('Sat-num').innerHTML = _sat;
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
                        
                        var roll = parseFloat(unpackedData[1][1]);
                        document.getElementById('roll-num').innerHTML = roll;
                        
                        var yaw = parseFloat(unpackedData[2][1]);
                        document.getElementById('yaw-num').innerHTML = yaw;
                        //Piggyback gyroY data through this uri_handler to save memory
                        var gyroY = parseFloat(unpackedData[3][1]);
                        document.getElementById('gyroY-num').innerHTML = gyroY;
                        
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
                        
                        var accY = parseFloat(unpackedData[1][1]);
                        document.getElementById('accY-num').innerHTML = accY;
                        
                        var accZ = parseFloat(unpackedData[2][1]);
                        document.getElementById('accZ-num').innerHTML = accZ;
                        //--
                        var gyroX = parseFloat(unpackedData[3][1]);
                        document.getElementById('gyroX-num').innerHTML = gyroX;
                        
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
                        document.getElementById('wfl-num').innerHTML = wfl;
                        document.getElementById('label1').innerHTML = 'WingFL<br>' + wfl;
                        //WFR
                        var wfr = parseFloat(unpackedData[1][1]);
                        document.getElementById('wfr-num').innerHTML = wfr;
                        document.getElementById('label2').innerHTML = 'WingFR<br>' + wfr;
                        //WRL
                        var wrl = parseFloat(unpackedData[2][1]);
                        document.getElementById('wrl-num').innerHTML = wrl;
                        document.getElementById('label3').innerHTML = 'WingRL<br>' + wrl;
                        //WRR
                        var wrr = parseFloat(unpackedData[3][1]);
                        document.getElementById('wrr-num').innerHTML = wrr;
                        document.getElementById('label4').innerHTML = 'WingRR<br>' + wrr;

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
                        //LONG
                        var PRESS = parseFloat(unpackedData[1][1]);
                        document.getElementById("TAPressure").innerHTML = 'Pressure<br>' + PRESS;

                        //Piggyback gyroZ data through this uri_handler to save memory
                        var gyroZ = parseFloat(unpackedData[2][1]);
                        document.getElementById('gyroZ-num').innerHTML = gyroZ;

                        //Piggyback throttle data through this uri_handler to save memory
                        var throttle = parseFloat(unpackedData[2][1]);
                        document.getElementById('label8').innerHTML = "THROTTLE: " + throttle;
                      
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

      </script>
      </body>
    </html>)html";

