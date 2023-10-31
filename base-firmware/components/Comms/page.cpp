#include "page.h"

extern const char* responseXX =R"html(<!DOCTYPE html>

<html>
<head>
<title>HIVE 2</title>
<meta content="width=device-width, initial-scale=1" name="viewport"/>




<style>html { font-family: sans-serif; text-align: center; background-color: rgb(0, 0, 0);}
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
  font-weight: bold;
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

  .topnav a.nonactive {
    background-color: #333;
    color: white;
  }
/* 
  #actions-menu{
      position: absolute;
      width:96%;
      height:85%;
      background-color: rgb(35, 35, 35);
      left:2%;
      top:12%;
      z-index: 100;
  } */

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
  color: #2bd41c;
  padding: 5px;
  border-radius: 3px;
  font-size: 14px;
  z-index: 100;
  font-weight: bolder;
  border-style: solid;
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

#BPnotification{
position: absolute;
z-index: 1000;
width: 20%;
height: 30%;
background: #4e4e4e;
border-radius: 15px;
margin-left: 22%;
margin-top: 5%;
visibility: hidden;
transition: all 0.1s ease;
box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
}

#BPnotification-button {
width: 50%;
height: 30%;
border-radius: 20px;
margin-top: 50%;
margin-left: 0%;
border-width: 0pt;
box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
background: #000000;
color: #fff;
font-size: large;
font-weight: bolder;
}
#BPnotification-button:hover{
background-color: rgb(255, 255, 255);
color: #000;
}

#BP-text{
position: absolute;
color:#fff;
margin-bottom: 0%;
width:80%;
left:10%;
top:10%;
}

#initStat-menu{
  visibility:visible;
}

#mainTelem-menu{
  visibility: hidden;
}

#actions-menu{
  visibility: hidden;
}

#emi-menu{
  visibility: hidden;
}

#mission-menu{
  visibility: hidden;
}

