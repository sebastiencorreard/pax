#if defined TARGET_angle1 || defined TARGET_angle2 || defined TARGET_angle3
\text{name_question=Bereken onderstaande hoeken.}
# if defined TARGET_angle1 || defined TARGET_angle2
\text{name_question1=De driehoek \(A B E\) heeft een rechte hoek in \(A\) en de vierhoek \(B C D E\) is een parallellogram.}
\text{name_question2=&ang; \(\widehat{C B E}) =,
  &ang; \(\widehat{F C E}) =}
# endif
# if defined TARGET_angle3
\text{name_question2=&ang; \(\widehat{A B C}) =,
  &ang; \(\widehat{A C D}) =,
  &ang; \(\widehat{A D C}) =}
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
\text{comp=complementair}
\text{supp=supplementair}
\text{opp=tegenovergestelde van de som}
\text{alt=buitenhoek-binnenhoek}
\text{corr=overeenkomstige hoeken}
\text{rien=niets van dit al}
\text{name_info_voc1=De driehoek \(A B E\) heeft een rechte hoek in \(A\) en de vierhoek \(B C D E\) is een parallellogram.}
\text{name_quest=De hoeken \(\widehat{\ang1}) en \(\widehat{\ang2}) zijn }
#endif
\text{name_ans=Hoeken}
