target=de1 de2 de3 de4 de5 de6

# include "entete.inc"

\text{prob=Étude d'un dé avec Python}
\text{pp=int}
\text{ppp=random}
\text{instructionf=Jouer le code et envoyer la réponse.}

\integer{tnf=randint(1..10)}
#if defined TARGET_de6
\integer{tnf=randint(1..3)}
#endif
\integer{tnf1=randint(1..3)}
\text{nff=3,4,6,8,10,12,16,20,24,30}
\integer{nf=\nff[\tnf]}
\integer{nf1=\nff[\tnf1]}
#if defined TARGET_de4 || defined TARGET_de5
\integer{nf=6}
#endif
\integer{nnf=randint(1..\nf)}
\integer{ntt=randint(5..30)}
\text{list_nff=wims(makelist x for x=1 to \nf)}
\text{list_nff1=wims(makelist x for x=1 to \nf1)}

\text{code=\#Importation des méthodes\#
from random import rand\pp}

#if defined TARGET_de1
# include "de1.inc"
# define NUM 1
#define GG 1
#define GGG 2
#endif
#if defined TARGET_de2
# include "de2.inc"
# define NUM 2
#define GG 1
#define GGG 2
#endif
#if defined TARGET_de3
# include "de3.inc"
# define NUM 3
#define GG 1
#define GGG 2
#endif
#if defined TARGET_de4
# include "de4.inc"
# define NUM 4
#define GG 1
#define GGG 2
#endif
#if defined TARGET_de5
# include "de5.inc"
# define NUM 5
#define GG 1
#define GGG 2
#endif
#if defined TARGET_de6
# include "de6.inc"
# define NUM 6
#define GG 2
#define GGG 3
#endif

\title{Dé NUM}
#if defined TARGET_de1 || defined TARGET_de2 || defined TARGET_de3 || defined TARGET_de4 || defined TARGET_de5
\text{instruction1=<ul><li>Initialiser les variables \(\text{vi}\)
  et \(\text{vf}\) afin que le programme simule un dé équilibré dont les issues sont \( \{ \list_nff \}\).</li>}
#endif
#if defined TARGET_de2 || defined TARGET_de3 || defined TARGET_de4 || defined TARGET_de5 || defined TARGET_de6
\text{instruction2=<li>Compléter la boucle for pour simuler \ntt tirages en initialisant
 la valeur \(\text{nt}\).</li>}
#endif
#if defined TARGET_de6
\text{instruction1=<ul><li>Initialiser les variables \(\text{videun}\), \(\text{vfdeun}\),
 \(\text{videdeux}\) et \(\text{vfdedeux}\) afin que le programme simule cette expérience.</li>}
#endif

\text{enonce=Pour étudier un dé, on lance ce dé un grand nombre de fois
et on étudie les données. Ce travail étant fastidieux et répétitif, on utilise
 la programmation pour arriver aux résultats. La simulation est réalisée
 en Python et la méthode <code>\ppp.rand\pp(3,9)</code> permet de tirer
 un entier compris entre 3 et 9 inclus.}

\statement{<div class="encadre">
<p class="problematique">\prob</p>
<div id="boiteg">
<img src="\imagedir/des.jpg" alt="Dés">
</div>
<div id="boited">
<img src="\imagedir/python.png" alt="Logo de Python">
</div>
<div class="enonce">
\enonce
<div class="question">
#if defined TARGET_de4 || defined TARGET_de5 || defined TARGET_de6
\if{\step==1}{
#endif
#if defined TARGET_de6
On souhaite simuler l'expérience aléatoire qui consiste à lancer deux dés équilibrés. Les issues possibles
du premier dé sont \( \{ \list_nff \}\) et pour le second dé, les issues possibles sont \( \{ \list_nff1 \}\).
Le but de cette expérience aléatoire est d'étudier la somme des deux dés.
 Déterminer les valeurs possibles prises par
 la somme :  <div class="wimscenter">\embed{reply1,2}</div>
#endif
\instruction1
\instruction2
\instruction3
\instruction4
<li>\instructionf</li>
</ul>
<div>
\embed{reply GG,[python,[\code]];[idtest2,theme=\theme canvas init \instruction_code,Jouer le code !]}
</div>
#if defined TARGET_de4 || defined TARGET_de5
<div class="wimscenter wimsborder box">
\B
</div>
\embed{reply2}}
\if{(\step==2 or \step==3) and \sc_reply1==1}{
<p>La simulation de \ntt lancers d'un dé à six faces est représentée ci-dessous :</p>
<div class="wimscenter box">
\BB
</div>
<ul><li>Quelle est la probabilité théorique d'apparition d'une des faces ? Arrondir au millième.
<div class="unbreakable">\(P_t=\)\embed{reply3,4}</div></li>
\for{jj=4 to 9}{
<li> Quelle est la fréquence expérimentale d'apparition de la face \de[\jj-3] ? Arrondir au millième.
<div class="unbreakable">\(F_{\text{exp}}(\de[\jj-3])=\)\embed{reply\jj,4}</div></li>}
<li>En comparant les fréquences expérimentales à la probabilité théorique,
 la simulation semble-t-elle satisfaisante ?\embed{reply10}</li>
<li>\last11\embed{reply11}</li>
</ul>
}
#endif
#if defined TARGET_de6
<div class="wimscenter">
\B
</div>
\embed{reply3}}
\if{(\step==2 or \step==3) and \sc_reply1==1}{
<p>La simulation de \ntt lancers de la somme de deux dés dont le premier à \nf faces et le deuxième à \nf1 faces est représentée ci-dessous :</p>
<div class="wimscenter wimsborder box">
\BB
</div>
Dans une situation d'équiprobabilité, la probabilité d'obtenir un événement A est
donnée par :
<div class="wimscenter unbreakable">\(p(A)=\frac{\text{Nombre de cas favorables à A}}{\text{Nombre des issues possibles }\,\Omega}\)</div>
Pour dénombrer les issues possibles et les différents événements, deux outils sont proposés :
<div class="wimscenter"><div><a class="bouton" \special{help tableau, Tableau&nbsp;de&nbsp;dénombrement}</a></div>
<div><a class="bouton"> \special{help arbre, Arbre&nbsp;de&nbsp;dénombrement}</a></div>
</div>
<ul>\for{jj=4 to \somme+2}{
<li> Quelle est la probabilité théorique d'apparition de la somme  \de[\jj-3] ? La fraction irréductible est attendue.
<div class="unbreakable">\(P_{\text{théorique}}(\de[\jj-3])=\)\embed{reply\jj,4}</div></li>}
<li>En comparant les fréquences expérimentales aux probabilités théoriques,
 la simulation semble-t-elle satisfaisante ?\embed{reply15}</li>
</ul>
}
#endif

</div>
\sscr
#if defined TARGET_de3
\embed{reply2}
<div>
\if{\sc_reply1==1 and \sc_reply2!=1}{<p class="oef_indbad">La ligne numéro 15 du programme
 est erronée. Modifier la condition sur l'instruction <code>if</code> pour que l'algorithme
 calcule le nombre d'apparitions de la face.</p>}
\if{\sc_reply1==1 and \sc_reply2==1}{<p class="oef_indgood">La condition sur l'instruction
 <code>if</code> est correcte.<p/>}
</div>
#endif
</div></div>}
#if defined TARGET_de4 || defined TARGET_de5
\text{A=\reply2}
\text{AA=wims(declosing \A)}
\text{grr=\gr
var nA=\A;
const xlen=nA.length;
var liii=brd.create('line',[[0,\ntt/6],[1,\ntt/6]],{Color:'red'});
brd.suspendUpdate();
var chart = brd.create('chart', [\A], {
         chartStyle:'bar',
         width:0.5,
         /*labels:\A,*/
         colors: color_liste,
         shadow:true
});
for(var jj = 0; jj < xlen; jj=jj+1) {
var tt=nA[jj].toFixed(\dec);
brd.create('point', [jj+1,nA[jj]],{name:tt,label:{offset:[-10, 10]},color:color_liste[jj]});}
brd.unsuspendUpdate();}
#endif
#if defined TARGET_de6
\text{A=\reply3}
\text{AA=wims(declosing \A)}
\text{grr=\gr
var nA=\A;
const xlen=nA.length;
brd.suspendUpdate();
for(var jj = 0; jj < xlen; jj=jj+1) {
var tt=nA[jj].toFixed(\dec);
brd.create('point', [jj+2,nA[jj]],{name:tt,label:{offset:[-10, 10]},color:color_liste[jj]});
brd.create('line', [[jj+2,0],[jj+2,nA[jj]]],{straightFirst:false, straightLast:false, strokeWidth:20,color:color_liste[jj]});}
brd.unsuspendUpdate();}
#endif


\text{BB=slib(geo2D/jsxgraph \grr)}
#if defined TARGET_de6
\answer{}{\de}{type=fset}{option=distinct_inputs}
#endif

\answer{}{\variable}{type=runcode}{option=precision=100}

#if defined TARGET_de3
\text{zz=\reply2}
\text{zzz=wims(declosing \zz)}
\answer{}{[n,[\MMN]]}{type=js2wims1}
#endif

#if defined TARGET_de4 || defined TARGET_de5
\answer{}{nn}{type=js2wims1}{option=noanalyzeprint}{weight=0}
\answer{}{0.167}{type=numeric}{option=comma}
#endif
#if defined TARGET_de6
\answer{}{nn}{type=js2wims1}{option=noanalyzeprint}{weight=0}
#endif


#if defined TARGET_de4
\integer{ff1=\AA[1]/\ntt*1000}
\real{f1=\ff1/1000}
\answer{}{\F1}{type=numeric}
\condition{la fréquence expérimentale d'apparition de la face 1 est de \f1}{\F1=\f1}

\integer{ff2=\AA[2]/\ntt*1000}
\real{f2=\ff2/1000}
\answer{}{\F2}{type=numeric}
\condition{la fréquence expérimentale d'apparition de la face 2 est de \f2}{\F2=\f2}

\integer{ff3=\AA[3]/\ntt*1000}
\real{f3=\ff3/1000}
\answer{}{\F3}{type=numeric}
\condition{la fréquence expérimentale d'apparition de la face 3 est de \f3}{\F3=\f3}

\integer{ff4=\AA[4]/\ntt*1000}
\real{f4=\ff4/1000}
\answer{}{\F4}{type=numeric}
\condition{la fréquence expérimentale d'apparition de la face 4 est de \f4}{\F4=\f4}

\integer{ff5=\AA[5]/\ntt*1000}
\real{f5=\ff5/1000}
\answer{}{\F5}{type=numeric}
\condition{la fréquence expérimentale d'apparition de la face 5 est de \f5}{\F5=\f5}

\integer{ff6=\AA[6]/\ntt*1000}
\real{f6=\ff6/1000}
\answer{}{\F6}{type=numeric}
\condition{la fréquence expérimentale d'apparition de la face 6 est de \f6}{\F6=\f6}

\answer{}{1;oui,non}{type=radio}{option=shuffle}
\answer{}{1;oui,non}{type=radio}{option=shuffle}

\text{nstep=}
\text{nstep=(\step==2 and \sc_reply1==1)?\lr}
#endif

#if defined TARGET_de5 
\integer{ff1=\AA[1]*1000}
\real{f1=\ff1/1000}
\answer{}{\F1}{type=numeric}
\condition{la fréquence expérimentale d'apparition de la face 1 est de \f1}{\F1=\f1}

\integer{ff2=\AA[2]*1000}
\real{f2=\ff2/1000}
\answer{}{\F2}{type=numeric}
\condition{la fréquence expérimentale d'apparition de la face 2 est de \f2}{\F2=\f2}

\integer{ff3=\AA[3]*1000}
\real{f3=\ff3/1000}
\answer{}{\F3}{type=numeric}
\condition{la fréquence expérimentale d'apparition de la face 3 est de \f3}{\F3=\f3}

\integer{ff4=\AA[4]*1000}
\real{f4=\ff4/1000}
\answer{}{\F4}{type=numeric}
\condition{la fréquence expérimentale d'apparition de la face 4 est de \f4}{\F4=\f4}

\integer{ff5=\AA[5]*1000}
\real{f5=\ff5/1000}
\answer{}{\F5}{type=numeric}
\condition{la fréquence expérimentale d'apparition de la face 5 est de \f5}{\F5=\f5}

\integer{ff6=\AA[6]*1000}
\real{f6=\ff6/1000}
\answer{}{\F6}{type=numeric}
\condition{la fréquence expérimentale d'apparition de la face 6 est de \f6}{\F6=\f6}

\answer{}{1;oui,non}{type=radio}{option=shuffle}
\answer{}{1;non,oui}{type=radio}{option=shuffle}

\text{nstep=}
\text{nstep=(\step==2 and \sc_reply1==1)?\lr}
#endif
#if defined TARGET_de6
\answer{}{\repp[1]}{type=numexp}
\answer{}{\repp[2]}{type=numexp}
\answer{}{\repp[3]}{type=numexp}
\answer{}{\repp[4]}{type=numexp}
\answer{}{\repp[5]}{type=numexp}
\answer{}{\repp[6]}{type=numexp}
\answer{}{\repp[7]}{type=numexp}
\answer{}{\repp[8]}{type=numexp}
\answer{}{\repp[9]}{type=numexp}
\answer{}{\repp[10]}{type=numexp}
\answer{}{\repp[11]}{type=numexp}
\answer{}{1;oui,non}{type=radio}{option=shuffle}
\text{nstep=}
\text{nstep=(\step==2 and \sc_reply1==1 and \sc_reply2==1)?\lr,reply15}

\help{
\if{\help_subject issametext tableau}{<div class="wimscenter"><h2>Tableau de dénombrement</h2>
\tableau1
}
\if{\help_subject issametext arbre}{<div class="wimscenter"><h2>Arbre de dénombrement</h2>
\arbre2
</div>}
</div>}
#endif
