target=add1 add2 substract1 substract2
\author{Cyrille, Douriez}
\email{cyrille.douriez@ac-amiens.fr}
\format{html}
\language{fr}
\range{-5..5}
\computeanswer{no}
\precision{100000000}

#include "avertissement.inc"


\text{liste=wims(shuffle -1,-2,-3,-4,-5,-6,-7,-8,-9,1,2,3,4,5,6,7,8,9)}
\text{vl=wims(sort numeric list \liste[1..3])}##facteurs des lignes##
\integer{place=randint(1..3)}
\text{vc=wims(sort numeric list \vl[\place],\liste[4..5])}##facteurs des colonnes##

\if{\vl[1]>0}{\integer{w=\vl[1]*(-1)}
\text{vl=\w,\vl[2],\vl[3]}
}##avoir au moins un entier négatif dans une ligne##
\if{\vc[1]>0}{\integer{w=\vc[1]*(-1)}
\text{vc=\w,\vc[2],\vc[3]}
}##avoir au moins un entier négatif dans une colonne##

#if defined TARGET_add1 || defined TARGET_add2
#define TITLE Table d'addition d'entiers relatifs
\text{voca=somme des}
\text{operations=additions}
\text{operation=d'addition}
\text{symbole=+}
\text{val=}
\for{i=1 to 3}{
\for{j=1 to 3}{
\integer{v=\vl[\i]+\vc[\j]}
\text{val=\val,\v}##sommes##
}}
\text{indic=Chaque case intérieure du tableau est la \voca entiers en gras contenus dans les cases situées à gauche et en haut.}
#endif
#if defined TARGET_substract1 || defined TARGET_substract2
#define TITLE Table de soustraction d'entiers relatifs
\text{voca=différence entre les}
\text{operations=soustractions}
\text{operation=de soustraction}
\text{symbole=-}
\text{val=}
\for{i=1 to 3}{
\for{j=1 to 3}{
\integer{v=\vl[\i]-\vc[\j]}
\text{val=\val,\v}##différences##
}}
\text{Cpltenonce=Chaque entier dans le tableau est la différence entre l'entier situé à gauche (dans la première colonne) et l'entier situé au dessus (dans la première ligne).}
\text{indic=Chaque case intérieure du tableau est la \voca entiers en gras contenus dans les cases situées à gauche (premier nombre) et en haut.}
#endif

\matrix{tableau=,\vc
\vl[1],\val[2..4]
\vl[2],\val[5..7]
\vl[3],\val[8..10]}

#if defined TARGET_add1 || defined TARGET_substract1
\title{TITLE 1}
\text{listerep=r6,r7,r8,r10,r11,r12,r14,r15,r16}##les numéros des réponses à trouver##
\matrix{contenu=,1,1,1
1,0,0,0
1,0,0,0
1,0,0,0}##Cases remplies(1) ou à trouver (0) du tableau##
\text{enonce=Compléter la table \operation suivante sans utiliser de calculatrice.}
#endif
#if defined TARGET_add2 || defined TARGET_substract2
\title{TITLE 2}
\text{listerep=r3,r5,r7,r8,r10,r12,r13,r15,r16}
\matrix{contenu=,1,0,1
0,1,0,0
1,0,1,0
0,1,0,0}
\text{enonce=Compléter la table \operation suivante sans utiliser de calculatrice.}
#endif

\nextstep{\listerep}
\statement{\enonce <p>\Cpltenonce</p>
<table class="wimscenter wimsborder">
<tr><th>\({}\symbole{})</th>
<th>\if{\contenu[1;2]=1}{\(\tableau[1;2])}{\embed{r2,3}}</th>
<th>\if{\contenu[1;3]=1}{\(\tableau[1;3])}{\embed{r3,3}}</th>
<th>\if{\contenu[1;4]=1}{\(\tableau[1;4])}{\embed{r4,3}}</th>
</tr>
<tr>
<th>\if{\contenu[2;1]=1}{\(\tableau[2;1])}{\embed{r5,3}}</th>
<td>\if{\contenu[2;2]=1}{\(\tableau[2;2])}{\embed{r6,3}}</td>
<td>\if{\contenu[2;3]=1}{\(\tableau[2;3])}{\embed{r7,3}}</td>
<td>\if{\contenu[2;4]=1}{\(\tableau[2;4])}{\embed{r8,3}}</td>
</tr>
<tr>
<th>\if{\contenu[3;1]=1}{\(\tableau[3;1])}{\embed{r9,3}}</th>
<td>\if{\contenu[3;2]=1}{\(\tableau[3;2])}{\embed{r10,3}}</td>
<td>\if{\contenu[3;3]=1}{\(\tableau[3;3])}{\embed{r11,3}}</td>
<td>\if{\contenu[3;4]=1}{\(\tableau[3;4])}{\embed{r12,3}}</td>
</tr>
<tr><th>\if{\contenu[4;1]=1}{\(\tableau[4;1])}{\embed{r13,3}}</th>
<td>\if{\contenu[4;2]=1}{\(\tableau[4;2])}{\embed{r14,3}}</td>
<td>\if{\contenu[4;3]=1}{\(\tableau[4;3])}{\embed{r15,3}}</td>
<td>\if{\contenu[4;4]=1}{\(\tableau[4;4])}{\embed{r16,3}}</td>
</tr>
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
<tr><th>\({}\symbole{})</th><th>\(\tableau[1;2])</th><th>\(\tableau[1;3])</th><th>\(\tableau[1;4])</th></tr>
<tr><th>\(\tableau[2;1])</th><td>\(\tableau[2;2])</td><td>\(\tableau[2;3])</td><td>\(\tableau[2;4])</td></tr>
<tr><th>\(\tableau[3;1])</th><td>\(\tableau[3;2])</td><td>\(\tableau[3;3])</td><td>\(\tableau[3;4])</td></tr>
<tr><th>\(\tableau[4;1])</th><td>\(\tableau[4;2])</td><td>\(\tableau[4;3])</td><td>\(\tableau[4;4])</td></tr>
</table>}
