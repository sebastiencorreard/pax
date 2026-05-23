!set lang_exists=yes
!set name_intro=is oefening, waarbij je in een plaatje op het centrum van\
  de rotatie moet aanklikken.

!distribute lines Je mag het moeilijkheids niveau aangeven\
  en het aantal keer klikken per sessie:\
  Na afloop van de oefening krijg je een cijfer.\
  Hier is je antwoord, samen met het echte rotatie centrum.\
  red,originele vorm\
  green, edraaide vorm\
  hier heb je geklikt,het echte rotatiecentrum\
  Gemiddelde precisie\
  De volgende Poging\
  Opnieuw\
  Reconfigureer de oefening\
  Score\
  Résumé of the shots of the session\
into name_introlevel, name_introcount, name_introscore,\
  name_answer,name_red,name_green,name_answer2,name_ecart2,\
  name_next,name_again, name_configure, name_score,name_resume

!set name_present=Hier zie je een tweetal vormen in verschillende kleuren.\
  De ene vorm ontstaat door rotatie -in het plattevlak- uit de andere.\
  Je moet klikken op het centrum van de rotatie

!set name_consigne=Je antwoord is dus een klik in het plaatje, op de plek \
  waar je het centrum van de rotatie verwacht.

!set name_ecart=!nosubst Precisie ( $reply_cnt uit $shoots)

!set name_end=!nosubst Einde van deze sessie, je hebt $reply_cnt pogingen gedaan.\
  Gemiddelde precisie
!set name_help=Het rotatiecentrum is het midden tussen twee "gelijke" punten \
  op twee vormen
