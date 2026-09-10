\text{name_ou=o}
\text{name_et=e}
\text{si1=se}
\text{si2=se}
\text{Si1=Se}
\text{Si2=Se}
\text{ssi=se e soltanto se}
\text{seulement=soltanto}
\text{alors=allora}
\text{Alors=Allora}
\text{oui=sì}
\text{non=no}
\text{non2=non}
\text{spacebeforecolon=}
\text{Remarque=Nota}
\text{Soient=Siano}
\text{glossaire=data/glossaire_it}

#if defined TARGET_connecteursLN
\text{Alist =
c'è uno sciopero degli autobus,
stamattina piove,
fa freddo,
c'è il sole,
sta piovendo,
mangio un sacco di torte,
sono felice,
ascolto Radio Latina,
voglio progredire in matematica,
voglio migliorare il mio inglese,
ho il raffreddore,
balla,
suoni la chitarra,
non vuole diventare un ingegnere,
fai schifo in matematica,
siamo tristi,
il lavoro è motivante
}

\text{Blist =
sono in ritardo per la scuola,
prendo il mio ombrello,
mi metto un maglione,
indosso occhiali scuri,
fa freddo,
sto ingrassando,
rido,
io ballo la salsa,
mi esercito con WIMS,
vedrò solo i film in versione originale,
la mia voce è rotta,
corre,
tu canti,
vuole andare all'estero,
sei forte in francese,
siamo innamorati,
la soddisfazione è totale
}

\text{nonAlist=
non c'è sciopero degli autobus,
stamattina non piove,
non fa freddo,
non c'è il sole,
non sta piovendo,
mangio poche torte,
sono triste,
non ascolto Radio Latina,
non voglio progredire in matematica,
non voglio migliorare il mio inglese,
non ho il raffreddore,
non balla,
non suoni la chitarra,
vuole diventare un ingegnere,
sei bravo in matematica,
siamo felici,
il lavoro non è motivante
}

\text{nonBlist=
non sono in ritardo per la scuola,
non prendo il mio ombrello,
non ho indossato un maglione,
non porto occhiali scuri,
è caldo,
non sto ingrassando,
non rido,
non ballo la salsa,
non mi esercito con WIMS,
guardo Lost In Translation in italiano,
parlo normalmente,
non corre,
tu non canti,
vuole restare in Italia,
fai schifo in francese,
non siamo innamorati,
la soddisfazione è parziale
}

\text{name_statement1=Per ciascuna delle seguenti proposizioni, a sinistra, determina la sua struttura logica.}
\text{name_statement2=le proposizioni possono essere solo vere o false... }
\text{name_statement3=Fare clic sugli elementi corrispondenti a due a due.}
#endif

#if defined TARGET_deduction
\text{Alist =
c'è uno sciopero degli autobus,
piove al mattino,
fa freddo,
c'è il sole,
mangio un sacco di torte,
sono felice,
io ballo la salsa,
voglio progredire,
voglio migliorare il mio inglese,
ho il raffreddore
}

\text{Blist =
sono in ritardo per la scuola,
prendo il mio ombrello,
mi metto un maglione,
indosso occhiali scuri,
sto ingrassando,
rido,
ascolto solo Radio Latina,
mi esercito con WIMS,
vedo tutti i film in versione originale,
la mia voce è rotta
}

\text{nonAlist=
gli autobus non scioperano,
non piove al mattino,
non è freddo,
non c'è il sole oggi,
ho mangiato poche torte,
sono triste,
non mi piace la salsa,
non voglio progredire,
non voglio migliorare il mio inglese,
non ho il raffreddore
}

\text{nonBlist=
non sono in ritardo per la scuola,
non prendo il mio ombrello,
non ho indossato un maglione,
non porto occhiali scuri,
non sono ingrassato,
non rido,
ho ascoltato Fun Radio,
non mi sono esercitato con WIMS,
Guardo Lost In Translation in italiano,
parlo normalmente
}

