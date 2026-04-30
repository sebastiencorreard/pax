target=franccarreau1 franccarreau2

# include "entete.inc"

\text{cconf=(\confparm1==)?1}
\integer{ncconf=(\confparm1==1)?0:1}
\text{defex=(\ncconf==1)?par défaut et par excès}
\text{theme=(\confparm2==)?ambiance:\confparm2}

\precision{10000000}
\matrix{nstep=r1}
\nextstep{\nstep}

\integer{nl=randint(10..20)}
\integer{nl2=}
\text{B=}
\text{D=}
\text{Aide=}

\integer{n_cote=random(+,-)randint(0..10)}
\integer{n_ra=random(+,-)randint(0..4)}
\rational{cote=4+0.1*\n_cote}
\rational{ra=1+0.1*\n_ra}
\rational{xmin=-\ra}
\rational{ymin=-\ra}
\rational{xmax=\cote+2*\ra}
\rational{ymax=\cote+2*\ra}
\text{list_repere=\xmin,\ymax,\xmax,\ymin}
\rational{pp=((\cote-2*\ra)/\cote)^2}
\text{ran=random}
\text{crochet=[]}
\text{ginclu=wims(char 1 of \crochet)}
\text{dinclu=wims(char 2 of \crochet)}

#define TITRE Jeu du franc&#8209;carreau
#if defined TARGET_franccarreau1
\title{TITRE niveau 3eme}
\text{list_rep= wims(makelist r x for x = 3 to 5)}
\integer{fin=7}
# include "franccarreau1.inc"
#endif

#if defined TARGET_franccarreau2
\title{TITRE niveau seconde}
\integer{nll=randint(100..150)} <= Attention limité par la taille de la requête
\text{list_rep= wims(makelist r x for x = 3 to 12)}
\integer{fin=15}

\text{DD1=}
\text{DD2=}
\text{DD3=}
\text{DD4=}
\text{DD=}
\text{adon=}
\text{adon1=}
\text{adon2=}
\integer{adon3=}
\real{adon33=}
\integer{adon4=}
\real{adon44=}
\text{rppi=}
\text{rnpi=}
\text{cint=}

\integer{jal=randint(1..2)}
\text{tjal1=(\jal==1)?
x_list_v.append(x)
        y_list_v.append(y)
        npi=??:
x_list_r.append(x)
        y_list_r.append(y)}
\text{tjal2=(\jal==1)?
x_list_r.append(x)
        y_list_r.append(y):
x_list_v.append(x)
        y_list_v.append(y)
        npi=??}


\text{tvide=}
\text{code=\#Importation des librairies\#
from random import \ran
\#Entrer les variables\#
nt=?? \#Nombre de points
npi= 0 \#Nombre de points à l'intérieur du carré vert
\#initialisation des listes\#
x_list_r = []
y_list_r = []
x_list_v = []
y_list_v = []
\#################
for i in range(nt):
    a=\ran()
    b=\ran()
    x = 4*a
    y = 4*b
    if ??
        \tjal1      
    else:
        \tjal2
  
p = ??
\tvide    
  
print('Dans cet exemple, la probabilité de réaliser un franc-carreau est égale à environ ', p)
}
\text{ic=if (0.5 < x and x < 3.5) and (0.5 < y and y < 3.5):,if (x <0.5 or x > 3.5) or (y < 0.5 or y > 3.5):}
\text{icc=shuffle(\ic)}
\text{instruction_code=instruction=[\icc]}
\text{embb=reply7,[python,[\code]];[idtest7,theme=\theme canvas init \instruction_code,Jouer le code !]}
\text{variable=[nt,\nll]}

Pas de var ni de let car elle passe en global
\text{jss= x_liste_r=Sk.ffi.remapToJs(Sk.globals["x_list_r"]);
y_liste_r=Sk.ffi.remapToJs(Sk.globals["y_list_r"]);
x_liste_v=Sk.ffi.remapToJs(Sk.globals["x_list_v"]);
y_liste_v=Sk.ffi.remapToJs(Sk.globals["y_list_v"]);
l_liste_r=x_liste_r.length;
l_liste_v=x_liste_v.length;
rppi=Sk.ffi.remapToJs(Sk.globals["p"]);
rnpi=Sk.ffi.remapToJs(Sk.globals["npi"]);
}
\text{donne=}

\text{quest6=Dans le cas où le nombre total \(nt\) de points est très important, déterminer le rapport entre l'aire du domaine
 vert et l'aire du domaine bleu en fonction du nombre total \(nt\) de points et du nombre \(npi\) de points qui
 réalisent franc-carreau .}
