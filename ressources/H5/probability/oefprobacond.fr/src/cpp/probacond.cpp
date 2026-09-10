target=probacond1 probacond2 probacond3 probacond4 probacond5 probacond6
\author{Cyrille, Douriez}
\email{cyrille.douriez@ac-amiens.fr}
\format{html}
#define TITLE Probabilités conditionnelles
\real{pA=randint(5..18)/20}
\real{pB=randint(4..16)/20}
\real{pBsA=randint(5..(100*\pA-5))/100}
\real{pAetB=\pBsA*\pA}
\real{pAouB=\pA+\pB-\pAetB}
\real{pAc=1-\pA}
\real{pBc=1-\pB}
\real{pAsB=\pAetB/\pB}
\real{pBsAc=randint(5..(100*(1-\pA)-5))/100}
\text{lettres=A,B}
\text{choixlettres=wims(shuffle 1,2)}
\text{A=\lettres[\choixlettres[1]]}
\text{B=\lettres[\choixlettres[2]]}
\text{preamb=On considère une probabilité \(p) sur un univers \({\Omega}) et deux événements \(A) et \(B).} 
\observation{Différents exercices sur l'utilisation de la formrule des probabilités conditionnelles :
<ul><li>Probabilités conditionnelles 1 : \(p(A)\) et \(p_A(B)\) donnés. Calculer \(p(A \cap B)\).</li>
<li>Probabilités conditionnelles 2 : \(p(A)\) et \(p(A \cap B)\) donnés. Calculer \(p_A(B)\).</li>
<li>Probabilités conditionnelles 3 : \(p(A)\), \(p(B)\) et \(p(A \cup B)\) donnés. Calculer \(p_A(B)\).</li>
<li>Probabilités conditionnelles 4 : \(p(A)\), \(p(B)\) et \(p_A(B)\) donnés. Calculer \(p_B(A)\).</li>
<li>Probabilités conditionnelles 5 : \(p(A)\), \(p_A(B)\) et \(p_{\overline{A}}(B)\) donnés. Calculer \(p(B)\).</li>
<li>Probabilités conditionnelles 6 : \(p(A)\), \(p(B)\) et \(p_A(B)\) donnés. Calculer \(p_{\overline{\A}}(\B)\)</li></ul>
}
#if defined TARGET_probacond1 
\title{TITLE 1}
\real{pBsA=randint(5..(100*\pA-5))/100}
\real{pAetB=\pBsA*\pA}
\statement{\preamb<br>
On donne \(p(\A)=\pA\) et \(p_\A(\B)=\pBsA\). 
<div class="wims_question">Calculer \(p(A\cap B)\). </div>
\(p(A\cap B)={}\)\embed{r1,10}.  }
\answer{\(p(A \cap B)\)}{\pAetB}{type=numeric}
\solution{\(p(A\cap B)=p_\A(\B) \times p(\A)=\pBsA \times \pA=\pAetB\).}
#endif
#if defined TARGET_probacond2 
\title{TITLE 2}
\statement{\preamb<br>
On donne \(p(\A)=\pA\) et \(p(A\cap B)=\pAetB\). 
<div class="wims_question">Calculer \(p_\A(\B)\).</div> 
\(p_\A(\B)={}\)\embed{r1,10}. }
\answer{\(p_\A(\B)\)}{\pBsA}{type=numeric}
\solution{\(p_\A(\B)=\frac{p(A\cap B)}{p(\A)}=\frac{\pAetB}{\pA}=\pBsA\).}
#endif
#if defined TARGET_probacond3
\title{TITLE 3}
\integer{m=maxima(min(100*\pA,100*\pB))}
\real{pAetB2=randint(2..(\m-5))/100}
\statement{\preamb<br>
On donne \if{\choixlettres[1]==1}{\(p(\A)=\pA\), \(p(\B)=\pB\)}{\(p(\B)=\pB\), \(p(\A)=\pA\)} et \(p(A\cup B)=\pAouB\). 
<div class="wims_question">Calculer \(p_\A(\B)\).</div> 
\(p_\A(\B)={}\)\embed{r1,10}.}
\answer{\(p_\A(\B)\)}{\pBsA}{type=numeric}
\solution{\(p(A \cup B)=p(A)+p(B)-p(A \cap B)\) donc \(p(A\cap B)=-(p(A\cup B)-p(A)-p(B))=-(\pAouB-\pA-\pB)=\pAetB\). <br>
\(p_\A(\B)=\frac{p(A\cap B)}{p(\A)}=\frac{\pAetB}{\pA}=\pBsA\).}
#endif
#if defined TARGET_probacond4
\title{TITLE 4}
\statement{\preamb<br>
On donne \if{\choixlettres[1]==1}{\(p(\A)=\pA\), \(p(\B)=\pB\)}{\(p(\B)=\pB\), \(p(\A)=\pA\)} et \(p_\A(\B)=\pBsA\). 
<div class="wims_question">Calculer \(p_\B(\A)\).</div>
\(p_\B(\A)={}\)\embed{r1,10}.}
\answer{\(p_\B(\A)\)}{\pAsB}{type=numeric}
\solution{\(p(A \cap B)=p_\A(\B)\times p(\A)=\pBsA \times \pA=\pAetB\). \(p_\B(\A)=\frac{p(A \cap B)}{p(\B)}=\frac{\pAetB}{\pB}=\pAsB\).}
#endif
#if defined TARGET_probacond5
\title{TITLE 5}
\real{pB=\pA*\pBsA+\pAc*\pBsAc}
\statement{\preamb<br>
On donne \(p(A)=\pA\), \(p_A(B)=\pBsA\) et \(p_{\overline{A}}(B)=\pBsAc\). 
<div class="wims_question">Calculer \(p(B)\).</div> 
\(p(B)={}\)\embed{r1,10}. }
\answer{\(p(B)\)}{\pB}{type=numeric}
\solution{\(\{ A, \overline{A} \}\) est une partition de l'univers donc, d'après la formule des probabilités totales, 
\(p(B)=p(A)\times p_A(B)+p(\overline{A}) \times p_{\overline{A}}(B)=\pA \times \pBsA+\pAc \times \pBsAc=\pB\).}
#endif
#if defined TARGET_probacond6
\title{TITLE 6}
\real{coef1=\pB-\pAetB}
\real{pBsAc=\coef1/\pAc}
\statement{\preamb<br>
On donne \if{\choixlettres[1]==1}{\(p(\A)=\pA\), \(p(\B)=\pB\)}{\(p(\B)=\pB\), \(p(\A)=\pA\)} et \(p_\A(\B)=\pBsA\).
<div class="wims_question"> Calculer \(p_{\overline{\A}}(\B)\)</div>
\(p_{\overline{\A}}(\B)={}\)\embed{r1,10}.}
\answer{\(p_{\overline{\B}}(\A)\)}{\pBsAc}{type=numeric}
\solution{\(p(\overline{\A})=1-p(\A)=\pAc). \(\{\A, \overline{\A} \}\) est une partition de l'univers donc, d'après la formule des probabilités totales, 
\(p(\B)=p(\A)\times p_\A(\B)+p(\overline{\A}) \times p_{\overline{\A}}(\B)\) c'est à dire \(\pB=\pA \times \pBsA+\pAc \times p_{\overline{\A}}(\B)\)
<br>\(\pB=\pA \times \pBsA+\pAc \times p_{\overline{\A}}(\B) \Leftrightarrow \pB=\pAetB+\pAc p_{\overline{\A}}(\B)\)
<br>\(\Leftrightarrow \coef1=\pAc p_{\overline{\A}}(\B)\)
<br>\(\Leftrightarrow p_{\overline{\A}}(\B)=\frac{\coef1}{\pAc}=\pBsAc\).
}
#endif