\text{name_statement1=Assumiamo che sia vera la seguente implicazione:}
\text{name_statement2=Qualcuno mi incontra e nota che:}
\text{name_statement3=Questa persona deduce che:}
\text{name_statement4=Il suo ragionamento è corretto?}
\text{name_answer=Ragionameto corretto}
#endif

#if defined TARGET_implication
\text{Quand=Quando}
\text{Chaque=Ogni volta che}
\text{Question=Domanda}

\text{prem=
il signor Alex si siede davanti alla TV,
la signora Alice esce a fare una passeggiata nel parco,
Fred è nel parco,
Suzy si arrampica sull'albero,
Nestor si gira nel parco,
Bubu si seppellisce sottoterra,
Fred fruga nella sporcizia,
la signora Alice è molto arrabbiata
}

\text{conc=
la signora Alice esce a fare una passeggiata nel parco,
il suo cane Fred lo accompagna,
Suzy si arrampica sull'albero,
Nestor lascia l'albero per girarsi nel parco,
Bubu si seppellisce sottoterra,
Fred fruga nella sporcizia,
la signora Alice si arrabbia,
il signor Alex si siede davanti alla TV
}

\text{nonPr=
il signor Alex non si siede davanti alla TV,
la signora Alice non esce a fare una passeggiata nel parco,
Fred non è nel parco,
Suzy non si arrampica sull'albero,
Nestor non si gira nel parco,
Bubu non si seppellisce sottoterra,
Fred non scava nella sporcizia,
la signora Alice non si arrabbia
}

\text{nonCo=
la signora Alice non esce a fare una passeggiata nel parco,
Fred non accompagna la signora Alice,
Suzy non si arrampica sull'albero,
Nestor non lascia l'albero per girarsi nel parco,
Bubu non si seppellisce sottoterra,
Fred non scava nella sporcizia,
la signora Alice non si arrabbia,
il signor Alex non si siede davanti alla TV
}

\text{sujPr=il Signor Alex, la Signora Alice, Fred il cane, Suzy il gatto, Nestor il passero, Bubu il lombrico, Fred il cane, la Signora Alice}
\text{sujCo=la Signora Alice, Fred il cane, Suzy il gatto, Nestor il passero, Bubu il lombrico, Fred il cane, la Signora Alice, il Signor Alex}
\text{none=non possiamo concludere nulla}

\text{name_citation=Questo esercizio si basa su un esempio fornito da Alan Selby, in "Elements of Reason: understanding and explaining reason and math"
Volume 1, Stampato in Canada, ISBN 0-9697564-1-0.}

\text{name_characters=I nostri personaggi sono}
\text{name_statement1a=Si consideri la seguente implicazione, che assumiamo essere vera:}
\text{name_statement1b=Si considerino le seguenti implicazioni, che assumiamo essere entrambe vere:}
\text{name_statement2=Senza fare altre ipotesi, cosa possiamo dire che succede quando}
#endif

#if defined TARGET_incoherence
\text{Contradiction=Contraddizione}
\text{Exemple=Esempio}

\text{Alist=è svedese, è scozzese, è australiano, è tedesca, è cubana, è giapponese}
\text{Blist=gioca a tennis, suona il violino, fa surf, suona il piano, balla la salsa, fa Kendo}
\text{Clist=è biondo, indossa una gonna, non indossa una cravatta, non si trucca, è bruna, indossa il kimono}
\text{Dlist=sta sciando, gioca a rugby, trascorre le vacanze a Bali, va in bicicletta, ama la matematica, fa gli origami}
\text{Elist=è vegetariano, è sposato, gli piace la birra, le piacciono i wurstel, beve tequila, è single}

\text{nonAlist=non è svedese, non è scozzese, non è australiano, non è tedesca, non è cubana, non è giapponese }
\text{nonBlist=non gioca a tennis, non suona il violino, non fa surf, non suona il piano, non balla la salsa, non fa Kendo}
\text{nonClist=non è biondo, non indossa una gonna, indossa una cravatta, è truccata, non è bruna, non indossa un kimono}
\text{nonDlist=non scia, non gioca a rugby, non passa le vacanze a Bali, non va in bicicletta, odia la matematica, non fa gli origami}
\text{nonElist=non è vegetariano, è single, non gli piace la birra, non le piacciono i wurstel, non beve tequila, è sposata}

