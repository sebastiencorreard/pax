target=mult1 mult2 mult3 mult4 mult5
\author{Cyrille, Douriez}
\email{cyrille.douriez@ac-amiens.fr}
\format{html}
\language{fr}
\range{-5..5}
\computeanswer{no}
\precision{100000000}
%%% MB
#include "avertissement.inc"
%%% Fin MB
#define TITLE Table de multiplication
#if defined TARGET_mult1 || defined TARGET_mult2 || defined TARGET_mult3
\observation{Suivant la configuration de l'exercice sur le module, il est possible d'exclure certaines tables.}
%%%% confparm1 : tables à exclure
\if{items(\confparm1)>0}
{%%%%%%%%% si on exclu 
\text{listel=2,3,4,5} %%% pour les lignes
\for{k=6 to 9}{
\text{listel=position(\k,\listel) issametext ? \listel:\listel,\k}
\text{listel=shuffle(\listel)} %%%%%% liste des tables à utiliser
}
\text{liste=item(1..3,\listel)} %%%%% liste des trois premiers
%%%% on complète la liste avec le autres entiers de 2 à 9
\text{listcomp=}
\for{k=2 to 9}{
\text{listecomp=position(\k,\liste) issametext ? wims(append item \k to \listcomp)}
}
\text{liste=\listel,\listecomp}
%%%%%% fin boucle si confparm1 saisi}
{\text{liste=shuffle(2,3,4,5,6,7,8,9)}}
#endif
#if defined TARGET_mult4 || defined TARGET_mult5
\text{liste=wims(shuffle -9,-8,-7,-6,-5,-4,-3,-2,2,3,4,5,6,7,8,9)}
#endif
\text{vl=wims(sort numeric list \liste[1..3])}##facteurs des lignes##
#if defined TARGET_mult4 || defined TARGET_mult5
\if{\vl[1]>0}{\integer{w=\vl[1]*(-1)}
\text{vl=\w,\vl[2],\vl[3]}
}##avoir au moins un entier négatif en ligne pour exercices avec relatifs##
#endif
\integer{place=randint(1..3)}
\text{vc=wims(sort numeric list \vl[\place],\liste[4..6])}##facteurs des colonnes##
#if defined TARGET_mult4 || defined TARGET_mult5
\if{\vc[1]>0}{\integer{w=\vc[1]*(-1)}
\text{vc=\w,\vc[2],\vc[3]}
}##avoir au moins un entier négatif en colonne pour exercices avec relatifs##
#endif
\text{val=}
\for{i=1 to 3}{
\for{j=1 to 3}{
\integer{v=\vl[\i]*\vc[\j]}
\text{val=\val,\v}##produits##
}}
\matrix{tableau=,\vc
\vl[1],\val[2..4]
\vl[2],\val[5..7]
\vl[3],\val[8..10]}

