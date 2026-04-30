#if defined TARGET_partita
\text{name_intro1=Giochiamo con una moneta. Scegli una terna di teste
(\testa) e croci (\croce), poi il computer sceglierà la sua terna. Lanceremo
ripetutamente la moneta. Se uscirà la terna del computer, vicerà il computer. Se uscirà la tua terna, vincerai tu.}
#endif
#if defined TARGET_giocatore
\text{name_intro1=Giochiamo con una moneta. Scegli una terna di teste
(\testa) e croci (\croce), poi il computer sceglierà la sua terna. Lanceremo
ripetutamente la moneta. Se uscirà la terna del compuer, il compuer guadagnerà un punto e ricominceremo. Allo stesso modo se uscirà la tua terna, tu guadagnerai un punto e ricominceremo. Vince chi avrà guadagnato più punti.}
#endif
#if defined TARGET_computer
\text{name_intro1=Giochiamo con una moneta. Il computer ha scelto una
terna di teste (\testa) e croci (\croce). Ora hai occasione di
scegliere la tua terna. Quindi lanceremo ripetutamente la moneta. Se
uscirà la terna del compuer, il compuer guadagnerà un punto e
ricominceremo. Allo stesso modo se uscirà la tua terna, tu guadagnerai
un punto e ricominceremo. Vince chi avrà guadagnato più punti.}
#endif
#if defined TARGET_partita || defined TARGET_giocatore
\text{name_intro3=Scegli una terna di monete.}
#endif
#if defined TARGET_computer
\text{name_intro3=Scegli una terna di monete diversa da quella scelta dal computer.}
#endif
#if defined TARGET_partita
\text{name_estrazione=Lancio}
text{name_avanti=Hai vinto tu,Ho vinto io,Ancora un lancio,Abbandona}
\text{name_avanti=Hai vinto tu,Ha vinto il computer,Ancora un lancio}
#endif
#if defined TARGET_computer || defined TARGET_giocatore
\text{name_estrazione=Partita}
\text{name_intro2=Giocheremo,partite.}
\text{name_avanti=Prosegui,Non serve continuare}
\text{name_condition2=Hai individuato il termine della partita?}
\text{name_feedback_log=Ecco un riepilogo delle,partite giocate}
#endif
#if defined TARGET_partita || defined TARGET_giocatore
\text{name_choice_list=Tu hai scelto,Allora il computer sceglie}
\text{name_answer=Hai capito chi ha vinto?}
#endif
#if defined TARGET_computer
\text{name_choice_list=Tu hai scelto,Il computer ha scelto}
#endif
#if defined TARGET_partita
\text{name_instruction=Seleziona <span class="wims_emph">\name_avanti[3]</span> fino a che non appare una delle terne e quindi indica il vincitore.}
#endif
#if defined TARGET_partita || defined TARGET_computer || defined TARGET_giocatore
\text{name_condition1=Hai seguito le istruzioni?}
\text{name_punteggio=Punteggio}
text{name_player_list=Tu,Io}
\text{name_player_list=Tu,Il computer}
text{name_whoscore_list=Hai fatto punto tu,Ho fatto punto io}
\text{name_whoscore_list=Hai fatto punto tu,Ha fatto punto il computer}
\text{name_help=<p>In questo gioco supponiamo di poter lanciare quante volte vogliamo una moneta equilibrata (cioè che dà testa e croce entrambe con probabilità pari a 1/2).</p>
<p>Il primo giocatore sceglie una sequenza di tre risultati (ad esempio <span class="wims_emph">TCC</span>), dopo di che il secondo giocatore ne sceglie un'altra (ad esempio <span class="wims_emph">CTC</span>). La partita consiste nel lanciare ripetutamente la moneta finché non compare una delle due sequenze scelte. Vince la partita il giocatore la cui sequenza è comparsa.</p>
<p>Nel nostro esempio, se la sequenza è <span class="wims_emph">CTTTCTTCC</span>, ha vinto il primo giocatore perché la sequenza <span class="wims_emph">CTC</span> non è mai comparsa, mentre la <span class="wims_emph">TCC</span> è comparsa negli ultimi tre lanci. Se invece avessimo ottenuto la sequenza <span class="wims_emph">CTTCTC</span>, avrebbe vinto il secondo giocatore.</p>
<p>Osserviamo che a priori non si sa quanti lanci si dovranno fare per finire la partita.</p>}
#endif
#if defined TARGET_pairs1 || defined TARGET_pairs2 || defined TARGET_pairs3 || defined TARGET_pairs4
note for translators: keep commas
\text{name_statement_list=Nel gioco tu hai scelto,mentre il computer ha scelto}
#endif
#if defined TARGET_single1
\text{name_statement=Nel gioco la probabilità che, esca nei primi 3 lanci è}
#endif
#if defined TARGET_single2
\text{name_statement=Nel gioco la probabilità che, esca entro i primi 4 lanci è}
#endif
#if defined TARGET_pairs3
\text{name_question=La probabilità che tu vinca la partita entro il quarto lancio è}
#endif
#if defined TARGET_pairs4
note for translators: keep commas
\text{name_statement=Se,la probabilità che vinca,è,allora}
\text{name_players=tu,il computer}
#endif
#if defined TARGET_pairs1
\text{name_statement=In uno stadio di una partita ancora in corso}
\text{name_cases_list=l'ultimo lancio è,gli ultimi due lanci sono}
\text{name_then=Allora}
#endif
#if defined TARGET_pairs1
\text{ans_list=Sicuramente vincerai tu,Sicuramente vincerà il computer,Non si può ancora dire chi vincerà}
#endif
#if defined TARGET_pairs2
\text{ans_list=Tu hai più probabilità di vincere,Il computer ha più probabilità di vincere,Avete la stessa probabilità di vincere,Non so}
#endif
