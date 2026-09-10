target=differences

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}
\title_es{TITLE_es}


% Choix du type d'ensemble (nombres, lettres ou aléatoire) en fontion du paramètre de configuration.

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

#include "lang.inc"

% Calcul des différences

\text{AmoinsB=wims(listcomplement \B in \A)}
\text{BmoinsA=wims(listcomplement \A in \B)}
\if{\AmoinsB=}{\text{AmoinsB=\name_empty}}
\if{\BmoinsA=}{\text{BmoinsA=\name_empty}}

% Enoncé

\statement{\name_statement1
<div class="wimscenter">
\(A=\{\A\}\) &nbsp; \name_and &nbsp; \(B=\{\B\}\).
</div>
\name_statement2 \(A\setminus B\) \name_and  \(B\setminus A\).
<div class="spacer"> 
\(A\setminus B=)\embed{r1,20}<br/> 
\(B\setminus A=)\embed{r2,20}
</div>
<div class="wims_instruction">\name_instruction</div>
}

% Analyse des réponses

\answer{}{\AmoinsB}{type=set}
\answer{}{\BmoinsA}{type=set}