\text{instruction2=À l'aide des réponses précédentes, compléter l'algorithme ci-dessous 
en effectuant \nll points.}
\text{instructionf=Jouer le code et envoyer la réponse.<br/>
<img src="\imagedir/attention.png" alt="Attention" /> : L'algorithme proposé est lent et il
 met plusieurs secondes à s'exécuter.}
#endif

\text{prob=Quelle est la probabilité de réaliser un franc-carreau ?}
\text{hist=<p>Le jeu du franc-carreau a été pratiqué dès le Moyen-Âge.
 Ce jeu consistait à jeter un écu sur un carrelage et à parier sur la position finale
 de la pièce : à cheval sur un des bords du carreau ou entièrement à l’intérieur d’un
 carreau, on parlait alors de « Franc-carreau ». Il a été étudié par Georges Louis Leclerc,
 comte de Buffon en 1733 :</p>
<div>Voici un problème qui m’a occupé ces jours passés, et qui sera peut-être du goût
 de Mr de Moivre. Vous ne savez peut-être pas ce que nous appelons en français le jeu
 du franc-carreau. Dans une chambre pavée de carreaux, on jette en l’air un écu.
<ul><li>S’il retombe sur un seul carreau, on dit qu’il tombe franc, et celui qui l’a jeté
 gagne.</li>
<li>S’il tombe sur deux ou plusieurs carreaux, celui qui l’a jeté perd.</li>
</ul>
 C’est un problème à résoudre et qui n’a point de difficulté : trouver la probabilité
 de gagner ou de perdre, les carreaux et l’écu étant donnés.</div>}
\text{enonce=<div>Pour jouer à franc-carreau, on utilise un quadrillage type carrelage ou damier,
et une pièce ou un palet plat et rond. On lance la pièce sur le quadrillage, et on regarde comment elle s'est
immobilisée : 
<ul><li>si elle ne touche qu'un seul carreau, on gagne et on dit qu'on a fait
« franc-carreau ».</li>
<li>Si elle chevauche une ligne du quadrillage (elle touche alors
plusieurs carreaux) ou si elle est tangente à une de ces lignes, on perd.</li>
<li> Si le centre de la pièce est à l'extérieur du quadrillage, on recommence.</li>
</ul>
</div>}
\text{quest1=Afin de simplifier ce problème, on travaille sur un unique carreau de côté \cote. Après
 avoir lancé \nl écus de rayon \ra, on obtient le graphique ci-dessous. Dénombrer le nombre de
 franc-carreau :}
\text{quest2=Conjecturer la zone de la figure qui va permettre d'obtenir un franc-carreau.}
\text{inst1=<div class="wims_instruction">Déplacer les centres des écus afin de délimiter cette zone.</div>}
\text{quest3=Calculer l'aire où le centre de la pièce peut tomber}
\text{quest4=Calculer l'aire où le centre de la pièce effectue un franc-carreau}
\text{quest5=En déduire la probabilité d'obtenir un franc-carreau}

\text{mjsx=}
\text{list_xy=}
\text{list_cercle=}
\integer{FC=0}
\for{kk=1 to \nl}{
\real{x=random(0..\cote)}
\real{y=random(0..\cote)}
\if{(\ra<\x and \x<\cote-\ra) and (\ra<\y and \y<\cote-\ra)}{\integer{FC=\FC+1}}
\text{list_xy=wims(append item \x,\y to \list_xy)}
\text{mjsx=wims(append line var c_\kk=brd.create('point', [\x,\y],{Name:'\(A_{\kk}\)',color:'black',fixed:true,visible:true}); to \mjsx)}
\text{list_cercle=wims(append line brd.create('circle', [c_\kk, \ra], {strokeColor: 'black', center: {visible:true}}); to \list_cercle)}
}

\text{AB=jsxbox,400 x 400,JXG.Options.point.fixed = true;
JXG.Options.point.highlight=false;
JXG.Options.point.showInfobox=false;
JXG.Options.point.name = "";
JXG.Options.point.face = "+";
JXG.Options.point.withLabel=true;
var brd = JXG.JSXGraph.initBoard('jsxbox', {axis:true, boundingbox: [\list_repere],
shownavigation:false,showCopyright : false,
showZoom : false,keepaspectratio : true,showFullscreen: true});
var a=brd.create('point',[0,0],{fixed:true,visible:false});
var b =brd.create('point',[0,\cote],{fixed:true,visible:false});
var c =brd.create('point',[\cote,0],{fixed:true,visible:false});
var d=brd.create('point',[\cote,\cote],{fixed:true,visible:false});
var pol1 = brd.create('polygon', [a,c,d,b], {vertices: {withLabel: false},Color: 'blue'});}

\text{ABB=wims(replace brd by brd2 in \AB)}
\text{AB2=wims(replace jsxbox by jsxbox2 in \ABB)}

\text{ABBB=wims(replace brd by brd3 in \AB)}
\text{AB3=wims(replace jsxbox by jsxbox3 in \ABBB)}

\text{ABBBB=wims(replace brd by brd4 in \AB)}
\text{AB4=wims(replace jsxbox by jsxbox4 in \ABBBB)}

\text{ABBBBB=wims(replace brd by brd5 in \AB)}
\text{AB5=wims(replace jsxbox by jsxbox5 in \ABBBBB)}

\text{A=slib(geo2D/jsxgraph \AB
\mjsx
\list_cercle
)}

\text{E=slib(geo2D/jsxgraph \AB5)}

\text{script=var brd3 = JXG.JSXGraph.initBoard('jxgbox3', {
 axis:true,boundingbox: [-0.5,5,5,-0.5], shownavigation:false,showCopyright : false,
showZoom : false,keepaspectratio : true,showFullscreen: true});
var a=brd3.create('point',[0,0],{name:"",fixed:true,visible:false});
var b =brd3.create('point',[0,\cote],{name:"",fixed:true,visible:false});
var c =brd3.create('point',[\cote,0],{name:"",fixed:true,visible:false});
var d=brd3.create('point',[\cote,\cote],{name:"",fixed:true,visible:false});
var pol1 = brd3.create('polygon', [a,c,d,b], {vertices: {withLabel: false},Color: 'blue'});
jxgbox_rep1 = brd3.create('point',jxgbox_var1,{face:"+",showInfobox:false});
jxgbox_rep2 = brd3.create('point',jxgbox_var2,{face:"+",showInfobox:false} );
jxgbox_rep3 = brd3.create('point',jxgbox_var3,{face:"+",showInfobox:false} );
jxgbox_rep4 = brd3.create('point',jxgbox_var4,{face:"+",showInfobox:false} );
brd3.create('circle', [jxgbox_rep1, \ra], {name:"A_1",strokeColor: 'black', center: {visible:true}});
brd3.create('circle', [jxgbox_rep2, \ra], {name:"A_2",strokeColor: 'black', center: {visible:true}});
brd3.create('circle', [jxgbox_rep3, \ra], {name:"A_3",strokeColor: 'black', center: {visible:true}});
brd3.create('circle', [jxgbox_rep4, \ra], {name:"A_4",strokeColor: 'black', center: {visible:true}});
brd3.create('polygon', [jxgbox_rep1,jxgbox_rep2,jxgbox_rep3,jxgbox_rep4], {vertices: {withLabel: false},Color: 'green'});
}


\statement{<div class="encadre">
<p class="problematique">\prob</p>
<div id="boiteg"><img src=\imagedir/GLLB.jpg alt="Georges-Louis Leclerc de Buffon" width="200" height="300"></div>
<div class="encadre">\hist</div>
<div id="boited">
<img src=\imagedir/FC.png alt="Jeu du franc-carreau" >
</div>
<div class="enonce">
\enonce
<div class="question">
<div class="etape">Étape \step sur 7</div>
\quest1  \embed{reply1,3}
<div class="wimscenter">
<div class="wimscenter" style="font-weight: bold;">\nl écus</div>
\A
</div>
\if{\step>=2}{
<div class="question">
\quest2
\inst1
\if{\step==2 or \sc_reply2!=1}{
<div class="wimscenter">
\embed{r2,400x400
jxgbox3 brd3
\script
jxgbox_var1=[Math.\ran()*\cote/2,Math.\ran()*\cote/2] ; jxgbox_var2=[Math.\ran()*\cote/2+\cote/2,Math.\ran()*\cote/2]; jxgbox_var3=[Math.\ran()*\cote/2+\cote/2,Math.\ran()*\cote/2+\cote/2];jxgbox_var4=[Math.\ran()*\cote/2,Math.\ran()*\cote/2+\cote/2]
}
</div>}
\if{\sc_reply2==1 or \step==6}{
<div class="wimscenter">
\D
</div>
}
\if{\step>=3 and \sc_reply2!=1}{
<div class="indication">\Aide 
<div class="wimscenter">
<div class="wimscenter" style="font-weight: bold;">\nl2 écus</div>
\B
</div>
</div>
}
}
\if{\step>=3 and \sc_reply2==1 or \step==6}{
<div class="question">
<ul><li>\quest3 : \embed{reply3,3}</li>
<li>\quest4 : \embed{reply4,3}</li>
<li>\quest5 : \embed{reply5,3}</li>
#if defined TARGET_franccarreau2
<li>\quest6
<div class="wimscenter">\(\frac{\mathcal{A}(verte)}{\mathcal{A}(bleue)}\approx\)\embed{reply6,3}</div>
</li>
<li>\instruction2</li>
<li>\instructionf</li>
#endif

#if defined TARGET_franccarreau2
<div class="wimscenter">
<img src="\imagedir/python.png" alt="Logo de Python" />
</div>
<div>
\embed{\embb}
</div>
<div class="wimscenter wimsborder box">
\E
</div>
\if{\sc_reply8=}{\embed{reply8}}
<li>Déterminer l'intervalle de confiance à \(10^{-2}\) près \defex : \special{mathmlinput [I_c=\left[reply9;reply10\right]],3
reply 9,,color:blue;font-size:20px
reply 10,,color:blue;font-size:20px}</li>
<li>Quelle est la probabilité théorique qui appartient à cet intervalle avec un seuil de confiance de 95% ? 
<div class="wimscenter">\embed{reply11,5}</div></li>
<li>La probabilité théorique \(p\) appartient-elle à l'intervalle de confiance ?
<ul class="wims_nopuce">\for{h=1 to 4}{<li>\embed{reply12,\h}</li>}</ul>
</li>
#endif

</ul>
</div>

#if defined TARGET_franccarreau2
<script>
function graph(){
\jss
let nl=Sk.ffi.remapToJs(Sk.globals["nt"]);
let npi=Sk.ffi.remapToJs(Sk.globals["npi"]);
JXG.Options.point.size =2;
var brd5 = JXG.JSXGraph.initBoard('jsxbox5', {axis:true, boundingbox: [\list_repere],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : true,showFullscreen: true});
brd5.suspendUpdate();
for(let jj = 0; jj < l_liste_r; jj=jj+1) {brd5.create('point', [x_liste_r[jj],y_liste_r[jj]],{Color:'red'});}
for(let jj = 0; jj < l_liste_v; jj=jj+1) {brd5.create('point', [x_liste_v[jj],y_liste_v[jj]],{Color:'green'});}

brd5.unsuspendUpdate();}
execidtest7.addEventListener('click',graph);
</script>
#endif
}
</div>
</div>
</div>}

#if defined TARGET_franccarreau2
\text{Donne=\reply8}
\text{DD1=wims(declosing \Donne[1])}
\text{DD2=wims(declosing \Donne[2])}
\text{DD3=wims(declosing \Donne[3])}
\text{DD4=wims(declosing \Donne[4])}
\text{DD=\DD1,\DD2;\DD3,\DD4}


\text{rnpi=wims(declosing \Donne[5])}
\text{rppi=wims(declosing \Donne[6])}
\text{rA_v=wims(declosing \Donne[6])}


text{DD=wims(replace internal \dinclu,\ginclu by ; in \Donne )} 
text{DD=wims(replace internal ; by , in \DDV )}

\text{aadon=pari(dat=[\DD];
cint=0;
npi=0;
m=matrix(2,\nll,i,j,if(0<=dat[i,j] && dat[i,j]<=\cote,if(i==1 && 0.5<dat[1,j] && dat[1,j] < 3.5 && 0.5<dat[2,j] && dat[2,j]<3.5,npi=npi+1;);,cint=cint+1;););
ppi=npi/\nll;
)}
\text{adon2=pari(print(ppi);)}
\text{adon=pari(print(cint);)}
\text{adon1=pari(print(npi);)}
\integer{adon3=(\adon1/\nll-1/sqrt(\nll))*100}
\integer{adon3=(\ncconf==0)?\adon3:floor(\adon3)}
\real{adon33=\adon3/100}
\integer{adon4=(\adon1/\nll+1/sqrt(\nll))*100}
\integer{adon4=(\ncconf==0)?\adon4:ceil(\adon4)}
\real{adon44=\adon4/100}

\integer{app2=((\adon33 < \pp) and (\pp < \adon44))?1:2}
\text{app3=((\adon33 < \pp) and (\pp < \adon44))?\in:\notin}

#endif

\answer{}{\FC}{type=numeric}

\answer{Graphique 4 cercles}{\ra,\ra;\cote-\ra,\ra;\cote-\ra,\cote-\ra;\ra,\cote-\ra}{type=jsxgraph}{option=precision=50 absolue}{option=nonstop}

\answer{}{\cote^2}{type=numeric}{option=nonstop}
\answer{}{(\cote-2*\ra)^2}{type=numeric}{option=nonstop}
\answer{}{((\cote-2*\ra)/\cote)^2}{type=numeric}{option=nonstop}

#if defined TARGET_franccarreau2
\answer{}{npi/nt}{type=formal}
\answer{}{\variable}{type=runcode}{option=precision=100}
\answer{Réponse non analysée}{[x_liste_r],[x_liste_v],[y_liste_r],[y_liste_v],[rnpi],[rppi]}{type=js2wims1}{weight=0}{option=noanalyzeprint}
\condition{Les valeurs de \(x\) et de \(y\) sont bien comprises entre 0 et \cote}{abs(\adon)<0.00001}
\condition{Le nombre de points à l'intérieur du carré est donc de \rnpi}{abs(\adon1-\rnpi)<0.1}
\condition{La valeur de \rppi renvoyée par l'algorithme est correcte}{abs(\adon2-\rppi)<10^(-6)}
\answer{inc1}{\conf1}{type=numeric}{option=comma}
\condition{La borne inférieure de l'intervalle de confiance est \adon33. Votre réponse est \conf1 }{abs(\adon33-\conf1)<10^(-2)}
\answer{inc2}{\conf2}{type=numeric}{option=comma}
\condition{La borne supérieure de l'intervalle de confiance est \adon44. Votre réponse est \conf2 }{abs(\adon44-\conf2)<10^(-2)}
\answer{inc1}{\pp}{type=formal}
\answer{}{\vvv;\(p \in I_c\),\(p \notin I_c\),\(p \cap I_c\),\(p \cup I_c\)}{type=radio}{option=shuffle}
\text{app4=(\in isin  \vvv)?1}
\text{app4=(\notin isin \vvv)?2}
\condition{La bonne réponse : \(p \app3 I_c\). Votre réponse \vvv est-elle juste ?}{\app4 == \app2 }
#endif

\integer{nl2=(\step==3 and \sc_reply2!=1 )?randint(100..200)}
\integer{nl2=(\step==4 and \sc_reply2!=1 )?randint(300..600)}
\integer{nl2=(\step==5 and \sc_reply2!=1 )?randint(1000..1500)}

\text{B=slib(geo2D/jsxgraph \AB2
brd2.suspendUpdate();
for (i=0; i<\nl2;i++) {let x=\cote*Math.\ran();
let y=\cote*Math.\ran();
let co="red";
if( \ra<x & x<\cote-\ra & \ra<y & y<\cote-\ra ){co="green";};
brd2.create('point', [x, y], { style:4, Color:co}); 
}
brd2.unsuspendUpdate();
)}

\text{Aide=Pour vous aider, on réalise \nl2 tirages. Pour une meilleure lecture
de la figure, on n'effectue pas les cercles. Les points verts correspondent aux centres des écus
 qui sont franc-carreau tandis que les points rouges correspondent aux centres des écus qui ne sont pas franc-carreau.}

\matrix{rep=\reply2}
\text{point1=\rep[1;]}
\text{point2=\rep[2;]}
\text{point3=\rep[3;]}
\text{point4=\rep[4;]}

\text{D=slib(geo2D/jsxgraph \AB4
zr1 = brd4.create('point',[\point1],{face:"+"});
zr2 = brd4.create('point',[\point2],{face:"+"} );
zr3 = brd4.create('point',[\point3],{face:"+"} );
zr4= brd4.create('point',[\point4],{face:"+"} );
brd4.create('circle', [zr1, \ra], {name:'\(A_{1}\)',strokeColor: 'black', center: {visible:true}});
brd4.create('circle', [zr2, \ra], {name:'\(A_{2}\)',strokeColor: 'black', center: {visible:true}});
brd4.create('circle', [zr3, \ra], {name:'\(A_{3}\)',strokeColor: 'black', center: {visible:true}});
brd4.create('circle', [zr4, \ra], {name:'\(A_{4}\)',strokeColor: 'black', center: {visible:true}});
brd4.create('polygon', [zr1,zr2,zr3,zr4], {vertices: {withLabel: false},Color: 'green'});
)}


\text{nstep=}
\text{nstep=(\step==2 )?r2}
\text{nstep=(\step=3 and \sc_reply2!=1)?r2}
\text{nstep=(\step=4 and \sc_reply2!=1)?r2}
\text{nstep=(\step=5 and \sc_reply2!=1)?r2}
\text{nstep=(\step=6 and \sc_reply2!=1)?\list_rep}
\text{nstep=(\step>=3 and \sc_reply2==1)?\list_rep}

\text{nstep=(\sc_reply3==1)?}
\text{nstep=(\step=\fin)?}
