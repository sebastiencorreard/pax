target=deduction1 deduction2 deduction3 deduction4 deduction5
#define TITRE Raisonnement en géométrie
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\computeanswer{no}

#if defined TARGET_deduction1
\title{TITRE 1}
\integer{k=randint(1,2)}
\if{\k=1}
{
\text{lstrep=On construit le symétrique \(A') de \(A) par rapport à \((d)),
\(X) est le point d'intersection de \((A'B)) et de \((d)),
On construit le symétrique \(B') de \(B) par rapport à \((d)),
\(X) est le point d'intersection de \((A B')) et de \((d)),
On projette \(A) en \(A1) et \(B) en \(B1) sur \((d)),
\(X) est le milieu de \([A_1B_1]),
On construit la médiatrice \(\Delta) de \([A B]),
\(X) est le point d'intersection de \(\Delta) et \((d))
}
}
{
\text{lstrep=On construit le symétrique \(U') de \(U) par rapport à \((B C)),
\(X) est le point d'intersection de \((U'V)) et de \((B C)),
On construit le symétrique \(V') de \(V) par rapport à \((B C)),
\(X) est le point d'intersection de \((U V')) et de \((B C)),
On construit le cercle \(\mathcal{C}) de diamètre \([U V]),
\(X) est le point d'intersection de \(\mathcal{C}) et de \((B C)),
On construit le point d'intersection \(H) de \((B V)) et de \((C U)),
\(X) est le projeté sur \((B C)) de \(H),
On construit la médiatrice \(\Delta) de \([U V]),
\(X) est le point d'intersection de \(\Delta) et \((B C)),
On trace la perpendiculaire \(\delta) à \((U V)),
\(X) est le point d'intersection de \(\delta) et \((B C))
}
}
\text{size=350x100x1}
\statement{
\if{\k=1}{
\(A) et \(B) sont deux points dans un demi plan limité par une droite \((d)).
Construisez, à l'aide des phrases ci-dessous, un raisonnement
 permettant de placer sur \((d)), un point \(X), tel que le chemin \(A X B),
composé de deux segments de droites, ait la longueur totale la plus petite possible.
}{
Un billard a la forme d'un rectangle \(A B C D).
Une boule est placée en un point \(U) de \([A B]) et on doit
 atteindre un point \(V) de \([C D]) en rebondissant sur
 le côté \([B C]) en un point \(X).<p>
Construisez, à l'aide des phrases ci-dessous, un raisonnement
 permettant de placer sur \([B C]) ce point \(X).</p>}
 <br class="clearall">
<ol>
<li>\embed{reply1,\size}</li>
<li>\embed{reply2,\size}</li>
</ol>
}
\answer{}{\rep1;\lstrep}{type=clickfill}
\answer{}{\rep2;\lstrep}{type=clickfill}
\condition{raisonnement}{(\rep1 issametext \lstrep[1] and \rep2 issametext \lstrep[2]) or (\rep1 issametext \lstrep[3] and \rep2 issametext \lstrep[4])}
#endif
#if defined TARGET_deduction2
\title{TITRE 2}
\text{lstrep=\((A Z)) est la médiatrice de \([O_1O_2]),
et \([O_1O_2]) est la médiatrice de \([A Z]).,
\(O_1A O_2Z) est un parallélogramme,
de même que \(O_2B O_3Z) et \(O_3C O_1Z).,
\([O_1A]) est un segment parallèle et de même longueur que \([O_3B]),
de même \([O_2B]) est un segment parallèle et de même longueur que \([O_1C]).,
\([O_1B]) &#44; \([O_2C]) et \([O_3A]) ont même milieu que l'on note K.,
dans la symétrie de centre \(K) &#44; \(B) est l'image de \(O_1),
 \(C) est l'image de \(O_2) et \(A) est l'image de \(O_3).,
le cercle passant par \(A,B,C) est symétrique du cercle \((C_c)) et a pour rayon 1.,
}
\text{size=350x100x1}
\text{rep=\lstrep[1],\lstrep[2],\lstrep[3],\lstrep[4],\lstrep[5],\lstrep[6],\lstrep[7],\lstrep[8],\lstrep[9],\lstrep[10]}
\text{dessin=
xrange -5,15
yrange -13,7
circle 0,0,150,blue
circle 8,0,150,blue
circle 1,-7,150,blue
circle 1,-1,150,red
linewidth 5
points black,4,3,4,-3,-3,-4,5,-4,0,0,8,0,1,-7
text black,4,3.8,medium,A
text black,4,-2.2,medium,Z
text black,-3.7,-4,medium,C
text black,5.3,-4,medium,B
text black,-0.5,0,medium,O1
text black,8.2,0,medium,O2
text black,1.2,-7,medium,O3

}
\statement{<div class="float_right">\draw{300,300}{\dessin}</div>
On considère trois cercles de rayon 1 ayant un point commun \(Z) à eux trois et trois points communs \(A,B,C) deux à deux.
On note \(O1),\(O2) et \(O3) les centres de ces trois cercles, et \((C_c)) le cercle passant par \(O_1,O_2) et \(O_3). Ce cercle n'est pas dessiné sur la figure.
<span style="color:red">Comme \(O_1Z=O_2Z=O_3Z=1), le cercle \((C_c)) a pour rayon 1 et pour centre \(Z).</span>
<p>
Il faut prouver que le cercle rouge passant par \(A,B,C) est également de rayon 1.
</p>
Pour cela, vous devez mettre en ordre les différents arguments.
<br class="clearall">
<ul class="wims_nopuce">
<li>\embed{reply1,\size} \embed{reply2,\size}</li>
<li><span style="color:red">Donc</span>\embed{reply3,\size} \embed{reply4,\size}</li>
<li><span style="color:red">Donc</span>\embed{reply5,\size} \embed{reply6,\size}</li>
<li><span style="color:red">Donc</span>\embed{reply7,\size}</li>
<li><span style="color:red">Donc</span> \embed{reply8,\size} \embed{reply9,\size}</li>
<li><span style="color:red">Donc</span> \embed{reply10,\size}
</li></ul>}

