\text{name_answer=Votre réponse&nbsp;}
#if defined TARGET_cplpremier1 || defined TARGET_cplpremier2 || defined TARGET_cplpremier3 || defined TARGET_cplpremier4 || defined TARGET_cplpremier5
\text{name_yesno=Oui,Non}
# if defined TARGET_cplpremier1 || defined TARGET_cplpremier3
\text{name_question=et,sont-ils premiers entre eux}
# else
\text{name_question=Sélectionner les étiquettes ci-dessous dont les deux nombres
    sont premiers entre eux.}
\text{name_cond=Liste correcte}
# endif
#endif
#if defined TARGET_vocabulaire1 || defined TARGET_vocabulaire2 || defined TARGET_vocabulaire3 || defined TARGET_vocabulaire4 || defined TARGET_vocabulaire5
\text{name_divmult=est un diviseur de,est un multiple de,est divisible par}
# if defined TARGET_vocabulaire4 || defined TARGET_vocabulaire5
\text{name_question=Parmi les affirmations suivantes, lesquelles sont vraies&nbsp;}
# else
\text{name_question=Laquelle de ces affirmations est juste&nbsp;}
# endif
#endif
#if defined TARGET_pgcd1 || defined TARGET_pgcd2 || defined TARGET_pgcd3 || defined TARGET_pgcd4 || defined TARGET_pgcd5
\matrix{name_question=Quel est le plus grand diviseur commun à,et
  Le plus grand diviseur commun à , et , est}
# if defined TARGET_pgcd4 || defined TARGET_pgcd5
\text{name_hint=Utiliser un algorithme de calcul.}
# endif
#endif
#if defined TARGET_listdiv1 || defined TARGET_listdiv2 || defined TARGET_listdiv3 || defined TARGET_listdiv4 || defined TARGET_listdiv5
\text{name_question=Écrire la liste des diviseurs du nombre}
\text{name_question1=L'ensemble des diviseurs du nombre,est }
\text{name_instruction=Séparer les diviseurs par des virgules.}
#endif
#if defined TARGET_fractionsimp1 || defined TARGET_fractionsimp2 || defined TARGET_fractionsimp3 || defined TARGET_fractionsimp4 || defined TARGET_fractionsimp5
\text{name_question=Quelle est l'écriture irréductible de la fraction}
\text{name_numden=numérateur, dénominateur}
#endif
#if defined TARGET_critere1 || defined TARGET_critere2 || defined TARGET_critere3 || defined TARGET_critere4 || defined TARGET_critere5
\text{name_phrases=Son chiffre des unités est XXXX.,
  La somme de ses chiffres est divisible par YYYY.,
  La somme de son chiffre des unités et de son chiffre des centaines est égal à celui des dizaines.,
  La somme de ses deux derniers chiffres est divisible par YYYY.}
\text{name_phrase2=Le nombre formé par ses deux derniers chiffres est divisible par YYYY}
\text{name_question=Un nombre est divisible par, si}
#endif
#if defined TARGET_calcfract1 || defined TARGET_calcfract2 || defined TARGET_calcfract3 || defined TARGET_calcfract4 || defined TARGET_calcfract5
\text{name_question=Calculer et simplifier l'expression, suivante}
#endif
#if defined TARGET_Applcritere1 || defined TARGET_Applcritere2 || defined TARGET_Applcritere3 || defined TARGET_Applcritere4 || defined TARGET_Applcritere5
\text{name_question=Parmi ces nombres, lesquels sont divisibles par}
\text{name_question2=Les nombres divisibles par,sont}
\text{name_num=Numérateur}
\text{name_cond=Liste correcte}
\text{name_sol=La liste des nombres divisibles par, est}
#endif
