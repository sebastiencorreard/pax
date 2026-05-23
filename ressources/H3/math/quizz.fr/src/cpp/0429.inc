\title{Question 0429 Problème multiplicatif}
\keywords{mental_calculation,pbsolving}

\integer{a=randint(2,2,3,3)}
\integer{b=\a*randint(2,2,3)}
\integer{c=\a==2?randint(10,10,8,12):randint(12,15,12,9)}

\integer{rep0=\c/\a*\b}
\integer{rep=\rep0}

\text{enonce= Quand je monte de \a marches, je m'élève de \c cm.<br>Quand je monte de \b marches, je m'élève de}
\text{enonceb= cm}
%%%% feedback %%%%
\integer{d=\c/\a}
\integer{d2=\b/\a}
\text{feedback=randomitem(Une marche me fait monter de \d cm. Donc \(\d\times \b=\rep0\).,\(\b=\a \times \d2\) donc \(\d2 \times \c=\rep0\).)}
