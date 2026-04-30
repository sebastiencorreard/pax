target=pixel_art1 pixel_art2 pixel_art3 pixel_art4 pixel_art5 pixel_art6 pixel_art7 pixel_art8 pixel_art8p pixel_art9 pixel_art90 pixel_art90p pixel_art90pp pixel_art91 pixel_art92
pixel_art93
\text{tenonce=Les premières consoles de jeux ne disposent pas de beaucoup de mémoire donc les programmeurs
 sont obligés de coder les images en binaire, c'est-à-dire par une suite de 0 et de 1.
 Le zéro correspond à la couleur noire.}

\text{theme=(\confparm1==)?ambiance:\confparm1}
#if defined TARGET_pixel_art1
\integer{tot=4}
# include "pixel_art1.inc"
#endif
#if defined TARGET_pixel_art2
# include "pixel_art2.inc"
#endif
#if defined TARGET_pixel_art3
# include "pixel_art3.inc"
#endif
#if defined TARGET_pixel_art4
# include "pixel_art4.inc"
#endif
#if defined TARGET_pixel_art5
# include "pixel_art5.inc"
#endif
#if defined TARGET_pixel_art6
# include "pixel_art6.inc"
#endif
#if defined TARGET_pixel_art7
# include "pixel_art7.inc"
#endif
#if defined TARGET_pixel_art8
# include "pixel_art8.inc"
#endif
#if defined TARGET_pixel_art8p
# include "pixel_art8p.inc"
#endif
#if defined TARGET_pixel_art9
# include "pixel_art9.inc"
#endif
#if defined TARGET_pixel_art90
# include "pixel_art90.inc"
#endif
#if defined TARGET_pixel_art90p
# include "pixel_art90p.inc"
#endif
#if defined TARGET_pixel_art90pp
# include "pixel_art90pp.inc"
#endif
#if defined TARGET_pixel_art91
# include "pixel_art91.inc"
#endif
#if defined TARGET_pixel_art92
# include "pixel_art92.inc"
#endif
#if defined TARGET_pixel_art93
# include "pixel_art93.inc"
\text{tenonce=}
#endif

\language{fr}
\author{Julien, Lyotard}
\email{Julien.Lyotard@ac-dijon.fr}

\real{ncc=0.1*\nc}
\real{ncm=1.1*\nc}
\real{psize=150/\nc}

\text{code=
#################
##Initialisation#
#################
nombre_ligne=\nl
nombre_colonne=\nll
mat=\encop
########################
##Boucle sur la matrice#
########################
for i in range(nombre_ligne):
  for j in range(nombre_colonne):
      mat[i][j]=??

###########################
##Affichage de la matrice##
###########################
for i in range(nombre_ligne):
  print(mat[i])
}
#if defined TARGET_pixel_art93
\text{code=
#################
##Initialisation#
#################
nombre_ligne=\nl
nombre_colonne=\nll
img=\encop
########################
##Boucle sur la matrice#
########################
mat=[[1] * nombre_colonne for _ in range(nombre_ligne)]
for i in range(nombre_ligne):
  for j in range(nombre_colonne):
      mat[i][j]=img[i][j]

###########################
##Affichage de la matrice##
###########################
for i in range(nombre_ligne):
  print(mat[i])
}
#endif
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
</div>
<div class="enonce">
\enonce
</div>
\tenonce
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
if(mat[jj][ii]==0){
brd.create('point', [ii+0.5,jj+0.5],{color:'black'});}}}
brd.unsuspendUpdate();}
execidtest2.addEventListener('click',graph);
</script>
}


\answer{}{[mat,[\DD]]}{type=runcode}{option= keyword_python=\keytest}
