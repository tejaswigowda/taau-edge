var Client = require('node-rest-client').Client;
var express = require("express");
var app = express();
var bodyParser = require('body-parser');
var errorHandler = require('errorhandler');
var methodOverride = require('method-override');
var hostname = process.env.HOSTNAME || 'localhost';
var port = 1234;

function getRandomInt(max) {
  return Math.floor(Math.random() * max);
}

app.get("/", function (req, res) {
    res.redirect("index.html")
});

app.get("/getValue", function (req, res) {
  var id = req.query.location;
  console.log(id);

  switch(id) {
      case "phx":
          client.get("http://remote.site/rest/xml/method", function (data, response) {
	// parsed response body as js object
	console.log(data);
              var csv = data;
        res.end(csv);
	// raw response
	console.log(response);
});
        break;
  
      case "insta2":
        break;
  
      case "insta3":
        break;
  
      case "insta4":
        break;
  
      case default:
        res.end(getRandomInt(100) + "," + getRandomInt(100) + "," + getRandomInt(100));
        break;
  
  }


});

app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(errorHandler());

console.log("Simple static server listening at http://" + hostname + ":" + port);
app.listen(port);