\text{name_statement1=Per entrare in un circolo ricreativo}
\text{name_statement2=maschile, ogni candidato è tenuto a}
\text{name_statement3=femminile, ogni candidata è tenuta a}
\text{name_statement4=soddisfare tutte le seguenti condizioni}

\text{name_question1=Trova nel seguente elenco una proposizione \(A\), che dovrebbe essere}
\text{name_question2=allo stesso tempo vera e falsa}
\text{name_question3=, e questo}
\text{name_question4=in qualsiasi interpretazione}
\text{name_question5=dove i termini del regolamento siano contemporaneamente veri}
\text{name_question6=Ciò dimostra per assurdo che i termini del regolamento sono inconsistenti.}

\text{name_remark=Nota: alla stregua di Sherlock Holmes, devi considerare tutti i casi e tenere traccia di tutte le inferenze...}

\text{name_hint1=Fai un'analisi dei casi}
\text{name_hint2=considera le interpretazioni secondo le quali i termini del regolamento sono tutti veri;}
\text{name_hint3=considera i diversi casi, e per ciascuno assegna i valori di verità alle diverse proposizioni elementari;}
\text{name_hint4=trova \(A) tale che in ogni interpretazione \(A) dovrebbe essere sia vera che falsa;}
\text{name_hint5=Ciò dimostra per assurdo che non esiste un'interpretazione che renda contemporaneamente veri tutti i termini del regolamento.}

\text{name_example1=Supponiamo che le seguenti condizioni siano contemporaneamente vere:}
\text{name_example2=\(P_1) ci permette di distinguere due casi: o \(A) è vero o \(B) è vero.}
\text{name_example3=Se \(A) è vero, indipendentemente da \(B): per \(P_2) e \(P_4) deduciamo che C è necessariamente vero; di \(P_3) deduciamo allora che \(A) è falso.}
\text{name_example4=Se \(A) è falso e quindi \(B) è vero: per \(P_4) deduciamo che \(A) è vero.}
\text{name_example5=In ogni caso, \(A) dovrebbe essere sia vero che falso. Questo non ha senso. Non c'è quindi
nessuna interpretazione in cui \(P_1), \(P_2) e \(P_3) sono simultaneamente veri. Diciamo che \(P_1), \(P_2) e \(P_3) sono inconsistenti.}
#endif

#if defined TARGET_negationLN
\text{Ilexiste=Esiste un}
\text{qui=che}
\text{Tous1=Tutti i}
\text{Tous2=Tutti gli}
\text{Aucun=Nessun}
\text{nest=è}
\text{Certains=Alcuni}

\text{name_subjects=greco, greci, logico, logici, compito di matematica, compiti di matematica, film, film, saggio, saggi, allievo, allievi, adulto, adulti}
\text{name_verbs=è un bugiardo, sono bugiardi, è pazzo, sono pazzi, è facile, sono facili, è divertente, sono divertenti, è vecchio, sono vecchi, è fortunato,
sono fortunati, è responsabile, sono responsabili}
\text{name_nonverbs=è schietto, sono schietti, è sano di mente, sono sani di mente, è difficile, sono difficili, è tragico, sono tragici, è giovane, sono giovani,
è sfortunato, sono sfortunati, è irresponsabile, sono irresponsabili}
\text{name_adj=bugiardo, pazzo, facile, comico, vecchio, felice, responsabile}
\text{name_nonadj=franco, sano di mente, difficile, tragico, giovane, infelice, irresponsabile}

\text{name_Alist=
Sta piovendo,
Lei balla,
Lui suona la chitarra,
Sarà un ingegnere,
Faccio schifo in matematica,
Siamo tristi,
I pesci non volano}

\text{name_Blist=
fa freddo,
corre,
canta,
lavorerà all'estero,
sono bravo in italiano,
sfortunati,
le galline nuotano
}

\text{name_nonAlist=
Non sta piovendo,
Lei non balla,
Lui non suona la chitarra,
Non sarà un ingegnere,
Sono bravo in matematica,
Siamo felici,
Il pesci volano
}

\text{name_nonBlist=
fa caldo,
non corre,
non canta,
resterà in Italia,
faccio schifo in italiano,
fortunati,
le galline non nuotano
}

\text{name_statement1=Sia data la proposizione \(P\) seguente:}
\text{name_statement2=Qual è la negazione di \(P\)?}
\text{name_question=La negazione di \(P) è}
\text{name_remark1=La vostra risposta}
\text{name_remark2=non è la negazione di}
\text{name_remark3=&#32; al contrario è equivalente}
#endif

#if defined TARGET_negationMath
\text{ilexiste=esiste un}
\text{telque=tale che}
\text{pourtout=per ogni}
\text{reel=reale}
\text{linequation=la disequazione}
\text{aaumoins=ha almeno}
\text{aauplus=ha al più}
\text{solutions=soluzioni}
\text{solution=soluzione}
\text{strictementpositif=strettamente positivo}
\text{negatif=negativo}
\text{amoinsde=ha meno di}
\text{aplusde=ha più di}
\text{naaucune=non ha nessuna}
\text{auneinfinite=ha una infinità di}

\text{name_statement1=Sia data la proposizione}
\text{name_statement2=Tra le proposizioni seguenti, qual è la negazione di}
#endif

#if defined TARGET_reciproque
\text{Puis=Successivamente}
\text{Laproposition=La proposizione}
\text{formuleepar=formulata da}
\text{enonceepar=enunciata da}
\text{delaproposition=della proposizione}
\text{sa=la sua}
\text{reciproque=reciproca}
\text{contraposee=contronominale}
\text{estlaproposition=è la proposizione}
\text{Laconjonction=La congiunzione}
\text{Ladisjonction=La disgiunzione}
\text{apournegation=ha per negazione}

\text{Alist=è svedese, è scozzese, è australiano, è tedesca, è cubana, è giapponese}
\text{Blist=gioca a tennis, gioca a biniou, fa surf, suona il piano, balla la salsa, pratica il Kendo}
\text{Clist=è biondo, indossa una gonna, non porta la cravatta, non si trucca, è bruna, indossa il kimono}
\text{Dlist=ha figli, esce la domenica, trascorre le vacanze a Bali, va in bicicletta, ama la matematica, fa gli origami}
\text{Elist=è vegetariano, è sposato, gli piace la birra, a piace il Bratwurst, beve tequila, è single}
\text{nonAlist=non è svedese, non è scozzese, non è australiano, non è tedesca, non è cubana, non è giapponese}
\text{nonBlist=non gioca a tennis, non gioca a biniou, non fa surf, non suona il piano, non balla la salsa, non pratica il Kendo}
\text{nonClist=non è biondo, non indossa la gonna, indossa la cravatta, si trucca, non è bruna, non indossa il kimono }
\text{nonDlist=non ha figli, non esce la domenica, non trascorre le vacanze a Bali, non va in bicicletta, odia la matematica, non fa gli origami}
\text{nonElist=non è vegetariano, non è sposato, non gli piace la birra, a non piace il Bratwurst, non beve tequila, è sposata}

\text{name_statement1=enuncia la seguente implicazione}
\text{name_statement2=enuncia la proposizione}

\text{name_answers=è la reciproca, è la contronominale, non è né la reciproca né la contronominale}
\text{name_hint=Si consideri l'implicazione}
#endif

#if defined TARGET_tautologie
\text{Alist=
c'è uno sciopero dell'autobus,
piove al mattino,
è freddo,
c'è il sole,
piove,
mangio molte torte,
sono felice,
ascolto Radio Latina,
sto facendo progressi in matematica,
mi piace l'inglese,
ho il raffreddore,
balla,
tu suoni la chitarra,
vuoi essere un ingegnere,
fai schifo in matematica,
siamo tristi,
i pesci non volano,
il lavoro è motivante,
}

\text{Blist=
sono in ritardo per il liceo,
prendo il mio ombrello,
ho messo un maglione,
indosso gli occhiali scuri,
è freddo,
sto ingrassando,
rido,
io ballo salsa,
mi esercito con WIMS,
vedo tutti i film nella loro versione originale,
la mia voce è rotta,
corre,
tu canti,
vai all'estero,
sei un francese forte,
siamo innamorati,
le galline nuotano,
la soddisfazione è totale,
}

\text{nonAlist=
non c'è sciopero dell'autobus,
non piove al mattino,
non fa freddo,
non c'è il sole,
non sta piovendo,
mangio poche torte,
sono triste,
non ascolto Radio Latina,
non sto facendo progressi in matematica,
non mi piace l'inglese,
non ho il raffreddore,
non balla,
non suoni la chitarra,
non vuoi essere un ingegnere,
sei bravo in matematica,
siamo felici,
mosca dei pesci,
il lavoro non è motivante
}

\text{nonBlist=
sono arrivato a scuola in orario,
non prendo il mio ombrello,
non ho indossato un maglione,
non indosso gli occhiali scuri,
è caldo,
non sono ingrassato,
non rido,
non ballo salsa,
non mi esercito con WIMS,
non vedo nessun film in versione originale,
parlo normalmente,
non corre,
tu non canti,
non vai all'estero,
fai schifo in francese,
non siamo innamorati,
le galline non nuotano,
la soddisfazione è parziale
}

\text{name_statement1=Si consideri la proposizione}
\text{name_statement2=seguente}
\text{name_question1=A quale formula logica corrisponde}
\text{name_question2=è una tatologia}
\text{name_hint=Una tautologia è una proposizione logica che è sempre vera (qualunque sia il valore di verità delle sue proposizioni elementari).}
#endif

#if defined TARGET_valeursVerite
\text{V=V}
\text{F=F}

\text{name_statement1=quattro proposizioni}
\text{name_statement2=Definiamo una <i>interpretazione</i> o un <i>modello</i> logico di queste proprosizioni assegnando loro i valori di verità Vero (V) o Falso (F).}
\text{name_statement3=Per un promemoria sulle regole della logica booleana, clicca sul link <span class="wims_button_help disabled">Istruzioni</span> in basso.}
\text{name_question1=Secondo questa interpretazione, calcola i valori di verità delle seguenti formule:}
#endif

#if defined TARGET_validite
\text{masculin=maschile}
\text{feminin=femminile}
\text{vrai=vero}
\text{faux=falso}

\text{Alist=è svedese, è scozzese, è australiano, è tedesca, è cubana, è giapponese}
\text{Blist=gioca a tennis, suona il violino, fa surf, suona il piano, balla la salsa, fa kendo}
\text{Clist=è biondo, indossa la gonna, non indossa la cravatta, non si trucca, è bruna, indossa il kimono}
\text{Dlist=sta sciando, gioca a rugby, trascorre le vacanze a Bali, va in bicicletta, ama la matematica, impara l'ikebana}

\text{nonAlist= non è svedese, non è scozzese, non è australiano, non è tedesca, non è cubana, non è giapponese}
\text{nonBlist= non gioca a tennis, non suona il violino, non fa surf, non suona il piano, non balla la salsa, non fa kendo}
\text{nonClist= non è biondo, non indossa la gonna, indossa la cravatta, si trucca, non è bruna, non indossa il kimono}
\text{nonDlist= non scia, non gioca a rugby, non trascorre le vacanze a Bali, non va in bicicletta, odia la matematica, non impara l'ikebana}

\text{name_statement1=possiede le seguenti caratteristiche}
\text{name_statement2=Per entrare in un club ricreativo}
\text{name_statement3=deve soddisfare tutte le seguenti condizioni}
\text{name_statement4=Per ciascuna di esse, indicare se}
\text{name_statement5=la verifica oppure no}
\text{name_hint1=Si tratta di calcolare i valori di verità delle asserzioni (formule) proposte, conoscendo i valori di verità delle proposizioni elementari.}
\text{name_hint2=Per qualsiasi promemoria sul calcolo dei valori di verità, consultare le <span class="wims_button_help disabled">Istruzioni</span> o l'esercizio "Valori di verità".}
#endif
