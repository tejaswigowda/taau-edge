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

function updatePhxData() {
      client.get(
        "https://clarity-data-api.clarity.io/v1/measurements?aqi=pm2_5ConcMass,no2Conc&lat=33.4913623&lon=-111.9231936&limit=1",
          {"headers":{"x-api-key": "WsWbuQACdYp3aRjp3sAMtxy6HXCt9au5PZVXDI87"}},
        function (data, response) {
 //           console.log(JSON.stringify(data), typeof data);
          phxDataObj = data[0];
        }
      );
}


setTimeout(function() {
    updatePhxData();
}, 60*1000);

updatePhxData();

function getRandomInt(max) {
  return Math.floor(Math.random() * max);
}

app.get("/", function (req, res) {
  res.redirect("index.html");
});

app.get("/getValue", function (req, res) {
  var id = req.query.location;
  console.log(id);

  switch (id) {
    case "phx":
      res.end(
          phxDataObj.characteristics.pm2_5ConcMass.aqi.toString()
      );
      break;

    case "insta2":
      break;

    case "insta3":
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
