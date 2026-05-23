\text{warning=Les réponses doivent être séparées par une virgule}

#if defined TARGET_1
\text{instruction=La somme de trois nombres entiers naturels impairs
  successifs est égale à \N. Quels sont ces trois nombres ?}
#endif
#if defined TARGET_2
\text{instruction=XXXXX et YYYYY choisissent un même nombre. XXXXX le multiplie par \a
puis soustrait \b au résultat obtenu. YYYYY le multiplie par \c
et ajoute \d au résultat obtenu. IIIII obtiennent tous les deux le même résultat.
Quel nombre XXXXX et YYYYY avaient-iiiii choisi au départ ?
}
\text{name_ils=ils,elles}
\text{name_Ils=Ils,Elles}
#endif
#if defined TARGET_3
\text{instruction=Aujourd'hui, XXXXX a \a ans et YYYYY \b ans. Dans
  combien d'années l'âge de YYYYY sera-t-il le double de celui de XXXXX&nbsp;}
#endif
#if defined TARGET_4
\matrix{name_mon=Mon père,il
  Ma mère, elle}
\text{instruction=\name_mon[\choix;1] a \a ans de plus que moi. Dans \b ans, \name_mon[\choix;2] aura le triple
  de l'âge que j'ai aujourd'hui.
  Quel est mon âge}
#endif
#if defined TARGET_5
\text{instruction=La somme de deux nombres entiers est égale à \s.
  La différence de leurs carrés est aussi égale à \t.
  Quels sont ces deux nombres ?
}
#endif
#if defined TARGET_groupe1 || defined TARGET_groupe2
\text{name_enonce= On veut former des groupes avec
  XXXX OOOO et YYYY UUUU
  de sorte que chaque groupe ait le même nombre de OOOO et le
  même nombre de UUUU.}
\text{name_answer=Nombre de groupes}
\text{name_question1=Combien de groupes au maximum peut-on former&nbsp;}
# if defined TARGET_groupe1
\text{name_question2=Dans ce cas combien MMMM y aura-t-il dans chaque groupe&nbsp;}
\text{name_answer=\name_answer,Nombre MMMM dans chaque groupe}
# endif
# if defined TARGET_groupe2
\text{name_question2=Dans ce cas combien de OOOO y aura-t-il dans chaque groupe&nbsp;}
\text{name_answer=\name_answer, Nombre OOOO dans chaque groupe}
# endif
\text{name_object1=filles,billets,boules rouges,pions blancs}
\text{name_object2=garçons,pièces,boules jaunes, pions noirs}
\text{name_object=d'élèves,de billets et de pièces,de boules, de pions}
#endif

