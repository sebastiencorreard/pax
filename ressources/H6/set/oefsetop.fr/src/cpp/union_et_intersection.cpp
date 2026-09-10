target=union_et_intersection

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}
\title_es{TITLE_es}

% Choix du type d'ensemble (nombres, lettres ou aléatoire) en fontion du paramètre de configuration

\text{nombres=0,1,2,3,4,5,6,7,8,9,10}
\text{lettres=a,b,c,d,e,f,g,h,i,j,k}
\if{\confparm1=1}{\text{l=\nombres}}
\if{\confparm1=2}{\text{l=\lettres}}
\if{(\confparm1=3) or (\confparm1=)}{\if{randint(1,2)=1}{\text{l=\nombres}}{\text{l=\lettres}}}

% Création des ensembles A et B

\text{nA=randint(4..6)}
\text{l=shuffle(\l)}
\text{A=\l[1..\nA]}
\text{nB=randint(4..6)}
\text{l=shuffle(\l)}
\text{B=\l[1..\nB]}

% Calcul de l'union et de l'intersection avec A

\text{AinterB=wims(listintersect \A and \B)}
\text{AunionB=wims(listunion \A and \B)}

#include "lang.inc"

\if{\AinterB=}{\text{AinterB=\name_empty}}

% Enoncé

\statement{\name_statement1
<div class="wimscenter">
\(A=\{\A\}\) &nbsp; \name_and &nbsp; \(B=\{\B\}\).
</div>
\name_statement2 \(A\cup B\) \name_and  \(A\cap B\).
<div class="spacer">
\(A\cup B=)\embed{r1,20}<br/> 
\(A\cap B=)\embed{r2,20}
</div>
<div class="wims_instruction">\name_instruction</div>
}

% Analyse des réponses

\answer{}{\AunionB}{type=set}
\answer{}{\AinterB}{type=set}
