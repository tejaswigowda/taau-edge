var mac2Insta = {
    "ab:cd:ef:gh:ij:kl": "insta1",
    "ab:cd:ef:gh:ij:kl": "insta2",
    "ab:cd:ef:gh:ij:kl": "insta3",
    "ab:cd:ef:gh:ij:kl": "insta4",
    "ab:cd:ef:gh:ij:kl": "insta5"
}


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
  var id = req.query.mac;
  console.log(id);

  switch(mac2Insta[id]){
      case "insta1":
        break;
  
      case "insta2":
        break;
  
      case "insta3":
        break;
  
      case "insta4":
        break;
  
      case default:
        break;
  
  }

  res.end(getRandomInt(100) + "," + getRandomInt(100) + "," + getRandomInt(100));

});

app.use(methodOverride());
app.use(bodyParser());
app.use(express.static(__dirname + '/public'));
app.use(errorHandler());

console.log("Simple static server listening at http://" + hostname + ":" + port);
app.listen(port);
