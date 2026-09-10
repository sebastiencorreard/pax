target=operations_combinees1

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

% Création des ensembles A, B et C

\text{nA=randint(3..7)}
\text{l=shuffle(\l)}
\text{A=\l[1..\nA]}
\text{nB=randint(3..7)}
\text{l=shuffle(\l)}
\text{B=\l[1..\nB]}
\text{nC=randint(3..7)}
\text{l=shuffle(\l)}
\text{C=\l[1..\nC]}

% Calcul de l'opération sur A, B et C (choisie parmi 4 cas différents)

\text{cas=randint(1..4)}
\if{\cas=1}{
\text{exprD=(A \cap  B ) \cup C}
\text{AinterB=wims(listintersect \A and \B)}
\text{D=wims(listunion \AinterB and \C)}
}
\if{\cas=2}{
\text{exprD= (A \cup  B ) \cap C}
\text{AunionB=wims(listunion \A and \B)}
\text{D=wims(listintersect \AunionB and \C)}
}
\if{\cas=3}{
\text{exprD=A \cap  (B  \cup C)}
\text{BunionC=wims(listunion \B and \C)}
\text{D=wims(listintersect \BunionC and \A)}
}
\if{\cas=4}{
\text{exprD= A \cup (B  \cap C)}
\text{BinterC=wims(listintersect \B and \C)}
\text{D=wims(listunion \BinterC and \A)}
}

#include "lang.inc"

\if{\D=}{\text{D=\name_empty}}

% Enoncé

\statement{\name_statement1
<div class="wimscenter">
\(A=\{\A\}\), &nbsp; \(B=\{\B\}\) &nbsp; \name_and &nbsp; \(C=\{\C\}\).
</div>
\name_statement2 \(\exprD\).
<div class="spacer">
\(\exprD=\)\embed{r1,20}
</div>
<div class="wims_instruction">\name_instruction</div>
}

% Analyse de la réponse

\answer{}{\D}{type=set}
