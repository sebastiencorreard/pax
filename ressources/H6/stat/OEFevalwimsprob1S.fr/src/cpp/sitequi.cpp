target=sitequi1 sitequi2 sitequi3 sitequi4 sitequi5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}

#if defined TARGET_sitequi4
\title{Univers et équiprobabilité 4}
\integer{n=randint(4..6)}
\integer{a=randint(1..5)}
\integer{b=\a+randint(1..4)}
\integer{adix=randint(\a,\b)*10^(\n-1)}
\integer{tot=2^\n}
\rational{p1=1/2}
\text{U1=wims(makelist x for x=0 to \n)}
\statement{<p>
On compose au hasard (de manière équiprobable) un nombre de \n chiffres avec uniquement des \a et des \b.
</p><p>
Pour modéliser cette expérience, on considère les deux univers suivants :
</p><ol>
<li>\(U_1=\lbrace \U1 \rbrace\) qui donne le nombre de fois où le chiffre \a apparaît.</li>
<li>\(U_2\) : ensemble formé de tous les nombres différents obtenus.<br>
Combien l'univers \(U_2\) contient-il d'éléments ? \embed{reply1,5}
</li>
</ol>
Dans quel univers la loi de probabilité correspondant à l'expérience est-elle équirépartie ?
<div class="wimscenter"> \embed{reply2}</div>
}
\answer{Cardinal de \(U2)}{\tot}{type=numeric}
\answer{Univers équiprobable}{2;\(U_1),\(U_2)}{type=radio}
#endif

#if defined TARGET_sitequi5
\title{Univers et équiprobabilité 5}
\integer{n=randint(4..6)}
\integer{tot=\n^2}
\text{U1=wims(makelist x for x=1 to \n)}
\text{U2=}
\for{i=1 to \n}
 {
  \for{j=\i to \n}
    {
     \text{v=\i \; et \; \j}
     \text{U2=wims(append item \v to \U2)}
    }
  }
\statement{<p>
Deux urnes indiscernables contiennent chacune \n boules numérotées de 1 à \n.<br>
On tire au hasard (de manière équiprobable), simultanément, une boule dans chaque urne.
</p>
Pour modéliser cette expérience on considère les deux univers suivants :
<ol>
<li>\(U_1) l'ensemble de tous les couples formés avec \(\lbrace \U1 \rbrace\).
Combien l'univers \(U_1\) contient-il d'éléments ? \embed{reply1,5}
</li>
<li>\(U_2=\lbrace \U2 \rbrace\)<br>
</li>
</ol>
Dans quel univers la loi de probabilité correspondant à l'expérience est-elle équirépartie ?
<div class="wimscenter"> \embed{reply2}</div>
}
\answer{Cardinal de \(U1\)}{\tot}{type=numeric}
\answer{Univers équiprobable}{1;\(U_1\),\(U_2\)}{type=radio}
#endif

