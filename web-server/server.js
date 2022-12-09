var Client = require("node-rest-client").Client;
var client = new Client();
var express = require("express");
var app = express();
var bodyParser = require("body-parser");
var errorHandler = require("errorhandler");
var methodOverride = require("method-override");
var hostname = process.env.HOSTNAME || "localhost";
var port = 1234;

var phxDataObj = {};
var sagradoDataObj = {};
var ideaDataObj = {};

function updatePhxData() {
      client.get(
        "https://clarity-data-api.clarity.io/v1/measurements?aqi=pm2_5ConcMass,no2Conc&lat=33.4913623&lon=-111.9231936&limit=1",
          {"headers":{"x-api-key": "WsWbuQACdYp3aRjp3sAMtxy6HXCt9au5PZVXDI87"}},
        function (data, response) {
          phxDataObj = data[0];
        }
      );
}


function updateSGData() {
      client.get(
        "https://clarity-data-api.clarity.io/v1/measurements?aqi=pm2_5ConcMass,no2Conc&lat=33.3872158&lon=-112.0729866&limit=1",
          {"headers":{"x-api-key": "WsWbuQACdYp3aRjp3sAMtxy6HXCt9au5PZVXDI87"}},
        function (data, response) {
          sagradoDataObj = data[0];
        }
      );
}


function updateIdeaData() {
      client.get(
        "https://clarity-data-api.clarity.io/v1/measurements?aqi=pm2_5ConcMass,no2Conc&lat=33.416460&lon=-111.835910&limit=1",
          {"headers":{"x-api-key": "WsWbuQACdYp3aRjp3sAMtxy6HXCt9au5PZVXDI87"}},
        function (data, response) {
          sagradoDataObj = data[0];
        }
      );
}


setInterval(function() {
    updatePhxData();
    updateSGData();
    updateIdeaData();
}, 60*1000);

updatePhxData();
updateSGData();
updateIdeaData();

function getRandomInt(max) {
  return Math.floor(Math.random() * max);
}

app.get("/", function (req, res) {
  res.redirect("index.html");
});

app.get("/getValue", function (req, res) {
  var id = req.query.location;
  switch (id) {
    case "phx":
      res.end(
          phxDataObj.characteristics.no2Conc.aqi + " " + phxDataObj.characteristics.pm2_5ConcMass.aqi
      );
      break;

    case "sagrado":
      res.end(
          sagradoDataObj.characteristics.no2Conc.aqi + " " + sagradoDataObj.characteristics.pm2_5ConcMass.aqi
      );
      break;

    case "idea":
      res.end(
          ideaDataObj.characteristics.no2Conc.aqi + " " + ideaDataObj.characteristics.pm2_5ConcMass.aqi
      );
      break;

    case "insta4":
      break;

    default:
      res.end(
        getRandomInt(100) + "," + getRandomInt(100) + "," + getRandomInt(100)
      );
      break;
  }
});

app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + "/public"));
app.use(errorHandler());

console.log(
  "Simple static server listening at http://" + hostname + ":" + port
);
app.listen(port);
