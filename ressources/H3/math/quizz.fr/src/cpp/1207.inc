\title{Question 1207 Probabilité}
\keywords{probability,mental_calculation}
\text{quest=shuffle(2,3,4,5)}
\integer{n=\quest[1]} %%%% boules noires
\text{ntxt=slib(numeration/ecriturelettre \n)}
\integer{b=\quest[2]} %%%% boules  blanches
\text{btxt=slib(numeration/ecriturelettre \b)}
\text{coul=random(noire,blanche)}
\integer{tot=\n+\b}
\real{rep=\coul issametext noire ? \n/\tot:\b/\tot}
\text{s=s} %%%% pour avoir le s dans le feedback
\integer{tempsol=\coul issametext noire ? \n:\b}
\text{enonce=Une urne contient \ntxt boules noires et \btxt boules blanches. <br><i>On tire une boule au hasard.</i><br>Quelle est la probabilité de tirer une boule \coul &#63; }
\text{enonceb=}
\text{feedback=Attention, il y a \tot boules \coul\s. Donc \(\frac{\tempsol}{\tot}\).}
