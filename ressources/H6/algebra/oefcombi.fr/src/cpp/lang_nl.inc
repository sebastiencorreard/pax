\text{name_answer=Aantal manieren}
#if defined TARGET_tablediner1 || defined TARGET_tablediner2 || defined TARGET_tablediner3 || defined TARGET_tablediner4
\text{name_enonce=<em>hetero</em> paren hebben een etentje. Op hoeveel manieren kunnen deze,
  personen aan één tafel zitten}
# if defined TARGET_tablediner1 || defined TARGET_tablediner2 || defined TARGET_tablediner4
\text{name_question=onder de voorwaarde dat elke heer tussen twee dames moet zitte}
#   if defined TARGET_tablediner2
\text{name_question2= en elke man naast zijn vrouw moet zitten}
#   endif
#   if defined TARGET_tablediner4
\text{name_question2=en dat geen enkele echtgenoot naast zijn eigen echtgenote zit}
#   endif
# endif
# if defined TARGET_tablediner3
\text{name_question2=onder de voorwaarde dat elke vrouw naast haar eigen man moet zitten}
# endif
#endif
#if defined TARGET_Regtriangle
\text{name_enonce=Gegeven is de regelmatige veelhoek (polygoon) met,zijden}
\text{name_question=Hoeveel verschillende driehoeken zijn er, waarvan de 3 hoeken ook hoekpunten zijn
  van polygoo \(P\)}
\text{name_answer=Het aantal verschillende driehoeken}
#endif
#if defined TARGET_boiteslettres
\text{name_question=Op hoeveel verschillende manieren kun je,
  letters op ,leesplankjes leggen}
#endif
#if defined TARGET_bonbon
\text{name_method=elk meisje er op z'n minst één krijgt,
	elke jongen er op z'n minst één krijgt,
	elk kind er op z'n minst één krijgt,
	elk meisje er op z'n minst één en elke jongen er op z'n minst één krijgen,
	elk meisje er op z'n minst twee en elke jongen krijgt er op z'n minst één krijgen,
	elk kind er op z'n minst twee krijgt,
	elk meisje er op z'n minst twee en elke jongen er op z'n minst drie krijgt,
	elk meisje er op z'n minst drie en elke jongen er op z'n minst twee krijgt
}
\text{name_question=Op hoeveel manieren kun je,
  snoepjes verdelen onder, meisjes en , jongens zo dat}
#endif
#if defined TARGET_Doublelangue
\text{name_enonce=In een klas zitten, leerlingen, leerlingen spreken Frans,
  leerlingen spreken Duits. Elke leerling spreekt in elk geval 1 taal: of Frans of Duits}
\text{name_question=We kiezen twee leerlingen uit deze groep van, zo dat er eentje
  Frans spreekt en de andere spreekt Duits.
 Hoeveel mogelijke combinaties zijn er}
