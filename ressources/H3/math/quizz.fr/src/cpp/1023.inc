\title{Question 1023 Exploiter un ratio}
\keywords{mental_calculation,proportionality}
%%%%%%%%%%% question 8 %%%%%%%%%%%

\integer{f8=randitem(3,4,5,7)}
\integer{g8=randitem(3,4,5,7)}
\integer{g8=\f8==\g8? \g8+1}

\integer{m8=randitem(3,4,5,6,8)}
\integer{choix8=randitem(1,2)} #choix8 = 1 -> on donne le nombre de filles et on demande celui de garçons
\real{d8=\choix8==1? \m8*\f8 : \m8*\g8}
\real{d18=\choix8==1?\f8:\g8}
\real{d28=\choix8==1?\g8:\f8}

\real{rep=\choix8==1? \m8*\g8 : \m8*\f8}

\text{t18=\choix8==1? filles : garçons}
\text{t28=\choix8==1? garçons : filles}

\text{t38=\choix8==1? \f8: \g8}
\text{t48=\choix8==1? \g8: \f8}

\text{enonce=Dans une classe de troisième, le ratio filles &#58; garçons est de \f8 &#58; \g8.<br>Il y a dans cette classe \d8 \t18. Calculer le nombre de \t28. <br> Réponse &#58; }
\text{enonceb=}
\text{feedback=L'énoncé signifie qu'il y a \f8 filles pour \g8 garçons. 
Comme il y a au total \m8 fois \d18  \t18, cela fait \m8 fois \d28 \t28.}
