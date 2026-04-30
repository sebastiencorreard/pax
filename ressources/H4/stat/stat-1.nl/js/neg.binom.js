"use strict";
var dot = new Image;
dot.src = "scripts/authors/jm.evers/gifs/punt.gif";
var plinko_data = new Array();

function galton(P,num,bin){
 var k;var bakje;var jumps = bin - 1;
 for(bakje = 0; bakje < bin; bakje++){
  plinko_data[bakje] = 0;
 };
 for(var p = 0 ; p < num ; p++){
  bakje = 0;
  for(var b = 0; b < jumps; b++){
   k = Math.random();
   if(k > P){ bakje++; };
  };
  plinko_data[bakje] = plinko_data[bakje] + 1;
 };
};

function extra_balls(P,num){
 var bakje = 0;var k;var len = plinko_data.length;
 for(var p = 0; p < num ; p++){
  bakje = 0;
  for(var b = 0; b < len - 1; b++){
    k = Math.random();
    if(k > P){ bakje++; };
  };
  plinko_data[bakje] = plinko_data[bakje] + 1;
 };
};

function find_max(data){
 var len = data.length;
 var max = 0;
 for(var p = 0 ; p < len ; p++){
  if( data[p] > max){ max = data[p];}
 };
 return max;
};

function make_plinko(xsize,ysize,fillcolor,strokecolor,fontsize){
 var canvas = document.getElementById('plinko_bord');
 var plinko_div = document.getElementById('plinko_div');
 plinko_div.style.display = 'block';
 var ctx = canvas.getContext("2d");
 ctx.clearRect(0,0,xsize,ysize);
 var max = find_max(plinko_data);var yf = 0.8*ysize / max;var len = plinko_data.length;var binwidth = xsize / len;
 ctx.lineWidth = 2;ctx.font = "bold "+fontsize+"px Ariel";var y;var x;
 ctx.beginPath();
 ctx.strokeStyle = "#000000";
 for(var p = 0 ; p < len ;p++){
  x = p*binwidth;
  ctx.moveTo(x,ysize);
  ctx.lineTo(x,0);
 }
 ctx.stroke();
 ctx.closePath();
 //ctx.fillStyle = "rgba("+fillcolor+")";
 ctx.strokeStyle = "rgba("+strokecolor+")";
 var pat = ctx.createPattern(dot, "repeat");
 ctx.fillStyle = pat;
 ctx.beginPath();
 var marge = 30;
 var h;
 for(var p = 0 ; p < len ;p++){
  x = p*binwidth;
  h = yf*plinko_data[p];
  y=ysize - marge - h
  ctx.rect(x,y,binwidth,h);
 };
 ctx.closePath();
 ctx.fill();
 ctx.stroke();
 ctx.strokeStyle = "rgba(0,0,0,0.8)";
 ctx.fillStyle = "rgba(0,0,0,0.8)";
 for(var p = 0 ; p < len ;p++){
  x = p*binwidth + 0.3*binwidth;;
  y= ysize - marge - yf*plinko_data[p]
  ctx.fillText(plinko_data[p],x,y);
  ctx.fillText(" "+(p+1)+" ",x,ysize);
  
 };
};

function make_data_table(name_class,name_ball,name_bin){
 var table_div = document.getElementById('table_div');
 table_div.style.display = 'block';
 var table="<table class="+name_class+"><tr><th>"+name_bin+"</th>";
 var len = plinko_data.length;
 for(var p = 0 ; p < len ;p++){
    table+="<th>"+(p+1)+"</th>";
 };
 table+="</tr><tr><th>"+name_ball+"</th>";
 for(var p = 0 ; p < len ;p++){
    table+="<th>"+plinko_data[p]+"</th>";
 };
 table+="</tr></table>";
 table_div.innerHTML = table;
};
