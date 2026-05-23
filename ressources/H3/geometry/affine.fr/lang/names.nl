!set lang_exists=yes

!set name_intro=is een oefening over grafieken bij lineaire formules \
 Je wordt gevraagd punten in de grafiek bij een lineaire formule aan te geven.

!set name1=een formule
!set name2=een richtingscoefficient en een functiewaarde
!set name3=een richtingscoefficient $a en een invers beeld
!set name4=een lineaire functie en een functiewaarde
!set name5=een lineaire functie en een invers beeld

!distribute lines Klik op een punt van de lijn\
  Klik op een tweede punt van de lijn\
  De door jou gegeven punten liggen veel te dicht bij elkaar, overdoen dus.\
into name_clickpoint,name_clickpoint2,name_msg

!distribute lines lineair gegeven door,lineair door de oorsprong\
  gehele getallen, breuken, decimale getallen\
\
  De co&euml;fficienten zijn \
into name_intro_afflin, name_typenumber,name_givenby,name_coefficienttype

!distribute lines Geef twee punten van de grafiek van de lineaire formule\
  Geef twee punten van de grafiek van de lineaire formule \
  \
  Geef twee punten van de grafiek van de lineaire formule\
into name_rep,name_traceraffine,name_lineaireassoc,name_clicktwopoints

!set name_direct=!nosubst met hellingsgetal rc = $a en zo dat het beeld van $A gelijk is aan $B.
!set name_indirect=!nosubst met hellingsgetal rc = $a  en zo dat $B het beeld is van $A.
!set name_applindir=!nosubst voor een nog onbekende b zo dat $B het beeld is van $A.
!set name_applinante=!nosubst voor een nog onbekende b zodat het beeld van $A gelijk is aan $B.

!distribute lines Heel goed.\
  Je antwoord is getekend in rood, het correcte antwoord is getekend in groen.\
  één van je punten ligt niet op de rechte lijn.\
  beiden punten liggen niet op de lijn.\
  jouw lijn loopt parallel aan de correcte lijn.\
  de constante van je lijn is wel goed, de richtingsco&euml;fficient is fout.\
  De grafiek van de lijn gaat altijd door de oorsprong (O).\
into name_answergood,name_redgreen,name_outline,name_nopoints, name_parallel,\
  name_ordonnee,name_origin

!set name_score=!nosubst Je score is $module_score (uit 10).
