target= additrou

#include "author.inc"
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{signe=+,-}
\text{sign1=random(+,-)}

\title{TITRE}

\text{entier=shuffle(30)}
\integer{nb1=\entier[1]}
\integer{nb2=\entier[2]}
\text{signe=+,-}
\text{sign1=random(+,-)}
\text{sign2=random(+,-)}
\integer{snb1=\sign1\nb1}
\integer{snb2=\sign2\nb2}
\integer{rep=\sign2\nb2-\sign1\nb1}
\text{choix=randint(2)}
\if{\choix=1}{\text{quest1=\(\lpar\sign1\nb1\rpar+\lpar\)}
\text{quest2=\(\rpar\)}}{\text{quest2=\(\rpar+\lpar\sign1\nb1\rpar\)}
\text{quest1=\(\lpar\)}}
\text{result=\(=\sign2\nb2\)}
\if{\rep>0}{\text{ttrep=\textcolor{red}{( \plus \rep )}}
            \text{trep=\textcolor{red}{\plus \rep}}}
            {\text{ttrep=\textcolor{red}{( \rep )}}
            \text{trep=\textcolor{red}{\rep}}}
\if{\choix=1}{\text{solu=\((\sign1 \nb1 ) \plus \)\(\ttrep\)\( =\sign2 \nb2\)}}{\text{solu=\( \ttrep\)\( \plus (\sign1 \nb1 ) =\sign2 \nb2\)}}
\if{\sign1=+ and \sign2=+ and \nb2>\nb1}{\integer{min=-1}
\integer{max=\nb2+2}}
\if{\sign1=+ and \sign2=+ and \nb1>\nb2}{\integer{min=-1}
\integer{max=\nb1+2}}
\if{\sign1=- and \sign2=- and \nb2>\nb1}{\integer{max=1}
\integer{min=-\nb2-2}}
\if{\sign1=- and \sign2=- and \nb1>\nb2}{\integer{max=\nb2+2}
\integer{min=-\nb1-2}}
\if{\sign1=+ and \sign2=- and \nb2>\nb1}{\integer{max=\nb1+1}
\integer{min=-\nb2-2}}
\if{\sign1=+ and \sign2=- and \nb1>\nb2}{\integer{max=\nb1+1}
\integer{min=-\nb2-2}}
\if{\sign1=- and \sign2=+ and \nb2>\nb1}{\integer{max=\nb2+1}
\integer{min=-\nb1-2}}
\if{\sign1=- and \sign2=+ and \nb1>\nb2}{\integer{max=\nb2+1}
\integer{min=-\nb1-2}}
%%Droite graduée
\integer{xsize=600}
\integer{marge=40}
#include "drgrlight.inc"
\text{url2=draw(600,150
\essai
translate \sign1 \nb1,0
arrow 0,1.5,\rep,1.5,10,red
text red,\rep/2,2.5,giant,?
killtranslate
)}

\statement{<p><label for="reply1">Trouver le nombre manquant&nbsp;:</label></p>
<div><span class="nowrap"> \quest1\embed{reply1,5}\quest2\result.</span></div>
<div class="wims_instruction">Le nombre cherché sera écrit sans parenthèses.</div>}
\answer{Votre réponse}{\rep}{type=numexp}

\solution{Pour aller de \(\snb1\) à \(\snb2\), il faut...<span class="nowrap">\(\trep\).</span>
<img src="\url2" alt="droite graduée avec flèches bout à bout">
<p>\solu</p>}