#if defined TARGET_mult1
\title{TITLE 1}
\text{listerep=r6,r7,r8,r10,r11,r12,r14,r15,r16}##les numéros des réponses à trouver##
\matrix{contenu=,1,1,1
1,0,0,0
1,0,0,0
1,0,0,0}##Cases remplies(1) ou à trouver (0) du tableau##
\text{indic=Chaque case intérieure du tableau est le produit des entiers contenus dans les cases situées en haut et à gauche.}
#endif
#if defined TARGET_mult2
\title{TITLE 2}
\text{listerep=r3,r5,r7,r8,r10,r12,r13,r15,r16}
\matrix{contenu=,1,0,1
0,1,0,0
1,0,1,0
0,1,0,0}
\text{indic=Chaque case intérieure du tableau est le produit des entiers contenus dans les cases situées en haut et à gauche.<br/>
Les entiers de la première colonne sont tous différents et ceux de la première ligne sont tous différents.}
#endif
#if defined TARGET_mult3
\title{TITLE 3}
\text{listerep=r2,r3,r4,r5,r7,r9,r10,r12,r13,r14}
\matrix{contenu=,0,0,0
0,1,0,1
0,0,1,0
0,0,1,1}
\text{indic=Chaque case intérieure du tableau est le produit des entiers (différents de 1) contenus dans les cases situées en haut et à gauche.<br/>
Les entiers de la première colonne sont tous différents et ceux de la première ligne sont tous différents.}
#endif
#if defined TARGET_mult4
\title{TITLE d'entiers relatifs 1}
\text{listerep=r6,r7,r8,r10,r11,r12,r14,r15,r16}##les numéros des réponses à trouver##
\matrix{contenu=,1,1,1
1,0,0,0
1,0,0,0
1,0,0,0}##Cases remplies(1) ou à trouver (0) du tableau##
\text{indic=Chaque case intérieure du tableau est le produit des entiers contenus dans les cases situées en haut et à gauche.}
#endif
#if defined TARGET_mult5
\title{TITLE d'entiers relatifs 2}
\text{listerep=r3,r5,r7,r8,r10,r12,r13,r15,r16}
\matrix{contenu=,1,0,1
0,1,0,0
1,0,1,0
0,1,0,0}
\text{indic=Chaque case intérieure du tableau est le produit des entiers (compris entre -9 et -2 ou entre 2 et 9) en gras contenus dans les cases situées en haut et à gauche.<br/>
Les entiers de la première colonne sont tous différents et ceux de la première ligne sont tous différents.}
#endif

\nextstep{\listerep}
%%% MB mise en forme des éléments de tableau par \(  )
\statement{Compléter le tableau de multiplication suivant sans utiliser de calculatrice.
<table class="wimscenter wimsborder">
<tr><th>\({}\times{})</th>
<th>\if{\contenu[1;2]=1}{\(\tableau[1;2])}{\embed{r2,3}}</th>
<th>\if{\contenu[1;3]=1}{\(\tableau[1;3])}{\embed{r3,3}}</th>
<th>\if{\contenu[1;4]=1}{\(\tableau[1;4])}{\embed{r4,3}}</th>
</tr>
<tr><th>\if{\contenu[2;1]=1}{\(\tableau[2;1])}{\embed{r5,3}}</th>
<td>\if{\contenu[2;2]=1}{\(\tableau[2;2])}{\embed{r6,3}}</td>
<td>\if{\contenu[2;3]=1}{\(\tableau[2;3])}{\embed{r7,3}}</td>
<td>\if{\contenu[2;4]=1}{\(\tableau[2;4])}{\embed{r8,3}}</td>
</tr>
<tr><th>\if{\contenu[3;1]=1}{\(\tableau[3;1])}{\embed{r9,3}}</th>
<td>\if{\contenu[3;2]=1}{\(\tableau[3;2])}{\embed{r10,3}}</td>
<td>\if{\contenu[3;3]=1}{\(\tableau[3;3])}{\embed{r11,3}}</td>
<td>\if{\contenu[3;4]=1}{\(\tableau[3;4])}{\embed{r12,3}}</td>
</tr>
<tr><th>\if{\contenu[4;1]=1}{\(\tableau[4;1])}{\embed{r13,3}}</th>
<td>\if{\contenu[4;2]=1}{\(\tableau[4;2])}{\embed{r14,3}}</td>
<td>\if{\contenu[4;3]=1}{\(\tableau[4;3])}{\embed{r15,3}}</td>
<td>\if{\contenu[4;4]=1}{\(\tableau[4;4])}{\embed{r16,3}}</td></tr>
</table>
\avertissement
}
\hint{\indic}

\answer{}{0}{type=numexp}{option=comma}
\answer{}{\tableau[1;2]}{type=numexp}{option=comma}
\answer{}{\tableau[1;3]}{type=numexp}{option=comma}
\answer{}{\tableau[1;4]}{type=numexp}{option=comma}
\answer{}{\tableau[2;1]}{type=numexp}{option=comma}
\answer{}{\tableau[2;2]}{type=numexp}{option=comma}
\answer{}{\tableau[2;3]}{type=numexp}{option=comma}
\answer{}{\tableau[2;4]}{type=numexp}{option=comma}
\answer{}{\tableau[3;1]}{type=numexp}{option=comma}
\answer{}{\tableau[3;2]}{type=numexp}{option=comma}
\answer{}{\tableau[3;3]}{type=numexp}{option=comma}
\answer{}{\tableau[3;4]}{type=numexp}{option=comma}
\answer{}{\tableau[4;1]}{type=numexp}{option=comma}
\answer{}{\tableau[4;2]}{type=numexp}{option=comma}
\answer{}{\tableau[4;3]}{type=numexp}{option=comma}
\answer{}{\tableau[4;4]}{type=numexp}{option=comma}

\solution{Voici le tableau complet:
<table class="wimscenter wimsborder">
<tr><th>\({}\times{})</th><th>\(\tableau[1;2])</th><th>\(\tableau[1;3])</th><th>\(\tableau[1;4])</th></tr>
<tr><th>\(\tableau[2;1])</th><td>\(\tableau[2;2])</td><td>\(\tableau[2;3])</td><td>\(\tableau[2;4])</td></tr>
<tr><th>\(\tableau[3;1])</th><td>\(\tableau[3;2])</td><td>\(\tableau[3;3])</td><td>\(\tableau[3;4])</td></tr>
<tr><th>\(\tableau[4;1])</th><td>\(\tableau[4;2])</td><td>\(\tableau[4;3])</td><td>\(\tableau[4;4])</td></tr>
</table>}
