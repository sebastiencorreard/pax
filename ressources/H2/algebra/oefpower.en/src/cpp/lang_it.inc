#if defined TARGET_ppower11 || defined TARGET_ppower12 || defined TARGET_ppower13 || defined TARGET_ppower01 || defined TARGET_ppower02
\text{name_statement=Esegui i calcoli senza calcolatrice}
#endif
#if defined TARGET_powerneg
\matrix{name_statement=Il numero,è
  Scrivilo come prodotto di potenze}
\text{name_choix=positivo, negativo}
\matrix{name_feed=Hai verificato se,l'esponente,gli esponenti
  del numero negativo,è pari o dispari
  dei numeri negativi,sono pari o dispari
  Invece il segno di questo esponente non influenza,Invece i segni di questi esponenti non influenzano, la risposta a questa domanda.
  Il prodotto di numeri positivi e le potenze di numeri positivi sono sempre positivi.}
#endif
#if defined TARGET_defecritscien
\text{name_statement=Scrivi il numero dato utilizzando la notazione scientifica:}
#endif
#if defined TARGET_defpuisdix
\text{name_statement=Scrivi il valore del numero }
\text{name_instruction=Scrivi il numero come numero intero oppore come numero decimale.}
#endif
#if defined TARGET_defpuisnb
\text{name_statement=Scrivi il valore del numero}
#endif
#if defined TARGET_defpuisnb2
\text{name_statement=Scrivi il valore del numero}
\text{name_instruction=Scrivi il numero come numero intero oppore come frazione ridotta ai minini termini.}
#endif
#if defined TARGET_encadr
\text{name_statement=Appossima il numero, con potenze consecutive di 10.}
\text{name_answer1=Esponente}
\text{name_answer2=Esponente}
\text{name_hint=Come prima cosa puoi scrivere il numero utilizzando la notazione scientifica.}
#endif
#if defined TARGET_operation1 || defined TARGET_operation2
\text{name_statement=Completa l'eguaguaglianza}
\text{name_instruction=Scrivi il risultato nella forma}
#endif
#if defined TARGET_ordregrandeur
\text{name_statement=Determina l'ordine di grandezza del numero \(A\) dato.}
\text{name_instruction=Se necessario, l'esponente di 10 può essere zero.}
#endif
#if defined TARGET_tabpuis
\text{name_statement=Completa la tabella}
\text{name_feed=Fai attenzione! Si ha sempre}
#endif
#if defined TARGET_tabpuis2
\text{name_statement=Completa la tabella}
\text{name_feed=Fai attenzione! In generale \(a^m*a^n\) non è uguale a \(a^{m n}\).}
\text{name_warning=Attenzione}
#endif
#if defined TARGET_decimal
\matrix{name_statement=Scrivi il numero, nei due modi seguenti
  in notazione scientifica
  nella forma,dove \(a\) è un intero non multiplo di 10}
\text{name_answer=notazione scientifica,esponente,\(a\), esponente}
#endif
#if defined TARGET_power
\text{name_statement1=Scrivi}
\text{name_statement2=in forma di potenza di un
  intero (con il più grande esponente possibile)}
\text{name_hint=Come prima cosa puoi ridurre la frazione ai minimi termini.}
\text{name_feedback1=Hai applicato correttamente la regola}
\text{name_feedback2=Non confondere}
\text{name_and=e}
#endif
#if defined TARGET_power10
\text{name_statement=Scrivi il numero seguente nella forma}
\text{name_answer=exponente}
#endif