\answer{raisonnement}{\rep[1];}{type=dragfill}
\answer{raisonnement}{\rep[2];}{type=dragfill}
\answer{raisonnement}{\rep[3];}{type=dragfill}
\answer{raisonnement}{\rep[4];}{type=dragfill}
\answer{raisonnement}{\rep[5];}{type=dragfill}
\answer{raisonnement}{\rep[6];}{type=dragfill}
\answer{raisonnement}{\rep[7];}{type=dragfill}
\answer{raisonnement}{\rep[8];}{type=dragfill}
\answer{raisonnement}{\rep[9];}{type=dragfill}
\answer{raisonnement}{\rep[10];}{type=dragfill}
#endif
#if defined TARGET_deduction3
\title{TITRE 3}
\integer{k=randint(1,2)}
\if{\k=1}
{
\text{intro=Soit un parallélogramme \(A B D C),\(I) et \(J) les milieux respectifs
des segments \([B D]) et \([C A]).<p>
\((B J)) et \((C I)) coupent \((D A)) en \(U) et \(V).</p>
Montrez que \(A U=U V=V D)}
\text{dessin=
xrange -2,8
yrange -2,8
poly black,1,0,6,2,5,6,0,4
segment 0,4,3.5,1,blue
segment 2.5,5,6,2,blue
segment 1,0,5,6,red
text black,0.2,0,medium,A
text black,-0.8,4,medium,B
text black,6.5,2,medium,C
text black,5.5,6,medium,D
text black,3.5,0.6,medium,J
text black,2.5,5.7,medium,I
text black,2.3,2.8,medium,U
text black,3.5,3.8,medium,V

 }
\text{lstrep=Il découle des définitions que \(\overrightarrow{B I}=\overrightarrow{J C}),
\(B I C J) est un parallélogramme et donc \((B J)) est parallèle à \((I C)),
Par le théorème "de la droite des milieux" &#44; dans le triangle \(D B J) &#44; \(V) est le milieu de \([D U]),
Par le théorème "de la droite des milieux" &#44; dans le triangle \(A C V) &#44; \(U) est le milieu de \([A V]),
\(A U=U V) et \(U V=V D) &#44; donc les trois segments sont de même longueur.
}
\text{\size=400x100x1}

}
{
\text{intro=Soit \(A B C D) un trapèze, \(E) le point commun
des diagonales \((A C)) et \((B D)).
Par \(E) on mène la parallèle aux bases, elle coupe \((A D)) en \(M) et \((B C)) en \(N).
<p> Montrer que \(E) est le milieu de \([M N])}
\integer{xA=0}
\integer{yA=10}
\integer{xB=10}
\integer{yB=10}
\integer{xC=randint(5..14)}
\integer{yC=0}
\integer{xD=randint(-5..4)}
\integer{yD=0}
\rational{p1=(\yC-\yA)/(\xC-\xA)}
\rational{p2=(\yD-\yB)/(\xD-\xB)}
\rational{xE=(\p1*\xA-\p2*\xB+\yB-\yA)/(\p1-\p2)}
\rational{yE=\p1*\xE- \p1*\xA+\yA}
\rational{yM=\yE}
\rational{yN=\yE}
\rational{xM=\xA+(\yM-\yA)/(\yD-\yA)*(\xD-\xA)}
\rational{xN=\xB+(\yN-\yB)/(\yC-\yB)*(\xC-\xB)}
\text{dessin=
xrange -5,15
yrange -2,12
poly black,\xA,\yA,\xB,\yB,\xC,\yC,\xD,\yD
segment \xA,\yA,\xC,\yC,blue
segment \xB,\yB,\xD,\yD,blue
line \xM,\yE,\xN,\yE,red
text black,\xA,\yA+1,medium,A
text black,\xB,\yB+1,medium,B
text black,\xC,\yC-1,medium,C
text black,\xD,\yD-1,medium,D
text black,\xM-1,\yM,medium,M
text black,\xN+0.5,\yN,medium,N
text black,\xE,\yE+1,medium,E
}


\text{lstrep=Le théorème de Thalès pour les sécantes \((A D)) et \((A C)) et les parallèles \((M N)) et \((D C)) &#44; donne: \(\frac{A E}{A C}=\frac{M E}{D C}).,
Le théorème de Thalès pour les sécantes \((B D)) et \((B C)) et les parallèles \((M N)) et \((D C)) &#44; donne: \(\frac{E N}{D C}=\frac{B E}{B D}).,
Le théorème de Thalès pour les sécantes \((A C)) et \((B D)) et les parallèles \((A B)) et \((D C)) &#44; donne: \(\frac{E C}{A E}=\frac{E D}{B E}) &#44; soit \(\frac{A C}{A E}=\frac{B D}{B E}).,
Il suffit de considérer l'égalité des fractions inverses: \(\frac{A E}{A C}=\frac{B E}{B D}).,
Donc &#44; en considérant des égalités déjà acquises &#44; par transitivité on obtient \(\frac{M E}{D C}=\frac{E N}{D C}) soit \(M E=E N).
}
\text{\size=250x80x1}
}
\text{rep=\lstrep}
\statement{<div class="float_right">\draw{200,200}{\dessin}</div>
\intro en ordonnant les arguments ci-dessous.</p>
<br class="clearall">
<ul class="wims_nopuce"><li>
\embed{reply1,\size} \embed{reply2,\size} </li>
<li>\embed{reply3,\size} \embed{reply4,\size}</li>
<li>\embed{reply5,\size}</li></ul>
}
\if{\k=2}
 {
\integer{i1=position(\rep1,\lstrep)}
\integer{i2=position(\rep2,\lstrep)}
\integer{i3=position(\rep3,\lstrep)}
\integer{i4=position(\rep4,\lstrep)}
\text{indlst=\i1,\i2,\i3,\i4}
\integer{po3=position(3,\indlst)}
\integer{po4=position(4,\indlst)}
}
\answer{raisonnement}{\rep1;\lstrep}{type=clickfill}
\answer{raisonnement}{\rep2;\lstrep}{type=clickfill}
\answer{raisonnement}{\rep3;\lstrep}{type=clickfill}
\answer{raisonnement}{\rep4;\lstrep}{type=clickfill}
\answer{raisonnement}{\rep5;\lstrep}{type=clickfill}
\condition{raisonnement}{(\rep5 issametext \rep[5]) and ((\k=1 and (\rep1 issametext \rep[1]) and (\rep2 issametext \rep[2]) and ((\rep3 issametext \rep[3] and \rep4 issametext \rep[4]) or (\rep3 issametext \rep[4] and \rep4 issametext \rep[3]))) or (\k=2 and \po3 < \po4))}
\feedback{\k=2}{\rep5<br>\rep[5]<br> \po < \po4}
#endif
#if defined TARGET_deduction4
\title{TITRE 4}
\text{size=350x100x1}
\integer{k=randint(1,2)}
\text{dessin=
xrange -4,12
yrange -3,13
segment 0,-2,0,10,black
segment -2,9,12,2,black
text black,11,1,medium,d1
text black,-1,-1,medium,d2
text black,1,8.5,medium,S
linewidth 5
}
\if{\k=1}{
\integer{xP=randint(1..7)}
\text{dessin=\dessin
point \xP,\xP/2,black
text black,\xP,\xP/2+0.7,medium,P
}
\text{cond= \(P) soit le milieu de \([U V])}
\text{lstrep=On trace par \(P) la parallèle à \(d_1) qui coupe \(d_2) en Y&#44; et la parallèle à \(d_2) qui coupe \(d_1) en \(X).,
\(S X P Y) est un parallélogramme. Soit \(Z) le milieu de \([X Y]) &#44; la droite \((S P)) passe par \(Z).,
La parallèle à  \((X Y)) passant par \(P) coupe \(d_1) en \(U) et \(d_2) en \(V).,
D'après le théorème de Thalès appliqué aux sécantes \(d_1)&#44;\(d_2) et \((S P)) et aux parallèles \(X Y) et \((U V)) &#44; on a \(\frac{Z X}{P U}=\frac{S Z}{S P}=\frac{Z Y}{P V}).,
Comme \(Z X=Z Y)&#44; il vient \(P U=P V) et \(P) est le milieu de \([U V]).
}
}{
\integer{yP=randint(-1..7)}
\text{dessin=\dessin
point -2,\yP,black
text black,-2,\yP+0.7,medium,P
}
\text{cond=\(V) soit le milieu de \([P U])}
\text{lstrep=On trace la parallèle à \(d_1) passant par \(P) qui coupe \(d_2) en X.,
Soit \(V) le milieu de \([S X]).,
La droite \((V P)) coupe \(d_1) en \(U).,
D'après le théorème de Thalès appliqué aux sécantes \(d_2) et \((V P)) et aux parallèles \(d_1) et \((P X)) &#44; on a \(\frac{V P}{V U}=\frac{V X}{V S}).,
Comme \(V X=V S)&#44;  il vient \(V P=V U) et \(V) est le milieu de \([P U]).
}
 }
