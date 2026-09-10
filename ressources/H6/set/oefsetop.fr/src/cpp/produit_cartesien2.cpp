target=produit_cartesien2

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

\text{taille=2,2;2,3;3,3;3,4;1,4;2,4} % tailles possibles pour les ensembles A et B
\text{i=randint(1..6)}
\text{tailleAB=shuffle(\taille[\i;])}
\text{nA=\tailleAB[1]}
\text{nB=\tailleAB[2]}
\text{l=shuffle(\l)}
\text{A=\l[1..\nA]}
\text{l=shuffle(\l)}
\text{B=\l[1..\nB]}

% Calcul du produit cartésien
% L'ordre d'énumération des couples n'est pas toujours le même pour introduire plus de variété dans l'énoncé.

\text{AcroixB=}
\if{randitem(1,2)=1}{
\for{i=1 to \nA}{
	\for{j=1 to \nB}{
		\text{couple=(\A[\i],\B[\j])}
		\text{AcroixB=wims(append item \couple to \AcroixB)}
	}
}
}{
\for{j=1 to \nB}{
	\for{i=1 to \nA}{
		\text{couple=(\A[\i],\B[\j])}
		\text{AcroixB=wims(append item \couple to \AcroixB)}
	}
}
}


% Enoncé

#include "lang.inc"

\statement{\name_statement1
<div class="wimscenter">
\(E=\{\AcroixB\}\).
</div>
\name_statement3
<div class="spacer">
\(E =\)\embed{r1,8}\({\times}\)\embed{r2,8}
</div>
}

% Analyse des réponses

\answer{}{\A}{type=set}
\answer{}{\B}{type=set}
