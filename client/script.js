'use strict';

var blue = [];
var chosen = -1;
var id = 0;

window.onload = function () {
		id = (new Date()).getTime();
		let board = [[0,-1,0,-1,0,-1,0,-1],[-1,0,-1,0,-1,0,-1,0],[0,-1,0,0,0,0,0,-1],[0,0,-1,0,1,0,0,0],[0,0,0,0,0,0,0,0],[1,0,0,0,0,0,1,0],[0,1,0,1,0,1,0,1],[1,0,1,0,1,0,1,0]];
		let plays = [["B6","A5"],["C5","B4"],["C5","D4"],["C7","D6"],["E7","D6"],["E7","F6"],["G7","F6"],["H6","G5"]];

		drawBoard();
		drawPieces(board);
		let sz = plays.length;

		for(let i=0; i<sz;i++){
			createPlay(plays[i],i);
		}
	/*getData().then(function(response){
		id = (new Date()).getTime();
		let board = response['board'];
		let plays = response['plays'];

		drawBoard();
		drawPieces(board);
		let sz = plays.length;

		for(let i=0; i<sz;i++){
			createPlay(plays[i],i);
		}
	});*/
}

document.getElementById('submit').onclick = function() {
	if(chosen == -1){
		console.log(chosen);
		document.getElementById('info').innerHTML = "Invalid Submission";
		return;
	}
	srv_vote(id,chosen).then(function(response){
		if(response['error']) document.getElementById('info').innerHTML = "Submission ERROR";
		else document.getElementById('info').innerHTML = "Submission Successful";
	})
}

/******************************************************************************/
/******************************************************************************/

const canvas = document.getElementById('board');
const context = canvas.getContext('2d');

const canvasSize = 500;
const sectionSize = canvasSize / 8;

canvas.width = canvasSize;
canvas.height = canvasSize;

context.translate(0.5, 0.5);

function initBoard(){
	let b = [];

	for(let i=0;i<8;i++){
		b.push([]);
		for(let j=0;j<8;j++) b[i].push(0);
	}

	return b;
}

function drawKing(i,j,color){
	drawCircle(i+2,j,color);
	drawCircle(i-2,j,color);
}

function drawCircle_aux(i,j,color){
	context.beginPath();
	context.arc(i,j,(sectionSize*3/8),0,2*Math.PI);

	context.fillStyle = color;
	context.fill();

	context.lineWidth = 1;
  context.strokeStyle = "black";
  context.stroke();
}

function drawCircle(i,j,color){
	drawCircle_aux(i+2,j,color);
	drawCircle_aux(i-2,j,color);
}

function drawSquare(pos,mycolor){
	let color;
	const i = pos.charCodeAt(0)-"A".charCodeAt(0);
	const j = "8".charCodeAt(0)-pos.charCodeAt(1);
	if((i+j)%2 != 0 && !mycolor) color =  "lightgray";
	else if(!mycolor) color = "white";
	else color = mycolor;

	context.beginPath();
	context.rect(i*sectionSize,j*sectionSize,sectionSize,sectionSize);
	context.fillStyle = color;
	context.fill();

	context.fillStyle = "black";
	context.font = "12px Arial";
	context.fillText(pos,i*sectionSize,j*sectionSize+10);
}

function drawBoard () {
	for(let i=0;i<8;i++){
		for(let j=0;j<8;j++){
			drawSquare(String.fromCharCode(i+"A".charCodeAt(0))+""+(8-j));
		}
	}
}

function drawPiece(board,i,j){
	if(board[i][j] == 1)
		drawCircle(j*sectionSize + sectionSize/2,i*sectionSize + sectionSize/2, "darkgray");
	else if(board[i][j] == -1)
		drawCircle(j*sectionSize + sectionSize/2,i*sectionSize + sectionSize/2, "LightCoral");
	else if (board[i][j] > 0) {
		drawKing(j*sectionSize + sectionSize/2,i*sectionSize + sectionSize/2, "#565656");
	}
	else if (board[i][j] < 0) {
		drawKing(j*sectionSize + sectionSize/2,i*sectionSize + sectionSize/2, "FireBrick");
	}
}

function drawPieces(board){
	for(let i=0;i<8;i++){
		for(let j=0;j<8;j++){
			drawPiece(board,i,j);
		}
	}
}

/******************************************************************************/
/******************************************************************************/

const plays = document.getElementById('plays');

function createPlay(pieces, playId){
	let li = document.createElement("li");
	li.classList.add("play");
	li.id = playId;

	let span= document.createElement("div");
	span.classList.add("span");
	span.innerHTML = pieces[0];
	for(let i=1;i<pieces.length;i++) span.innerHTML += "-" + pieces[i];

	let input= document.createElement("input");
	input.classList.add("radio");
	input.type = "radio";
	input.name= "radio";
	input.id = "radio "+ playId;
	input.playId = playId;
	input.pieces = pieces;

	li.appendChild(span);
	li.appendChild(input);

	plays.appendChild(li);

	li.onclick = function(){
		document.getElementById("radio " + this.id).click();
	}

	input.onclick = function(){
		if(this.checked){
			chosen = this.playId;
			for(let i=0;i<blue.length;i++) drawSquare(blue[i]);
			for(let i=0;i<this.pieces.length;i++) drawSquare(this.pieces[i], "lightblue");
		}
	}
}
