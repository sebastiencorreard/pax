target=range1p range2p range3p range1l range2l range3l for1p for1l for2p for2l for3p for3l forc1p forc1l forc2p forc2l forc3p forc3l

\integer{nbtheme=(\confparm1==)?1:\confparm1}
\matrix{theme=ambiance,neat;rubyblue,eclipse;the-matrix,3024-day}
\text{cro=[]}
\text{ee=wims(char 1 of \cro)}

# include "entete.inc"

#define FR Fonction range avec
#define MS en modifiant le script
#define LS en lecture de script
#define A argument
#define AA arguments
#define BF Boucle for avec
#define BFC Boucle for en compréhension avec
#define CJ Le code suivant est joué :
#define DL Déterminer la liste créée :
#define PCLC pour lister par compréhension

#if defined TARGET_range1p
\title{FR 1 A MS}
#endif
#if defined TARGET_range1l
\title{FR 1 A LS}
#endif
#if defined TARGET_for1p
\title{BF 1 A MS}
#endif
#if defined TARGET_for1l
\title{BF 1 A LS}
#endif
#if defined TARGET_forc1p
\title{BF 1 A PCLC MS}
#endif
#if defined TARGET_forc1l
\title{BF 1 A PCLC LS}
#endif
#if defined TARGET_for1p || defined TARGET_for1l
#include "forrange1.inc"
#include "range1.inc"
\text{exfor1=<div style="width:50px;overflow:auto"><pre>0<br>1<br>2<br></pre></div>}
#include "for.inc"
#endif
#if defined TARGET_forc1p || defined TARGET_forc1l
#include "forrange1.inc"
#include "range1.inc"
\text{exempleran=<code>print([i for i in range(\rrr)])</code> renvoie la liste : [0,1,2]}
#include "forc.inc"
#endif
#if defined TARGET_range1p || defined TARGET_range1l
#include "forrange1.inc"
#include "range1.inc"
#endif

#if defined TARGET_range2p
\title{FR 2 AA MS}
#endif
#if defined TARGET_range2l
\title{FR 2 AA LS}
#endif
#if defined TARGET_for2p
\title{BF 2 AA MS}
#endif
#if defined TARGET_for2l
\title{BF 2 AA LS}
#endif
#if defined TARGET_forc2p
\title{BF 2 AA PCLC MS}
#endif
#if defined TARGET_forc2l
\title{BF 2 AA PCLC LS}
#endif
#if defined TARGET_for2p || defined TARGET_for2l
#include "forrange2.inc"
#include "range2.inc"
\text{exfor1=<div style="width:50px;overflow:auto"><pre>3<br>4<br>5<br>6<br></pre></div>}
#include "for.inc"
#endif
#if defined TARGET_forc2p || defined TARGET_forc2l
#include "forrange2.inc"
#include "range2.inc"
\text{exempleran=<code>print([i for i in range(\rrr)])</code> renvoie la liste : [3,4,5,6]}
#include "forc.inc"
#endif
#if defined TARGET_range2p || defined TARGET_range2l
#include "forrange2.inc"
#include "range2.inc"
#endif

#if defined TARGET_range3p
\title{FR 3 AA MS}
#endif
#if defined TARGET_range3l
\title{FR 3 AA LS}
#endif
#if defined TARGET_for3p
\title{BF 3 AA MS}
#endif
#if defined TARGET_for3l
\title{BF 3 AA LS}
#endif
#if defined TARGET_forc3p
\title{BF 3 AA PCLC MS}
#endif
#if defined TARGET_forc3l
\title{BF 3 AA PCLC LS}
#endif
#if defined TARGET_for3p || defined TARGET_for3l
# include "forrange3.inc"
# include "range3.inc"
#endif
#if defined TARGET_forc3p || defined TARGET_forc3l
# include "forrange3.inc"
# include "range3.inc"
\text{exempleran=<code>print([i for i in range(\rrr)])</code> renvoie la liste : [2,5,8,11]}
# include "forc.inc"
#endif
#if defined TARGET_range3p || defined TARGET_range3l
# include "forrange3.inc"
# include "range3.inc"
#endif

\text{instruction_code=}

\text{DD=pari(l=vector(\nbe);
for(x=1,\nbe,l[x]=\debut+\pas*(x-1));)}
\text{lp=pari(print(l);)}
\text{alist=[\lp]}
\text{lr=[\lp]:}


#if defined TARGET_range1p || defined TARGET_range2p || defined TARGET_range3p || defined TARGET_range1l || defined TARGET_range2l || defined TARGET_range3l
\text{code=print(list(range(\rrr)))}
#endif

