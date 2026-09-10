
#if defined TARGET_majunion
\text{name_maj1=majoré, minoré}
\text{name_maj2=majorant, minorant}
\text{yes=C'est toujours vrai}
\text{no=parfois vrai et parfois faux}
\text{bad=Ce n'est jamais vrai}
\text{name_enonce=Soient \(A\) et \(B\) deux sous-ensembles de \(\displaystyle{\RR}\).
  Supposons que \(A\) (resp. \(B\)) est ,
  par \(a\) (resp. par \(b\)). Les énoncés suivants sont-ils vrais&nbsp;}
\text{name_isby=est, par}
\text{name_answer=Intersection,Union}
#endif
#if defined TARGET_imfunc
\text{name_choix=borné,minoré,majoré,pas forcément minoré ni majoré}
\text{name_data=bijective,
  continue,
  continue et bijective,
  continue et dérivable,
  continue et périodique,
  croissante,
  croissante et périodique,
  croissante et surjective,
  décroissante,
  décroissante et périodique,
  décroissante et surjective,
  impaire,
  impaire et croissante,
  impaire et décroissante,
  injective,
  paire,
  paire et croissante,
  paire et décroissante,
  périodique,
  strictement croissante,
  strictement décroissante}
\text{name_enonce=Soit,une fonction, et soit \(A\) un ensemble,de,
  Considérons l'image,et l'image réciproque, de}
\text{name_question=Que peut-on dire de \(B\) et de \(C\)&nbsp;}
\text{name_instruction=Il faut choisir les réponses les plus pertinentes.}
\text{name_is=est}
#endif
#if defined TARGET_bornesup1 || defined TARGET_bornesup2
# if defined TARGET_bornesup1
\text{name_rep=l'énoncé ne permet pas de savoir si ,existe}
# endif
#if defined TARGET_bornesup2
\text{name_rep=est minoré par,est majoré par,aucune des propositions ne convient}
# endif
\text{name_enonce=Si \(A) est un ensemble non vide,
  on note \(\sup(A)) sa borne supérieure et \(\inf(A)) sa borne inférieure
  si elles existent.}
\text{name_know=On sait que&nbsp;}
\text{name_answer=La réponse}
#endif
#if defined TARGET_bornesup3
\text{name_rep=est un majorant de,est un minorant de}
\text{name_cond=majorés, minorés, supérieures,inférieures}
\text{name_enonce=Soient \(A) et \(B) deux ensembles non vides et,
  On note respectivement, et, leurs bornes, On sait que}
#endif
#if defined TARGET_bornesup1 || defined TARGET_bornesup2 || defined TARGET_bornesup3
\text{name_question=On peut en déduire (il peut y avoir une ou plusieurs bonnes réponses).}
#endif
#if defined TARGET_bornesup4
\text{name_rep=
  il n'y a plus rien à faire c'est une conséquence de la définition de la borne supérieure,
  il n'y a plus rien à faire c'est une conséquence de la définition de la borne inférieure,
  ce cas ne peut pas se produire,
  il reste à montrer que}
\text{name_mhyp=est un majorant de,est un minorant de,et on veut montrer que}
\text{name_enonce=Si \(A\) est un ensemble non vide et,
  on note,sa borne, On sait que}
\text{name_question=Choisir parmi les propositions suivantes (une seule bonne réponse).}
\text{name_answer=La réponse}
#endif
