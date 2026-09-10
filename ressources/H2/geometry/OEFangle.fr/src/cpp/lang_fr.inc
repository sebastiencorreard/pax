#if defined TARGET_angle1 || defined TARGET_angle2 || defined TARGET_angle3
\text{name_question=Calculer les angles ci-dessous.}
# if defined TARGET_angle1 || defined TARGET_angle2
\text{name_question1=Le triangle \(A B E\) est rectangle en \(A\) et le quadrilatère \(B C D E\) est un parallélogramme.}
\text{name_question2=L'angle \(\widehat{C B E}) mesure,
  l'angle \(\widehat{F C E}) mesure}
# endif
# if defined TARGET_angle3
\text{name_question2=L'angle \(\widehat{A B C}) mesure,
  L'angle \(\widehat{A C D}) mesure,
  L'angle \(\widehat{A D C}) mesure}
# endif
#endif
#if defined TARGET_oeftrouvangltriang1 || defined TARGET_oeftrouvangltriang2 ||defined TARGET_oefmesangltriang
\matrix{quest=le sommet opposé au côté [\n[1] \n[2]] est le sommet,
 le côté opposé au sommet \(\n[1]\) est le côté }
\text{name_info=Voici quelques informations sur le triangle}
\text{name_instruc0=Construire le triangle \(\nom[1] \nom[2] \nom[3]\) avec les bonnes dimensions sur le brouillon,
  et mesurer les angles du triangle :}
\text{name_instruc1=Dans le triangle \(\nom[1] \nom[2] \nom[3]\), trouver la mesure de l'angle suivant:}
\text{name_instruc2=Pour vous aider, vous pouvez faire un dessin au brouillon avec les bonnes mesures.}
#endif
#if defined TARGET_vocangle1
\text{comp=complémentaires}
\text{supp=supplémentaires}
\text{opp=opposés par le sommet}
\text{alt=alternes-internes}
\text{corr=correspondants}
\text{rien=rien de particulier }
\text{name_info_voc1=Le triangle \(A B E\) est rectangle en \(A\) et le quadrilatère \(B C D E\) est un parallélogramme.}
\text{name_quest=Les angles \(\widehat{\ang1}\) et \(\widehat{\ang2}\) sont}
#endif
\text{name_ans=Angle}


