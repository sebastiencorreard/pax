\text{name_hkm=uur,km,km/uur}

#if defined TARGET_arret
\matrix{name_enonce=De reactietijd van een rijder is
  Bij een nat wegdek zijn de remafstanden
  hoger. Vul de tabel in (er is hulp).
  De afstanden worden op een decimaal naar boven afgerond.}
\text{name_header=snelheid van de auto in km/h,
  afstand in m afgelegd tijdens de reactietijd,
  remafstand in m bij een droog wegdek,
  afstand tot stilstand in m bij een droog wegdek,
  remafstand in m bij een nat wegdek,
  afstand tot stilstand in m bij een nat wegdek}
\text{name_seconde=seconde,seconden}
\text{name_help1=Tussen het tijdstip waarop de rijder een obstakel ziet en het tijdstip waarop
  hij begint te remmen, zit de <span class="defn"><b> reaktietijd</b> </span>.
  Dit is de tijd die nodig is voor het signaal om van de zenuwen van het oog
  (receptie orgaan) naar die van de hand die aan de rem trekt of naar de voet die op de rempedaal trapt (uitvoerend orgaan) te gaan.}
\text{name_help2=De afstand die tijdens de reaktietijd doorlopen wordt is een functie van de
  snelheid van de auto. De reaktietijd is langer of minder lang naar gelang de
  individu, zijn vermoeidheid. De gemiddelde lengte is 1 à 3 seconden.}
\text{name_help3=Tussen het tijdstip waarop de rijder de rem activeert en dat waarop de auto
  stilstaat, wordt een afstand doorlopen die de
  <span class="bold"><b> remafstand</b></span> heet. De remafstand hangt
  van de auto af (staat van de remmen), van de snelheid, het wegdek (glad,nat, droog, ijzel).}
\text{name_help4=De <span class="defn"> <b>afstand tot stilstand </b></span>
  is de som van de afstand die doorlopen is tijdens de reaktietijd en de remafstand.}
#endif
#if defined TARGET_impot
\text{name_enonce=Vous êtes, sans enfant,avec, enfants, à charge, vous avez donc droit à,
  part,parts}
\text{name_question=Calculez l'impôt pour un revenu,en,
  en utilisant le graphique de la fonction impôt qui est formé de segments,
  et d'une demi-droite à partir du point,Les coordonnées sont les suivantes}
\text{name_hint=Il faut calculer le coefficient directeur \(coeff\) de la droite}
\text{name_answer=impôt arrondi à 0.01 près}
\text{name_etat=célibataire,marié}
#endif
#if defined TARGET_trajet
\text{name_heuv=Tijd, Snelheid}
\text{name_enonce=Anne moet de afstand van, km doorlopen volgens het
volgende grafiek}
\matrix{name_question1=Lees het diagram
  Hoe lang stopt zij onderweg
  Hoe lang na haar vertrek neemt zij haar eerste pauze
  Hoeveel km heeft ze dan gereden}
\matrix{name_question2=Het einde van het traject (na de tweede pauze) heeft ze gereden met een gemiddelde snelheid gehad van
  Hoe laat komt ze aan, Ze komt om XXXX aan
  Met welke gemiddelde snelheid heeft ze het einde van het traject (na de tweede pauze) gereden}
\text{name_question3=Ze komt dus om,
 uur aan met een gemiddelde snelheid voor laatste stuk van,
 Wat is haar gemiddelde snelheid voor het hele traject}
\text{name_instruction=Rond de snelheden naar boven af op de eenheid (in km/h).
  Schrijf de tijden als uren en minuten,
  bijvoorbeeld als 120 min of 2u 30 min.}
\text{name_answer=Duur van de pauze,pauze,Aantal km}
#endif
#if defined TARGET_vitesse
\text{name_enonce=Een motorfietser rijdt,met een snelheid van,
  en,met een snelheid van}
\text{name_question1=Wat is zijn gemiddelde snelheid}
\text{name_enonce2=Wat is zijn gemiddelde snelheid, Zijn gemiddelde snelheid over het geheel is,
  QWat is zijn gemiddelde snelheid over het laatste stu}
\text{name_instruction=De resultaten worden gegeven met één cijfer achter
  de comma, en in km/u. Schrijf de eenheid erbij.}
\text{name_answerGemiddelde snelheid,
  Snelheid in het laatste stuk}
#endif
#if defined TARGET_vitesse2
\text{name_enonce=Een automobilist vertrek van zijn huis om XXXX \name_hkm[1], zijn
kilometerteller geeft YYYY \name_hkm[2] aan. Hij komt om ZZZZ \name_hkm[1] terug, de teller
staat dan op TTTT \name_hkm[2].}
\text{name_question=Welke afstand heeft hij gereden,
  PHoe lang heeft hij gereden}
\matrix{name_question2=Inderdaad, hij heeft
  gereden, in
  Wat was zijn gemiddelde snelheid, per uur}
\text{name_instruction=Afspraak : geef de eenheden aan.}
\text{name_answer=De afgelegde afstand is,
  Hij heeft,
  Zijn gemiddelde snelheid is}
\text{name_hint1=De afgelegde afstand is het verschil tussen wat de teller
  bij aankomst aangeeft en wat hij bij vertrek aangaf.}
\text{name_hint2=De duur van het traject is het verschil tussen de tijd van
  aankomst en de tijd van vertrek.}
\text{name_hint3=De gemiddelde snelheid per uur is de afgelegde afstand gedeeld
  door de tijd die hij gereden heeft}
#endif
#if defined TARGET_vitesse12
\text{liste=ja, nee}
\text{name_list=gedurende, met een snelheid van, gedurende}
\text{name_enonce=Meneer Snel vertrekt van Amsterdam om, uur en rijdt eerst,
  vervlogens, en daarna}
\text{name_question=Hoeveel kilometers heeft hij afgelegd (naar boven afgerond tot op een nauwkeurigheid van 0.01),
  Hij heeft XXXX km een afgelegd.,
  Hoeveel tijd heeft hij over het traject gedaan,
  Zijn traject heeft YYYY geduurd.,
  Wat was zijn gemiddelde snelheid over de hele rit,
  Zijn gemiddelde snelheid over de hele rit is,
  Hij heeft om ZZZZ uur een afspraak. Zal hij op tijd zijn}
\text{name_instruction1=Afspraak: geef de eenheden aan: bijvoorbeeld 3 km, 5 km/h , 1h 32min}
\text{name_instruction2=laat een spatie tussen de uren en de minuten}
\text{name_hint1=We berekenen de afstand vanaf de tijd voor het traject
  (in uren) en de snelheid met behulp van de relatie \(a=s*t\)}
\text{name_hint2=Of hij wel of niet op tijd aankomt hangt van zijn
  aankomsttijd af, en dus van de tijd die hij over het traject doet}
\text{name_answer=Afgelegde afstand,Duur van het traject,Gemiddelde snelheid}
\text{name_feed=De duur van zijn traject is,
  Hij komt dus om, ann wat,
  ,vor, na,het tijdstip van zijn afspraak is}
#endif