#emi-mpopup{
  position: absolute;
  top: 20%;
  left: 5%;
  z-index: 500;
  width: 30%;
  height: 70%;
  background-color: rgb(0, 0, 0);
  border-radius: 15px;
  box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
  color: #fff;
  font-weight: bolder;
  font-size: larger;
  border-style: none;
  }
  #emi-mpopup:hover{
  background-color: rgb(255, 255, 255);
  color: #000;
  }

  #ECV-menu{
    position: absolute;
    top: 10%;
    left: 10%;
    z-index: 1100;
    width: 80%;
    height: 80%;
    background-color: rgb(22, 21, 21);
    border-radius: 15px;
    box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
    visibility: hidden;
  }

  #ECV-menu-close{
    position: absolute;
    width: 1%;
    height: 1%;
    border-radius: 40px;
    padding: 2%;
    left: 93%;
    top: 3%;
    border-width: 0pt;
    background-color: #fff;
    box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
    display: flex;
    justify-content: center;
    align-items: center;
  }

  #missionStats{
    color: white;
  }
  
  .wayPointContainer{
    background-color: black;
    position: absolute;
    font-size: 1em;
    color: white;
    width: 165px;
    height: 165px;
    left: 50%;
    top: 50%;
    display: grid;
    place-items: center;
    font-family: "Poppins",sans-serif;
    border-radius: 0.3em;
    cursor:move;
    text-align: left;
  }

  .wayPointContainer #exit_waypoint{
    background-color: transparent;
    color: white;
    border: 0;
    font-size: 20px;
    cursor: pointer;
    position: absolute;
    right: 2px;
    top:2px;
    border-radius: 50%;
    transition: all 0.2s ease-in;
  }

  .wayPointContainer .label{
    width: 50px;
    display: inline;
    cursor: auto;
  }

  .wayPointContainer #latitude{
    position: relative;
    font:message-box;
    color: white;
    background-color: grey;
    border-radius: 200px;
    width: 50px;
    margin-left: auto;
    cursor: auto;
  }

  .wayPointContainer #longitude{
    position: relative;
    font:message-box;
    color: white;
    background-color: grey;
    border-radius: 200px;
    width: 50px;
    cursor: auto;

  }
  
  .wayPointContainer #altitude{
    position: relative;
    font:message-box;
    color: white;
    background-color: grey;
    border-radius: 200px;
    width: 50px;
    cursor: auto;

  }

 #newWayPoint-button{
  position: relative;
  font:message-box;
  color: white;
  background-color: #000000;
  text-align: center;
  border-radius: 200px;
  width: 150px;
  height: 50px;
  position: absolute;
  bottom: 25px;
  left: 15px;
 }

 #setMissionPlan-button{
  position: relative;
  font:message-box;
  color: white;
  background-color: #000000;
  text-align: center;
  border-radius: 200px;
  width: 150px;
  height: 50px;
  position: absolute;
  left: 75%;
  bottom: 25px;
 }

  #ECV-menu-close:hover{
    background-color: rgb(0, 0, 0);
    color: #ffffff;
  }

  #ECV-PIC{
    position: absolute;
    top: 15%;
    left:24%;
  }

  #controller-status{
    position: absolute;
    top: 70%;
    left: 40%;
    color: #fff;
  }

  #response-status{
    position: absolute;
    top: 80%;
    left: 43%;
    color: #fff;
    font-weight: lighter;
  }

  #emi-title{
    position:absolute;
    top: 15%;
    left: 45%;
    color: #fff;
  }

  #emi-version{
    position: absolute;
    top: 25%;
    left: 57%;
    color: #fff;
  }

  #controller-stat-check{
    position: absolute;
    top: 47%;
    left: 53%;
    color: #fff;
  }

  #emi-loading{
    position: absolute;
    top: 60%;
    left: 60%;
    width: 20%;
    height: 20%;
  }

  #supdater-subMenu{
    position: absolute;
    top: 15%;
    left: 1%;
    z-index: 500;
    width: 48%;
    height: 40%;
    background-color: rgb(0, 0, 0);
    border-radius: 15px;
    box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
    color: #fff;
    font-weight: bolder;
    font-size: larger;
    border-style: none;
  }

  #subMenu2{
    position: absolute;
    top: 15%;
    left: 51%;
    z-index: 500;
    width: 48%;
    height: 40%;
    background-color: rgb(0, 0, 0);
    border-radius: 15px;
    box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
    color: #fff;
    font-weight: bolder;
    font-size: larger;
    border-style: none;
  }

  #subMenu3{
    position: absolute;
    top: 57%;
    left: 1%;
    z-index: 500;
    width: 48%;
    height: 40%;
    background-color: rgb(0, 0, 0);
    border-radius: 15px;
    box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
    color: #fff;
    font-weight: bolder;
    font-size: larger;
    border-style: none;
  }

  #subMenu4{
    position: absolute;
    top: 57%;
    left: 51%;
    z-index: 500;
    width: 48%;
    height: 40%;
    background-color: rgb(0, 0, 0);
    border-radius: 15px;
    box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
    color: #fff;
    font-weight: bolder;
    font-size: larger;
    border-style: none;
  }
  
  #controller-screen1-connected{
    position: absolute;
    top: 45%;
    left: 43%;
    z-index: 500;
    width: 48%;
    height: 48%;
    color: #fff;
    visibility: hidden;
  }

  #left-stick{
    position: absolute;
    top: 36.5%;
    left: -10%;
    z-index: 500;
    width: 48%;
    height: 48%;
    color: #fff;
  }

  #lstick-line{
    position: absolute;
    top: 36.5%;
    left: 21%;
    z-index: 500;
    width: 25%;
    color: #fff;
  }

  #right-stick{
    position: absolute;
    top: 36.5%;
    left: 65%;
    z-index: 500;
    width: 48%;
    height: 48%;
    color: #fff;
  }

  #rstick-line{
    position: absolute;
    top: 36.5%;
    left: 56.5%;
    z-index: 500;
    width: 25%;
    color: #fff;
  }

  #right-trigger{
    position: absolute;
    top: 22%;
    left: 65%;
    z-index: 500;
    width: 48%;
    height: 48%;
    color: #fff;
  }

  #rtrigger-line{
    position: absolute;
    top: 22%;
    left: 65%;
    z-index: 500;
    width: 16.5%;
    color: #fff;
  }

  #arm_seq_ui{
    position: absolute;
    left: 30.5%;
    top: 0%;
    width: 34%;
    height:48%;
    z-index: 1000;
    border-radius: 15px;
    background-color: rgb(35,35,35);
    box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
    visibility: hidden;
  }

  #arm_seq_ui-title{
    position: absolute;
    left: 5%;
    top:3%;
    color: #fff;
  }

  #arm_seq_auth_req{
    position: absolute;
    left: 25%;
    top: 23%;
    width: 50%;
    height:10%;
    background-color: #fff;
    border-radius: 20px;
    font-weight: bold;
    justify-content: center;
    align-items: center;
    display: flex;
  }

  #arm_seq_auth_req:hover{
    background-color: #000000;
    color: #fff;
  }

  #arm_seq_ui-label1{
    position: absolute;
    left: 5%;
    top:40%;
    color: #fff;
  }

  #arm_seq_ui-input{
    position: absolute;
    left: 5%;
    top: 55%;
    width: 30%;
    height:5%;
    border-radius: 5px;
  }

  #arm_seq_auth_ARM{
    position: absolute;
    left: 5%;
    top: 82%;
    width: 30%;
    height:10%;
    background-color: #fff;
    border-radius: 20px;
    font-weight: bold;
    justify-content: center;
    align-items: center;
    display: flex;
  }

  #arm_seq_auth_ARM:hover{
    background-color: #000000;
    color: #fff;
  }

  #arm_seq_auth_autofill{
    position: absolute;
    left: 5%;
    top:68%;
    width: 20%;
    height:7%;
    background-color: rgb(57, 57, 57);
    color: #fff;
    border-radius: 20px;
    font-weight: bold;
    justify-content: center;
    align-items: center;
    display: flex;
  }

  #arm_seq_auth_autofill:hover{
    background-color: rgb(0, 0, 0);
    color: #fff;
  }

  #arm_seq_terminal{
    position: absolute;
    left: 45%;
    top: 45%;
    width: 50%;
    height:50%;
    background-color: #000000;
    border-radius: 20px;
    overflow: auto;
    padding: 10px;
    color: #fff;
  }

  #arm_seq_ui_close{
    position: absolute;
    width: 3%;
    height: 3%;
    border-radius: 40px;
    padding: 2%;
    left: 90%;
    top: 5%;
    border-width: 0pt;
    background-color: #fff;
    box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
    display: flex;
    justify-content: center;
    align-items: center;
  }

  #arm_seq_ui_close:hover{
    background-color: #000000;
    color: #ffffff;
  }

  #su-text1{
    position: absolute;
    left: 5%;
    top: 0%;
  }

  #su-text2{
    position: absolute;
    left: 5%;
    top: 18%;
    font-weight: lighter;
  }

  #supdater-menu-button{
    position: absolute;
    left: 5%;
    top: 55%;
    width: 70%;
    height: 30%;
    border-radius: 20px;
    background-color: #fff;
    box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
    display: flex;
    justify-content: center;
    align-items: center;
    color: #000;
  }

  #supdater-menu-button:hover{
    color: #ffffff;
    background-color: rgb(57, 57, 57);
  } 

  #supdater-menu{
    position: absolute;
    top: 10%;
    left: 10%;
    z-index: 1100;
    width: 80%;
    height: 80%;
    background-color: rgb(22, 21, 21);
    border-radius: 15px;
    box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
    visibility: hidden;
  }

  #supdater-menu-close{
    position: absolute;
    width: 1%;
    height: 1%;
    border-radius: 40px;
    padding: 2%;
    left: 93%;
    top: 3%;
    border-width: 0pt;
    background-color: #fff;
    box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
    display: flex;
    justify-content: center;
    align-items: center;
    z-index: 500;
  }

  #supdater-menu-close:hover{
    background-color: #000000;
    color: #ffffff;
  }

  #su-topbar-PIC{
    position: absolute;
    left:40%;
    top:0%;
    width: 60%;
    height: 40%;
  }

  #su-topbar{
    position: absolute;
    left:0%;
    top:0%;
    width: 40%;
    height: 40%;
    background-color:#000;
    color: #fff;
  }

  #su-topbar-title{
    position: absolute;
    left: 10%;
    top: 70%;
  }

  #supdater-settings{
    position: absolute;
    left: 2%;
    top:43%;
    border-radius: 20px;
    width: 40%;
    height: 55%;
    background-color:#000;
    color: #fff;
  }

  #supdater-release-notes{
    position: absolute;
    left:43%;
    top:43%;
    border-radius: 20px;
    width: 55%;
    height: 55%;
    background-color:#000;
    color: #fff;
  }

  /* Add a black background color to the top navigation */
  .settings-nav {
    background-color: #333;
    overflow: hidden;
    }
  
    /* Style the links inside the navigation bar */
    .settings-nav a {
    float: left;
    color: #f2f2f2;
    text-align: center;
    padding: 14px 16px;
    text-decoration: none;
    font-size: 17px;
    font-weight: bold;
    }
  
    /* Change the color of links on hover */
    .settings-nav a:hover {
    background-color: #ddd;
    color: black;
    }
  
    /* Add a color to the active/current link */
    .settings-nav a.active {
    background-color: #04AA6D;
    color: white;
    }
  
    .settings-nav a.nonactive {
      background-color: #333;
      color: white;
    }

    #standard-menu{
      visibility: hidden;
    }

    #advanced-menu{
      visibility: inherit;
    }

    #upload-box {
      position: absolute;
      top: 60%;
      left: 9%;
      width: 80%;
      height: 30%;
      border: 5px dashed #ccc;
      display: flex;
      justify-content: center;
      align-items: center;
      cursor: pointer;
  }

    input[type="file"] {
      display: none;
    }

    #firmware-push-button{
      position: absolute;
      top: 18%;
      left: 70%;
      width: 20%;
      height: 30%;
      border-radius: 20px;
      display: flex;
      justify-content: center;
      align-items: center;
      cursor: pointer;
      background-color: #fff;
      color: #000;
    }
    #firmware-push-button:hover{
      background-color: rgb(57, 57, 57);
      color: #ffffff;
    }

    #advanced-menu-text1{
      position: absolute;
      left: 10%;
      top: 15%;
    }

    #advanced-menu-text2{
      position: absolute;
      left: 10%;
      top: 30%;
    }
    
    #advanced-menu-text3{
      position: absolute;
      left: 10%;
      top: 45%;
      font-weight: lighter;
    }

    #input-text1-advanced{
      position: absolute;
      left: 30%;
      top: 20%;
    }

    #input-text2-advanced{
      position: absolute;
      left: 30%;
      top: 35%;
    }

    #input-text2-advanced{
      position: absolute;
    }

    #release-notes-text{
      display: flex;
      justify-content: center;
      align-items: center;
    }</style></head>
