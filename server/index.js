const http = require('http');
const url = require('url');
const fs = require('fs');
const path = require('path');

const headers = require('./headers').headers;

const port = 8134;

var board = [];
var plays = [];
var last = [];
var ids = new Set();
var counter =  [];
var best_i = 0;
var best = 0;

function main(input) {
    //Enter your code here
    // var arr = input.split("")
    input = input.split('\n');

    board = JSON.parse(input[0]);
    plays = JSON.parse(input[1]);
    last = JSON.parse(input[2]);

    for(let i = 0;i<plays.length; i++) counter.push(0);
    startServer();
}

process.stdin.resume();
process.stdin.setEncoding("utf-8");
var stdin_input = "";

process.stdin.on("data", function (input) {
    stdin_input += input;
});

process.stdin.on("end", function () {
   main(stdin_input);
});

function startServer() {
  const server = http.createServer(function (request, response) {
    const purl = url.parse(request.url);
    switch (request.method) {
      case 'GET'://update
        //console.log("get");
        response.writeHead(200, headers['plain']);
        response.write(JSON.stringify({"board": board, "plays": plays, "last": last}));
        response.end();
        break;
      case 'POST':
        //console.log("post");
        const pathname = purl.pathname;
        switch (pathname) {
          case '/vote':
            //console.log("register");
            vote(request, response);
            break;
          default:
            response.writeHead(501, { 'Content-Type': "application/json", 'Access-Control-Allow-Origin': '*' });
            response.end();
            return;
        }
	break;
      default:
	response.writeHead(501, { 'Content-Type': "application/json", 'Access-Control-Allow-Origin': '*' });
        response.end();
    }
  });

  server.listen(port);

  console.log("Listening on port "+port);
}

function vote(request, response){
  let body = '';
  request.on('data', (chunk) => {body += chunk; }).on('end', () => {
    const query = JSON.parse(body);
    if(!query || query.id == undefined || query.play == undefined){
      response.writeHead(400, headers['plain']);
      response.write(JSON.stringify({error: 'Nick is undefined'}));
      response.end();
      return;
    }
    if(ids.has(query.id) || query.play<0 || query.play>=counter.length){
      response.writeHead(400, headers['plain']);
      response.write(JSON.stringify({error: 'Pass is undefined'}));
      response.end();
      return;
    }

    counter[query.play] += 1;
    ids.add(query.id);

    if(counter[query.play] > best){
      best = counter[query.play];
      best_i = query.play;
    }

    s = "";
    for(let i=0;i<counter.length;i++) s+="["+i+","+counter[i]+"]"
    console.log(s + " Most voted: "+best_i+" ("+best+" votes)");

    response.writeHead(200, headers['plain']);
    response.write(JSON.stringify({}));
    response.end();

  }).on('error',(error) => {console.log(error.message); });
}
