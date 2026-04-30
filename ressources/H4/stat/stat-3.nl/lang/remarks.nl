:kaartleggen, bereken de kans.
:&nbsp;Boer
:&nbsp;Vrouw
:&nbsp;Heer
:&nbsp;Aas
: Ik heb een volledig pakje kaarten. (52 kaarten)<br />Ik schud ze goed door elkaar...<br />en pak vervolgens $[$k+1] kaarten van het stapeltje af<br />en draai er $k om...<br />Hoe groot is nu de kans dat de nog niet omgedraaide kaart een <em>$naam $num</em> is ?<br />
: De kans op een $naam $num uit een stapeltje kaarten is natuurlijk 1/52<br />Liggen er al $k andere kaarten op tafel -er zijn dus in het spel kaarten nog 52-$k over)<br />is de kans op een bepaalde kaart 1/(52-$k) = 1/$[52-$k] =$(answer$n) of afgerond $GG .
: Ik heb twee kaarten omgedraaid...<br />Er zijn $mogelijkheden manieren om twee kaarten te pakken waarvan de som $som is...<br /><small><em>zie de tabel in de help-pagina</em></small><br />De kans is dan: $mogelijkheden &times; (4/52) &times; (4/51) = $mogelijkheden &times; 4/663 = $(answer$n)
: Ik heb twee kaarten omgedraaid...<br />Er zijn $mogelijkheden manieren om twee kaarten te pakken waarvan de som $som is...<br /><small><em>zie de tabel in de help-pagina</em></small><br />Omdat de som van de kaarten ($som) even is,<br />is er &eacute;&eacute;n mogelijkheid waarbij je twee kaarten pakt met de zelfde waarde...<br />De kans is dan: ( $mogelijkheden - 1) &times; (4/52) &times; (4/51) + (4/52)&times;(3/51) = $[$mogelijkheden-1] &times; 4/663 + 1/221 = $(answer$n)
: Van een goed geschud pakje kaarten, bestaand uit 52 kaarten, pak ik de eerste twee kaarten.<br />Hoe groot is de kans dat de waarde van twee omgedraaide kaarten samen $som is?<br /><small>Let op: De waarde van een Boer=11 ; een Vrouw=12 ; een Koning=13 en een Aas=1</small><br /><br />Zoals <em>bijvoorbeeld</em> in deze combinatie:<br />$kaarten
: Ik leg $k kaarten uit een volledig setje kaarten op tafel. Het volledige setje bestaat uit 52 kaarten.<br /> Ik draai er $[$k - $opkop] om.<br />Hoe groot is de kans dat de nog niet omgedraaide $opkop kaarten de volgende combinatie heeft?<br /><small>$NAAM</small><br /><small>de volgorde van deze $opkop kaarten doet er niet toe</small><br />$kaarten
: de kans op de $N kaart is 1/$[$over-$p+1]<br />
: Ik heb $[$k-$opkop] kaarten omgedraaid...er zitten nog $over kaarten in het pak<br />$extratext<br />en dus is de kans $opkop ! $berekening = $(answer$n) en afgerond $GG
: Kijk hier <img src=\'$gifdir/help.jpg\' alt=\'help\' /> voor een voorbeeld setje kaarten...
: Bereken de Kans op Zwart of Rood
: zwart , rood
: Ik heb een goed geschud pakje eerlijke kaarten. Het pakje bestaat uit 52 kaarten.<br />Ik pak $tot kaarten van het stapeltje en leg ze op tafel.<br />Ik draai er $aantal om. (Zie plaatje)<br />Hoe groot is de kans dat de $F nog niet omgedraaide kaarten allemaal <em>$kleur</em> zijn ?<br />
: Er lagen $zz zwarte kaarten en $rr rooie kaarten omgedraaid op de tafel<br />De kans dat de $F kaarten ,die nog niet waren omgedraaid, allemaal $kleur zijn , is $(answer$n) (afgerond ongeveer $GG )<br />Deze kun je als volgt uitrekenen:<br />
: We hebben 26 zwarte kaarten in een spelletje.<br />Er liggen al $zz zwarte kaartenomgedraaid op tafel.<br />Dus we hebben nog 26-$zz=$t1 zwarte kaarten over.<br />We hebben 26-$rr = $t2 rooie kaarten over.<br />We hebben in het totaal 52-($rr+$zz) = $t3 niet-omgedraaide kaarten<br />Dus:<br />  
: Ik heb een goed geschud pakje eerlijke kaarten. (52 kaarten)<br />Ik pak $tot kaarten van het stapeltje en leg ze op tafel.<br />Ik draai er $aantal om. (Zie plaatje)<br />Hoe groot is de kans dat er van de $F nog niet omgedraaide kaarten $r rood zijn en $z zwart ?
: Bereken de Kans op ?
:harten,ruiten,klaver,schoppen 
: We hebben een goed geschud normaal pakje spelkaarten. (52 kaarten)<br />We pakken de bovenste $F kaarten van het stapeltje.<br /> Hoe groot is de kans dat deze $F kaarten bestaan uit <b>$rr rooie en $zz zwarte</b> kaarten  ?<br />
: De kans is op $rr rooie en $zz zwarte kaarten is $(answer$n) , afgerond ongeveer $GG <br />Deze kun je als volgt uitrekenen:<br />
: We hebben een goed geschud normaal pakje spelkaarten. (52 kaarten)<br />We pakken de bovenste $F kaarten van het stapeltje.<br />Hoe groot is de kans op <b>$rr $kaart1 en $zz $kaart2</b> kaarten  ?<br />
: De kans is $(answer$n) , afgerond ongeveer $GG <br />Deze kun je als volgt uitrekenen:<br />
: Ik heb een goed geschud eerlijk setje kaarten. Dit setje bestaat uit 52 kaarten.<br />Ik pak $tot kaarten van het stapeltje en leg ze op tafel.<br />Hoe groot is de kans dat deze $F kaarten bestaan uit:<br /><ul><li>$HH $kaart1</li><li>$RR $kaart2</li><li>$KK $kaart3</li></ul><br />
: Ik heb een goed geschud eerlijk setje kaarten. Dit setje bestaat uit 52 kaarten.<br />Ik pak $tot kaarten van het stapeltje en leg ze op tafel.<br />Hoe groot is de kans dat deze $F kaarten bestaan uit:<br /><ul><li>$HH $kaart1</li><li>$RR $kaart2</li><li>$KK $kaart3</li><li>$SS $kaart4</li></ul><br />
: Er zijn maar twee kleuren...rood en zwart.<br />Van beide kleuren zitten er 26 in een pakje.<br />De kans is dus fifty fifty. Dus de kans is 1/2.
: Er zitten vier soorten kaarten in een setje.<br />Te weten: klaver,harten,schoppen en ruiten.<br />Van alle vier soorten heb je er evenveel, nl. 13.<br />De kans is dus 1/4. 
: Je hebt een volledig setje kaarten. Dit setje bestaat uit 52 kaarten.<br />Je schudt ze goed door elkaar en pakt vervolgens &eacute;&eacute;n kaart van het stapeltje.<br />Hoe groot is de kans dat deze kaart $soort is ?
: Je hebt een volledig setje kaarten. Dit setje bestaat uit 52 kaarten.<br />Je schudt ze goed door elkaar en pakt vervolgens $t1 kaarten van het stapeltje.<br />Hoe groot is de kans dat deze kaarten $soort zijn ?
:groter,kleiner
: Je heb een volledig pakje kaarten. Dit pakje bestaat uit 52 kaarten.<br />Elke kaart telt als z'n nummer. <br />Verder geldt: een Boer=11,Vrouw=12,Heer=13 en een Aas=1</em></small><br />Je schud ze goed door elkaar en pak vervolgens &eacute;&eacute;n kaart van het stapeltje<br />Hoe groot is de kans dat die kaart $kleiner is dan $keuze ?
: Je hebt 4 keer $[$keuze -1] kaarten kleiner dan $keuze . <br /> [5~P(kaart&lt; $keuze)=$[4*($keuze -1)]/52= $(answer$n)
: Je hebt 4 keer $[13 - $keuze] kaarten groter dan $keuze . <br /> P(kaart&gt; $keuze)=$[4*(13- $keuze)]/52= $(answer$n)
: kaartleggen, bereken de kans met terugleggen.
:Azen,Koningen,Vrouwen,Boeren,Harten,Ruiten,Klaver,Schoppen
: We hebben in ons stapeltje 16 kaarten.<br />Hierin zitten vier $soort .<br />De kans op bijvoorbeeld &eacute;&eacute;n van de $aantal is 1/4<br />De kans op $aantal is dan (1/4)<sup>$aantal</sup>  &asymp; $GG
: $kleur kaarten.
: We hebben in ons stapeltje 16 kaarten.<br />Hierin zitten acht $kleur .<br />De kans op &eacute;&eacute;n $kleur is 1/2<br />De kans op $aantal $kleur is dan (1/2)<sup>$aantal</sup> &asymp; $GG
: We hebben een pakje normale spelkaarten. We maken alleen gebruik van:<table><tr><td><ul><li>de Boer</li><li>de Vrouw</li><li>de Koning</li><li>de Aas</li></ul><br />De rest van de kaarten gebruiken we nu niet...</td><td><img src="$module_dir/cards/00.gif" alt="noalt" /></td></tr></table>We trekken &eacute;&eacute;n voor &eacute;&eacute;n $aantal kaarten uit het stapeltje.<br />Na elke trekking stoppen we de getrokken kaart terug in het stapelje en schudden opnieuw...<br /><small>dit heet dus <em>"trekken met terugleggen"</em></small><br />Bereken de kans op $hoeveel $kaart .     
: Aas,Koning,Vrouw,Boer
: We hebben in ons stapeltje 16 kaarten.<br />De kans op bijvoorbeeld &eacute;&eacute;n $soort is 1/4<br />De kans op &eacute;&eacute;n <kbd>g&eacute;&eacute;n</kbd>$soort is dan 1 - 1/4 = 3/4<br />We kunnen de $soort op $aantal manieren pakken; dus de kans wordt $aantal&times;0.25&times;0.75<sup>$h</sup>=$(answer$n) &asymp; $GG
: We hebben een pakje normale spelkaarten.We maken alleen gebruik van:<table><tr><td><ul><li>de Boer</li><li>de Vrouw</li><li>de Koning</li><li>de Aas</li></ul><br />De rest van de kaarten gebruiken we nu niet...</td><td><img src="$module_dir/cards/00.gif" alt="noalt" /></td></tr></table>We trekken &eacute;&eacute;n voor &eacute;&eacute;n $aantal kaarten uit het stapeltje.<br />Na elke trekking stoppen we de getrokken kaart terug in het stapelje en schudden opnieuw...<br /><small>dit heet dus <em>"trekken met terugleggen"</em></small><br />Bereken de kans op &eacute;&eacute;n $soort en $hoeveel andere kaarten <em>(niet $soort , dus)</em> .     
:Azen,Koningen,Vrouwen,Boeren
: We kunnen de $soort op "$aantal boven $p" manieren (op de  grafische rekenmachine: <kbd>$aantal ncr $p</kbd>) pakken.
: We hebben een pakje normale spelkaarten. We maken alleen gebruik van:<br /><table><tr><td><ul><li>de Boer</li><li>de Vrouw</li><li>de Koning</li><li>de Aas</li></ul><br />De rest van de kaarten gebruiken we nu niet...</td><td><img src="$module_dir/cards/00.gif" alt="noalt" /></td></tr></table>We trekken &eacute;&eacute;n voor &eacute;&eacute;n $aantal kaarten uit het stapeltje.<br />Na elke trekking stoppen we de getrokken kaart terug in het stapelje en schudden opnieuw...<br /><small>dit heet dus <em>"trekken met terugleggen"</em></small><br />Bereken de kans op $hoeveel1 $soort en $hoeveel2 andere kaarten <em>(niet $soort , dus)</em> .     
: Dobbelstenen en bereken de Kans op ?
: en,een
: Ik heb $numdobbel eerlijke dobbelstenen<br />Hoe groot is de kans op:<br /> $dobbel ?<br />De volgorde doet er niet toe !<br />
: Ik heb twee eerlijke dobbelstenen.<br />Hoe groot is de kans op een totaal score van $dob ogen?
:minstens,maximaal
: Ik heb twee eerlijke dobbelstenen.<br />Hoe groot is de kans op een totaal score van <b>$maximaal</b> $dob ?
: Ik heb drie eerlijke dobbelstenen.<br />Hoe groot is de kans op een totaal score van $dob ogen? 
: Zoals bijvoorbeeld<br />$dice
: Oneerlijke dobbelstenen en bereken de Kans op ?
: Ik heb een <b>oneerlijke</b> dobbelsteen<br /><table><tr><td>De kans op een <b>$zes</b> bij deze dobbelsteen is:</td><td><img src="$module_dir/gifs/$PL.gif" alt="noalt" /></td></tr><tr><td>de kans op de andere ogen , behalve $een , is gewoon:</td><td><img src="$module_dir/gifs/1:6.gif" alt="noalt" /></td></tr></table><br />Hoe groot is de kans op een <b>$een</b> bij deze dobbelsteen?<br />
: Die kans is dus $(answer$n)
:red@rooie,blue@blauwe,green@groene,yellow@gele
: Trekken zonder terugleggen
:vaas,bak,aquarium,bakje,schaal,doos,kistje,zak
:ballen,knikkers,kogels,kogeltjes,stuiters,kauwgomballen
: We hebben een $vaas met $a $kleur1 en $b $kleur2 $ballen .<br />Je trekt er <em>aselect</em> $aantal $ballen uit <em>zonder terugleggen</em>.<br />Wat is de kans bij deze trekking op $aantal $kleur $ballen .<br /><small><em>Rond af op tenminste 4 decimalen</em></small>
: We hebben een $vaas met $a $kleur1 en $b $kleur2 $ballen .<br />Je trekt er <em>aselect</em> $[$aantal+1] $ballen uit <em>zonder terugleggen</em>.<br />Wat is de kans bij deze trekking op &eacute;&eacute;n  $kleur1 en $aantal $kleur2 $ballen .<br /><small><em>Rond af op tenminste 4 decimalen</em></small>
: We hebben een $vaas met $a $kleur1 en $b $kleur2 $ballen .<br />Je trekt er <em>aselect</em> $[$a1+$b1] $ballen uit <em>zonder terugleggen</em>.<br />Wat is de kans bij deze trekking op $a1 $kleur1 en $b1 $kleur2 $ballen .<br /><small><em>Rond af op tenminste 4 decimalen</em></small>
:hoogstens,ten minste
:We hebben een $vaas met $a $kleur1 en $b $kleur2 $ballen .<br />Je trekt er <em>aselect</em> $aantal $ballen uit <em>zonder terugleggen</em>.<br />Wat is de kans bij deze trekking op <b><kbd>$hoogstens</kbd></b> $a11 $kleur1 ?<br /><small><em>Rond af op tenminste 4 decimalen</em></small>
: Trekken met terugleggen
: We hebben een $vaas met $a $kleur1 en $b $kleur2 $ballen .<br />Je trekt er <em>aselect</em> $aantal $ballen uit <em>met terugleggen</em>.<br />Wat is de kans bij deze trekking op $aantal $kleur $ballen .<br /><small><em>Rond af op tenminste 4 decimalen</em></small>
: We hebben een $vaas met $a $kleur1 en $b $kleur2 $ballen .<br />Je trekt er <em>aselect</em> $[$aantal+1] $ballen uit <em>met terugleggen</em>.<br />Wat is de kans bij deze trekking op &eacute;&eacute;n  $kleur1 en $aantal $kleur2 $ballen .<br /><small><em>Rond af op tenminste 4 decimalen</em></small>
: We hebben een $vaas met $a $kleur1 en $b $kleur2 $ballen .<br />Je trekt er <em>aselect</em> $[$a1+$b1] $ballen uit <em>met terugleggen</em>.<br />Wat is de kans bij deze trekking op $a1 $kleur1 en $b1 $kleur2 $ballen .<br /><small><em>Rond af op tenminste 4 decimalen</em></small>
: We hebben een $vaas met $a $kleur1 en $b $kleur2 $ballen .<br />Je trekt er <em>aselect</em> $aantal $ballen uit <em>met terugleggen</em>.<br />Wat is de kans bij deze trekking op <b><kbd>$hoogstens</kbd></b> $a11 $kleur1 ?<br /><small><em>Rond af op tenminste 4 decimalen</em></small>
: Permutaties en Combinaties
: studenten,leerlingen,amateur voetballers,volleyballers,krantenjongens,krantenmeisjes,oud leerlingen,buurtbewoners,camping gasten
: party,feest,fuif,avondje,gala avond,barbecue,bonte avond,swing feest,beachparty
: financi&euml;en,muziek,drank,hapjes,schoonmaken,vervoer
: $aantal $leerlingen willen een $feest organiseren .<br />Voor de organisatie hiervan zijn $num personen uit deze groep $leerlingen nodig.<br />De volgende taken worden verdeeld onder deze $num personen:<ul>$zaken</ul>Op hoeveel manieren kunnen we $num personen kiezen uit deze groep van $aantal $leerlingen ?
: $aantal $leerlingen willen een $feest organiseren .<br />Voor de organisatie hiervan zijn $num personen uit deze groep $leerlingen nodig.<br />Hoeveel verschillende groepen van $num personen kunnen we samenstellen<br /> uit deze groep van $aantal $leerlingen ?
: personen voor 
: $aantal $leerlingen willen een $feest ...<br />Ze spreken af dit met <em>z'n allen</em> te organiseren.<br />De volgende $num taken worden verdeeld onder deze $aantal $leerlingen:<ul>$zaken</ul><br />Op hoeveel manieren kunnen we $aantal $leerlingen verdelen over $num taken ??
: Permutaties
: Hoeveel verschillende woorden van $NUM letters kun je uit $AANTAL letters maken?<br />We maken gebruik van de letters: <br /><table class="grid_table"><tr><th>$letters</th></tr></table>Een zelfde letter mag meerdere keren voorkomen in een "woord".<br />Zo'n woord hoeft geen ree&euml;le betekenis te hebben,<br /><b>$bijvoorbeeld</b> is bijvoorbeeld ook een "woord" van $NUM letters.
: Hoeveel verschillende woorden van $NUM letters kun je uit $AANTAL letters maken?<br />We maken gebruik van de letters: <br /><table class="grid_table"><tr><th>$letters</th></tr></table>Een letter mag maar &eacute;&eacute;n keer in een woord gebruikt worden.<br />Zo'n woord hoeft geen ree&euml;le betekenis te hebben,<br /><b>$bijvoorbeeld</b> is bijvoorbeeld ook een "woord" van $NUM letters.
:banketstaaf,chocolade,marsepein,witte chocolade,pure chocolade,hazelnoot chocolade
: We hebben $AANTAL $chocolade letters, nl de letters:<br /><table class="grid_table"><tr><th>$letters</th></tr></table>Je mag er $NUM uit kiezen.<br />Hoeveel keuze mogelijkheden heb je?
: Hoeveel verschillende woorden van $NUM letters kun je uit onderstaande $AANTAL letters maken?<br />We maken gebruik van de letters: <br /><table class="grid_table"><tr><th>$letters</th></tr></table>Elke letter van de $AANTAL letters mag maar &eacute;&eacute;n keer in een woord gebruikt worden.<br />Zo'n woord hoeft geen ree&euml;le betekenis te hebben.
: Een kans is een getal tussen 0 en 1 en geen percentage.<br /><small>alhoewel we het daar in het dagelijks leven niet zo nauw mee nemen.</small>
: Een kans die groter is dan &eacute;&eacte;n is wel een beetje vreemd.<br />De kans is per definitie <b>0 &lt; P &lt; 1</b><br />Reken je zaakjes nog eens even na.
: Een kans die kleiner is dan nul is een beetje vreemd.<br />De kans is per definitie <b>0 &lt; P &lt; 1</b><br />Reken je antwoord nog eens even na.
: Een kans is geen percentage (je hebt dan ook geen %-teken ingevuld...).<br />De kans is per definitie <b>0 &lt; P &lt; 1</b>Kijk nog eens even goed naar je berekeningen
: Een kans is geen percentage (je hebt dan ook geen %-teken ingevuld...).<br />De kans is per definitie <b>0 &lt; P &lt; 1</b><br />Probeer het nog eens.
: en ook op $factor1 decimalen nauwkeurig...
: je mocht hier afronden op <b>minimaal</b> $factor2 decimalen<br />Ik zie hier dat je hebt afgerond op maar $factor1 decimalen...<br />Ik zou daar nog maar eens even naar kijken (want $(reply$n) reken ik <em>echt</em> fout)
: <br /><small>Je hebt -waarschijnlijk-  een percentage opgeschreven i.p.v. een Kans<br />De kans is namenlijk per definitie <b>0 &lt; P &lt; 1</b><br />Bij een examen krijg je hiervoor absoluut strafpunten.<br />(en zeker als je dan ook nog het %-teken vergeet...)</small>
: <br />prima, je hebt de kans als breuk uitgerekend !!<br />
: Je hebt een paar rekenfoutjes gemaakt, en zit er een ordegrootte naast...
: zwarte , rode
:In een $vaas zitten $aantal_b $ballen , genummerd:<table><tr><td><kbd>$lijst</kbd></td></tr></table><kbd>X</kbd> is het getrokken nummer bij een trekking.<br />Hoe groot is de <em>verwachtingswaarde</em> van de toevalsvariabele (<em>Stochast</em>) <kbd>X</kbd>?<br />en hoe groot is de <em>Standaard afwijking</em> &#963; ?
:Verwachtingswaarde E(X) :
:Standaard afwijking &#963; (S) :
:In een $vaas zitten $aantal_b $ballen , genummerd:<table><tr><td><kbd>$lijst</kbd></td></tr></table>Jij trekt uit de $vaas $aantal_c $ballen <em>met terugleggen</em>.<br />S is de som van de $aantal_c getrokken nummers.<br />Hoe groot is de <em>verwachtingswaarde</em> van de toevalsvariabele <kbd>S</kbd>?<br />en hoe groot is de <em>Standaard afwijking</em> &#963; ?
:Verwachtingswaarde E(S) :
:In een $vaas zitten $aantal_b $ballen , genummerd:<table><tr><td><kbd>$lijst</kbd></td></tr></table>Jij trekt uit de $vaas $aantal_c $ballen <em>met terugleggen</em>.<br />S is het gemiddelde van de $aantal_c getrokken nummers.<br />Hoe groot is de <em>verwachtingswaarde</em> van de toevalsvariabele <img src="$module_dir/gifs/barX.gif" alt="noalt" /> ?<br />en hoe groot is de <em>Standaard afwijking</em>?
:Verwachtingswaarde 
:Standaard afwijking
:Hij,hij,hem,zijn
:Zij,zij,haar,haar
:Het goede antwoord is:
:broer,zus,vriend,vriendin,oom,tante,neef,nicht
:$naam heeft $A boeken in $zijn boekenkast .<br />$Hij wil er $B weggeven aan $zijn $doel .<br />Het maakt $hem niet uit welke boeken $hij weggeeft.<br />Lukraak doet $naam een greep in $zijn boekenkast .<br /><br />Hoeveel verschillende mogelijkheden zijn er om<br />$b boeken te kiezen uit een verzameling van $a ?
:Met de grafische rekenmachine Ti83 :<br /> $a ncr $b of <br /> met behulp van een $[$a-$b] bij $b rooster<br />zie ook deze <a href="$module_dir/docs/combinaties_en_permutaties.pdf">uitleg </a>(PDF)
:$naam heeft $A boeken in $zijn boekenkast .<br />$Hij wil er $B weggeven.<br />$Hij geeft ze aan $text .<br /><br />Hoeveel verschillende keuze mogelijkheden heeft $naam ?
:Met de grafische rekenmachine Ti83 :<br /> $a npr $b<br />zie ook deze <a href="$module_dir/docs/combinaties_en_permutaties.pdf">uitleg </a>(PDF)
:Lidl,AH,Aldi,Welkoop ,Jumbo,COOP,Karstadt,V&D,HEMA 
:$naam heeft een prijsvraag gewonnen bij de <em>$super</em>.<br />Uit $A producten mag $hij er $B gratis uitzoeken.<br />$Hij mag ook $B dezelfde producten kiezen...<br /><br />Hoeveel keuze mogelijkheden heeft $naam ?
:$naam heeft een prijsvraag gewonnen bij de <em>$super</em>.<br />Uit $A producten mag $hij er $B gratis uitzoeken.<br />$Hij moet echter allemaal verschillende producten kiezen<br /><br />Hoeveel keuze mogelijkheden heeft $naam ?
:galajurk,baljurk,cocktailjurk,ballroomjurk,dansjurk,latinjurk,partyjurk,glitterjurk
:cocktailfeest,galafeest,eindexamenfeest,feest,party,dansfeest,swingfeest,cocktailparty,bruiloftsfeest
:$a vriendinnen zijn op zoek naar een $jurk voor een $feest .<br />Bij winkelketen X-factor vinden ze een flinke collectie mooie jurken.<br />Voorradig zijn jurken in de kleuren:<br /> <b>$kk</b><br />Ze kopen allemaal &eacute;&eacute;n jurk.<br />Het maakt de vriendinnen niet uit of ze dezelfde kleur $jurk kiezen.<br />Er zijn meer dan genoeg jurken voorradig, in alle kleuren.<br />Hoeveel keuzemogelijkheden hebben de vriendinnen, wanneer je alleen let op de kleur ?
:$a vriendinnen zijn op zoek naar een $jurk voor een $feest .<br />Bij winkelketen X-factor vinden ze een flinke collectie mooie jurken.<br />Voorradig zijn jurken in de kleuren:<br /> <b>$kk</b><br /> Ze kopen allemaal &eacute;&eacute;n jurk.<br />De vriendinnen willen uiteraard allemaal een verschillende kleur $jurk<br />Hoeveel keuzemogelijkheden hebben de vriendinnen, wanneer je alleen let op de kleur ?
:$naam is op zoek een $jurk , en wel $a stuks voor haar toneelvereniging.<br />Bij winkelketen X-Factor vindt ze een hele partij geschikte jurken voorradig in de kleuren: <br /> <b>$kk</b> <br />Ze wil $a verschillende kleuren.<br />Hoeveel keuzemogelijkheden heeft $naam, wanneer je alleen let op de kleur?
:Met de grafische rekenmachine Ti83 :<br /> $b npr $a<br />zie ook deze <a href="$module_dir/docs/combinaties_en_permutaties.pdf">uitleg </a>(PDF)
:Met de grafische rekenmachine Ti83 :<br /> $b ncr $a of <br /> met behulp van een $[$b-$a] bij $a rooster<br />zie ook deze <a href="$module_dir/docs/combinaties_en_permutaties.pdf">uitleg </a>(PDF)
:aantal blessures , leeftijd ,totaal ,blessures 
:Een sportvereniging heeft van haar $totaal_voetballers actieve leden <br />gedurende &eacute;&eacute;n jaar het aantal blessures bijgehouden.<br />Verdeeld naar leeftijdsklassen <u>staan hun resultaten in deze tabel</u>.<br />Bereken in $decimalen decimalen nauwkeurig de kans dat een <em>willekeurig gekozen lid</em><br />
:jonger dan $leeftijd jaar is.
:ouder dan $leeftijd jaar is.
:De kans is $sum/$totaal_voetballers<br />Dus $P = $(answer$n) en afgerond op $decimalen decimalen $afgerond                                                                     
:jonger dan $leeftijd jaar is en minder dan $[$injury-1] blessure(s) heeft.
:jonger dan $leeftijd jaar is en meer dan $[$injury-1] blessure(s) heeft.
:ouder dan $leeftijd jaar is en minder dan $[$injury-1] blessure(s) heeft.
:ouder dan $leeftijd jaar is en meer dan $[$injury-1] blessure(s) heeft.
:De kans is dan $sum/$totaal_voetballers<br />Dus $P = $(answer$n) en afgerond op $decimalen decimalen $afgerond
:leeftijd,levenden,overledenen,zie hier voor de tabel
:Gegeven is de <u>volgende sterftetabel</u>.<br />In deze sterftetabel kun je zien dat van de 100000 mensen van 30 jaar,<br />er gemiddeld $d1 zullen sterven in de daarop volgende 5 jaar.<br />
:Bereken in $decimalen decimalen nauwkeurig de kans dat<br />iemand van $l1 jaar oud de leeftijd van $l2 jaar bereikt.
:Volgens de tabel zijn er van de $L1 $l1 jarigen na $[$p*5] jaar nog $L2 in leven.<br />Dus het goede antwoord is $(answer$n) , of afgerond op $decimalen decimalen $ans .
:Bereken in $decimalen decimalen nauwkeurig de kans<br />dat iemand van $l1 jaar binnen $[$p*5] jaar zal sterven.<br />
:Volgens de tabel zijn er van de $L1 $l1 jarigen in $[$p*5] jaar $show = $tot mensen overleden.<br />De kans op sterven is dan $(answer$n) , of afgerond op $decimalen decimalen $ans 
:prijs,aantal,kans,prijzengeld
:Tijdens een loterij zijn de <u>volgende prijzen </u>gevallen. <br />Bereken het gemiddelde prijzengeld per lot.
:Tijdens een loterij heb je kans op verschillende prijzen. <br />In de <u>tabel</u> staan de verschillende prijzen en bijbehorende kansen. <br />Bereken het verwachte prijzengeld per lot.
:Tijdens een loterij heb je kans op verschillende prijzen. <br />In de <u>tabel</u> staan de verschillende prijzen en bijbehorende kansen.<br />Een lot kost $lot euro. <br />Hoeveel winst per lot verwacht de organisatie te maken?
:<b>E</b>($prijzengeld)=$prijs_tex &asymp; $ans &euro; <br />Dus de winst per lot is: $lot - $ans = $round_ans &euro;
:"Ik heb het volgende commentaar op je tekening:<br />","Je hebt een lege tekening ingestuurd ?","Er staan lijnen zonder nummer of labels in je kansboom...","Sommige lijnen zijn nog niet klaar: er missen nog wat getallen/labels...","Er zijn lijnen met teveel getallen/labels: iets nauwkeurige tekenen...","Er zijn niet genoeg lijnen in verhouding met het aantal getallen/labels...","Er zijn teveel lijnen in verhouding met het aantal getallen/labels...","Er staan geen getallen of labels in je kansboom...","Er staan geen lijnen in je kansboom..."
:In een loterij is de kans op winst $winst .<br />We kopen $Num loten.<br />Teken hierbij de kansboom<br />en bereken de kans op $Aantal_winst keer winst.<br /><small>Gebruik in de kansboom voor winst de letter <b>Y</b><br />en voor verlies de letter <b>N</b></small>
:De kans op $Aantal_winst keer winst is dus :
:<br />Je hebt je antwoord in procenten gegeven...<br />Maar een kans is een getal tussen 0 en 1 !!
:<br />Erg onnauwkeuring...en bovendien heb je een antwoord in procenten gegeven...<br />Maar een kans is een getal tussen 0 en 1 !! 
:je komt $[$lines_g2 - $lines_a2] regel(s) te kort in je diagram...
:je bent een onderdeeltje (een getal of een letter ? )vergeten aan je kans-boom...
:je hebt er wat takken ($[$ta1-$tg1] ) bij bedacht?
:je bent wat ($[$tg1-$ta1] ) takken vergeten...
:Dat is niet al te nauwkeurig...
:Deze kon ik niet vinden in je kansboom:
:nummer bakje,aantal ballen,empirische kans P,theoretische kans P,verschil theoretische en empirische kans,emprisch,theoretisch,rest
:Deze Plinko Applet is gemaakt door Dr. D.P. Little<br />Zie voor meer statistische applets <a target=new href=http://www.math.psu.edu/dlittle/applets.html> zijn website</a><br />Let op: de applet stopt vanzelf met het werpen van de balletjes<br />als het aantal van $var2 balletjes is bereikt.<br />Meer balletjes laten vallen mag wel, minder mag niet..
:In een <em>bord van Galton</em> (ballenbak / Quincunx) laat je tenminste $var2 knikkers in $var1 bakjes vallen...<br /><small><em>de applet stopt vanzelf -hopelijk- na $var2 balletjes</em></small><br />De kans voor een bal om naar rechts te gaan is $var4 <br />Voer het experiment in de applet uit.<br />Bepaal aan de hand van je resultaten: $the_question 
:Je moet tenminste $var2 balletjes <br /> laten vallen in dit experiment...
:je hebt een invuldveld vergeten...<br />
:Klaar...zie tabel
:je hebt wat onzin ingevuld.<br /> Ik verwacht gewoon een paar getallen...
:Je data staan al in de tabel...<br />
:Neem de gegevens over in de tabel
:<small>je kunt in de applet met je muis op het bakje klikken<br />en aflezen hoeveel balletjes erin zitten...</small>
:Je hebt me geen gegevens gestuurd...<br />er is dus ook geen goed antwoord :)
:De totale kans is natuurlijk gewoon 1 .... en niet $testvar
:Je moet alle letters en nummers wel op de lijnen plaatsen...<br /> Anders kan ik ze natuurlijk niet nakijken !<br />
:totaal $sum ballen , waarvan $ball in bakje $p
:Met behulp van een $[$a-$b] bij $b rooster of <br />met de grafische rekenmachine Ti83 :<br /> $a ncr $b <br /> zie ook deze <a href="$module_dir/docs/combinaties_en_permutaties.pdf">uitleg </a>(PDF)
:of
:Met behulp van een $[$a-$b] bij $b rooster 
:Met behulp van een $[$b-$a] bij $a rooster 
:
:
:
:
:
:
:
:
:28 Combinaties & Permutaties : toepassing VII (simpel)
:27 Combinaties & Permutaties : toepassing VI (simpel)
:26 Combinaties & Permutaties : toepassing V (simpel)
:25 Combinaties & Permutaties : toepassing IV (simpel)
:24 Negatieve Binomiale Verdeling [plinko-II applet]
:23 NIET KLAAR Kansboom I [applet] 
:22 Galton bord II [plinko applet]
:21 Galton bord I [plinko applet]
:20 Gemiddelde en verwachtingswaarde
:19 Empirische kans & Tabellen II
:18 Empirische kans & Tabellen I
:17 Combinaties & Permutaties : toepassing III
:16 Combinaties & Permutaties : toepassing II
:15 Combinaties & Permutaties : toepassing I
:14 Verwachtingswaarde en Standaardafwijking
:13 Lettercombinaties (permutaties)
:12 Wie organiseert wat? (permutaties)
:11 Trekken met terugleggen (binomiaal)
:10 Trekken zonder terugleggen
:9 Niet klaar:andere soorten dobbelstenen
:8 Oneerlijke dobbelstenen...
:7 Hoe groot is de kans dat de som ogen is
:6 Gooien met 2 , 3 of 4 dobbelstenen
:5 Kaarten: nu met terugleggen
:4 Kaarten:simpel
:3 Kaarten:harten of ruiten?
:2 Kaarten:zwart of Rood
:1 Kaartleggen: bereken de kans
