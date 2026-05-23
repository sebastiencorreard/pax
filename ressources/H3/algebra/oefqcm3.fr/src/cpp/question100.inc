\title{Question 100 Fractions d'une quantité}
\keywords{quizz,fraction}
\observation{Question du sujet zéro sujet-zero-dnb-serie-generale-a-mathematiques.pdf du DNB publié sur éduscol en décembre 2025  }
\matrix{qte=tiers,quart,cinquième
3,4,5}
\integer{cas=randint(1..3)}
\text{q=\qte[1;\cas]}
\text{f=\qte[2;\cas]}
\integer{q2=randomitem(5,6,8,9,3)}
\integer{q3=\q2*\f}

\text{enonce=Quel est le \q de \q3&nbsp;&#63;}
\text{enonceb=}

\text{rep=\q2}
\text{typerep=numeric}

\text{feedback=La bonne réponse est <b>\q2. </b><br>Rappel&nbsp;&#58; prendre le \q d'un nombre&#44; c'est le diviser par \f}
