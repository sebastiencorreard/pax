#if defined TARGET_CORequ3 || defined TARGET_CORequ4 || defined TARGET_CORequ5
\text{name_question=Mettez en relation chaque équation d'inconnue,avec sa solution.}
\text{name_answer=La correspondance}
#endif
#if defined TARGET_CORinequ3 || defined TARGET_CORinequ4 || defined TARGET_CORinequ5
\text{name_question=Mettez en relation les inéquations équivalentes
  (c'est-à-dire ayant le même ensemble de solutions).}
\text{name_answer=La correspondance}
#endif
#if defined TARGET_Equation3 || defined TARGET_Equation4 || defined TARGET_optrou3 || defined TARGET_optrou4 || defined TARGET_optrou5
# if defined TARGET_Equation3 || defined TARGET_Equation4
\text{name_question=Résoudre l'équation}
# else
\text{name_question=Complétez l'opération suivante&nbsp;}
# endif
\text{name_answer=Réponse}
\text{name_instruction=Donner votre résultat sous une forme aussi simplifiée que possible.}
#endif
#if defined TARGET_resoudre1 || defined TARGET_resoudre2 || defined TARGET_resoudre3
\text{name_question=Résoudre l'équation&nbsp;}
\text{name_question1=L'ensemble des solutions de l'équation est}
\text{name_instruction=S'il y a plusieurs solutions, séparez-les par des virgules.}
#endif
#if defined TARGET_probsys
\text{listnoms=randitem(CD,DVD),BD}
\text{enonce=Dans un grand magasin, le prix des \listnoms[1] est unique, ainsi que celui des \listnoms[2].
  \prenom1 achète \nbA1 \listnoms[1] et \nbB1 \listnoms[2] pour \total1 euros.
  \prenom2 achète \nbA2 \listnoms[1] et \nbB2 \listnoms[2] pour \total2 euros.
}
\text{enonce2=Déterminez le prix d'un \listnoms[1] et le prix d'une \listnoms[2].}
\text{name_prix=Prix d'un,Prix d'une}
#endif
#if defined TARGET_probsys2
\text{listnoms=shuffle(de pommes,de poires,de pêches,de fraises,de framboises,de poivrons,de courgettes,de carottes,de tomates,d'aubergines)}
\text{enonce=Chez l'épicier, \prenom1 achète \nbA1 kilos \listnoms[1] et \nbB1 kilos \listnoms[2]
  pour \total1 euros. \prenom2 achète \nbA2 kilos \listnoms[1] et \nbB2 kilos \listnoms[2] pour \total2 euros.}
\text{enonce2=Déterminez le prix d'un kilo \listnoms[1] et le prix d'un kilo \listnoms[2].}
\text{name_prix=Prix d'un kilo,Prix d'un kilo}
#endif
#if defined TARGET_equadiv
\title{Équation avec division}
\text{name_question=Voici une équation, Quelle doit être la valeur de,
  pour que l'égalité soit vraie}
#endif
#if defined TARGET_produit
\text{name_instruction=Vous devez écrire les nombres sous une forme aussi simplifiée que possible.}
\text{name_Question=Question}
\text{name_question=Développer et réduire l'expression,
  Factoriser l'expression,
  Factoriser,
  Quelles sont les solutions de l'équation}
#endif
#if defined TARGET_systeme
\text{name_question=Parmi les couples de nombres,lequel est solution du système d'équations suivant}
\text{name_answer=Réponse}
#endif
#if defined TARGET_solvesys
\text{name_question=Résoudre le système d'équations suivant&nbsp;}
\text{name_answer=Réponse}
#endif
#if defined TARGET_solution
\text{name_question=Pour chacune des équations ci-dessous,
  cochez les nombres qui sont solution dans la liste proposée.}
\text{name_header=Équation,Solution(s)}
\text{name_none=Aucune}
#endif
#if defined TARGET_Equation2 || defined TARGET_Equation
\text{name_question=Résoudre l'équation}
\text{name_instruction=Donner votre résultat sous une forme aussi simplifiée que possible.}
\text{name_guide=On vous propose de résoudre l'exercice en vous guidant.
  Complétez les différentes étapes de calcul qui vous sont proposées}
\text{name_question2=En ajoutant, à chacun des membres de l'égalité puis en réduisant on obtient }
\text{name_answer=Réponse}
# if defined TARGET_Equation2
\text{name_question3=En ajoutant, à chacun des membres de l'égalité puis en réduisant on obtient}
\text{name_question4=En divisant chacun des membres de l'égalité par, on obtient}
\text{name_question5=On termine en simplifiant le résultat }
# endif
# if defined TARGET_Equation
\text{name_question2=En ajoutant, à chacun des membres de l'égalité puis en réduisant on obtient }
\text{name_question3=En divisant chacun des membres de l'égalité par , on obtient}
\text{name_question4=On termine en simplifiant le résultat }
# endif
#endif
