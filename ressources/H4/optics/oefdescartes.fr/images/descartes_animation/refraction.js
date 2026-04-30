//pour les écrans tactiles
var passiveSupported = false;

try {
  window.addEventListener("test", null, Object.defineProperty({}, "passive", { get: function() { passiveSupported = true; } }));
} catch(err) {}


//VARIABLES

//taille de l'écran
let largeur = window.innerWidth;
let hauteur = window.innerHeight;
let orientation=0; //0 paysage 1 portrait
//orientation
if (largeur>hauteur){orientation=0}else{orientation=1}
//les images

let laser=new Image();
function creelaser(chemin){
	laser.src=chemin;
	laser.onload=function(){adapterTaille()};
}


//les variables d'animation et de gestion des éléments affichés		
let posLaser={x:10,y:50};
let ratioLaser=1;
let largLaser=0;
let longLaser=0;
let angle=0;
let anglebis=0;
let cadran=[0,0];
let dioptre=0;
let sourisDown=false;
let n1=1;
let n2=1.5;
let dessin=document.getElementById("dessin");let ctxDessin=dessin.getContext('2d');



function coordPolaire(x,y){
		if (x>0&&y>=0){return Math.atan(y/x)};
		if (x>0&&y<0){return Math.atan(y/x)+2*Math.PI};
		if (x<0){return Math.atan(y/x)+Math.PI};
		if (x==0&&y>0){return Math.PI/2};
		if (x==0&&y<0){return 3*Math.PI/2};
	};	
function codeCouleur(codePt) {
		if (codePt > 0xFFFF) {
			codePt -= 0x10000;
			return String.fromCharCode(0xD800 + (codePt >> 10), 0xDC00 + (codePt & 0x3FF));
		} 
		return String.fromCharCode(codePt);
	}

