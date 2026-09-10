#if defined TARGET_cond1
\matrix{name_statement=On dispose de trois résistances
  Ces trois résistances sont branchées en
  entre les bornes d'une alimentation continue.
}
\text{name_choix1=Elles ont pour valeurs respectives }

\matrix{name_choix2=La tension aux bornes de l'alimentation \(U) a pour valeur
  Calculer l'intensité \(I) du courant débité dans le circuit.}

\text{name_choix3=Le courant \(I) débité dans le circuit a pour valeur \I A.
  Quelle est la tension \(U) aux bornes du générateur ?}

\text{name_choix4=Les résistances \(R_1), \(R_2) ont pour valeurs respectives \
\R1 Ohms, \R2 Ohms. La tension aux bornes du générateur est \U volts
et le courant débité est de \I Ampères.
Quelle est la valeur de la résistance \(R_3) ?}
\text{name_instruction=Les résultats sont demandés avec une erreur relative de \(10^(-2))
  et l'unité.}
#endif
#if defined TARGET_cond2
\text{choix=série,parallèle}
\text{name_statement1=On dispose de quatre résistances. Leurs valeurs sont}
!!keep lines
\matrix{name_statement2=Ces quatre résistances sont branchées en
  entre les bornes d'une alimentation continue dont la tension est }
\text{name_step1=Calculer la résistance équivalente du montage en ohms.}
\matrix{name_step2=La résistance équivalente est
  Calculer l'intensité du courant
  qui les traverse,du circuit}
#endif
#if defined TARGET_cond1 || defined TARGET_cond2
\text{name_answer=Résistance équivalente,Intensité}
\text{name_feedback1=Il s'agit ici de résistances en série et non pas en parallèle.}
\text{name_feedback2=Il s'agit ici de résistances en parallèle et non pas en série.}
#endif
#if defined TARGET_maille
\matrix{name_statement=Voici une maille dans un circuit électrique alimenté en continu&nbsp;
  Quelle est la valeur du potentiel \(U) manquant&nbsp;}
#endif
#if defined TARGET_noeud
\matrix{name_statement=Voici un noeud dans un circuit électrique alimenté en continu&nbsp;
  Quelle est la valeur de l'intensité \(I) manquante&nbsp;}
#endif
#if defined TARGET_maille || defined TARGET_noeud
\text{name_instruction=Vous devez écrire l'unité.}
\text{name_hint=Il s'agit de valeurs algébriques. Appliquer la loi des noeuds.}
#endif
