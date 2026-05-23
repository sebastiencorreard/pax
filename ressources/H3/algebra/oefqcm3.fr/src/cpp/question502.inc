\title{Question 502 Tracer un carré}
\keywords{quizz,algorithmics}
\observation{Question du sujet zéro sujet-zero-dnb-serie-generale-a-mathematiques.pdf du DNB publié sur éduscol en décembre 2025  }
\language{fr}
\format{html}
%% MB %%%
%%% adaptation : on demande soit le 4 soit le 90


\text{rep=randomitem(4,90)}
\integer{nligne=\rep=4?1:4}
\text{img=\rep=4?\imagedir/../q502_e1.png:\imagedir/../q502_e2.png}
\text{endfeed=\rep=4?Il faut tracer et tourner quatre fois pour tracé un carré.:Il faut tourner de 90° à chaque sommet pour tracer un carré.}
\text{typerep=numeric}

\text{enonce=Une élève souhaite réaliser un programme avec un logiciel de programmation pour dessiner un carré.
<div class="wimscenter"><img src="\img" alt=""></div>
Par quelles valeurs doit-on compléter la ligne \nligne du bloc pour obtenir un carré&nbsp;&#63;}
\text{enonceb=}
\text{feedback=La bonne réponse est \rep. <div class="wimscenter"><img src="\imagedir/../q502_corr.png" alt=""></div>\endfeed}
