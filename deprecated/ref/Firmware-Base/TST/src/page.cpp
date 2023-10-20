#include "page.h"

extern const char* responseXX =R"html(<!DOCTYPE html>
    <html>
      <head>
        <title>HIVE 2</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel= "stylesheet" type= "text/css" href= "styles.css">
        <style>
          html { font-family: sans-serif; text-align: center; background-color: rgb(0, 0, 0);}
          body { display: inline-flex; flex-direction: column;overflow: hidden; }

          #unit-title{
            color: #fff;
            left: 2%;
            top: 2%;
          }
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
            background-color: rgb(35, 35, 35);
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
          }

          #HIVE-PIC{
            position: absolute;
            width: 110%;
            height:90%;
            left: 0%;
            top:0%;
            max-width:100%;
            max-height:100%;
            object-fit: contain;
            border-radius: 15px;
          }
          #DRONE-STATE{
            position: absolute;
            width: 40%;
            height:10%;
            left:30%;
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
          #terminal-input{
            position: absolute;
            width: 90%;
            height:20%;
            left:5%;
            top:10%;
            background-color: rgb(0, 0, 0);
            border-radius: 15px;
            border-style: none;
            box-shadow: 0px 5px 15px 0px rgba(0, 0, 0, 0.5);
            color: rgb(255, 255, 255);
          }
          #terminal-panel{
            position: absolute;
            width: 90%;
            height:60%;
            left:5%;
            top:35%;
            background-color: rgb(0, 0, 0);
            border-radius: 15px;
            border-style: none;
            box-shadow: 0px 5px 15px 0px rgba(0, 0, 0, 0.5);
            color: rgb(255, 255, 255);

          }
          #Raw-Data{
            margin-top: 10%;
            margin-left: 20%;
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

        </style>
      </head>
            
      <body>
        
        <div id = "config-menu">
            <h1 id = "unit-title">HIVE 2 UNIT</h1>
            <div id = "HIVE-IMG">
             
            </div>
            <button id = "DRONE-STATE"> STANDBY</button>

            <div id = "Config"> 
              <h3 id = "config-title"> Configuration</h3>
            </div>
        </div>
        
        <div id = "attitude-ind-area">
          <canvas id="drawingCanvas"></canvas>
        </div>

        <div id = "map-ind-area">
          <div id="map" style="width: 100%; height: 100%; border-radius: 15px;"></div>
        </div>

        <div id = "terminal-area">
            
            <input type="text" id="terminal-input" placeholder="CMD">
          
            <input type="text" id="terminal-panel" placeholder="Quick Access Terminal">
        </div>

        <div id = "stats-menu">
            <div class="topnav">
                <a class="active">Stats</a>
                <a>Actions</a>
                <a>Logs</a>
            </div>

            <div id = "mainTelem-menu">

            </div>
            <div id = "actions-menu">
                <div id = "opt-menu">
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
                </div>
            </div>
        </div>

        <div id = "data-area">
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
                <td>0</td>
              </tr>
              <tr>
                <td>Longitude</td>
                <td>0</td>
              </tr>
              <tr>
                <td>Satellites</td>
                <td>0</td>
              </tr>
              <tr>
                <td>Pitch</td>
                <td>0</td>
              </tr>
              <tr>
                <td>Roll</td>
                <td>0</td>
              </tr>
              <tr>
                <td>Yaw</td>
                <td>0</td>
              </tr>
              <tr>
                <td>WingFL</td>
                <td>0</td>
              </tr>
              <tr>
                <td>WingFR</td>
                <td>0</td>
              </tr>
              <tr>
                <td>WingRL</td>
                <td>0</td>
              </tr>
              <tr>
                <td>WingRR</td>
                <td>0</td>
              </tr>
            </tbody>
          </table>
        </div>


        <script type="text/javascript">
            // Add an event listener to the task button
          document.getElementById("DRONE-STATE").addEventListener("click", function() {
            // Send an AJAX request to the ESP32 server
            var xhttp = new XMLHttpRequest();
            xhttp.open("GET", "/perform-task", true);
            xhttp.send();
          });

           // Add an event listener to the SET LAT button
           document.getElementById("LAT-set").addEventListener("click", function() {
            // Send an AJAX request to the ESP32 server
            var xhttp = new XMLHttpRequest();
            xhttp.open("GET", "/LAT-set", true);
            xhttp.send();
          });

           // Add an event listener to the SET LONG button
           document.getElementById("LNG-set").addEventListener("click", function() {
            // Send an AJAX request to the ESP32 server
            var xhttp = new XMLHttpRequest();
            xhttp.open("GET", "/LNG-set", true);
            xhttp.send();
          });

           // Add an event listener to the SET ALT button
           document.getElementById("Alt-set").addEventListener("click", function() {
            // Send an AJAX request to the ESP32 server
            var xhttp = new XMLHttpRequest();
            xhttp.open("GET", "/Alt-set", true);
            xhttp.send();
          });

      </script>
      </body>
    </html>)html";