function ecrisAngle(cadran){
	with(ctxDessin){
		beginPath();
			shadowOffsetX = 4;
			shadowOffsetY = 4;
			shadowBlur = 4;	
			shadowColor   = "gray";
			textAlign="center";
			font = "20px Arial";
			fillText((Math.abs(cadran[0])/Math.PI*180).toFixed(1)+'°',dessin.width/2+100*Math.cos(cadran[1]),dioptre+100*Math.sin(cadran[1]));
			shadowOffsetX = 0;
			shadowOffsetY = 0;
			shadowBlur = 0;	
			shadowColor   = "rgba(0, 0, 0, 0)";
		closePath();
	}
}	
function misAjour(){
	with(ctxDessin){
		clearRect(0,0,dessin.width,dessin.height);
		fillStyle="lightpink";
		rect(0,0,dessin.width,dessin.height);
		fill();
	}	
	rempliDegrade(0,0,largeur,dioptre,['#D0F6FB','#69DCEB','#12D4EE'],false);
	rempliDegrade(0,dioptre,largeur,dessin.height,['#E7EBEB','#D1D5D5','#B0B1B1'],true);
	with(ctxDessin){
		beginPath();
			shadowOffsetX = 4;
			shadowOffsetY = 4;
			shadowBlur = 4;	
			shadowColor   = "gray";
			fillStyle="red";
			textAlign="center"
			textBaseline="middle"
			font="50px Mansalva";
			fillText("Réflexion et réfraction de la lumière",dessin.width/2,30);
		closePath();
	}		
	
	dessineNormale();
	dessineLaser();
	
	dessineAngle();
};
function rempliDegrade(x,y,l,h,tableauCouleur,sens){
	let lineaire = ctxDessin.createLinearGradient(0,y,0,h);
	let nbZone=tableauCouleur.length;
	for (let i=0;i<nbZone;i++){
		lineaire.addColorStop(i/(nbZone-1),tableauCouleur[i]);
	}	
	with(ctxDessin){
		beginPath();
		shadowOffsetX = 0;
			shadowOffsetY = 0;
			shadowBlur = 0;	
			shadowColor   = "rgba(0, 0, 0, 0)";
		fillStyle = lineaire;
		//fillRect(x,y,l,h);
		arc(dessin.width/2,dessin.height/2,Math.min(dessin.height*0.4,dessin.width*.4)-longLaser,0, Math.PI,sens);
		fill();
		closePath();
	
	}
}
function dessineNormale(){
	with(ctxDessin){
		beginPath();
			strokeStyle="black";
			setLineDash([5, 15]);
			moveTo(dessin.width/2,dessin.height/2-Math.min(dessin.height*0.4,dessin.width*.4));
			lineTo(dessin.width/2,dessin.height/2+Math.min(dessin.height*0.4,dessin.width*.4));
			stroke();
			setLineDash([]);
		closePath();
	}
}	
function dessineAngle(){
	if (le_angles.checked){
		with(ctxDessin){
			//incidence
			beginPath();
				shadowOffsetX = 4;
				shadowOffsetY = 4;
				shadowBlur = 4;	
				shadowColor   = "gray";
				fillStyle="red";
				moveTo(dessin.width/2,dioptre);
				if ((posLaser.x+largLaser/2)!=dessin.width/2){
					if (posLaser.y<dioptre){
						if ((posLaser.x+largLaser/2)<dessin.width/2 ){
							arc(dessin.width/2,dioptre,30,-Math.PI/2,-Math.PI/2-angle,true);
							
							
						}else{
							arc(dessin.width/2,dioptre,30,-Math.PI/2-angle,-Math.PI/2,true);
						}	
						cadran=[angle,-Math.PI/2-angle/2];
					}else{	
						if ((posLaser.x+largLaser/2)<dessin.width/2 ){
							arc(dessin.width/2,dioptre,30,Math.PI/2,Math.PI/2-angle,false);
						}else{
							arc(dessin.width/2,dioptre,30,Math.PI/2-angle,Math.PI/2,false);
						}
						cadran=[angle,Math.PI/2-angle/2]
					}	
				}	
				fill();
			closePath();
			ecrisAngle(cadran);
			//refracte
			if (le_refracte.checked){
				beginPath();
					shadowOffsetX = 4;
					shadowOffsetY = 4;
					shadowBlur = 4;	
					shadowColor   = "gray";
					fillStyle="blue";
					moveTo(dessin.width/2,dioptre);
					if ((posLaser.x+largLaser/2)!=dessin.width/2){
						if (posLaser.y<dioptre){
							if ((posLaser.x+largLaser/2)<dessin.width/2 ){
								arc(dessin.width/2,dioptre,30,Math.PI/2,Math.PI/2-anglebis,true);
							}else{
								arc(dessin.width/2,dioptre,30,Math.PI/2-anglebis,Math.PI/2,true);
								
							}
							cadran=[anglebis,Math.PI/2-anglebis/2]							
						}else{	
							if ((posLaser.x+largLaser/2)<dessin.width/2 ){
								arc(dessin.width/2,dioptre,30,-Math.PI/2,-Math.PI/2-anglebis,false);
								cadran=[anglebis,-Math.PI/2-anglebis/2]
							}else{
								arc(dessin.width/2,dioptre,30,-Math.PI/2-anglebis,-Math.PI/2,false);
								
							}
							cadran=[anglebis,-Math.PI/2-anglebis/2]
						}
					}	
					fill();
				closePath();
				ecrisAngle(cadran);
			};	
			//réflechi
			if (le_reflechi.checked && n1!=n2){
				beginPath();
					shadowOffsetX = 4;
					shadowOffsetY = 4;
					shadowBlur = 4;	
					shadowColor   = "gray";
					fillStyle="green";
					moveTo(dessin.width/2,dioptre);
					if ((posLaser.x+largLaser/2)!=dessin.width/2){
						if (posLaser.y<dioptre){
							if ((posLaser.x+largLaser/2)<dessin.width/2 ){
								arc(dessin.width/2,dioptre,30,-Math.PI/2,-Math.PI/2+angle,false);
							}else{
								arc(dessin.width/2,dioptre,30,-Math.PI/2+angle,-Math.PI/2,false);
							}	
							cadran=[angle,-Math.PI/2+angle/2]
						}else{	
							if ((posLaser.x+largLaser/2)<dessin.width/2 ){
								arc(dessin.width/2,dioptre,30,Math.PI/2,Math.PI/2+angle,true);
							}else{
								arc(dessin.width/2,dioptre,30,Math.PI/2+angle,Math.PI/2,true);
							}
							cadran=[angle,Math.PI/2+angle/2]
						}	
					}	
					fill();
				closePath();
				ecrisAngle(cadran);
			}	
		}	
	}	
}
function dessineLaser(){
	let posRotateX=largLaser/2+posLaser.x;
	angle=Math.atan((dessin.width/2-posRotateX)/(dioptre-posLaser.y));
	if (posLaser.y<dioptre){anglebis=Math.asin(n1/n2*Math.sin(angle))}else{anglebis=Math.asin(n2/n1*Math.sin(angle))};
	if (n1==n2){anglebis=angle}
	if (angle==Math.PI/2){anglebis=-Math.PI/2};
	if (angle==-Math.PI/2){anglebis=Math.PI/2};
	let R=Math.abs((n1-n2)/(n1+n2));
	R=R*R;
	let T=1-R;
	with(ctxDessin){
		shadowOffsetX = 4;
		shadowOffsetY = 4;
		shadowBlur = 4;	
		shadowColor   = "gray";
		//rayon incident
		beginPath();
			strokeStyle="red";
			lineWidth=2;
			moveTo(posRotateX,posLaser.y);
			lineTo(dessin.width/2,dioptre);
			stroke();
		closePath();
		//dessin du laser
		if (posLaser.y<dioptre){
			save();
			translate(posRotateX,posLaser.y);
			rotate(-angle);
			drawImage(laser,-largLaser/2,0,largLaser,longLaser);
			rotate(angle);
			translate(-posRotateX,-posLaser.y);
			restore();
		}else{
			save();
			translate(posRotateX,posLaser.y);
			rotate(Math.PI-angle);
			drawImage(laser,-largLaser/2,0,largLaser,longLaser);
			rotate(-Math.PI+angle);
			translate(-posRotateX,-posLaser.y);
			restore();
		}	
		//rayon refracté
		if (le_refracte.checked){
			beginPath();
				globalAlpha=T;
				moveTo(dessin.width/2,dioptre);
				if (posLaser.y<dioptre){
					lineTo(dessin.width/2+(dessin.height-dioptre)*Math.tan(anglebis),dessin.height);
				}else{
					lineTo(dessin.width/2-(dioptre)*Math.tan(anglebis),50);
				}
				stroke();
			closePath();
		}
		//rayon réfléchi	
		if (le_reflechi.checked && n1!=n2){
			beginPath();
				if (isNaN(anglebis)){globalAlpha=1}else{globalAlpha=R*50/9};
				moveTo(dessin.width/2,dioptre);
				if (posLaser.y<dioptre){
					lineTo(dessin.width/2+(dioptre)*Math.tan(angle),50);
				}else{
					lineTo(dessin.width/2-(dessin.height-dioptre)*Math.tan(angle),dessin.height);
				}
				stroke();
			closePath();
		}	
		globalAlpha=1;
	}
}	
//ecouteur sur le canvas
dessin.addEventListener('touchstart',start,   passiveSupported ? { passive: false } : false);
dessin.addEventListener('touchmove', bouge,   passiveSupported ? { passive: false } : false);
dessin.addEventListener('touchend', stop,  passiveSupported ? { passive: false } : false);
dessin.addEventListener('mousemove',bouge,  passiveSupported ? { passive: false } : false);
dessin.addEventListener('mousedown',start,  passiveSupported ? { passive: false } : false);
dessin.addEventListener('mouseup',stop,  passiveSupported ? { passive: false } : false);
function bouge(e){
	let bounds = dessin.getBoundingClientRect();
	e.preventDefault();
	try{
		
		let touch = e.targetTouches[0];
		var x=touch.pageX- bounds.left;
		var y=touch.pageY- bounds.top;
	}
	catch(error) {
		var x=e.clientX- bounds.left;
		var y=e.clientY- bounds.top;
	}
	let the_angle=coordPolaire(x-dessin.width/2,dioptre-y);	
	let the_angle2=coordPolaire(largLaser/2+posLaser.x-dessin.width/2,dioptre-posLaser.y);	
	if (Math.abs(the_angle2-the_angle)<0.01)
	{
		dessin.style.cursor="pointer"
	}
	else{
		dessin.style.cursor="default"
	};
	if (sourisDown){
		
		posLaser.x=dessin.width/2+(Math.min(dessin.height*0.4,dessin.width*.4)+largLaser)*Math.cos(the_angle);
	    posLaser.y=dessin.height/2-(Math.min(dessin.height*0.4,dessin.width*.4)+largLaser)*Math.sin(the_angle)
		misAjour();
	};	
};
function start(e){
	let bounds = dessin.getBoundingClientRect();
	e.preventDefault();
	try{
		
		let touch = e.targetTouches[0];
		var x=touch.pageX- bounds.left;
		var y=touch.pageY- bounds.top;
	}
	catch(error) {
		var x=e.clientX- bounds.left;
		var y=e.clientY- bounds.top;
	}
	sourisDown=true
}
function stop(e){
	let bounds = dessin.getBoundingClientRect();
	e.preventDefault();
	try{
		
		let touch = e.targetTouches[0];
		var x=touch.pageX- bounds.left;
		var y=touch.pageY- bounds.top;
	}
	catch(error) {
		var x=e.clientX- bounds.left;
		var y=e.clientY- bounds.top;
	}
	sourisDown=false;
	misAjour();
}
function adapterTaille(){
	largeur = window.innerWidth;
	hauteur = window.innerHeight;
	let les_labels=document.getElementsByClassName("commande");
	if (hauteur>largeur){
		for (let i=0;i<les_labels.length;i++){
			les_labels[i].style.display="inline";
		}
	}	
	else{
		for (let i=0;i<les_labels.length;i++){
			les_labels[i].style.display="block";
		}
	}
	//dimension canvas
	dessin.width=largeur;
	dessin.height=hauteur;
	dioptre=dessin.height/2;
	ratioLaser=laser.width/laser.height;
	if (largeur>hauteur){
		largLaser=dessin.height/6*ratioLaser;
		longLaser=dessin.height/6;
	}else{
		
		largLaser=dessin.width/6*ratioLaser;
		longLaser=dessin.width/6;
	}	
	posLaser.x=dessin.width/2+(Math.min(dessin.height*0.4,dessin.width*.4)+largLaser)*Math.cos(3*Math.PI/4);
	posLaser.y=dessin.height/2-(Math.min(dessin.height*0.4,dessin.width*.4)+largLaser)*Math.sin(3*Math.PI/4)
	misAjour();
}	