<body>
<div id="config-menu">
<h1 id="unit-title">HIVE 2 UNIT</h1>
<div id="HIVE-IMG">
<img id="HIVE-PIC" src="data:image/png;base64,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"/>
</div>
<select id="DRONE-STATE">
<option value="standby">STANDBY</option>
<option value="armed">ARMED</option>
<option value="bypass">BYPASS</option>
</select>
<div id="Config">
<h3 id="config-title"> Configuration</h3>
<h4 id="VHSN"> Vehicle SN: 0001x </h4>
<h4 id="VHTME"> Vehicle Time: --</h4>
<button id="MV-Button"> Mission Viewer</button>
</div>
</div>
<div id="arm_seq_ui">
<h1 id="arm_seq_ui-title"> Vehicle Arming</h1>
<div id="arm_seq_auth_req"> Request Authorization Token</div>
<h3 id="arm_seq_ui-label1">Token Entry</h3>
<input id="arm_seq_ui-input"/>
<div id="arm_seq_auth_ARM"> ARM</div>
<div id="arm_seq_auth_autofill"> Autofill</div>
<div id="arm_seq_terminal"></div>
<div id="arm_seq_ui_close">X</div>
</div>
<div id="attitude-ind-area">
<div class="terminal" id="terminal">
<pre id="output"></pre>
<input autofocus="" id="input" type="text"/>
</div>
</div>
<div id="map-ind-area">
<img alt="" id="HIVE-PIC" src="data:image/jpeg;base64,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AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH//xAAUAQEAAAAAAAAAAAAAAAAAAAAA/9oACAECEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAP/EABQBAQAAAAAAAAAAAAAAAAAAAAD/2gAIAQMQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA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"/>
<div class="line"></div>
<div id="label1">Wing FL<br/> -</div>
<div id="label2">Wing FR<br/> -</div>
<div id="label3">Wing RL<br/> -</div>
<div id="label4">Wing RR<br/> -</div>
<div id="label5">BATTERY : -</div>
<div id="label6">NO NAV SET </div>
<div id="label7">FAIL 84</div>
<div id="label8">THROTTLE: -  </div>
<div id="label9">NO DATA RESPONSE</div>
<div id="label10">TRGT: </div>
</div>
<div id="terminal-area">
<div id="terminal-panel">
<div id="PayloadStat">NO PAYLOAD</div>
<div id="TAvar">ALT<br/> -</div>
<div id="TAPressure"> Pressure<br/> -</div>
<div id="TATemp"> OAT<br/> -</div>
<hr id="Tline"/>
<div id="VL1"></div>
<div id="VL2"></div>
<div id="VL3"></div>
<div id="VL4"></div>
</div>
</div>
<div id="BPnotification">
<h3 id="BP-text">Vehicle State needs to be in BYPASS before direct access to motors</h3>
<button id="BPnotification-button">OKAY</button>
</div>
<div id="stats-menu">
<div class="topnav">
<a class="active" id="stats-select">Stats</a>
<a class="nonactive" id="actions-select">Actions</a>
<a class="nonactive" id="logs-select">Logs</a>
<a class="nonactive" id="emi-select">EMI</a>
<a class="nonactive" id="mission-select">Mission</a>
</div>
<div id="initStat-menu">
<div id="AltGraphTitle">Altitude</div>
<canvas id="AltCanvas"></canvas>
</div>
<div id="mainTelem-menu">
</div>
<div id="actions-menu">
<div id="supdater-subMenu">
<h3 id="su-text1">Software Update
<h5 id="su-text2">You are up-to-date</h5></h3>
<div id="supdater-menu-button">Release Notes</div>
</div>
<div id="subMenu2">
</div>
<div id="subMenu3">
</div>
<div id="subMenu4">
</div>
</div>
<div id="emi-menu">
<button id="emi-mpopup"> Control Viewer</button>
<h2 id="emi-title"> Experimental Manual Control</h2>
<h2 id="emi-version"> Version 1.0.1</h2>
<div id="controller-screen1-connected">
<h3 id="controller-screen1-connected-label"> Controller Connected</h3>
<h4 id="controller-screen1-connected-label"> See Control Viewer for additional details</h4>
</div>
<h3 id="controller-stat-check"> Checking for Controller</h3>
<img alt="" id="emi-loading" src="data:image/gif;base64,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"/>
</div>
<div id="mission-menu">
<button class="pill" id="setMissionPlan-button">
          Set Mission Plan
        </button>
