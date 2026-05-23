!set lang_exists=yes

!set name_intro=Een Magisch Vierkant is een tabel van n rijen en n kolommen, \
  gevuld met de getallen 1, 2, ..., \(n^2\) zo dat de som van elke\
  rij en de som van elke kolom gelijk zijn.
!set name_intro2=is een variatie op dit principe

!distribute lines Je ziet hier een tabel van\
  rijen\
  en\
  kolommen\
  met een gegeven getal bij elke rij en kolom\
  Het nu jouw taak om deze tabel in te vullen, waarbij je gebruik moet maken van de getallen 1,2,...,rijen&times;kolommen, zo dat\
  van elke rij en elke kolom gelijk zijn aan het gegeven getal.\
  En je moet dit probleem oplossen binnen de\
  minuten\
  En natuurlijk mag je een getal maar 1 keer gebruiken.\
into name_intro3,name_rows,name_and,name_cols,name_intro4,name_intro5,name_intro6\
  name_intro7,name_minutes,name_intro8

!set n_sum=som
!set n_product=product

!set name_instruction=!nosubst Vul de volgende tabel met de getallen\
  1, 2, ..., $[$cols*$rows]\
  zo dat de  $(n_$kind) van elke rij en van elke kolom gelijk is aan het gegeven\
  blauwe getal.\
  Elk getal mag maar een enkele keer worden gebruikt.

!set name_tester=Test deze Oplossing
!set name_chrono=!nosubst Om een maximale score te bereiken, moet je dit probleem binnen de
!set name_chrono2=Je hebt nog
!set name_second=seconden
!set name_secondplus=oplossen
!set name_start=Start het Spel
!set name_giveup=Laat maar zitten: ik wil de oplossing wel eens zien

!set goed=!randitem Geweldig,Fantasische,heel goed,grandioos,heel mooi,zeer fraai,kan niet beter
!set name_answer=$goed! je hebt met de tabel correct afgemaakt.
!set name_answerchrono=maar je hebt er wel wat langer overgedaan dan we hadden afgesproken...

!set name_answergiveup=jammer, dat je de puzzel niet hebt afgemaakt. \
  Hier staat een oplossing van het probleem\
  (er kunnen meerdere goede oplossingen zijn)

!set name_Score=Je eindresultaat
