target=arbrepond1  arbrepond2 arbrepond3
\author{Cyrille, Douriez}
\email{cyrille.douriez@ac-amiens.fr}
\format{html}
#define TITLE Arbre pondéré

\real{p11=5*randint(4..9)/100}
\real{p11c=1-\p11}
\real{p12=5*randint(2..7)/100}
\real{p13=1-\p11-\p12}
\real{p21=5*randint(2..9)/100}
\real{p21c=1-\p21}
\real{p22=5*randint(5..8)/100}
\real{p22c=1-\p22}
\real{p23=1-\p21-\p22}
\real{p24=5*randint(6..9)/100}
\real{p24c=1-\p24}
\real{p25=5*randint(2..7)/100}
\real{p26=1-\p24-\p25}
\text{taille=300,300}
\text{font=large}
\text{fontn=medium}

#if defined TARGET_arbrepond1 
\title{TITLE 1}

\integer{xmax=12}
\integer{ymax=7}

\text{dessin=canvasdraw(\taille
xrange -1,\xmax
yrange 0,\ymax
linewidth 2
segment 0,3.5,4,2,black
segment 0,3.5,4,5,black
text black , 5,5,\font,A
text black , 5,2,\font,B
segment 6,2,10,1,black
segment 6,2,10,3,black
text black ,11,3,\font,C
text black , 11,1,\font,D
segment 6,5,10,4,black
segment 6,5,10,6,black
text black ,11,6,\font,C
text black , 11,4,\font,D
text black ,2,4.7,\fontn,\p11
text black ,2,2.75,\fontn,\p11c
text black ,8,5.8,\fontn,\p21
text black ,8,4.5,\fontn,\p21c
text black ,8,2.8,\fontn,\p22
text black ,8,1.5,\fontn,\p22c
)}

\matrix{let=A,B
C,D}##matrice des lettres de l'arbre##
\matrix{proba=\p11,\p11c
\p21,\p21c,\p22,\p22c}##matrice des probas de l'arbre##
\integer{ch1=randint(1,2)}##Choix première lettre intersection##
\integer{ch2=randint(1,2)}##Choix deuxième lettre intersection##
\integer{ch3=randint(1,2)}##Choix lettre question 2##
\integer{pos=\ch2+2*(\ch1-1)}##rang proba conditionnelle voulue dans 2ème ligne de proba##
\real{rep2=\p11*\proba[2;\ch3]+\p11c*\proba[2;\ch3+2]}
\text{let3=\let[2;\ch3]}
\text{corrigeq2=\(p(\let3)=p(A)\times p_{A}(\let3)+p(B)\times p_{B}(\let3)=\p11\times\proba[2;\ch3]+\p11c\times\proba[2;\ch3+2]=\rep2)}
\text{probarbre=\(p(A)=\p11\), \(p(B)=p(\overline{A})=\p11c\), \(p_{A}(C)=\p21\), \(p_{A}(D)=\p21c\), \(p_{B}(C)=\p22\) et \(p_{B}(D)=\p22c\)}
#endif

#if defined TARGET_arbrepond2
\title{TITLE 2}

\integer{xmax=12}
\integer{ymax=11}

\text{dessin=canvasdraw(\taille
xrange -1,\xmax
yrange 0,\ymax
linewidth 2
segment 0,5.5,4,3,black
segment 0,5.5,4,8,black
text black , 5,8,\font,A
text black , 5,3,\font,B
segment 6,3,10,1,black
segment 6,3,10,3,black
segment 6,3,10,5,black
text black ,11,5,\font,C
text black , 11,3,\font,D
text black , 11,1,\font,E
segment 6,8,10,6,black
segment 6,8,10,8,black
segment 6,8,10,10,black
text black ,11,10,\font,C
text black , 11,8,\font,D
text black , 11,6,\font,E
text black ,2,7.4,\fontn,\p11
text black ,2,4.25,\fontn,\p11c
text black ,8,9.5,\fontn,\p21
text black ,8,8.2,\fontn,\p22
text black ,8,7,\fontn,\p23
text black ,8,4.5,\fontn,\p24
text black ,8,3.2,\fontn,\p25
text black ,8,2,\fontn,\p26
)}

