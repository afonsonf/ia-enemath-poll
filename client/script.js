'use strict';

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

function drawSquare(i,j,color){
	context.beginPath();
	context.rect(i*sectionSize,j*sectionSize,sectionSize,sectionSize);
	context.fillStyle = color;
	context.fill();

	context.fillStyle = "black";
	context.font = "12px Arial";
	context.fillText(String.fromCharCode(i+"A".charCodeAt(0))+""+(8-j),i*sectionSize,j*sectionSize+10);
}

function drawBoard () {
	for(let i=0;i<8;i++){
		for(let j=0;j<8;j++){
			if((i+j)%2 != 0){
				drawSquare(i,j,"lightgray");
			}
			else drawSquare(i,j,"white");
		}
	}
}

function drawPieces(){
	for(let i=0;i<8;i++){
		for(let j=0;j<8;j++){
			if(board[i][j] == 1)
				drawCircle(i*sectionSize + sectionSize/2,j*sectionSize + sectionSize/2, "darkgray");
			else if(board[i][j] == -1)
				drawCircle(i*sectionSize + sectionSize/2,j*sectionSize + sectionSize/2, "LightCoral");
			else if (board[i][j] > 0) {
				drawKing(i*sectionSize + sectionSize/2,j*sectionSize + sectionSize/2, "#565656");
			}
			else if (board[i][j] < 0) {
				drawKing(i*sectionSize + sectionSize/2,j*sectionSize + sectionSize/2, "FireBrick");
			}
		}
	}
}

drawBoard();

let board = [
  [0, 1, 0, 0, 0, -2, 0, -1],
  [1, 0, 2, 0, 0,  0, -1, 0],
  [0, 1, 0, 0, 0, -1, 0, -1],
  [1, 0, 1, 0, 0,  0,-1,  0],
  [0, 1, 0, 0, 0, -1, 0, -1],
  [1, 0, 1, 0, 0,  0,-1,  0],
  [0, 1, 0, 0, 0, -1, 0, -1],
  [1, 0, 1, 0, 0,  0, -1, 0]
];

drawPieces(board);

/******************************************************************************/
/******************************************************************************/

const plays = document.getElementById('plays');

function createPlay(piece, codes, play){
	let li = document.createElement("li");
	li.classList.add("play");
	li.id = play;

	let span= document.createElement("div");
	span.classList.add("span");
	span.innerHTML = "(" + piece[0] + "," + piece[1] + ")";

	let input= document.createElement("input");
	input.classList.add("radio");
	input.type = "radio";
	input.name= "radio";
	input.id = "radio "+play;

	li.appendChild(span);
	li.appendChild(input);

	plays.appendChild(li);

	li.onclick = function(){
		document.getElementById("radio " + this.id).click();
	}
}

//lst_plays in form list of list of places

let lst_plays = [[0,1],[0,2],[0,3]]
let sz = lst_plays.length;

for(let i=0; i<sz;i++){
	createPlay(lst_plays[i],0,i);
}