#if (defined TARGET_sitequi1 || defined TARGET_sitequi2 || defined TARGET_sitequi3)
#if defined TARGET_sitequi1
\title{Univers et équiprobabilité 1}
\integer{k=randint(1..4)}
integer{k=4}
\if{\k=1}
 {
 \text{intro=On lance un dé cubique bien équilibré.<br>
On s'intéresse à la sortie du numéro 6.}
 \text{tU1=\(U_1=\lbrace\) le 6 sort; le 6 ne sort pas \(\rbrace\)}
 \text{tU2=\(U_2= \lbrace 1;2;3;4;5;6 \rbrace\)}
 \integer{rep=2}
 }
\if{\k=2}
 {
 \text{intro=On tire au hasard (de manière équiprobable) simultanément deux boules d'une urne
 contenant deux boules rouges et deux boules noires.<br> On s'intéresse aux couleurs des boules
obtenues.}
 \text{tU1=\(U_1=\lbrace\) 2 rouges; 1 rouge et une noire; 2 noires \(\rbrace\)}
 \text{tU2=\(U_2= \lbrace N1N2;R1N1;R1N2;R2N1;R2N2;R1R2 \rbrace\) où on a numéroté N1 et N2 les deux boules noires et R1 et R2 les deux boules rouges}
 \integer{rep=2}
 }
\if{\k=3}
 {
 \text{intro=On lance deux fois une pièce équilibrée.<br> On s'intéresse aux faces
obtenues.<br>On note \(p) l'obtention de pile et \(f) celle de face.}
 \text{tU1=\(U_1 = \lbrace (p,p);(p,f);(f,p);(f,f)\rbrace\)}
 \text{tU2=\(U_2 = \lbrace 2p;2f;1p1f \rbrace\)}
 \integer{rep=1}
 }
\if{\k=4}
 {
 \text{intro=On répartit au hasard (de manière équiprobable) deux boules \(
 b1\) et \(b2\) dans deux boîtes \(A\) et \(B\).<br>
 On s'intéresse au nombre de boules présentes dans la boîte \(A\).}
 \text{tU1=\(U_1 = \lbrace\) 2 dans A; 2 dans B; \(b1\) dans A et \(b2\) dans B; \(b2\) dans A et \(b1\) dans B \(\rbrace\)}
 \text{tU2=\(U_2 = \lbrace 0;1;2 \rbrace\) }
 \text{rep=1}
 }

#endif


#if defined TARGET_sitequi2
\title{Univers et équiprobabilité 2}
\integer{k=randint(1..4)}
integer{k=4}
\if{\k=1}
 {
 \text{intro=On lance un dé tétraédrique bien équilibré dont les faces portent les
numéros 1;1;2;3.<br> On s'intéresse au numéro porté par la face cachée du dé.}
 \text{tU1=\(U_1 = \lbrace 1;2;3\rbrace\)}
 \text{tU2=\(U_2 = \lbrace 1a;1b;2;3 \rbrace) où on appelle \(a\) et \(b\) les faces qui portent le numéro 1}
 \integer{rep=2}
 }
\if{\k=2}
 {
 \text{intro=On tire au hasard (de manière équiprobable) une boule dans une urne contenant
une boule rouge et trois boules noires.<br> On s'intéresse à la couleur de
la boule obtenue.}
 \text{tU1=\(U_1 = \lbrace R;N \rbrace\)}
 \text{tU2=\(U_2 = \lbrace R;N1,N2;N3 \rbrace\) où on a numéroté N1,N2 et N3 les trois boules noires}
 \integer{rep=2}
 }
\if{\k=3}
 {
 \text{intro=On tire au hasard (de manière équiprobable) <b>successivement et avec remise</b>
deux boules d'une urne contenant
une boule rouge et deux boules noires.<br> On s'intéresse aux couleurs des boules
obtenues.}
 \text{tU1=\(U_1 = \lbrace (R,R);(R,N1);(N1,R);(R,N2);(N2,R);(N1,N1);(N1,N2);(N2,N1);(N2,N2)\rbrace\)}
 \text{tU2=\(U_2 = \lbrace\) R et R; R et N1; R et N2; N1 et N1; N1 et N2; N2 et N2\( \rbrace\)}
 \integer{rep=1}
 }
\if{\k=4}
 {
 \text{intro=On tire au hasard (de manière équiprobable) <b>successivement et sans remise</b>
deux boules d'une urne contenant
une boule rouge et trois boules noires.<br> On s'intéresse aux couleurs des boules
obtenues.}
 \text{tU1=\(U_1=\lbrace (R,N1);(N1,R);(R,N2);(N2,R);(R,N3);(N3,R);(N1,N2);(N2,N1);(N1,N3);(N3,N1);(N2,N3);(N3,N2)\rbrace\)}
 \text{tU2=\(U_2= \lbrace\) R et N1; R et N2; R et N3; N1 et N2; N1 et N3; N2 et N3\( \rbrace\)}
 \text{rep=1}
 }

#endif

#if defined TARGET_sitequi3
\title{Univers et équiprobabilité 3}
\integer{k=randint(1..4)}
integer{k=4}
\if{\k=1}
 {
 \text{intro=On choisit au hasard une famille de deux enfants.<br>
 On s'intéresse au sexe de chaque enfant (on suppose l'équiprobabilité des sexes).}
 \text{tU1=\(U_1=\lbrace 2F;2G;1F1G\rbrace\)}
 \text{tU2=\(U_2= \lbrace (F,F);(F,G);(G,F);(G,G) \rbrace\)}
 \integer{rep=2}
 }
\if{\k=2}
 {
 \text{intro=On lance deux dés cubiques bien équilibrés.<br>
 On s'intéresse aux numéros obtenus.}
 \text{tU1=\(U_1) l'ensemble qui contient les 6 doubles et les 15 paires formées avec \(\lbrace 1;2;3.4;5;6 \rbrace\)}
 \text{tU2=\(U_2) l'ensemble des 36 couples formés avec les éléments de \(\lbrace 1;2;3.4;5;6 \rbrace\)}
 \integer{rep=2}
 }
\if{\k=3}
 {
 \text{intro=On écrit les quatre lettres du prénom AZIZ sur quatre
cartons indiscernables que l'on place dans un sac. <br>
On tire au hasard (de manière équiprobable) <b>simultanément</b> deux cartes de ce sac.<br>
 On s'intéresse aux lettres obtenues.}
 \text{tU2=\(U_2=\lbrace\) Z1 et Z2; A et Z1; A et Z2; I et Z1; I et Z2; A et I\(\rbrace) en numérotant les deux lettres Z}
 \text{tU1=\(U_1= \lbrace\) Z et Z; A et Z; I et Z; A et I\(\rbrace)}
 \integer{rep=2}
 }
\if{\k=4}
 {
 \text{intro=On écrit les quatre lettres du prénom AZIZ sur quatre
cartons indiscernables que l'on place dans un sac. <br>
On tire au hasard (de manière équiprobable) <b>successivement et avec remise</b>
deux cartes de ce sac.<br>
 On s'intéresse aux lettres obtenues.}
 \text{tU2=\(U_2=\lbrace ZZ;AZ;ZA;IZ;ZI;AA;AI;IA;II\rbrace\)}
 \text{tU1=\(U_1= \lbrace Z1Z1;Z2Z2;Z1Z2;Z2Z1;AZ1;Z1A;IZ1;Z1I;AZ2;Z2A;IZ2;Z2I;AA;AI;IA;II\rbrace\)}
 \text{rep=1}
 }

#endif
 \statement{<p>
\intro</p>
Pour modéliser cette expérience on considère les deux univers suivants :
<ol>
<li> \tU1 </li>
<li> \tU2 </li>
</ol>


Dans quel univers la loi de probabilité correspondant à l'expérience est-elle équirépartie ?

<div class="wimscenter">\embed{reply1}</div>
}
\answer{Univers équiprobable}{\rep;\(U_1\),\(U_2\)}{type=radio}
#endif
