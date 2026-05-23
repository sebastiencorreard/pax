\title{Question 103 Calcul de proportion}
\keywords{quizz,percents,proportionality,fraction}
\observation{Question du sujet zéro sujet-zero-dnb-serie-generale-a-mathematiques.pdf du DNB publié sur éduscol en décembre 2025  }

\integer{efftot=randomitem(3,3,4,5,5)*100}
\integer{percent=randomitem(25,75)}

\text{enonce=Dans un collège&#44; \(\percent \%\) des \(\efftot\) élèves participent à une olympiade de mathématiques.<br>
Combien d’élèves ne participent pas à cette olympiade &nbsp;&#63;}
\text{enonceb=}

\integer{rep=(100-\percent)*\efftot/100}
\text{rep=\rep}
\text{typerep=numeric}
\integer{percenbis=100-\percent}
\text{mot1=\percent=25?les trois quarts:le quart}
\integer{quart=\efftot/4}
\text{mots2=\percent=25?<li> Puis \(\quart \times 3\).</li>:}
\text{feedback=La bonne réponse est&nbsp;&#58; <span class="nowrap">\(\rep\).</span> <br>En effet&nbsp;&#58;
<ul class="wims_nopuce"><li> Il y a \(\percenbis \%\) qui <b>n'y participent pas</b> (\mot1).</li>
<li>Il reste à faire le calcul \(\efftot \div 4 =\quart\).</li>\mots2</ul>}
