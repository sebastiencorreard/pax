target=fonction1 fonction2 fonction3 fonction4 fonction5 fonction6 fonction7 fonction8 fonction9 fonction90 fonction91 fonction92 fonction93 fonction94 fonction95 fonction96

#define FCT Fonction
#define VV la valeur de la variable
#define VVS les valeurs des variables

\text{parialgo=}
\text{IC=Initialiser correctement}
\text{JE=Jouer le code et envoyer la réponse.}
\text{AFD=dans le programme afin d'obtenir une représentation graphique identique.}
\text{PAP=<img src="\imagedir/attention.png" alt="Attention"> La variable
  \(\text{a}\) doit impérativement être comprise entre 0.01 et 1.}
\text{AID=<ul><li>Il est indispensable d'appeler la librarie mathématique de Python en utilisant
  l'instruction <code>from math import *</code>
  au début du programme si l'on souhaite utiliser la fonction racine carrée <code>sqrt(x)</code>.
  </li><li>
  L'instruction <code>assert</code> suivie d'une condition permet d'effectuer une
  <strong>exception</strong> sur des valeurs définies par la condition.</li>
 </ul>}
\text{conj=Quelle(s) conjecture(s) pouvez-vous effectuer par lecture du graphique ?}

\integer{nbtheme=(\confparm1==)?1:\confparm1}
\matrix{theme=ambiance,neat;rubyblue,eclipse;the-matrix,3024-day}
#if defined TARGET_fonction1
\text{instruction=\IC VV \(\text{x}\) dans le programme. \JE}
# include "fonction1.inc"
#endif
#if defined TARGET_fonction2
\text{instruction=\IC VVS \(\text{x}\) et \(\text{a}\) \AFD \JE}
# include "fonction2.inc"
#endif
#if defined TARGET_fonction3
\text{instruction=\IC VVS \(\text{x}\),
 \(\text{a}\) et \(\text{xm}\) \AFD \JE}
# include "fonction3.inc"
#endif
#if defined TARGET_fonction4
\text{instruction=\IC dans le programme VV \(\text{a}\) pour que les
 10 premiers termes de la liste et la représentation graphique soient identiques. \JE <br>\PAP}
# include "fonction4.inc"
#endif
#if defined TARGET_fonction5
\text{instruction=Déterminer la FCT \AFD}
# include "fonction5.inc"
#endif
#if defined TARGET_fonction6 || defined TARGET_fonction8 || defined TARGET_fonction9 || defined TARGET_fonction90
\text{instruction=\IC VVS \(\text{x}\),
 \(\text{a}\), \(\text{xm}\) et déterminer la fonction \AFD \JE <br>\PAP}
#endif
#if defined TARGET_fonction6
# include "fonction6.inc"
#endif
#if defined TARGET_fonction7
\text{instruction=Déterminer la fonction \AFD}
# include "fonction7.inc"
#endif
#if defined TARGET_fonction8
# include "fonction8.inc"
#endif
#if defined TARGET_fonction9
# include "fonction9.inc"
#endif
#if defined TARGET_fonction90
# include "fonction90.inc"
#endif
#if defined TARGET_fonction91 || defined TARGET_fonction92
\text{instruction=\IC VVS \(\text{x}\),
 \(\text{a}\), \(\text{xm}\) et déterminer la fonction \AFD \JE
\AID\PAP}
#endif
#if defined TARGET_fonction91
# include "fonction91.inc"
#endif
#if defined TARGET_fonction92
# include "fonction92.inc"
#endif
#if defined TARGET_fonction93
\text{prob=Déterminer le signe d'une fonction sur un intervalle}
\text{instruction=\IC VVS \(\text{x}\),
 \(\text{a}\), \(\text{xm}\). L'instruction conditionnelle
 "if else" est à compléter avec une inégalité au sens strict ou large afin d'obtenir une
  représentation graphique identique. \JE De manière arbitraire,
 le point est rouge lorsque la valeur de son ordonnée est supérieure ou égale à zéro.
\AID \PAP}
# include "fonction93.inc"
#endif
#if defined TARGET_fonction94
\text{prob=Déterminer le sens de variation d'une fonction sur un intervalle}
\text{instruction=\IC VVS \(\text{x}\),
 \(\text{a}\), \(\text{xm}\). Déterminer la fonction. L'instruction conditionnelle
 "if else" est à compléter avec une inégalité au sens strict ou large afin d'obtenir une
  représentation graphique identique. \JE
\AID \PAP}
# include "fonction94.inc"
#endif
#if defined TARGET_fonction95
# include "fonction95.inc"
\text{prob=Résolution d'équation \(\underline{f(x) = k}\) sur un intervalle}
\text{instruction=On souhaite conjecturer les intervalles solution de
 l'équation :
<div class="wimscenter">  \( \fct_ecr = \b\) sur l'intervalle \(\left \cri \xi; \xm \right \cre\).</div>
\IC VVS \(\text{x}\),
 \(\text{a}\), \(\text{xm}\). Déterminer la fonction. Compléter l'instruction conditionnelle "if else" avec une
 égalité ou une inégalité afin d'obtenir une représentation graphique identique.
 \JE
<br>  \PAP}
#endif
#if defined TARGET_fonction96
# include "fonction96.inc"
\text{prob=Résolution d'inéquation \(\underline{f(x) \inn k}\) sur un intervalle}
\text{instruction=On souhaite conjecturer les intervalles solution de
 l'inéquation :
<div class="wimscenter"> \( \fct_ecr \inn \b \) sur l'intervalle \(\left \cri \xi; \xm \right \cre\).</div>
\IC VVS \(\text{x}\),
 \(\text{a}\), \(\text{xm}\). Déterminer la fonction. Compléter l'instruction conditionnelle "if else" avec une
 inégalité au sens strict ou large afin d'obtenir une représentation graphique identique.
 \JE
<br> \PAP}
#endif

#if defined TARGET_fonction1 || defined TARGET_fonction2 || defined TARGET_fonction3 || defined TARGET_fonction4 || defined TARGET_fonction5 || defined TARGET_fonction6 || defined TARGET_fonction7 || defined TARGET_fonction8 || defined TARGET_fonction9 || defined TARGET_fonction90 || defined TARGET_fonction91 || defined TARGET_fonction92
\text{prob=Maîtriser la construction de représentations graphiques}
#endif

\language{fr}
\author{Julien, Lyotard}
\email{Julien.Lyotard@ac-dijon.fr}

\text{zz=pari(f(t)=\fct_pari;)}

\text{DD=pari(default(format, "f.5");
nn=1;
xi=\xi;
ymin=f(xi);
ymax=f(xi);
pas=\pas;
xl=[];
yl=[];
colorl=[];
colorll=[black];
while(xi<=\xm || abs(xi-\xm)<10^(-4),
yi=f(xi);
xl=concat(xl,xi);
yl=concat(yl,yi);
xi=xi+pas;
\parialgo
if(f(xi)<ymin && abs(xi)>0.0001,ymin=f(xi););
if(f(xi)>ymax && abs(xi)>0.0001,ymax=f(xi));
nn=nn+1;);
)}

\text{xl=pari(print(xl);)}
\text{yl=pari(print(yl);)}

\text{ymin=pari(print(ymin);)}
\text{ymax=pari(print(ymax);)}

\text{colorl=pari(print(colorl);)}
\text{colorll=pari(print(colorll);)}
\text{nzero=pari(print(nzero);)}

\integer{nx=floor((\xm-\xi)/\pas)+1}
\integer{tnx=min(10,\nx)}

\text{enonce=Le code Python donné ci-dessous permet de construire le tableau de valeurs
  d'une fonction dans 2 listes \(\text{x_list}\) et \(\text{y_list}\). La représentation
  graphique du tableau de valeurs est construite automatiquement lorsque le code est joué.
  Compléter cet algorithme afin de réaliser la représentation graphique proposée. Afin de
  vous aider, les coordonnées exactes des \tnx premiers points
  sont données dans le tableau de valeurs ci-dessous.}

\text{mjsx=}
#if defined TARGET_fonction1 || defined TARGET_fonction2 || defined TARGET_fonction3 || defined TARGET_fonction4 || defined TARGET_fonction5 || defined TARGET_fonction6 || defined TARGET_fonction7 || defined TARGET_fonction8 || defined TARGET_fonction9 || defined TARGET_fonction90 || defined TARGET_fonction91 || defined TARGET_fonction92
\for{kj=1 to \nx}{\text{mjsx=wims(append line board.create('point', [\xl[\kj],\yl[\kj]],{color:"black"}); to \mjsx)}}
#endif
#if defined TARGET_fonction93 || TARGET_fonction95 || TARGET_fonction96
\for{kj=1 to \nx}{\text{mjsx=wims(append line board.create('point', [\xl[\kj],\yl[\kj]],{color:"\colorl[\kj]"}); to \mjsx)}}
#endif
#if defined TARGET_fonction94
\for{kj=1 to \nx}{\text{mjsx=wims(append line board.create('point', [\xl[\kj],\yl[\kj]],{color:"\colorll[\kj]"}); to \mjsx)}}
#endif

\text{code=
\#Initialisation des variables#
\initpythn
x=\xi_alg
a=\pas_alg
xm=\xm_alg

\#Définition d'une fonction#
def f(x):
  return \fct_alg

\#Initialisation des listes#
x_list=[]
y_list=[]
\initpythcol
\#Boucle afin de construire les listes#
while x<=xm:
  y=f(x)
  x_list.append(x)
  y_list.append(y)
  x=x+a
  \scriptpyth

\#Affichage des 10 premiers termes des listes#
print(x_list[\:10])
print(y_list[\:10])
\scriptpythh}

\text{A=slib(geo2D/jsxgraph jsxbox1,400 x 400,JXG.Options.point.fixed = true;
JXG.Options.point.showInfobox=false;
JXG.Options.point.highlight=false;
JXG.Options.point.name = "";
JXG.Options.point.face = "[]";
JXG.Options.point.size = 60/\nx;
JXG.Options.point.withLabel=true;
var board = JXG.JSXGraph.initBoard('jsxbox1', {axis:true, boundingbox: [\xi-1,\ymax+1,\xm+1,\ymin-1],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : false,
  zoom: {factorX: 1.25,factorY: 1.25,wheel: true,needShift: false,eps: 0.001},
  pan: {needShift: false,enabled: true,needTwoFingers: true,pinchHorizontal: true, pinchVertical: true,pinchSensitivity: 7}});
\mjsx
)}
\text{B=slib(geo2D/jsxgraph jsxbox,400 x 400,JXG.Options.point.fixed = true;
JXG.Options.point.highlight=false;
JXG.Options.point.showInfobox=false;
JXG.Options.point.name = "";
JXG.Options.point.face = "[]";
JXG.Options.point.withLabel=true;)}

\statement{
<div class="encadre">
<p class="problematique">\prob</p>
<div id="boited">
<img src="\imagedir/python.png" alt="Logo de Python">
</div>
<div class="enonce">
\enonce
<table class="wimscenter wimsborder">
<tr><th>\(x_i\)</th>
\for{ii=1 to \tnx}{<td>\xl[\ii]</td>}
</tr>
<tr><th>\(y_i\)</th>
\for{ii=1 to \tnx}{<td>\yl[\ii]</td>}
</tr>
</table>
<div class="question">
\instruction
</div>
</div>
<div>
\embed{reply1,[python,[\code]];[idtest2,fullscreen theme=[\theme[\nbtheme;]] canvas init \instruction_code,Jouer le code !]}
</div>
\inst
<br>
<div class="wimscenter wimsborder box">
<div>Représentation graphique du tableau de valeurs</div>
\B
</div>
<div class="wimscenter wimsborder box">
<div>Représentation graphique à effectuer</div>
\A
</div>
#if defined TARGET_fonction4
<div class="question">Quel est l'intérêt de diminuer la valeur de \(\text{a}\) ?
<ul>\for{h=1 to 3}{<li>\embed{reply2,\h}</li>}</ul></div>
#endif
#if defined TARGET_fonction93
<div class="question">\conj
<ul>
<li>La fonction \(f\) est \embed{reply2} sur l'intervalle
\special{mathmlinput [ \gau1 {reply3};{reply4} \droi1 ],3,
reply 3,,color:blue;font-size:20px
reply 4,,color:blue;font-size:20px}
</li>
\if{\aq==2 or \aq==3 or \aq==6 or \zzz==2}{<li>La fonction \(f\) est \embed{reply5} sur l'intervalle
\special{mathmlinput [ \gau2 {reply6};{reply7} \droi2],3,
reply 6,,color:blue;font-size:20px
reply 7,,color:blue;font-size:20px}
</li>}
</ul></div>
#endif
#if defined TARGET_fonction94
<div class="question">\conj
<ul>
<li>La fonction \(f\) est \embed{reply2} sur l'intervalle 
\special{mathmlinput [ \gau1 {reply3};{reply4} \droi1 ],3,
reply 3,,color:blue;font-size:20px
reply 4,,color:blue;font-size:20px}
</li>
\if{\aq==2 or \aq==4 or \aq==5}{<li>La fonction \(f\) est \embed{reply5} sur l'intervalle
\special{mathmlinput [ \gau2 {reply6};{reply7} \droi2],3,
reply 6,,color:blue;font-size:20px
reply 7,,color:blue;font-size:20px}
</li>}
</ul></div>
#endif
#if defined TARGET_fonction95
<div class="question">\conj
<br>La résolution de l'équation \( \fct_ecr = \b \) sur l'intervalle \(\left \cri \xi; \xm \right \cre\) a pour solution :
<div class="wimscenter">
\special{mathmlinput [\text{S}=\left \lbrace \, {reply2};{reply3} \, \right \rbrace],2,
reply 2,,color:blue;font-size:20px
reply 3,,color:blue;font-size:20px}
</div>
<div class="wims_instruction">Pour le symbole infini, taper inf.
  Donner les solutions dans l'ordre croissant.</div>
</div>
#endif
#if defined TARGET_fonction96
<div class="question">\conj
<br>La résolution de l'inéquation \( \fct_ecr \inn \b \) sur l'intervalle \(\left \cri \xi; \xm \right \cre\) a pour solution :
<div class="wimscenter">
\( \text{S}= \ca \)\embed{reply2,1};\embed{reply3,1}\(\caa\)
\if{(\aq==1 and (\inn==>= or \inn==>)) or (\aq==2 and (\inn==&lt;= or \inn==&lt;))}{\embed{reply4,1};\embed{reply5,1}\(\left \cre\)}
</div>
<div class="wims_instruction">Pour le symbole infini, taper inf.</div>
</div>
#endif
</div>
<script>
function graph(){
x_liste=Sk.ffi.remapToJs(Sk.globals["x_list"]);
y_liste=Sk.ffi.remapToJs(Sk.globals["y_list"]);
\javalc
const xlen=x_liste.length;
function findMinMax(arr,ar) {let xmin = arr[0], xmax = arr[0],ymin = ar[0], ymax = ar[0];
  for (let i = 1, len=arr.length; i < len; i++){
    let v = arr[i];
    let vv = ar[i];
    xmin = (v < xmin && Math.abs(v)>0.0001) ? v : xmin;
    xmax = (v > xmax && Math.abs(v)>0.0001) ? v : xmax;
    ymin = (vv < ymin && Math.abs(v)>0.0001) ? vv : ymin;
    ymax = (vv > ymax && Math.abs(v)>0.0001) ? vv : ymax;}
  return [Math.round(xmin)-1,Math.round(xmax)+1,Math.round(ymin)-1,Math.round(ymax)+1];}
let xyminmax=findMinMax(x_liste,y_liste);
JXG.Options.point.size =60/\nx;
var brd = JXG.JSXGraph.initBoard('jsxbox', {axis:true, boundingbox: [xyminmax[0],xyminmax[3],xyminmax[1],xyminmax[2]],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : false,
  zoom: {factorX: 1.25,factorY: 1.25,wheel: true,needShift: false,eps: 0.001},
  pan: {needShift: false,enabled: true,needTwoFingers: true,pinchHorizontal: true, pinchVertical: true,pinchSensitivity: 7}});
brd.suspendUpdate();
for(var jj = 0; jj < xlen; jj=jj+1) {
#if defined TARGET_fonction1 || defined TARGET_fonction2 || defined TARGET_fonction3 || defined TARGET_fonction4 || defined TARGET_fonction5 || defined TARGET_fonction6 || defined TARGET_fonction7 || defined TARGET_fonction8 || defined TARGET_fonction9 || defined TARGET_fonction90 || defined TARGET_fonction91 || defined TARGET_fonction92
brd.create('point', [x_liste[jj],y_liste[jj]],{color:'black'});
#endif
#if defined TARGET_fonction93 || defined TARGET_fonction94 || defined TARGET_fonction95 || defined TARGET_fonction96
brd.create('point', [x_liste[jj],y_liste[jj]],{color:color_liste[jj]});
#endif
}
brd.unsuspendUpdate();}
execidtest2.addEventListener('click',graph);
</script>
}
#if defined TARGET_fonction1 || defined TARGET_fonction2 || defined TARGET_fonction3 || defined TARGET_fonction4 || defined TARGET_fonction5 || defined TARGET_fonction6 || defined TARGET_fonction7 || defined TARGET_fonction8 || defined TARGET_fonction9 || defined TARGET_fonction90 || defined TARGET_fonction91 || defined TARGET_fonction92
\answer{}{[x_list,[\xl]],[y_list,[\yl]]}{type=runcode}{option=precision=1000 \instruction_code}
#endif
#if defined TARGET_fonction93
\answer{}{[x_list,[\xl]],[y_list,[\yl]],[color_list,[\colorl]]}{type=runcode}{option=precision=100 \instruction_code}{weight=10}
\answer{}{\pn;positive,négative}{type=menu}{option=shuffle noanalyzeprint}{weight=1}
\answer{}{\int1}{type=numeric}{option=noanalyzeprint}{weight=1}
\answer{}{\int11}{type=numeric}{option=noanalyzeprint}{weight=1}
\answer{}{\pnn;positive,négative}{type=menu}{option=shuffle noanalyzeprint}{weight=1}
\answer{}{\int2}{type=numeric}{option=noanalyzeprint}{weight=1}
\answer{}{\int22}{type=numeric}{option=noanalyzeprint}{weight=1}
\condition{Conjecture}{(\pn iswordof \rep_np) and \int1==\xi and \int11==\xm}{weight=1}
\condition{Conjecture}{((\pn iswordof positive) and \int1==0 and \int11==\xm)}{weight=1}
\condition{Conjecture}{((\pnn iswordof négative) and \int2==\xi and \int22==0)}{weight=1}
\condition{Conjecture 1}{((\pn iswordof \rep_np) and \int1==\xi and \int11==0) or ((\pn iswordof \rep_npp) and \int1==0 and \int11==\xm)}{weight=1}
\condition{Conjecture 2}{((\pnn iswordof \rep_np) and \int2==\xi and \int22==0) or ((\pnn iswordof \rep_npp) and \int2==0 and \int22==\xm)}{weight=1}
\condition{Conjecture 1}{((\pn iswordof \rep_np) and \int1==\sol and \int11==\xm) or ((\pn iswordof \rep_npp) and \int1==\xi and \int11==\sol)}{weight=1}
\condition{Conjecture 2}{((\pnn iswordof \rep_np) and \int2==\sol and \int22==\xm) or ((\pnn iswordof \rep_npp) and \int2==\xi and \int22==\sol)}{weight=1}
#endif
#if defined TARGET_fonction94
\answer{}{[x_list,[\xl]],[y_list,[\yl]],[color_list,[\colorll]]}{type=runcode}{option=precision=100 \instruction_code}{weight=10}
\answer{}{\cd;croissante,décroissante}{type=menu}{option=shuffle noanalyzeprint}{weight=1}
\answer{}{\int1}{type=numeric}{option=noanalyzeprint}{weight=1}
\answer{}{\int11}{type=numeric}{option=noanalyzeprint}{weight=1}
\answer{}{\cdd;croissante,décroissante}{type=menu}{option=shuffle noanalyzeprint}{weight=1}
\answer{}{\int2}{type=numeric}{option=noanalyzeprint}{weight=1}
\answer{}{\int22}{type=numeric}{option=noanalyzeprint}{weight=1}
\condition{Conjecture}{(\cd iswordof \rep_np) and \int1==\xi and \int11==\xm}{weight=1}
\condition{Conjecture 1}{((\cd iswordof décroissante) and \int1==\xi and \int11==0)}{weight=1}
\condition{Conjecture 2}{((\cdd iswordof décroissante) and \int2==0 and \int22==\xm)}{weight=1}
\condition{Conjecture 1}{((\cd iswordof \rep_npp) and \int1==\xi and \int11==0) or ((\cd iswordof \rep_nppp) and \int1==0 and \int11==\xm)}{weight=1}
\condition{Conjecture 2}{((\cdd iswordof \rep_npp) and \int2==\xi and \int22==0) or ((\cdd iswordof \rep_nppp) and \int2==0 and \int22==\xm)}{weight=1}
#endif
#if defined TARGET_fonction95
\answer{}{[x_list,[\xl]],[y_list,[\yl]],[color_list,[\colorl]]}{type=runcode}{option=precision=100 \instruction_code}{weight=10}
\answer{}{\xsol1}{type=numexp}{option=noanalyzeprint}{weight=1}
\answer{}{\xsol2}{type=numexp}{option=noanalyzeprint}{weight=1}
#endif
#if defined TARGET_fonction96
\answer{}{[x_list,[\xl]],[y_list,[\yl]],[color_list,[\colorl]]}{type=runcode}{option=precision=100 \instruction_code}{weight=10}
\answer{}{\pn}{type=numexp}{weight=1}
\answer{}{\pnn}{type=numexp}{weight=1}
\answer{}{\xsol2}{type=numexp}{weight=1}
\answer{}{\xm}{type=numexp}{weight=1}
#endif
#if defined TARGET_fonction4
\answer{}{2;Construire plus de points sur le graphique,Donner l'illusion de la continuité,Réaliser un segment continu}{type=checkbox}{option=split shuffle}
#endif
#if defined TARGET_fonction4 || defined TARGET_fonction5 || defined TARGET_fonction6 || defined TARGET_fonction7 || defined TARGET_fonction8 || defined TARGET_fonction9 || defined TARGET_fonction90 || defined TARGET_fonction91 || defined TARGET_fonction92 || defined TARGET_fonction93 || defined TARGET_fonction94 || defined TARGET_fonction95 || defined TARGET_fonction96
# include "feedback_mantisse.inc"
#endif
#if defined TARGET_fonction93
# include "feedback_zero.inc"
#endif
#if defined TARGET_fonction94
# include "feedback_fctinv.inc"
#endif