//LES BOUTONS
//gestion du bouton angle
let le_angles=document.getElementById("bangles");
le_angles.addEventListener('click',function(e){
	misAjour();}, passiveSupported ? { passive: false } : false);

//gestion bouton rayon réfléchi
let le_reflechi=document.getElementById("breflechi");
le_reflechi.addEventListener('click',function(e){
		misAjour();
}, passiveSupported ? { passive: false } : false);
le_reflechi.addEventListener('touchend',function(e){
		e.preventDefault();
		misAjour();
}, passiveSupported ? { passive: false } : false);
//gestion bouton rayon réfléchi
let le_refracte=document.getElementById("brefracte");
le_refracte.addEventListener('touchend',function(e){
		e.preventDefault();
		misAjour();
}, passiveSupported ? { passive: false } : false);	
le_refracte.addEventListener('click',function(e){
		misAjour();
},  passiveSupported ? { passive: false } : false);	
le_refracte.addEventListener('touchend',function(e){
		e.preventDefault();
		misAjour();
} , passiveSupported ? { passive: false } : false);
// On exécute la fonction une première fois au chargement de la page

window.addEventListener("resize", adapterTaille, passiveSupported ? { passive: false } : false);
//window.addEventListener("deviceorientation", adapterTaille,  passiveSupported ? { passive: false } : false);
