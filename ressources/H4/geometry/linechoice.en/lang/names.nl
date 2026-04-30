!set lang_exists=yes

!set t_1=parametrisch

!distribute lines We hebben een rechte lijn in het cartesisch co&ouml;rdinatenstelsel\
    zoals in de onderstaande figuur.\
    Grafiek van de lijn\
    Grafiek van jouw keuze\
    beschreven door de onderstaande parametrische vergelijkingen.\
    beschreveven door de onderstaande vergelijking.\
    Welke van de onderstaande figuren komt overeen met de lijn ? \
    Klik op het plaatje.\
    klik hier\
    als je denkt dat de goede oplossing er niet tussen staat.\
into name_present1,name_present2,name_attribut1,name_attribut2,name_equations,name_equation,\
 name_question1,name_clickon,name_clickhere,name_nochoice

!set name_question2=!nosubst Welke van de volgende $(t_$asktype) vergelijkingen \
komt overeen met deze lijn?
!distribute line Verlaat deze sessie\
  Een nieuwe sessie\
  Verander de oefening\
  een nieuwe oefening\
  Reconfigureer de oefening\
into name_abandon,name_news,name_newexo,name_otherexo,name_reconfig

!set name_intro1=Er zijn een viertal manieren om een lijn (niet door de oorsprong; \
niet verticaal en niet horizontaal) in het cartesisch co&ouml;rdinatenstelsel \
te beschrijven: door een implicite vergelijking, een vergelijking met \(y\) als functie van \(x\), \
een vergelijking van \(x\) als functie van \(y\), of een systeem van parametrische vergelijkingen.

!set name_intro2=Deze oefening kun je gebruiken om te trainen \
  met deze verschillende beschrijvingen van een lijn, als ook met de grafiek van de lijn.

!distribute lines Het kan\
  Je kunt het type vergelijking kiezen\
  \
  Een sessie bestaat uit \
  oefeningen \
  met een cijfer aan het eind van elke sessie\
  vergelijkingen of grafieken worden als keuzes aangeboden, met\
  het goede antwoord\
into name_intro3,name_type,name_chinese,name_session,name_questions,name_Score,\
 name_numberequation,name_good

!set name_prompt1=geef een grafiek en vraag naar de vergelijking,\
	geef de vergelijking en vraag de grafiek te herkennen,\
	geef een vergelijkingsvorm en vraag de andere te herkennen

!set name_prompt2=systeem van parametrische vergelijkingen,implicite vergelijking,\
y als functie van x, x als functie van y

!set name_prompt3=bevat altijd, bevat mogelijk niet

!set name_questionnumber=!nosubst Opgave nummer $[$replycnt+1] uit een sessie van $repeat.
!set name_related=lijnen, grafiek keuzes, vergelijkingen, parametrische vergelijkingen

!set name_answer1=Je keuze is in't <span class="bold">vet</span>, \
 en de goed oplossing is in't <span style="color:blue">blauw</span>.

!distribute lines  Ja, je keuze komt goed overeen met de lijn.\
   Nee, je hebt een andere lijn gekozen.\
   Nee, jouw keuze lijkt op \
   Nee hoor, het goede antwoord staat er gewoon tussen !\
  Heel goed gezien, het goede antwoord staat er inderdaad niet tussen !\
   Goede antwoord\
   Slechte antwoord\
   Cijfer\
   Ga door naar de volgende opdracht.\
into name_answer2,name_answer3,name_answer4,name_answer5,name_answer6,\
 name_goodanswer,name_badanswer,name_score,name_continue

!set name_questionon=!nosubst Opgave nummer $replycnt uit $repeat
!set name_theend=!nosubst Je hebt een sessie van $repeat opdrachten afgerond, met een eind cijfer:
!set name_mustfinish=!nosubst Je moet wel de $repeat opdrachten afronden om een eind cijfer te krijgen.

!! only latin character without accent
!set name_gnuplot_good=Goede antwoord
!set name_gnuplot_choice=Jouw keuze
