target=produit_cartesien3

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}
\title_es{TITLE_es}


% Choix du type d'ensemble (nombres, lettres ou aléatoire) en fontion du paramètre de configuration.

\text{nombres=0,1,2,3,4}
\text{lettres=a,b,c,d,e}
\if{\confparm1=1}{\text{l=\nombres}}
\if{\confparm1=2}{\text{l=\lettres}}
\if{(\confparm1=3) or (\confparm1=)}{\if{randint(1,2)=1}{\text{l=\nombres}}{\text{l=\lettres}}}

% Création des ensembles A, B et C

\text{ltaille=1,2,2;1,2,3;2,2,2;1,3,3} % tailles possibles pour les ensembles
\text{i=randint(1..4)}
\text{taille=shuffle(\ltaille[\i;])}
\text{nA=\taille[1]}
\text{nB=\taille[2]}
\text{nC=\taille[3]}
\text{l=shuffle(\l)}
\text{A=\l[1..\nA]}
\text{l=shuffle(\l)}
\text{B=\l[1..\nB]}
\text{l=shuffle(\l)}
\text{C=\l[1..\nC]}

% Choix du produit cartésien demandé (AxBxC, BxAxC, etc.)

\text{s=shuffle(3)}
\text{lens=A,B,C}
\text{fprod=\lens[\s[1]] \times \lens[\s[2]]\times \lens[\s[3]]}

% Calcul du produit cartésien

\text{prod=}
\for{i=1 to \nA}{
	\for{j=1 to \nB}{
		\for{k=1 to \nC}{
			\text{lval=\A[\i],\B[\j],\C[\k]}
			\text{triplet=(\lval[\s[1]],\lval[\s[2]],\lval[\s[3]])}
			\text{prod=wims(append item \triplet to \prod)}
		}		
	}
}

% Enoncé



#include "lang.inc"

\statement{\name_statement1
<div class="wimscenter">
\(A=\{\A\}\), &nbsp; \(B=\{\B\}\) &nbsp; \name_and &nbsp; \(C=\{\C\}\).
</div>
\name_statement2 \(\fprod\).
<div class="spacer">
\(\fprod=\)\embed{r1,50}
</div>
<div class="wims_instruction">
\name_instruction
</div>
}

% Analyse des réponses

\answer{}{\prod}{type=set}
