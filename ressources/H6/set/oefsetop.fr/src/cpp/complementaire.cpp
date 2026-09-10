target=complementaire complementaire_h

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}
\title_es{TITLE_es}

% Choix du type d''ensemble (nombres, lettres ou aléatoire) en fontion du paramètre de configuration.

\text{nombres=0,1,2,3,4,5,6,7,8,9,10}
\text{lettres=a,b,c,d,e,f,g,h,i,j,k}
\if{\confparm1=1}{\text{l=\nombres}}
\if{\confparm1=2}{\text{l=\lettres}}
\if{(\confparm1=3) or (\confparm1=)}{\if{randint(1,2)=1}{\text{l=\nombres}}{\text{l=\lettres}}}

% Création des ensembles A et B

\text{nA=randint(6..8)}
\text{l=shuffle(\l)}
\text{A=\l[1..\nA]}
\text{nB=randint(2..\nA)}
\text{l=shuffle(\A)}
\text{B=\l[1..\nB]}

% Calcul du complémentaire

#include "lang.inc"

\text{AmoinsB=wims(listcomplement \B in \A)}
\if{\AmoinsB=}{\text{AmoinsB=\name_empty}}

% Enoncé

\statement{\name_statement1
<div class="wimscenter">
\(A=\{\A\}\) &nbsp; \name_and &nbsp; \(B=\{\B\}\).
</div>
\name_statement2 \(\complement_A B\).
<div class="spacer">
\(\complement_A B=\)\embed{r1,20}
</div>
<div class="wims_instruction">\name_instruction</div>
}

% Analyse de la réponse

\answer{}{\AmoinsB}{type=set}

#if defined TARGET_complementaire_h
\hint{\name_hint}
#endif
