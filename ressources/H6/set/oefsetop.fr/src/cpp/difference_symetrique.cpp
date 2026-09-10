target=difference_symetrique difference_symetrique_h

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

% Calcul de la différence symétrique

\text{AmoinsB=wims(listcomplement \B in \A)}
\text{BmoinsA=wims(listcomplement \A in \B)}
\text{AdiffB=wims(listunion \AmoinsB and \BmoinsA)}
\if{\AdiffB=}{\text{AdiffB=\name_empty}}

% Enoncé

\statement{\name_statement1
<div class="wimscenter">
\(A=\{\A\}\) &nbsp; \name_and &nbsp; \(B=\{\B\}\).
</div>
\name_statement2 \(A\ \Delta\ B\).
<div class="spacer">
\(A\ \Delta\ B=)\embed{r1,20}
</div>
<div class="wims_instruction">\name_instruction</div>
}

% Analyse de la réponse

\answer{}{\AdiffB}{type=set}

#if defined TARGET_difference_symetrique_h
\hint{\name_hint}
#endif