\matrix{let=A,B
C,D,E}
\matrix{proba=\p11,\p11c
\p21,\p22,\p23,\p24,\p25,\p26}
\integer{ch1=randint(1,2)}
\integer{ch2=randint(1..3)}
\integer{ch3=randint(1..3)}
\integer{pos=\ch2+3*(\ch1-1)}
\real{rep2=\p11*\proba[2;\ch3]+\p11c*\proba[2;\ch3+3]}
\text{let3=\let[2;\ch3]}
\text{corrigeq2=\(p(\let3)=p(A)\times p_{A}(\let3)+p(B)\times p_{B}(\let3)=\p11\times\proba[2;\ch3]+\p11c\times\proba[2;\ch3+3]=\rep2)}
\text{probarbre=\(p(A)=\p11\), \(p(B)=p(\overline{A})=\p11c\), \(p_{A}(C)=\p21\), \(p_{A}(D)=\p22\), \(p_{A}(E)=\p23\), \(p_{B}(C)=\p24\), \(p_{B}(D)=\p24\) et \(p_{B}(E)=\p26\)}

#endif

#if defined TARGET_arbrepond3
\title{TITLE 3}

\integer{xmax=12}
\integer{ymax=10}

\text{dessin=canvasdraw(\taille
xrange -1,\xmax
yrange 0,\ymax
linewidth 2
segment 0,5,4,2,black
segment 0,5,4,5,black
segment 0,5,4,8,black
text black , 5,8,\font,A
text black , 5,5,\font,B
text black , 5,2,\font,C
segment 6,8,10,7,black
segment 6,8,10,9,black
text black ,11,9,\font,D
text black , 11,7,\font,E
segment 6,5,10,4,black
segment 6,5,10,6,black
text black ,11,6,\font,D
text black , 11,4,\font,E
segment 6,2,10,3,black
segment 6,2,10,1,black
text black ,11,3,\font,D
text black , 11,1,\font,E
text black ,2,7.3,\fontn,\p11
text black ,2,5.2,\fontn,\p12
text black ,2,3.5,\fontn,\p13
text black ,8,9,\fontn,\p21
text black ,8,7.5,\fontn,\p21c
text black ,8,6,\fontn,\p22
text black ,8,4.5,\fontn,\p22c
text black ,8,3,\fontn,\p24
text black ,8,1.5,\fontn,\p24c
)}

\matrix{let=A,B,C
D,E}
\matrix{proba=\p11,\p12,\p13
\p21,\p21c,\p22,\p22c,\p24,\p24c}
\integer{ch1=randint(1..3)}
\integer{ch2=randint(1,2)}
\integer{ch3=randint(1,2)}
\integer{pos=\ch2+2*(\ch1-1)}
\real{rep2=\p11*\proba[2;\ch3]+\p12*\proba[2;\ch3+2]+\p13*\proba[2;\ch3+4]}
\text{let3=\let[2;\ch3]}
\text{corrigeq2=\(p(\let3)=p(A)\times p_{A}(\let3)+p(B)\times p_{B}(\let3)+p(C) \times p_{C}(\let3)=\p11\times\proba[2;\ch3]+\p12\times\proba[2;\ch3+2]+\p13\times\proba[2;\ch3+4]=\rep2)}
\text{probarbre=\(p(A)=\p11\), \(p(B)=\p12\), \(p(C)=\p13\), \(p_{A}(D)=\p21\), \(p_{A}(E)=\p21c\), \(p_{B}(D)=\p22\), \(p_{B}(E)=\p22c\), \(p_{C}(D)=\p24\) et \(p_{C}(E)=\p24c\)}
#endif

\text{let1=\let[1;\ch1]}
\text{let2=\let[2;\ch2]}
\real{rep1=\proba[1;\ch1]*\proba[2;\pos]}
\text{lettres=\let[1;],\let[2;]}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col"> \dessin</div>
  <div class="medium_size text_col">L'arbre ci-contre décrit une probabilité \(p) sur un univers \({\Omega}\). <br>On considère les événements\(\lettres\).<br>
 <div class="wims_question">Calculer les probabilités suivantes.
<br> \(p(\let1 \cap \let2)=\)\embed{r1,5} 
<br>\(p(\let3)=\)\embed{r2,5}</div>
 
 
</div>
 }

\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}

\solution{L'arbre nous donne les probabilités suivantes : \probarbre.<br>\(p(\let1 \cap \let2)=p(\let1)\times p_{\let1}(\let2)=\proba[1;\ch1] \times \proba[2;\pos]=\rep1\).<br>
\corrigeq2.
}