<button class="pill" id="newWayPoint-button">
          Add New Waypoint
        </button>
</div>
</div>
<div id="ECV-menu">
<img alt="" id="ECV-PIC" src="data:image/png;base64,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"/>
<h2 id="controller-status"> No Controller Detected</h2>
<h4 id="response-status"> Vehicle Response Time: </h4>
<div id="left-stick"> - </div>
<hr id="lstick-line"/>
<div id="right-stick"> - </div>
<hr id="rstick-line"/>
<div id="right-trigger"> - </div>
<hr id="rtrigger-line"/>
<div id="ECV-menu-close">X</div>
</div>
<div id="supdater-menu">
<div id="supdater-menu-close">X</div>
<div id="su-topbar">
<h1 id="su-topbar-title">Software Update</h1>
</div>
<div id="supdater-settings">
<div class="settings-nav">
<a class="active" id="standard-select">Standard</a>
<a class="nonactive" id="advanced-select">Advanced</a>
</div>
<div id="standard-menu">
<h3>No New Updates
</h3></div>
<div id="advanced-menu">
<div id="firmware-push-button">Push</div>
<h4 id="advanced-menu-text1">Package:</h4>
<input autofocus="" id="input-text1-advanced" type="text"/>
<h4 id="advanced-menu-text2">Version:</h4>
<input autofocus="" id="input-text2-advanced" type="text"/>
<h4 id="advanced-menu-text3"> Maximum of 1 firmware image</h4>
<div id="upload-box" onclick="document.getElementById('file-input').click()">
<span>Upload new firmware image</span>
<input accept=".bin" id="file-input" multiple="false" onchange="handleFileUpload()" type="file"/>
</div>
</div>
</div>
<div id="supdater-release-notes">
<h3>Release Notes</h3>
<h5 id="release-notes-text"> <br/> <br/> <br/> <br/> <br/> <br/> No data found</h5>
</div>
<img alt="" id="su-topbar-PIC" src="data:image/jpeg;base64,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"/>
</div>

