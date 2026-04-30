!set lang_exists=yes
!!present
!distribute lines We hebben de functie f(x) met de grafiek.\
 We hebben de functie \
 Welke van de volgende grafieken\
 Welke van de volgende functies\
  komt overeen met\
  Klik erop.\
into name_present1,name_present2,name_present3,name_present4, name_present5,\
  name_present6

!!main
!set name_giveup=Verlaat deze sessie

!set name_intro=Deze module helpt je het herkennen van de grafiek bij een\
functie of het herkennen van een functie bij de grafiek.<br/>\
De functies die in deze module aan de orde komen zijn polynomen van de\
tweede orde (ofwel gewoon kwadratische functies).

!distribute lines Je kan deze module naar wens configureren\
  Styl van de Opgaven\
  Moeilijkheidsgraad:\
  Het aantal sommetjes in een enkele sessie\
 \
  aan het einde van de sessie krijg je dan een cijfer.\
into name_choiceintro, name_style,name_level,name_seance,\
  name_questions,name_scoreremark

!set name_prompt=zoek de functie bij een gegeven grafiek,\
    zoek de grafiek van een gegeven functie,\
    willekeurig bepaald door de server

!!form
!distribute lines Klik hier\
 als je denkt dat <b>geen</b> van de aangegeven keuzes correct is.\
 into name_click1, name_click2

!set name_questionnumber=!nosubst Vraag nummer $[$replycnt+1] \
  uit een serie van $repeat opdrachten.


!!answer
!distribute line Jazeker, jouw keuze komt prima overeen met de goede functie.\
   Neem je hebt de verkeerde functie.\
   Neem je hebt het verkeerde plaatje.\
    Nee hoor, het goede antwoord zit wel degelijk tussen de mogelijkheden!\
   Inderdaad, het goede antwoord zit er niet bij, heel goed!!\
   Goed beantwoord.\
   Niet goed beantwoord.\
   Jouw keuze wordt getoond <b>in vette letters</b>,en het goede antwoord is <span style="color:blue">in het blauw</span>\
   Doorgaan met de volgende vraag.\
   Score\
into name_feed1,name_feed2,name_feed3,name_feed4,name_feed5,\
  name_feed6,name_feed7,name_feed8,name_feed9,name_feed10

!set name_answer1=!nosubst opgave nummer $replycnt uit $repeat vragen
!set name_answer2=!nosubst Je moet $repeat vragen beantwoorden voor dat je een cijfer krijgt.
!set name_answer3=!nosubst Je hebt een sessie met $repeat vragen afgerond.\
  Je behaalde score is $module_score uit 10.
!!! no accent in the following
!distribute items Choice,Jouw keuze,Het goed antwoord \
  into name_choice,name_yourchoice,name_goodanswer