\text{name_answer=Aantal keuzemogelijkheden}
#endif
#if defined TARGET_Hotellampe
\text{name_enonce=In een hotel is een lange gang verlicht door een rij van, lampen.}
\text{name_enonce2=In het kader van energie besparing worden,, lampen's nachts uitgeschakeld}
\text{name_question=Voor een minimale verlichting , mogen er geen twee achter elkaar liggende lampen worden gedoofd.
Ook de lampen aan de uiteinden van de gang moeten blijven branden.
Op hoeveel verschillende manieren kan het hotel}
\text{name_lampe=lampen}
#endif
#if defined TARGET_triangline
\text{name_enonce=We hebben twee parallele lijnen in het platte vlak.
  Op de eerste lijn liggen LLLL punten. Op de tweede lijn liggen, MMMM punten.}
\text{name_question=Hoeveel driehoeken kunnen door deze TTTT punten worden gevormd}
\text{name_answer=Aantal driehoeken}
#endif
#if defined TARGET_triangle
\text{name_enonce=We hebben LLLL lijnen in het platte vlak.<br>
  Van deze LLLL lijnen lopen er XXXX door de Oorsprong (0:0).
  Er is geen punt waardoor meer dan twee lijnen lopen.
  Verder zijn er geen lijnen parallel aan elkaar.}
\text{name_question=Hoeveel driehoeken worden door deze,lijnen gevormd}
\text{name_answer=Aantal driehoeken}
#endif
#if defined TARGET_subsets
\text{name_enonce=A finite set \(S\) has,subsets of,elements.
  What is the number of elements of \(S\)}
#endif
#if defined TARGET_rectangle
\text{name_enonce=We hebben XXXX lijnen in het platte vlak, waarvan YYYY horizontaal,
  en ZZZZ vertikaal zijn.}
\text{name_question=Hoeveel rechthoeken worden gevormd door deze,lijne}
#endif
#if defined TARGET_Ordinat1 || defined TARGET_Ordinat2
\text{name_enonce=Een school heeft een computer lokaal met XXXX PC's.
  Een klas van YYYY leerlingen heeft les in dit lokaal.}
# if defined TARGET_Ordinat1
\text{name_question=Op hoeveel verschillende manieren kan elke leerling een
  computer toegewezen krijgen}
# endif
# if defined TARGET_Ordinat2
\text{name_question=Op hoeveel verschillende manieren kunnen we deze leerlingen verdelen over de
  aanwezige PC's, zo dat achter elke PC ZZZZ leerlingen zitten}
# endif
#endif
#if defined TARGET_quadriline
\text{name_enonce=We nemen twee parallele lijnen in het platte vlak. Op de eerste lijn
  zijn XXXX punten, en op de tweede lijn zijn er YYYY punten.}
\text{name_question=Hoeveel vierhoeken kunnen worden gevormd door deze, punten}
\text{name_answer=Aantal vierhoekens}
#endif
#if defined TARGET_partfix
\matrix{name_question=Op hoeveel manieren kunnen we schrijven
  waarin \(n_i\) integers zijn groter of gelijk aan,en gerangschikt in, volgorde}
\text{name_order=toenemende,afnemende}
#endif
#if defined TARGET_n || defined TARGET_nn
\text{name_enonce=Laat \(n\) een positieve integer zijn zo dat}
\text{name_question=Wat is dan de waarde van }
\text{name_answer=Your answer}
#endif
#if defined TARGET_busetconducteu
\text{name_enonce=Een busmaatschappij heeft, bestuurders, controleurs en,bussen}
\text{name_question=Op hoeveel verschillende manieren kunnen ze de bestuurders en controleurs verdelen over de bussen,<br>
  zo dat elke bus één bestuurder en één controleur heeft}
#endif
#if defined TARGET_committee
\text{name_question=In een klas zitten YYYY meisjes en XXXX jongens.
  Op hoeveel verschillende manieren kunnen we een klasse commissie
  samenstellen met CCCC deelnemers uit deze groep leerlingen,
  onder voorwaarde dat er tenminste BBBB en GGGG zitting nemen in deze commissie}
\text{name_answer=Aantal mogelijkheden}
\text{name_gb=jongen,meisje}
\text{name_gbs=jongens,meisjes}
#endif
#if defined TARGET_intersection || defined TARGET_intersection2 || defined TARGET_intersection3
\text{name_enonce=In het platte vlak hebben twee rechte lijnen maximaal één snijpunt.}
\text{name_question=Hoeveel snijpunten zijn er maximaal tussen,rechte lijnen}
\text{name_answer=Maximaal aantal snijpunten}
# if defined TARGET_intersection2
\text{name_question1=waarvan er,,  zijn en dus parallel}
\text{name_dir=horizontaal,vertikaal}
# endif
# if defined TARGET_intersection3
\text{name_question1=waarvan erh, door de oorsprong (0:0) gaan }
# endif
#endif
#if defined TARGET_posneg
\text{name_enonce=Laat \(S\) een set zijn van, positieve integers en,
  negatieve integers. De absolute waarde van deze, integers
  zijn priem getallen.}
\text{name_question=Wat is het aantal, van twee verschillende getallen uit \(S\)}
\text{qlist=negatieve getallen welke producten zijn,
positieve getallen welke producten zijn,
negatieve rationele getallen welke quoti&euml;nten zijn,
positieve rationele getallen welke quoti&euml;nten zijn}
\text{name_answer=Het aantal}
#endif
#if defined TARGET_party
\text{name_enonce=XXXX paren en YYYY niet-getrouwde personen ontmoeten elkaar op een feestje.
  Elke feestgangen schud één keer de hand van een andere feestganger,
  behalve de getrouwde paren, deze schudden natuurlijk geen handen met elkaar...}
\text{name_question=Hoeveel "handcontacten" vonden er plaats}
\text{name_answer=Aantal "handcontacten"}
#endif
#if defined TARGET_couples
\text{name_question=Op hoeveel manieren kunnen we een,
  heteroparen vormen uit ,mannen en and, vrouwen}
#endif
#if defined TARGET_groupement
\text{name_question=Op hoeveel manieren kunnen we een klas van ,
  leerlingen opsplitsen in, groepjes van elk , leerlingen}
#endif
#if defined TARGET_helico
\text{name_enonce=Een vliegmaatschappij heeft,helicopters. Als personeel hebben ze,
  piloten en, stewardessen in dienst.}
\text{name_question=Op hoeveel verschillende manieren kunnen ze de piloten en stewardessen
  verdelen over de helicopters, zo dat elke helicopter één
  piloot en twee stewardessen aan boord heeft}
#endif
#if defined TARGET_mots
\text{name_question=Hoeveel verschillende woorden kunnen worden gevormd uit de TTTT eerste letters
  van het alfabet, met als voorwaarde dat elke letter maar één keer mag voorkomen
  in elk woord, en dat de AAAA eerste letters {BBBB} ls groep moeten voorkomen
  in elk woord}
\text{name_hint=Bekijk de, eerste letters eerst als één element.}
\text{name_answer=Aantal woorden}
#endif
#if defined TARGET_monom3 || defined TARGET_monom4
\text{name_question=Hoeveel integers zijn er in de vorm,
  met daarin de niet-negatieve exponenten,
  waarvoor geldt}
\text{name_answer=Het aantal integers}
\text{name_hint=De basis getallen XXXX zijn relatief priem,
  en deze integers zijn verschillend bij de keuzes van XXXX.
  Dus is het afdoende uit te rekenen}
#endif

