target=carlo1 carlo11 carlo2 carlo3

# include "entete.inc"

\text{cconf=(\confparm1==)?1}
\integer{ncconf=(\confparm1==1)?0:1}
\text{defex=(\ncconf==1)?par défaut et par excès}

\text{pp=int}
\text{ppp=random}
\text{crochet=[]}
\text{ginclu=wims(char 1 of \crochet)}
\text{dinclu=wims(char 2 of \crochet)}

\integer{zz=randint(0..10)}
\integer{ntt=1000+100*\zz}
\text{code=\#Importation des librairies\#
from random import \ppp
\#Entrer les variables\#}

\text{car=carré}

#if defined TARGET_carlo1
#define NUM (random)
# include "carlo1.inc"
#endif
#if defined TARGET_carlo11
\text{code=\#Importation des librairies\#
from random import uniform
\#Entrer les variables\#}
#define NUM 1 (uniform)
# include "carlo11.inc"
#endif
#if defined TARGET_carlo2
#define NUM 2
# include "carlo2.inc"
# include "carlo23.inc"
#endif
#if defined TARGET_carlo3
#define NUM 3
# include "carlo3.inc"
# include "carlo23.inc"
#endif

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

\text{enonce1=<p><b>Nicholas Constantine Metropolis</b>, né le 11 juin 1915 à Chicago est un
physicien gréco-américain qui propose une méthode très originale du calcul du nombre
\(pi\).</p>
<p>La méthode de Monte-Carlo consiste à tirer aléatoirement un grand nombre de points dont les
 coordonnées \(x\) et \(y\) vérifient les inéquations
suivantes : \ineqe1 et \ineqe2. On dénombre les points \tre1 et le nombre total de points.</p>}

\text{instructionf=Jouer le code et envoyer la réponse.<br>
<img src="\imagedir/attention.png" alt="Attention"> : L'algorithme proposé est lent et il
 met plusieurs secondes à s'exécuter. }


\title{Méthode de Monte-Carlo NUM}
\text{gr=jsxbox,400 x 400,JXG.Options.point.fixed = true;
JXG.Options.point.highlight=false;
JXG.Options.point.showInfobox=false;
JXG.Options.point.name = "";
JXG.Options.point.face = "+";
JXG.Options.point.withLabel=true;
JXG.Options.point.size =1;
var brd = JXG.JSXGraph.initBoard('jsxbox', {axis:true, boundingbox: [\xmin,\ymax,\xmax,\ymin],
shownavigation:false,showCopyright : false,
showZoom : false,keepaspectratio : true,showFullscreen: true});
}
\text{B=slib(geo2D/jsxgraph \gr)}

\text{instruction2=<li>À l'aide des réponses précédentes, compléter l'algorithme ci-dessous 
en effectuant \nll points.</li>}

donne1=\DD1
</br>
donne=\DD
</br>adon=\adon

\statement{<div class="encadre">
<p class="problematique">\prob</p>
<div id="boiteg">
<img src="\imagedir/Nicholas.png" style="width:200px" alt="Nicholas Constantine Metropolis">
</div>
<div id="boited">
<img src="\imagedir/python.png" alt="Logo de Python">
</div>
<div class="enonce">
\enonce1 \enonce2
\graphique

<div class="question">
<ul>
#if defined TARGET_carlo1 || defined TARGET_carlo11
<li> Soit \(M\) le point de coordonnées \( (x ; y )\) . Exprimer le carré de la distance
\(O M^2\) en fonction de \(x\) et \(y\).
<div class="unbreakable wimscenter">\(O M^2={}\)\embed{reply1,4}</div></li>
<li>En déduire une inégalité stricte qui décrit l'ensemble des
points \(M\) appartenant au disque de rayon 1 et de centre \(O\).
<div class="wimscenter">\embed{reply2,6}\embed{reply3}1</div></li>
<li>Quelle est l'aire du carré \( A B C D \) ?
<div class="wimscenter">\(\mathcal{A}( A B C D )=\)\embed{reply4,2}</div></li>
<li>Quelle est l'aire du disque de centre \(O\)  et de rayon 1 ?
<div class="wimscenter">\(\mathcal{A}(Disque)=\)\embed{reply5,2}</div></li>
<li>Dans le cas où le nombre total \(nt\) de points est très important, déterminer approximativement le rapport entre
 l'aire du disque et l'aire du carré en fonction du nombre total \(nt\) de points et du nombre \(npi\)
 de points à l'intérieur du disque .
<div class="wimscenter">\(\frac{\mathcal{A}(Disque)}{\mathcal{A}(A B C D)}\approx\)\embed{reply6,2}</div></li>
#endif
#if defined TARGET_carlo2 || defined TARGET_carlo3
<li> Soit \(M\) le point de coordonnées \(M (x ; y )\) appartenant à la courbe représentative de la fonction \(C_f\).
 Exprimer la relation entre \(x\), \(y\) et la fonction \(f\).
<div class="unbreakable wimscenter">\(y={}\)\embed{reply1,2}</div></li>
<li> Soit \(M\) le point de coordonnées \(M (x ; y )\) appartenant au plan délimité par les inéquations suivantes
 \ineqe1 et \ineqe2. Exprimer une inégalité stricte ou large en fonction de \(x\), \(y\)
 et la fonction \(f\) pour que le point \(M \) soit \adad de la courbe. 
<div class="unbreakable wimscenter">\(y\)\embed{reply2}\embed{reply3,2}</div></li>
<li>Quelle est l'aire du \car \(ABCD\) ?
<div class="wimscenter">\(\mathcal{A}(\mathrm{ABCD})=\)\embed{reply4,2}</div></li>
<li>Calculer l'aire exacte du domaine violet ci-dessus.
<div class="unbreakable wimscenter">\(\displaystyle \int_{0}^{1} \fct_ecr \, \mathrm{d}x={}\)\embed{reply5,4}</div></li>
<li>Dans le cas où le nombre total \(nt\) de points est très important, déterminer le rapport entre l'aire du domaine
 violet et l'aire du carré en fonction du nombre total \(nt\) de points et du nombre \(npi\) de points \tre1 .
<div class="wimscenter">\(\frac{\mathcal{A}(violette)}{\mathcal{A}(\mathrm{ABCD})}\approx\)\embed{reply6,2}</div></li>
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

#if defined TARGET_carlo1 || defined TARGET_carlo11 || defined TARGET_carlo2 || defined TARGET_carlo3
\if{\sc_reply1=}{\embed{reply8}}
<ul>
<li>Déterminer l'intervalle de confiance à \(10^{-2}\) près \defex : \special{mathmlinput [I_c=\left[reply9;reply10\right]],3
reply 9,,color:blue;font-size:20px
reply 10,,color:blue;font-size:20px}</li>
<li>Quelle est la probabilité théorique qui appartient à cet intervalle avec un seuil de confiance de 95% ? 
<div class="wimscenter">\embed{reply11,5}</div></li>
<li>La probabilité théorique \(p\) appartient-elle à l'intervalle de confiance ?
<ul class="wims_nopuce">\for{h=1 to 4}{<li>\embed{reply12,\h}</li>}</ul>
</li>
</ul>
#endif
</div>

<script>
function graph(){ptt=0;
\jsss3_1
let nl=Sk.ffi.remapToJs(Sk.globals["nt"]);
let npi=Sk.ffi.remapToJs(Sk.globals["npi"]);
JXG.Options.point.size =2;
var brd = JXG.JSXGraph.initBoard('jsxbox', {axis:true, boundingbox: [\xmin,\ymax,\xmax,\ymin],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : true,showFullscreen: true});
brd.suspendUpdate();
for(let jj = 0; jj < l_liste_b; jj=jj+1) {brd.create('point', [x_liste_b[jj],y_liste_b[jj]],{Color:'blue'});}
for(let jj = 0; jj < l_liste_r; jj=jj+1) {brd.create('point', [x_liste_r[jj],y_liste_r[jj]],{Color:'red'});}

\jsss3_2
brd.unsuspendUpdate();}
execidtest7.addEventListener('click',graph);
</script>
</div></div>}
#if defined TARGET_carlo1 || defined TARGET_carlo11
\answer{}{x^2+y^2}{type=formal}
\answer{}{x^2+y^2}{type=formal}
\answer{}{1;<,>}{type=menu}
\answer{}{4}{type=formal}
\answer{}{Pi}{type=formal}
\answer{}{npi/nt}{type=formal}
#endif
#if defined TARGET_carlo2 || defined TARGET_carlo3
\answer{}{f(x)}{type=formal}
\answer{}{\jal;<,>=,>,<=}{type=menu}{option=shuffle}
\answer{}{f(x)}{type=formal}
\answer{}{\A_r}{type=formal}
\answer{}{\val_int}{type=formal}
\answer{}{npi/nt}{type=formal}
#endif
#if defined TARGET_carlo2 || defined TARGET_carlo1 || defined TARGET_carlo3 || defined TARGET_carlo11
\answer{}{\variable}{type=runcode}{option=precision=100}
#endif


#if defined TARGET_carlo1 || defined TARGET_carlo11 || defined TARGET_carlo2 || defined TARGET_carlo3
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
#endif
#if defined TARGET_carlo1 || defined TARGET_carlo11
\text{aadon=pari(dat=[\DD];
cint=0;
npi=0;
m=matrix(2,\nll,i,j,if(-1<=dat[i,j] && dat[i,j]<=1,if(i==1 && ((dat[1,j])^2+(dat[2,j])^2)<1,npi=npi+1;),cint=cint+1;));
ppi=4*npi/\nll;
)}
\text{adon2=pari(print(ppi);)}
#endif
#if defined TARGET_carlo2 || defined TARGET_carlo3
\text{zz=pari(f(t)=\fct_pari;)}
\text{aadon=pari(dat=[\DD];
cint=0;
npi=0;
m=matrix(2,\nll,i,j,if(0<=dat[i,j] && dat[i,j]<=1,if(i==1 && (dat[2,j]<f(dat[1,j])),npi=npi+1;),cint=cint+1;));
A_v=npi/\nll;
)}
\text{adon2=pari(print(A_v);)}
#endif
#if defined TARGET_carlo3
\real{adon2=(\nfct==2)?0.25*\adon2:\adon2}
\real{rrint=(\nfct==2)?0.25*\rrint:\rrint}
#endif
#if defined TARGET_carlo1 || defined TARGET_carlo11 || defined TARGET_carlo2 || defined TARGET_carlo3
\text{adon=pari(print(cint);)}
\text{adon1=pari(print(npi);)}
\integer{adon3=(\adon1/\nll-1/sqrt(\nll))*100}
\integer{adon3=(\ncconf==0)?\adon3:floor(\adon3)}
\real{adon33=\adon3/100}
\integer{adon4=(\adon1/\nll+1/sqrt(\nll))*100}
\integer{adon4=(\ncconf==0)?\adon4:ceil(\adon4)}
\real{adon44=\adon4/100}
#endif
#if defined TARGET_carlo1 || defined TARGET_carlo11
\integer{app2=((\adon33 < pi/4) and (pi/4 < \adon44))?1:2}
\text{app3=((\adon33 < pi/4) and (pi/4 < \adon44))?\in:\notin}
\answer{}{[x_liste_b],[x_liste_r],[y_liste_b],[y_liste_r],[rnpi],[rppi]}{type=js2wims1}{weight=0}{option=noanalyzeprint}
\condition{Les valeurs de \(x\) et de \(y\) sont bien comprises entre -1 et 1}{abs(\adon)<0.00001}
\condition{Le nombre de points à l'intérieur du disque est donc de \rnpi}{abs(\adon1-\rnpi)<0.1}
\condition{La valeur de \rppi renvoyée par l'algorithme est correcte}{abs(\adon2-\rppi)<10^(-6)}
\answer{inc1}{\conf1}{type=numeric}{option=comma}
\condition{La borne inférieure de l'intervalle de confiance est \adon33. Votre réponse est \conf1 }{abs(\adon33-\conf1)<10^(-2)}
\answer{inc2}{\conf2}{type=numeric}{option=comma}
\condition{La borne supérieure de l'intervalle de confiance est \adon44. Votre réponse est \conf2 }{abs(\adon44-\conf2)<10^(-2)}
\answer{inc1}{pi/4}{type=formal}
#endif
#if defined TARGET_carlo2 || defined TARGET_carlo3
\integer{app2=((\adon33 < \rrint) and (\rrint <\adon44))?1:2}
\text{app3=((\adon33 < \rrint) and (\rrint < \adon44))?\in:\notin}
\answer{}{[x_liste_b],[x_liste_r],[y_liste_b],[y_liste_r],[rnpi],[rA_v]}{type=js2wims1}{weight=0}{option=noanalyzeprint}
\condition{Les valeurs de \(x\) et de \(y\) sont bien comprises entre 0 et 1}{abs(\adon)<0.00001}
\condition{Le nombre de points \tre1 est donc de \rnpi}{abs(\adon1-\rnpi)<0.1}
\condition{La valeur de \rA_v renvoyée par l'algorithme est correcte}{abs(\adon2-\rA_v)<10^(-6)}
\answer{inc1}{\conf1}{type=numeric}{option=comma}
\condition{La borne inférieure de l'intervalle de confiance est \adon33. Votre réponse est \conf1 }{abs(\adon33-\conf1)<10^(-2)}
\answer{inc2}{\conf2}{type=numeric}{option=comma}
\condition{La borne supérieure de l'intervalle de confiance est \adon44. Votre réponse est \conf2 }{abs(\adon44-\conf2)<10^(-2)}
\answer{inc1}{\rrint}{type=formal}
#endif
#if defined TARGET_carlo1 ||defined TARGET_carlo11 || defined TARGET_carlo2 || defined TARGET_carlo3
\answer{}{\vvv;\(p \in I_c\),\(p \notin I_c\),\(p \cap I_c\),\(p \cup I_c\)}{type=radio}{option=shuffle}
\text{app4=(\in isin  \vvv)?1}
\text{app4=(\notin isin \vvv)?2}
\condition{La bonne réponse : \(p \app3 I_c\). Votre réponse \vvv est-elle juste ?}{\app4 == \app2 }
#endif
