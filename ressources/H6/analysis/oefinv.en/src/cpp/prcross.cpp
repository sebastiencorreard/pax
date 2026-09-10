target=prcroiss

#include "xiao.inc"
#include "lang_titles.inc"


\text{f=random(f,g,h)}
\text{ij=shuffle(I,J,K,L)}
\text{I=\ij[1]}
\text{J=\ij[2]}
\text{incdec=random(1,2)}
\text{croiss=item(\incdec,\name_increasing)}
\text{croiss2=item(\incdec,\name_increasing2)}
\text{xy=shuffle(x,y)}
\text{x1=\xy[1]1}
\text{x2=\xy[1]2}
\text{y1=\xy[2]1}
\text{y2=\xy[2]2}
\text{dir=random(1,2)}
\text{ineq=item(\dir,>,<)}
\text{invq=item(\dir,<,>)}
\text{ineq2=item(\incdec,\ineq,\invq)}
\text{invq2=item(\incdec,\invq,\ineq)}

\text{g1={Je prends,Soient} \(\x1,\x2) \(\in) \(\J) {tels que,avec} \(\x1 \ineq \x2).}
\text{g2={Je prends,Je définis,Soient} \(\y1 = \f^-1(\x1))&#44; \(\y2 = \f^-1(\x2)).}
\text{g3={Donc,Cela veut dire,C'est-à-dire} \(\x1 = \f(\y1)) \(\ineq) \(\x2 = \f(\y2)).}
\text{g4={Comme,Puisque,Parce que} \(\f) est \croiss&#44;
{j'ai,je déduis} \(\y1 \ineq2 \y2).}

\text{b1={Je prends,Soient} \(\x1,\x2) \(\in) \(\I) {tels que,avec} \(\x1 \ineq \x2).}
\text{b2={Je prends,Je définis,Soient} \(\y1 = \f(\x1))&#44; \(\y2 = \f(\x2)).}
\text{b3={Comme,Puisque,Parce que} \(\f) est \croiss&#44;
{j'ai,je déduis} \(\y1 \invq2 \y2).}
\text{b4={Comme,Puisque,Parce que} \(\f^-1) est \croiss&#44;
{j'ai,je déduis} \(\y1 \ineq2 \y2).}

\text{good=wims(singlespace wims(embraced randitem \g1,\g2,\g3,\g4))}
\text{bad =wims(singlespace wims(embraced randitem \b1,\b2,\b3,\b4))}
\text{goodcnt=items(\good)}
\text{all=\good,\bad}

\text{size=400x35x1}

\statement{Soient \(\I,\J) deux intervalles, \(\f : \I \to \J\) une fonction bijective,
et soit \(\f^-1 : \J -> \I\) sa réciproque.
Montrez que si \(\f\) est strictement \croiss, alors \(\f^-1\) l'est aussi, en choisissant
quatre des phrases données plus bas.
<ol>
<li>\embed{r1,\size}</li>
<li>\embed{r2,\size}</li>
<li>\embed{r3,\size}</li>
<li>\embed{r4,\size}</li>
\if{\status notsametext end}{}
<li>Donc par définition, \(\f^{-}1\) est strictement \croiss.
</li></ol>
}

\answer{Phrase 1}{\t1;\all}{type=dragfill}
\answer{Phrase 2}{\t2}{type=dragfill}
\answer{Phrase 3}{\t3}{type=dragfill}
\answer{Phrase 4}{\t4}{type=dragfill}

\text{r1=positionof(\t1,\all)}
\text{r2=positionof(\t2,\all)}
\text{r3=positionof(\t3,\all)}
\text{r4=positionof(\t4,\all)}

\condition{Le raisonnement est bien-construit}{\r1,\r2,\r3,\r4 issametext
1,2,3,4}

\feedback{\r1 notin 15}{
  La phrase 1 est mauvaise : vous faites référence à des variables qui ne sont
  pas encore définies.
}
\feedback{8 isin \r2\r3\r4}{
  Logique circulaire : vous utilisez la \croiss2 de \(\f^{-1}\) pour la
  démontrer ensuite&nbsp;?
}
\feedback{\r1=5 and 2 isin \r2\r3\r4}{
  Confusion d'intervalle dans la première phrase : pour que \(\f^-1(\x1)\) ait un
  sens, il faut que \(\x1\) appartienne à \(\J\) et non pas à \(\I\).
}
\feedback{\r1=5 and 3 isin \r2\r3\r4}{
  Confusion d'intervalle dans la première phrase : pour que \(\x1\) soit une
  image de \(\f\), il faut que \(\x1\) appartienne à \(\J\) et non pas à \(\I\).
}
\feedback{\r1\r2=56 and \r4 isin 47}{
  La définition de la \croiss2 pour \(\f^-1\) ne s'applique pas après votre
  raisonnement&nbsp;: il fallait montrer la bonne inégalité pour deux
  arguments quelconques de \(\f^-1\), alors que vous n'avez pris que deux
  arguments quelconques de \(\f\).
}
\feedback{\r1 isin 15 and \r2 notin 26}{
  La phrase 2 est mauvaise : vous faites référence à \(\y1\) et \(\y2\) qui ne sont
  pas encore définis.
}
\feedback{\r1=1 and \r2=6}{
  Confusion d'intervalle dans la première phrase : pour que \(\f(\x1)\) ait un
  sens, il faut que \(\x1\) appartienne à \(\I\) mais pas à \(\J\).
}
\feedback{\r1\r2=12 and \r3!=3}{
  Les phrases 3 et 4 ne suivent pas le bon ordre de logique.
}
\feedback{\r1\r2=12 and \r4=7}{
  Mauvaise application de la définition de la \croiss2 de \(\f\)&nbsp;:
  l'inégalité dans la phrase 4 est dans le mauvais sens.
}