\text{rep=\lstrep}
\statement{<div class="float_right">\draw{200,200}{\dessin}</div>
Etant données deux droites \(d_1) et \(d_2) sécantes en \(S),
et un un point \(P) non situé sur ces droites, déterminez deux points
\(U) sur \(d_1) et \(V) sur \(d_2) tels que \cond.
<p>
Pour cela, ordonnez le raisonnement ci-dessous.
</p>
<br class="clearall">
<ul class="wims_nopuce"><li>\embed{reply1,\size} \embed{reply2,\size} </li>
<li>\embed{reply3,\size} \embed{reply4,\size} </li>
<li>\embed{reply5,\size} </li>
</ul>
}
\answer{raisonnement}{\rep[1];\lstrep}{type=clickfill}
\answer{raisonnement}{\rep2;\lstrep}{type=clickfill}
\answer{étape 3}{\rep3;\lstrep}{type=clickfill}
\answer{étape 4}{\rep[4];\lstrep}{type=clickfill}
\answer{étape 5}{\rep[5];\lstrep}{type=clickfill}
\condition{raisonnement}{(\rep2 issametext \rep[2] and \rep3 issametext \rep[3]) or (\k=1 and \rep2 issametext \rep[3] and \rep3 issametext \rep[2])}
#endif
#if defined TARGET_deduction5
\title{TITRE 5}
\integer{xD=randint(-4..-1)}
\integer{yD=randint(-3..4)}
\integer{xC=randint(5..14)}
\integer{yC=randint(-3..4)}
\integer{xP=4}
\integer{yP=10}
\integer{xP1=8}
\integer{yP1=10}
\rational{xQ1=\xD+(\xC-\xD)/3}
\rational{yQ1=\yD+(\yC-\yD)/3}
\rational{xQ=\xD+2*(\xC-\xD)/3}
\rational{yQ=\yD+2*(\yC-\yD)/3}
\rational{xR1=(\xD)/3}
\rational{yR1=10+(\yD-10)/3}
\rational{xR=2*(\xD)/3}
\rational{yR=10+2*(\yD-10)/3}
\rational{xS=12+(\xC-12)/3}
\rational{yS=10+(\yC-10)/3}
\rational{xS1=12+2*(\xC-12)/3}
\rational{yS1=10+2*(\yC-10)/3}
\rational{xX=\xR1+(\xS-\xR1)/3}
\rational{yX=\yR1+(\yS-\yR1)/3}
\rational{xY=\xR1+2*(\xS-\xR1)/3}
\rational{yY=\yR1+2*(\yS-\yR1)/3}
\rational{xZ=\xR+(\xS1-\xR)/3}
\rational{yZ=\yR+(\yS1-\yR)/3}
\rational{xT=\xR+2*(\xS1-\xR)/3}
\rational{yT=\yR+2*(\yS1-\yR)/3}

