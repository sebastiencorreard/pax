target=somme1 somme2 somme3 somme4 somme5
#define TITRE Déterminer la mesure d'un angle

\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}

\text{l=shuffle(A,B,C,D,E,F,G,H)}
\text{A=\l[1]}
\text{B=\l[2]}
\text{C=\l[3]}
\text{triname=randitem(\A\B\C,\A\C\B,\B\A\C,\B\C\A,\C\A\B,\C\B\A)}

#if defined TARGET_somme1
\title{TITRE 1}
 \text{prop=équilatéral}
 \text{rep=60}
 \text{ang=randitem(\A,\B,\C)}
#endif

#if defined TARGET_somme2
\title{TITRE 2}
 \text{prop=isocèle rectangle en \A}
 \text{rep=45}
 \text{ang=randitem(\B,\C)}
#endif

#if defined TARGET_somme3
\title{TITRE 3}
 \integer{a=randint(25..65)}
 \integer{rep=90-\a}
 \text{prop=rectangle en \A. L'angle \(\widehat{\B}) mesure \a degrés}
 \text{ang=\C}
#endif

#if defined TARGET_somme4
\title{TITRE 4}
 \integer{rep=randint(15..40)}
 \integer{a=180-2*\rep}
 \text{prop=isocèle en \A. L'angle \(\widehat{\A}) mesure \a degrés}
 \text{ang=randitem(\B,\C)}
#endif

#if defined TARGET_somme5
\title{TITRE 5}
 \integer{a=randint(15..40)}
 \integer{rep=180-2*\a}
 \text{prop=isocèle en \A. L'angle \(\widehat{\B}) mesure \a degrés}
 \text{ang=\A}
#endif

\statement{
Le triangle \triname est \prop.<p>
Quelle est la mesure, en degrés, de l'angle \(\widehat{\ang}) ?
</p>
<b>Votre réponse :</b>
\embed{r1,5} degrés.}

\answer{}{\rep}{type=numexp}
