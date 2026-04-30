target=pdfcttableffect,pdfcttablpourcent,pdfctstat
#define TITLE Pièces défectueuses

#if defined TARGET_pdfcttableffect
\title{TITLE (Tableau à compléter avec des effectifs)}
\observation{La machine dont la part de production n'est pas donnée dans l'énoncé n'est pas toujours la même.<br> On peut mettre un calcul à la place de la réponse numérique et Wims accepte la réponse.}
\keywords{absolute_frequency, relative_frequency, percentage}
#endif

#if defined TARGET_pdfcttablpourcent
\title{TITLE (Tableau à compléter avec des pourcentages)}
\observation{La machine dont la part de production n'est pas donnée dans l'énoncé n'est pas toujours la même.<br> On peut mettre un calcul à la place de la réponse numérique et Wims accepte la réponse.}
\keywords{absolute_frequency, relative_frequency, percentage}
#endif

#if defined TARGET_pdfctstat
\title{TITLE (Questions de statistiques)}
\observation{On peut donner les réponses en fractions ou en valeurs décimales. Une solution donne les bonnes réponses sous forme de fractions.}
\keywords{absolute_frequency, relative_frequency, percentage}
#endif

\language{fr}
\author{Paul,Byache}
\email{paul@byache.fr}
\computeanswer{yes}
\precision{200}
\format{html}
\integer{tot=randint(2..20)*1000}
\text{machines=shuffle(A,B,C,E,F,G,H)}
\text{A=\machines[1]}
\text{B=\machines[2]}
\text{C=\machines[3]}
//frequences des pieces defectueuses
\integer{fDA=randint(2..9)}
\integer{fDB=randint(2..9)}
\integer{fDC=randint(2..9)}
//part de production de chaque machine
\integer{fA=randint(1..4)*10}
\integer{fB=randint(1..4)*10}
\integer{fC=100-\fA-\fB}

#if defined defined TARGET_pdfctstat
\integer{eAD=\tot*\fA*\fDA/10000}
\integer{eBD=\tot*\fB*\fDB/10000}
\integer{eCD=\tot*\fC*\fDC/10000}
\integer{eD=\tot*(\fA*\fDA+\fB*\fDB+\fC*\fDC)/10000}
\integer{eAsD=\tot*\fA*(100-\fDA)/10000}
\integer{eBsD=\tot*\fB*(100-\fDB)/10000}
\integer{eCsD=\tot*\fC*(100-\fDC)/10000}
\integer{esD=\tot*(\fA*(100-\fDA)+\fB*(100-\fDB)+\fC*(100-\fDC))/10000}
\integer{eA=\tot*\fA/100}
\integer{eB=\tot*\fB/100}
\integer{eC=\tot*\fC/100}
#endif



#if defined TARGET_pdfctstat
//on prépare 4 questions, avec une formulation en phrase et une formulation en notation math (et la réponse en dernier argument)
\matrix{questions1=randomrow(Quelle est la fréquence des ampoules ayant un défaut parmi les ampoules produites par la machine \A,f_\A(D),\eAD/\eA
Quelle est la fréquence des ampoules ayant un défaut parmi les ampoules qui n'ont pas été produites par la machine \A,f_\overline{\A}(D),(\eD-\eAD)/(\tot-\eA)
Quelle est la fréquence des ampoules ayant un défaut parmi les ampoules produites par la machine \B,f_\B(D),\eBD/\eB
Quelle est la fréquence des ampoules ayant un défaut parmi les ampoules qui n'ont pas été produites par la machine \B,f_\overline{\B}(D),(\eD-\eBD)/(\tot-\eB))
randomrow(Quelle est la fréquence des ampoules produites par la machine \A parmi celles qui ont un défaut,f_D(\A),\eAD/\eD
Quelle est la fréquence des ampoules ne provenant pas de la machine \A parmi celles qui ont un défaut,f_D(\overline{\A}),(\eD-\eAD)/\eD
Quelle est la fréquence des ampoules produites par la machine \C parmi celles qui ont un défaut,f_D(\C),\eCD/\eD
Quelle est la fréquence des ampoules ne provenant pas de la machine \C parmi celles qui ont un défaut,f_D(\overline{\C}),(\eD-\eCD)/\eD)
randomrow(Quelle est la fréquence des ampoules ayant un défaut,f(D),\eD/\tot
Quelle est la fréquence des ampoules n'ayant pas de défaut,f(\overline{D}),\esD/\tot
Quelle est la fréquence des ampoules provenant de la machine \A,f(\A),\eA/\tot
Quelle est la fréquence des ampoules ne provenant pas de la machine \B,f(\overline{\B}),(\tot-\eB)/\tot
Quelle est la fréquence des ampoules ne provenant pas de la machine \C,f(\overline{\C}),(\tot-\eC)/\tot)
randomrow(Quelle est la fréquence des ampoules n'ayant pas de défaut parmi les ampoules produites par la machine \C,f_\C(\overline{D}),\eCsD/\eC
Quelle est la fréquence des ampoules produites par la machine \C parmi celles qui n'ont pas de défaut,f_\overline{D}(\C),\eCsD/\esD
Quelle est la fréquence des ampoules n'ayant pas de défaut parmi les ampoules produites par la machine \B,f_\B(\overline{D}),\eBsD/\eB
Quelle est la fréquence des ampoules produites par la machine \B parmi celles qui n'ont pas de défaut,f_\overline{D}(\B),\eBsD/\esD)}

//on mélange les 3 questions avec des "parmi"
\text{melange=shuffle(3,shuffle(1,2,4))}
\matrix{questions=\questions1[\melange[1];]
\questions1[\melange[2];]
\questions1[\melange[3];]
\questions1[\melange[4];]}
#endif

#if defined defined TARGET_pdfctstat
//préparation de l'afficahe de la solution avec des fractions :
\text{f=wims(replace internal / by , in \questions[1;3])}
\integer{n=\f[1]}
\integer{d=\f[2]}
\text{f1=\n/\d}
\text{f=wims(replace internal / by , in \questions[2;3])}
\integer{n=\f[1]}
\integer{d=\f[2]}
\text{f2=\n/\d}
\text{f=wims(replace internal / by , in \questions[3;3])}
\integer{n=\f[1]}
\integer{d=\f[2]}
\text{f3=\n/\d}
\text{f=wims(replace internal / by , in \questions[4;3])}
\integer{n=\f[1]}
\integer{d=\f[2]}
\text{f4=\n/\d}
#endif

//on ne donne que deux parts sur les trois, mais choisies au hasard :
\text{parts=randomrow(La machine \A produit \fA % de la production, la machine \B produit \fB % de la production et la machine \C fournit le reste.
La machine \B produit \fB % de la production, la machine \C produit \fC % de la production et la machine \A fournit le reste.
La machine \A produit \fA % de la production, la machine \C produit \fC % de la production et la machine \B fournit le reste.)}

\css{<style type="text/css">
.cadre {border-style:solid;text-align:center; border-width:0px;margin-left:auto; margin-right:auto; border: 1px; }
.ctable {text-align:center;padding:4px;}
.consigne {color:#000080;margin-bottom:6px;}
.bonne {color:#008000;margin-bottom:6px;}
.formatrep {font-style:italic;font-size:90%;}
table.tableau, table.cadre {margin-left:auto; margin-right:auto;
 border-collapse: collapse;
 padding: 6px;
 margin-top: 10px;
 margin-bottom: 10px;
}

table.tableau th, table.cadre th
{
 text-align:center;
 border: 1px solid #999;
 padding:6px;
 background-color:#D6EBEB;
}
table.tableau td, table.cadre td, table.tableau tr, table.cadre tr{
text-align:center;
 border: 1px solid #999;
 padding:6px;
}
table.tableau tr th:first-child {
 min-width:100px;
}
</style>}

\statement{
#if defined TARGET_pdfcttableffect || TARGET_pdfcttablpourcent
Un fabriquant d'ampoules possède trois machines notées \A, \B et \C.
\parts
<p>Certaines ampoules présentent un défaut de fabrication :</p>
<ul>
<li>à la sortie de la machine \A, \fDA % des ampoules présentent un défaut</li>
<li>à la sortie de la machine \B, \fDB % des ampoules présentent un défaut</li>
<li>à la sortie de la machine \C, \fDC % des ampoules présentent un défaut</li>
</ul>
La production quotidienne totale du fabriquant est de \tot ampoules.
#endif
#if defined TARGET_pdfcttableffect
Compléter le tableau ci-dessous avec des effectifs :
<table class="cadre">
<tr><td></td><th>Machine \A</th><th>Machine \B</th><th>Machine \C</th><th>Total</th></tr>
<tr><th>Avec défaut</th><td>\embed{r1,5}</td><td>\embed{r2,5}</td><td>\embed{r3,5}</td><td>\embed{r4,5}</td></tr>
<tr><th>Sans défaut</th><td>\embed{r5,5}</td><td>\embed{r6,5}</td><td>\embed{r7,5}</td><td>\embed{r8,5}</td></tr>
<tr><th>Total</th><td>\embed{r9,5}</td><td>\embed{r10,5}</td><td>\embed{r11,5}</td><td>\embed{r12,5}</td></tr>
</table>
#endif
#if defined TARGET_pdfcttablpourcent
Compléter le tableau ci-dessous avec des fréquences en pourcentages :
<table class="cadre">
<tr><td></td><th>Machine \A</th><th>Machine \B</th><th>Machine \C</th><th>Total</th></tr>
<tr><th>Avec défaut</th><td>\embed{r1,5} %</td><td>\embed{r2,5} %</td><td>\embed{r3,5} %</td><td>\embed{r4,5} %</td></tr>
<tr><th>Sans défaut</th><td>\embed{r5,5} %</td><td>\embed{r6,5} %</td><td>\embed{r7,5} %</td><td>\embed{r8,5} %</td></tr>
<tr><th>Total</th><td>\embed{r9,5} %</td><td>\embed{r10,5} %</td><td>\embed{r11,5} %</td><td>100 %</td></tr>
</table>
#endif

#if defined defined TARGET_pdfctstat
Un fabriquant d'ampoules possède trois machines notées \A, \B et \C.
La production quotidienne totale du fabriquant est de \tot ampoules. Certaines ampoules présentent un défaut de fabrication.
Voici un tableau résumant les différents effectifs dans la production.
<table class="cadre">
<tr><td></td><th>Machine \A</th><th>Machine \B</th><th>Machine \C</th><th>Total</th></tr>
<tr><th>Avec défaut</th><td>\eAD</td><td>\eBD</td><td>\eCD</td><td>\eD</td></tr>
<tr><th>Sans défaut</th><td>\eAsD</td><td>\eBsD</td><td>\eCsD</td><td>\esD</td></tr>
<tr><th>Total</th><td>\eA</td><td>\eB</td><td>\eC</td><td>\tot</td></tr>
</table>
#endif


#if defined TARGET_pdfctstat
<p>\questions[1;1] ? \embed{r1,10}</p>
<p>\questions[2;1] ? \embed{r2,10}</p>
<p>\questions[3;1] ? \embed{r3,10}</p>
#endif

#if defined TARGET_pdfctstat
<div class="wims_instruction">Donnez vos réponses sous forme décimale ou sous forme de fraction. Par exemple, si une réponse est 20%,
vous pouvez répondre 0.2 ou 20/100 ou encore 1/5.</div>
#endif
}


#if defined TARGET_pdfcttableffect
\answer{A avec défaut}{\tot*\fA*\fDA/10000}{type=numeric}
\answer{B avec défaut}{\tot*\fB*\fDB/10000}{type=numeric}
\answer{C avec défaut}{\tot*\fC*\fDC/10000}{type=numeric}
\answer{total avec défaut}{\tot*(\fA*\fDA+\fB*\fDB+\fC*\fDC)/10000}{type=numeric}

\answer{A sans défaut}{\tot*\fA*(100-\fDA)/10000}{type=numeric}
\answer{B sans défaut}{\tot*\fB*(100-\fDB)/10000}{type=numeric}
\answer{C sans défaut}{\tot*\fC*(100-\fDC)/10000}{type=numeric}
\answer{total sans défaut}{\tot*(\fA*(100-\fDA)+\fB*(100-\fDB)+\fC*(100-\fDC))/10000}{type=numeric}

\answer{total A}{\tot*\fA/100}{type=numeric}
\answer{total B}{\tot*\fB/100}{type=numeric}
\answer{total C}{\tot*\fC/100}{type=numeric}
\answer{total}{\tot}{type=numeric}
#endif
#if defined TARGET_pdfcttablpourcent
\answer{A avec défaut}{\fA*\fDA/100}{type=numeric}
\answer{B avec défaut}{\fB*\fDB/100}{type=numeric}
\answer{C avec défaut}{\fC*\fDC/100}{type=numeric}
\answer{total avec défaut}{(\fA*\fDA+\fB*\fDB+\fC*\fDC)/100}{type=numeric}

\answer{A sans défaut}{\fA*(100-\fDA)/100}{type=numeric}
\answer{B sans défaut}{\fB*(100-\fDB)/100}{type=numeric}
\answer{C sans défaut}{\fC*(100-\fDC)/100}{type=numeric}
\answer{total sans défaut}{(\fA*(100-\fDA)+\fB*(100-\fDB)+\fC*(100-\fDC))/100}{type=numeric}

\answer{total A}{\fA}{type=numeric}
\answer{total B}{\fB}{type=numeric}
\answer{total C}{\fC}{type=numeric}
#endif

#if defined TARGET_pdfctstat
\answer{question 1}{\questions[1;3]}{type=numeric}
\answer{question 2}{\questions[2;3]}{type=numeric}
\answer{question 3}{\questions[3;3]}{type=numeric}
\solution{Voici les bonnes réponses, données sous forme de fractions :
<p>\questions[1;1] ? <span class="oef_indgood">Réponse : \(\f1\)</span></p>
<p>\questions[2;1] ? <span class="oef_indgood">Réponse : \(\f2\)</span></p>
<p>\questions[3;1] ? <span class="oef_indgood">Réponse : \(\f3\)</span></p>}
#endif
