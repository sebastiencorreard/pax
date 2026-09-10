#if defined TARGET_calcul2
\text{name_statement=Calcule}
\text{name_and=et}
\text{name_feedback=La bonne réponse est,
  Ton premier résultat vaut,
  Ton second résultat vaut}
\text{name_andno=et non}
\text{name_answer=Premier,Second}
\text{name_instruction=Tu ne dois rentrer que des entiers.}
#endif
#if defined TARGET_additfrac0 || defined TARGET_additfrac
\text{name_effect=Calculate the following}
\matrix{name_statement=For that, reduce to the same denominator
  Then, do  multiplications
  Last, add (or substract) numerators
  And, if possible, simplify.}
\text{name_feedback=Finally}
\text{name_oper=the addition, the subtraction}
#endif
#if defined TARGET_calcul
\text{data1=\a plus \b multiplié par \c,
\a plus \b puis multiplie par \c,
\a plus \b que l'on a d'abord multiplié par \c,
\a multiplié par \b plus \c,
\a multiplié par la somme de \b et de \c,
\a plus \b divisé par \c,
\a plus \b que l'on a d'abord divisé par \c,
\a puis divise par \b plus \c ,
\a divisé par \b plus \c,
\a plus \b puis divise par \c,
\a divisé par \b puis ajoute \c
}
\text{name_statement=On calcule,
  Quelle est l'expression mathématique convenable&nbsp;}
\text{name_instruction=S'il y a ambiguité, il faut donner toutes les possibilités.}
#endif
#if defined TARGET_calcprio
\text{listechoix=the multiplication, the addition}
\text{name_statement=You have to calculate,
  et donner le résultat sous la forme d'une fraction irréductible.,
  Which operation are you going to do first,
  Do it (you must simplify fractions).}
\text{name_answer=Opération}
#endif
#if defined TARGET_FractionsI || defined TARGET_FractionsII || defined TARGET_FractionsIII
\text{name_instruction=À faire sans calculatrice.}
\text{name_answer=Votre réponse}
# if defined TARGET_FractionsI
  \text{name_statement=Calculer et donner le résultat sous la forme d'une fraction irréductible}
\text{name_hint=Pour additionner deux fractions, on réduit au même dénominateur.
  Dans cet exemple, le dénominateur commun est}
# endif
# if defined TARGET_FractionsII
\text{name_statement=Déterminer la fraction irréductible égale au produit}
\text{name_hint=La multiplication de deux fractions s'effectue en multipliant
les numérateurs et les dénominateurs entre eux. Pensez à simplifier dès que possible.}
# endif
# if defined TARGET_FractionsIII
\text{name_statement=Déterminer la fraction égale à}
\text{name_hint=Il faut commencer par calculer la somme des fractions au numérateur,
  puis celle située au dénominateur. Il restera ensuite à diviser deux fractions.}
# endif
#endif
#if defined TARGET_mult
\text{name_statement=Calculate}
#endif
#if defined TARGET_multintrus
\text{name_statement=Un des calculs donne un résultat différent des deux autres. Lequel&nbsp;}
\text{name_answer=Votre réponse}
#endif
#if defined TARGET_opsimple || defined TARGET_opsimple2
\text{openames=addition, soustraction, multiplication, division}
\text{operules=je prends tout simplement le signe des deux nombres.,
  j'enlève les parenthèses puis je prends le signe des deux nombres.,
  je regarde lequel des deux nombres a la plus grande distance à zéro.,
  j'enlève les parenthèses puis je regarde lequel des deux nombres a la plus grande distance à zéro.,
  j'applique la "règle des signes".}
\text{name_statement=Soit l'opération&nbsp;,
  C'est une,
  Pour trouver le signe du résultat,
  Quel est le signe du résultat&nbsp;,
  Pour calculer le résultat, je dois faire une,
  Je trouve }
#endif
#if defined TARGET_regleadd
\text{choix=la commutativité, l'associativité, la règle de signe, la règle de priorité}
\text{name_statement=Pour passer de la première à la seconde ligne, quelle propriété de
  l'addition a-t-on utilisée&nbsp;}
#endif
#if defined TARGET_signe
\text{name_statement=Le signe d'un produit de,
  facteurs non nuls comportant exactement,
  facteurs,
  est}
\text{name_sol=positif,négatif}
\text{name_negpos=négatifs, positifs}
\text{name_answer=Signe}
#endif
#if defined TARGET_transfmult
\text{multdiv= multiply, divide}
\text{multidivi= multiplied,divided}
\text{name_statement=How transforms the product of two numbers if one,
  one number by,
  and,
  the other one by,
  It is,by}
\text{name_feed=You should simplify.}
\text{name_num=Numerator}
\text{name_den=Denominator}
#endif
