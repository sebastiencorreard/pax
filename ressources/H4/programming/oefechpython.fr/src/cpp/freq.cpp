target=freq1 freq2 freq3 freq4

# include "entete.inc"

\text{pp=int}
\text{ppp=random}
\text{crochet=[]}
\text{ginclu=wims(char 1 of \crochet)}
\text{dinclu=wims(char 2 of \crochet)}

\text{enonce1=Pour étudier une pièce de monnaie, on lance cette pièce de monnaie un
  grand nombre de fois et on dénombre le nombre de "pile" et de "face". Ce travail étant fastidieux
  et répétitif, on utilise la programmation pour arriver aux résultats. La simulation est réalisée
 en Python et la méthode <code>\ppp.\ppp()</code> permet de générer un nombre à virgule aléatoire
 compris entre 0 inclus et 1 non inclus.}

\text{instructionf=Jouer le code et envoyer la réponse.}

\integer{zz=randint(0..10)}
\integer{ntt=1000+100*\zz}
\text{code=\#Importation des librairies\#
from random import \ppp
\#Entrer les variables\#}

#if defined TARGET_freq1
#define NUM 1
# include "freq1.inc"
#endif
#if defined TARGET_freq2
#define NUM 2
# include "freq2.inc"
#endif
#if defined TARGET_freq3
#define NUM 3
# include "freq3.inc"
#endif
#if defined TARGET_freq4
#define NUM 4
# include "freq4.inc"
#endif
\title{Fréquence NUM}
\text{gr=jsxbox,600 x 400,JXG.Options.point.fixed = true;
JXG.Options.point.highlight=false;
JXG.Options.point.showInfobox=false;
JXG.Options.point.name = "";
JXG.Options.point.face = "+";
JXG.Options.point.withLabel=true;
color_liste=['red','yellow','blue','green','orange','purple'];
JXG.Options.point.size =1;
var brd = JXG.JSXGraph.initBoard('jsxbox', {axis:false, boundingbox: [-\ntt*0.2,1,\ntt*1.2,-1],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : false,showFullscreen: true});
xaxis = brd.create('axis', [[0,0], [1,0]],
      {name:'Nombre de tirages',
      withLabel: true,
      label: {position: 'rt',/* possible values are 'lft', 'rt', 'top', 'bot'*/
      offset: [-60, 30]   /*(in pixels)*/},Color:'red'});
yaxis = brd.create('axis', [[0, 0], [0,1]],
      {name:'Probabilités',withLabel: true,
      label: {position: 'rt',/* possible values are 'lft', 'rt', 'top', 'bot'*/
      offset: [10, 0]   /*(in pixels)*/},Color:'red'});}
\text{B=slib(geo2D/jsxgraph \gr)}

\text{instruction2=<li>Compléter la boucle for pour simuler \ntt tirages en initialisant
 la valeur \(\text{nt}\).</li>}

\statement{
<div class="encadre">
<p class="problematique">\prob</p>
<div id="boiteg">
<img src="\imagedir/PileFace.jpg" style="width:200px" alt="Pile ou Face">
</div>
<div id="boited">
<img src="\imagedir/python.png" alt="Logo de Python">
</div>
<div class="enonce">
\enonce1 \enonce2
<div class="question">
<ul>
#if defined TARGET_freq2 || defined TARGET_freq3 || defined TARGET_freq4
<li> Quelle est la probabilité théorique d'apparition d'une des faces ?
<div class="unbreakable">\(P_t=\)\embed{reply1,4}</div></li>
#endif
\instruction2
\instruction3
<li>\instructionf</li>
</ul>
<div>
\embed{\embb}
</div>
<div class="wimscenter wimsborder box">
\B
</div>
#if defined TARGET_freq2
<div>
L'ensemble des ordonnées des points \ecol1 est donc contenu dans l'intervalle :
<div class="unbreakable">
\(\left\ginclu\right.\) \embed{reply3,4} ; \embed{reply4,4} \(\left\ginclu\right.\)
</div>
L'ensemble des ordonnées des points \ecol2 est donc contenu dans l'intervalle :
<div class="unbreakable">
\(\left\ginclu\right.\) \embed{reply5,4} ; \embed{reply6,4} \(\left\ginclu\right.\)
</div>
</div>
#endif
#if defined TARGET_freq3
  <div>
  Déterminer le \rkh :
  <ul>
  <li>\rkh1 : \embed{reply3,2}</li>
  <li>\rkh2 : \embed{reply4,2}</li>
  <li>\rkh3 : \embed{reply5,2}</li>
  <li>\rkh4 : \embed{reply6,2}</li>
  </ul>
  </div>
  \if{\sc_reply1==1 or \sc_reply1==0.5 or \sc_reply1==0}{}{\embed{reply7}}
  <div>
  Conclure en précisant si les assertions sont vraies ou fausses :
  <div>
  Le \rkh \rkh1 est égal au \rkh \rkh3 :\embed{reply8}
  </div>
  <div>
  Le \rkh \rkh2 est égal au \rkh \rkh4 :\embed{reply9}
  </div>
  </div>
#endif
#if defined TARGET_freq4
\if{\sc_reply1==1 or \sc_reply1==0.5 or \sc_reply1==0}{}{
\embed{reply3}
\embed{reply4}}
#endif
</div>
<script>
function graph(){ptt=0;
\jsss3_1
y_liste=Sk.ffi.remapToJs(Sk.globals["y_list"]);
ptt=Sk.ffi.remapToJs(Sk.globals["pt"]);
const ylen=y_liste.length;
JXG.Options.point.size =2;
var brd = JXG.JSXGraph.initBoard('jsxbox', {axis:false, boundingbox: [-ylen*0.2,2,ylen*1.2,-1],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : false,showFullscreen: true});
xaxis = brd.create('axis', [[0,0 ], [1,0]],
      {name:'Nombre de lancers',
      withLabel: true,
      label: {position: 'rt',/* possible values are 'lft', 'rt', 'top', 'bot'*/
      offset: [-60, 30]   /*(in pixels)*/},Color:'red'});
yaxis = brd.create('axis', [[0, 0], [0,1]],
      {name:'Probabilité',withLabel: true,
      label: {position: 'rt',/* possible values are 'lft', 'rt', 'top', 'bot'*/
      offset: [10, 0]   /*(in pixels)*/}}
      );
brd.suspendUpdate();
for(var jj = 0; jj < ylen; jj=jj+1) {
brd.create('point', [jj,y_liste[jj]],{Color:'black'});}
\jsss3_2
brd.unsuspendUpdate();}
execidtest2.addEventListener('click',graph);
</script>
</div></div>}
#if defined TARGET_freq2 || defined TARGET_freq3 || defined TARGET_freq4
\answer{}{0.5}{type=numeric}{option=comma}
#endif
#if defined TARGET_freq1 || defined TARGET_freq2 || defined TARGET_freq3 || defined TARGET_freq4
\answer{}{\variable}{type=runcode}{option=precision=100}
#endif

#if defined TARGET_freq2
\answer{}{\en1}{type=numeric}{option=comma}
\answer{}{\en2}{type=numeric}{option=comma}
\answer{}{\en3}{type=numeric}{option=comma}
\answer{}{\en4}{type=numeric}{option=comma}
#endif
#if defined TARGET_freq3
\text{dq=\reply7}
\text{dq1=wims(declosing \dq[1])}
\text{dq2=wims(declosing \dq[2])}
\text{dq3=wims(declosing \dq[3])}
\text{dq4=wims(declosing \dq[4])}

\text{rep1=\reply3}
\text{rep2=\reply4}
\text{rep3=\reply5}
\text{rep4=\reply6}

\answer{}{\ren1}{type=numeric}
\answer{}{\ren2}{type=numeric}
\answer{}{\ren3}{type=numeric}
\answer{}{\ren4}{type=numeric}
\answer{}{[NPN_ysup1],[NPN_yinf1],[NPB_y1],[NPB_y0]}{type=js2wims1}{option=noanalyzeprint}{weight=0}
\condition{le \rkh \rkh1 est de \rep1}{\ren1=\dq1}
\condition{le \rkh \rkh2 est de \rep2}{\ren2=\dq2}
\condition{le \rkh \rkh3 est de \rep3}{\ren3=\dq3}
\condition{le \rkh \rkh4 est de \rep4}{\ren4=\dq4}
\answer{}{1;vrai,faux}{type=radio}
\answer{}{1;vrai,faux}{type=radio}
#endif
#if defined TARGET_freq4
\text{donne=\reply3}
\matrix{aadon=pari(dat=\donne;
ff=0;
nf=0;
yy=[];
for(i=1,20,if(dat[i]==1,nf=nf+1;);
ff=nf/i;
yy=concat(yy,ff);
);
)}
\text{adon=pari(print(yy);)}

\text{donnef= wims(declosing \adon)}
\text{test=\reply4}
\text{test1=wims(declosing \test)}
\answer{}{[donne]}{type=js2wims1}{weight=0}{option=noanalyzeprint}
\answer{}{[test]}{type=js2wims1}{weight=0}{option=noanalyzeprint}
\condition{Donnée Python : \test1[1] Donnée PariGP : \donnef[1]}{abs(\donnef[1]-\test1[1])<0.00001}
\condition{Donnée Python : \test1[2] Donnée PariGP : \donnef[2]}{abs(\donnef[2]-\test1[2])<0.00001}
\condition{Donnée Python : \test1[3] Donnée PariGP : \donnef[3]}{abs(\donnef[3]-\test1[3])<0.00001}
\condition{Donnée Python : \test1[4] Donnée PariGP : \donnef[4]}{abs(\donnef[4]-\test1[4])<0.00001}
\condition{Donnée Python : \test1[5] Donnée PariGP : \donnef[5]}{abs(\donnef[5]-\test1[5])<0.00001}
\condition{Donnée Python : \test1[6] Donnée PariGP : \donnef[6]}{abs(\donnef[6]-\test1[6])<0.00001}
\condition{Donnée Python : \test1[7] Donnée PariGP : \donnef[7]}{abs(\donnef[7]-\test1[7])<0.00001}
\condition{Donnée Python : \test1[8] Donnée PariGP : \donnef[8]}{abs(\donnef[8]-\test1[8])<0.00001}
\condition{Donnée Python : \test1[9] Donnée PariGP : \donnef[9]}{abs(\donnef[9]-\test1[9])<0.00001}
\condition{Donnée Python : \test1[10] Donnée PariGP : \donnef[10]}{abs(\donnef[10]-\test1[10])<0.00001}
\condition{Donnée Python : \test1[11] Donnée PariGP : \donnef[11]}{abs(\donnef[11]-\test1[11])<0.00001}
\condition{Donnée Python : \test1[12] Donnée PariGP : \donnef[12]}{abs(\donnef[12]-\test1[12])<0.00001}
\condition{Donnée Python : \test1[13] Donnée PariGP : \donnef[13]}{abs(\donnef[13]-\test1[13])<0.00001}
\condition{Donnée Python : \test1[14] Donnée PariGP : \donnef[14]}{abs(\donnef[14]-\test1[14])<0.00001}
\condition{Donnée Python : \test1[15] Donnée PariGP : \donnef[15]}{abs(\donnef[15]-\test1[15])<0.00001}
\condition{Donnée Python : \test1[16] Donnée PariGP : \donnef[16]}{abs(\donnef[16]-\test1[16])<0.00001}
\condition{Donnée Python : \test1[17] Donnée PariGP : \donnef[17]}{abs(\donnef[17]-\test1[17])<0.00001}
\condition{Donnée Python : \test1[18] Donnée PariGP : \donnef[18]}{abs(\donnef[18]-\test1[18])<0.00001}
\condition{Donnée Python : \test1[19] Donnée PariGP : \donnef[19]}{abs(\donnef[19]-\test1[19])<0.00001}
\condition{Donnée Python : \test1[20] Donnée PariGP : \donnef[20]}{abs(\donnef[20]-\test1[20])<0.00001}
#endif