\text{dessin=
xrange -5,15
yrange -5,15
linewidth 2
poly black,0,10,12,10,\xC,\yC,\xD,\yD
segment \xP,\yP,\xQ1,\yQ1,blue
segment \xP1,\yP1,\xQ,\yQ,blue
segment \xR1,\yR1,\xS,\yS,blue
segment \xR,\yR,\xS1,\yS1,blue
segment \xP,\yP,\xR1,\yR1,red
segment \xS,\yS,\xQ1,\yQ1,red
text black,-0.8,10.5,medium,A
text black,12.8,10.5,medium,B
text black,\xC+0.5,\yC-0.8,medium,C
text black,\xD-0.8,\yD-0.8,medium,D

text blue,\xP-0.8,11,medium,P
text blue,\xP1-0.8,11,medium,P'
text blue,\xQ-0.8,\yQ-0.8,medium,Q
text blue,\xQ1-0.8,\yQ1-0.8,medium,Q'
text blue,\xR-1,\yR+0.5,medium,R
text blue,\xR1-1.5,\yR1+0.5,medium,R'
text blue,\xS+0.8,\yS+0.5,medium,S
text blue,\xS1+0.8,\yS1+0.5,medium,S'
text red,\xX-0.8,\yX+1,medium,X
text red,\xY-0.8,\yY+1,medium,Y
text red,\xZ-0.8,\yZ+1,medium,Z
text red,\xT-0.8,\yT+1,medium,T
linewidth 5
points black,\xP,\yP,\xP1,\yP1,\xR,\yR,\xR1,\yR1,\xQ,\yQ,\xQ1,\yQ1,\xS,\yS,\xS1,\yS1,\xX,\yX,\xY,\yY,\xZ,\yZ,\xT,\yT

}
\text{lstrep=On a \(\overrightarrow{P R'}=\frac{1}{3}\overrightarrow{B D}) et \(\overrightarrow{S Q'}=\frac{2}{3}\overrightarrow{B D}).,
Donc \(\overrightarrow{S Q'}=2\overrightarrow{P R'}).,
Le théorème de Thalès pour les sécantes \((P Q')) et \((S R')) et les parallèles \((P R')) et \((S Q')) donne \(X S= 2 X R') et \(X Q'=2 X P).,
On prouve de même que \(\overrightarrow{P S'}=2\overrightarrow{R Q'})&#44; donc que \(Z P= 2 Z Q') et que \(Z S'=2 Z R).,
Donc \(P X=X Z=Z Q').,
On prouve de la même manière que \(S Y=Y X=X R').,
Il en résulte que \(P Y Z R') est un parallélogramme &#44; donc \(\overrightarrow{Y Z}=\overrightarrow{P R'}).
}
\text{rep=\lstrep}
\text{size=350x100x1}
\statement{<div class="float_right">\draw{200,200}{\dessin}</div>
Les côtés d'un quadrilatère\(A B C D) sont divisés en trois parties égales.
On joint les points correspondants des côtés opposés.<p>
Montrez que \(\overrightarrow{Z Y}=\frac{1}{3}\overrightarrow{D B}) en ordonnant les arguments ci-dessous.
</p>
<br class="clearall">
<ul class="wims_nopuce"><li>\embed{reply1,\size} \embed{reply2,\size} \embed{reply3,\size}
</li><li>\embed{reply4,\size} \embed{reply5,\size} \embed{reply6,\size}
</li><li>\embed{reply7,\size}
</li></ul>
}
\answer{raisonnement}{\rep[1];\lstrep}{type=clickfill}
\answer{raisonnement}{\rep[2];\lstrep}{type=clickfill}
\answer{raisonnement}{\rep[3];\lstrep}{type=clickfill}
\answer{raisonnement}{\rep[4];\lstrep}{type=clickfill}
\answer{raisonnement}{\rep[5];\lstrep}{type=clickfill}
\answer{raisonnement}{\rep[6];\lstrep}{type=clickfill}
\answer{raisonnement}{\rep[7];\lstrep}{type=clickfill}
#endif