#if defined TARGET_for1p || defined TARGET_for1l || defined TARGET_for2p || defined TARGET_for2l || defined TARGET_for3p || defined TARGET_for3l
\text{lr=wims(replace internal , by : in \lp):}
\text{alist=wims(replace internal , by <br> in \lp)}
\text{code=for compteur in range(\rrr):
  print(compteur)}
\text{laff=wims(makelist x<br> for x=0 to \rrr-1)}
\text{laff=wims(replace internal , by in \laff)}
#endif

#if defined TARGET_forc1p || defined TARGET_forc1l || defined TARGET_forc2p || defined TARGET_forc2l || defined TARGET_forc3p || defined TARGET_forc3l
\text{code=print([i for i in range(\rrr)])}
#endif

\text{variable=[print,\lr]}

\text{enonce=\enonfor
\enonran1
\enonran2
<br>
<b><u>Exemple :</u></b>
<br>
\exempleran
\exemplefor

}
#if defined TARGET_range1p || defined TARGET_range2p || defined TARGET_range3p || defined TARGET_for1p || defined TARGET_for2p || defined TARGET_for3p || defined TARGET_forc1p || defined TARGET_forc2p || defined TARGET_forc3p
\text{enonce=\enonce
<div class="wims_instruction"> Pour éviter toutes erreurs de syntaxe, l'instruction proposée fonctionne et
 vous devez juste la modifier.</div>}
#endif

\text{instruction1=<li>Cliquer sur le bouton : "Jouer le code".</li>}
\text{instruction2=<li>Modifier le code afin d'obtenir l'affichage des éléments suivants :
<pre>\alist</pre>
</li>}
\text{instruction3=<li>Jouer le code et envoyer la réponse.</li>}

\statement{<div class="encadre">
<p class="problematique">\prob</p>
<div id="boited">
<img src="\imagedir/python.png" alt="Logo de Python">
</div>
<div class="enonce">
\enonce
<div class="question">
#if defined TARGET_range1p || defined TARGET_range2p || defined TARGET_range3p ||defined TARGET_for1p ||defined TARGET_for2p ||defined TARGET_for3p ||defined TARGET_forc1p || defined TARGET_forc2p || defined TARGET_forc3p
<ul>
\instruction1
\instruction2
\instruction3
</ul>
<div>
\embed{reply 1,[python,[\code]];[id1,init fullscreen theme=[\theme[\nbtheme;]] \instruction_code,Jouer le code !]}
</div>
#endif
#if defined TARGET_range1l || defined TARGET_range2l || defined TARGET_range3l
CJ <code>print(list(range(\lrrr)))</code>
#endif
#if defined TARGET_forc1l || defined TARGET_forc2l || defined TARGET_forc3l
CJ <code>print([i for i in range(\lrrr)])</code>
#endif
#if defined TARGET_for1l || defined TARGET_for2l || defined TARGET_for3l
CJ <div style="width:300px;overflow:auto">
<pre>for compteur in range(\lrrr):<br>
print(compteur)</pre>
</div>
#endif

#if defined TARGET_range1l || defined TARGET_range2l || defined TARGET_range3l || defined TARGET_forc1l || defined TARGET_forc2l || defined TARGET_forc3l
<div>
DL \embed{reply 1,20}
</div>
<div class="wims_instruction">
Écrire la liste des entiers séparés par une virgule.
</div>
#endif
#if defined TARGET_for1l || defined TARGET_for2l || defined TARGET_for3l
<div>
Déterminer les valeurs retournées : \embed{reply 1,30}
</div>
<div class="wims_instruction">
Écrire les entiers séparés par une virgule.
</div>
#endif
</div></div></div>}
#if defined TARGET_range1p || defined TARGET_range2p || defined TARGET_range3p || defined TARGET_for1p || defined TARGET_for2p || defined TARGET_for3p || defined TARGET_forc1p || defined TARGET_forc2p || defined TARGET_forc3p
\answer{}{\variable}{type=runcode}{option=precision=100}
#endif
#if defined TARGET_range1l || defined TARGET_range2l || defined TARGET_range3l || defined TARGET_forc1l || defined TARGET_forc2l || defined TARGET_forc3l
\answer{}{\lp}{type=vector}{option= vector_left_=\(\lbrack\) vector_right_=\(\rbrack\)}
#endif
#if defined TARGET_for1l || defined TARGET_for2l || defined TARGET_for3l
\answer{}{\lp}{type=vector}{option=vector_left_=\(\) vector_right_=\(\)}
#endif
