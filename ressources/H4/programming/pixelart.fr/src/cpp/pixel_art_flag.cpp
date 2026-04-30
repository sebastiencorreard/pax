target=pixel_art_flagV pixel_art_flagH pixel_art_flagC pixel_art_flagA

\text{theme=(\confparm1==)?ambiance:\confparm1}
#if defined TARGET_pixel_art_flagV
# include "pixel_art_flagV.inc"
# include "pixel_art_flagVH.inc"
#endif

#if defined TARGET_pixel_art_flagH
# include "pixel_art_flagH.inc"
# include "pixel_art_flagVH.inc"
#endif

#if defined TARGET_pixel_art_flagC
# include "pixel_art_flagC.inc"
# include "pixel_art_flagVH.inc"
#endif

#if defined TARGET_pixel_art_flagA
# include "pixel_art_flagA.inc"
# include "pixel_art_flagVH.inc"
#endif

\language{fr}
\author{Julien, Lyotard}
\email{Julien.Lyotard@ac-dijon.fr}

\text{rvb=le rouge, le vert et le bleu.}
\integer{rh=randint(0..255)}
\integer{gh=randint(0..255)}
\integer{bh=randint(0..255)}

\real{ncc=0.1*\nc}
\real{ncm=1.1*\nc}
\real{psize=150/\nc}

\text{code=
#################
##Initialisation#
#################
nombre_ligne=\nl
nombre_colonne=\nc
mat=\encop
########################
##Boucle sur la matrice#
########################
for i in range(nombre_ligne):
  for j in range(nombre_colonne):
      mat[i][j]=[255,0,0]

###########################
##Affichage de la matrice##
###########################
for i in range(nombre_ligne):
  print(mat[i])
}
\text{A=slib(geo2D/jsxgraph jsxbox1,400 x 400,JXG.Options.point.fixed = true;
JXG.Options.point.showInfobox=false;
JXG.Options.point.highlight=true;
JXG.Options.point.name = "";
JXG.Options.point.face = "[]";
JXG.Options.point.size = \psize;
JXG.Options.point.withLabel=true;
var board = JXG.JSXGraph.initBoard('jsxbox1', {axis:false, boundingbox: [-\ncc,-\ncc,\ncm,\ncm],
shownavigation:false,showCopyright:false,showFullscreen: true});
xaxis = board.create('axis', [[0, 0], [1,0]],
      {name:'nombre de colonnes',
      withLabel: true,
      label: {position: 'lrt',offset: [-100, 25]},
      });
xaxis.removeAllTicks();
board.create('ticks', [xaxis, 1],{
  strokeColor:'#ccc',
  majorHeight:-1,
  drawLabels:true,
  label: { offset: [5, 10]},
  minorTicks:0,
  drawZero:true});
yaxis = board.create('axis', [[0, 0], [0,1]],
      {name:'nombre de lignes',
      withLabel: true,
      label: {position: 'lrt',offset: [10, 0]}
      ,ticks:{scale: 1}}
      );
yaxis.removeAllTicks();
board.create('ticks', [yaxis, 1],{
  strokeColor:'#ccc',
  majorHeight:-1,
  drawLabels:true,
  label: { offset: [-15, -10]},
  minorTicks:0,
  drawZero:true});
\mjsx
)}
\text{B=slib(geo2D/jsxgraph jsxbox,400 x 400,JXG.Options.point.fixed = true;
JXG.Options.point.showInfobox=false;
JXG.Options.point.name = "";
JXG.Options.point.face = "[]";
JXG.Options.point.withLabel=true;)}

\statement{
<div class="encadre">
<p class="problematique">\prob</p>
<div id="boited">
<img src="\imagedir/\lii" alt="\nomi" />
<div class="wimscenter bold white">\nomi</div>
</div>
<div class="enonce">
\enonce
</div>
\enoncep
<div>
\embed{reply1,[python,[\code]];[idtest2,theme=\theme canvas init \instruction_code,Jouer le code !]}
</div>
\inst
<br/>
<div class="wimscenter wimsborder box">
\B
</div>
<div class="wimscenter wimsborder box">
\A
</div>
</div>
<script>
function graph(){
mat=Sk.ffi.remapToJs(Sk.globals["mat"]);
let matligne=mat.length;
let matcolonne=mat[0].length;
let max=Math.max(matligne,matcolonne);
let gg=1.1*max;
let ggm=0.1*max;
JXG.Options.point.size = 150/max;
var brd = JXG.JSXGraph.initBoard('jsxbox', {axis:false, boundingbox: [-ggm,-ggm,gg,gg],
shownavigation:false,showCopyright:false,showFullscreen: true});
xxaxis = brd.create('axis', [[0, 0], [1,0]],
      {name:'nombre de colonnes',
      withLabel: true,
      label: {position: 'lrt',offset: [-100, 25]},
      });
xxaxis.removeAllTicks();
brd.create('ticks', [xxaxis, 1],{
  strokeColor:'#ccc',
  majorHeight:-1,
  drawLabels:true,
  label: { offset: [5, 10]},
  minorTicks:0,
  drawZero:true});
yyaxis = brd.create('axis', [[0, 0], [0,1]],
      {name:'nombre de lignes',
      withLabel: true,
      label: {position: 'lrt',offset: [10, 0]}
      ,ticks:{scale: 1}}
      );
yyaxis.removeAllTicks();
brd.create('ticks', [yyaxis, 1],{
  strokeColor:'#ccc',
  majorHeight:-1,
  drawLabels:true,
  label: { offset: [-15, -10]},
  minorTicks:0,
  drawZero:true});

brd.suspendUpdate();
for(var jj = 0; jj < matligne; jj=jj+1) {
for(var ii = 0; ii < matcolonne; ii=ii+1) {
/*name:aaa[ss][jj][ii]*/
let s="rgb("+mat[jj][ii]+")";
brd.create('point', [ii+0.5,jj+0.5],{color:s});}}
brd.unsuspendUpdate();}
execidtest2.addEventListener('click',graph);
</script>
<script>
var bouboule=document.getElementById("boule");
var sliderRed=document.getElementById("rouge");
sliderRed.oninput=function(){document.getElementById("rv").innerHTML=this.value;coul();};
var sliderGreen = document.getElementById("vert");
sliderGreen.oninput = function (){document.getElementById("gv").innerHTML = this.value;coul();};
var sliderBlue = document.getElementById("bleu");
sliderBlue.oninput = function (){document.getElementById("bv").innerHTML = this.value;coul();};
function coul(){
  var r = document.getElementById("rv").innerHTML;
  var g = document.getElementById("gv").innerHTML;
  var b = document.getElementById("bv").innerHTML;
  bouboule.style.backgroundColor = "rgb("+r+","+g+","+b+")";
}
coul();
</script>
}


\answer{}{[mat,[\DD]]}{type=runcode}{option= keyword_python=\keytest}