<div class="table-container" id="data-area">
<table id="Raw-Data">
<thead>
<tr>
<th>Variable</th>
<th>Value</th>
</tr>
</thead>
<tbody>
<tr>
<td>Latitude</td>
<td id="Lat-num">-</td>
</tr>
<tr>
<td>Longitude</td>
<td id="Long-num">-</td>
</tr>
<tr>
<td>Satellites</td>
<td id="Sat-num">-</td>
</tr>
<tr>
<td>Pitch</td>
<td id="pitch-num">-</td>
</tr>
<tr>
<td>Roll</td>
<td id="roll-num">-</td>
</tr>
<tr>
<td>Yaw</td>
<td id="yaw-num">-</td>
</tr>
<tr>
<td>accX</td>
<td id="accX-num">-</td>
</tr>
<tr>
<td>accY</td>
<td id="accY-num">-</td>
</tr>
<tr>
<td>accZ</td>
<td id="accZ-num">-</td>
</tr>
<tr>
<td>gyroX</td>
<td id="gyroX-num">-</td>
</tr>
<tr>
<td>gyroY</td>
<td id="gyroY-num">-</td>
</tr>
<tr>
<td>gyroZ</td>
<td id="gyroZ-num">-</td>
</tr>
</tbody>
</table>
</div>
<script>//GLOBAL VARS & EVENT LISTENERS
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
function deleteWayPoint() {
    var waypointContainer = document.getElementById("wayPointContainer");
    waypointContainer.parentNode.removeChild(waypointContainer);
}

function addNewWayPoint() {
    var wayPointContainer = document.getElementById("wayPointContainer");
    if (wayPointContainer) {
      // Create a new div for the waypoint
      var newWayPointDiv = document.createElement("div");
      newWayPointDiv.className = "draggable";
  
      // Create the input fields for latitude, longitude, and altitude
      newWayPointDiv.innerHTML = `
        <button class="btn-close" onclick="deleteWayPoint()">&times;</button>
        <form>
          <label for="latitude">Latitude:</label>
          <input type="number" class="pill" name="latitude"><br>
          <label for="longitude">Longitude:</label>
          <input type="number" class="pill" name="longitude"><br>
          <label for="altitude">Altitude:</label>
          <input type="number" class="pill" name="altitude"><br>
        </form>
      `;
  
      // Append the new waypoint div to the wayPointContainer
      wayPointContainer.appendChild(newWayPointDiv);
    }
  }

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

  </script></body>
</html>)html";

