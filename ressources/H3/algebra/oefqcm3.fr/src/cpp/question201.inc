\title{Question 201 Mesure d'un angle particulier}
\keywords{quizz,angles}
\observation{Question du sujet zéro sujet-zero-dnb-serie-generale-b-mathematiques.pdf du DNB publié sur éduscol en décembre 2025  }
%%% LSD %%%
\text{x=randomitem(d,p,n)}
\text{typeangle=\x issametext d? droit}
\text{typeangle=\x issametext p? plat}
\text{typeangle=\x issametext n? nul}

\text{enonce=Quelle est la mesure&#44; en degrés&#44; d'un angle \typeangle ?}
\text{enonceb= degrés.}

\if{\x issametext d}
{\text{rep=90}}

\if{\x issametext p}
{\text{rep=180}}

\if{\x issametext n}
{\text{rep=0}}

\text{typerep=numeric}

\text{feedback=La mesure d'un angle \typeangle vaut \rep °}
