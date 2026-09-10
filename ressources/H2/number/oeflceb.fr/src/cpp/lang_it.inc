#if defined TARGET_lceb1a || defined TARGET_lceb1b || defined TARGET_lceb2a || defined TARGET_lceb2b
\text{instruction1=Con i numeri della prima riga e le 4 operazioni
dovete ottenere il numero \N ; scrivi la tua prima operazione e il corrispondente risultato,
per esempio}
\text{instruction2=invia la risposta, quindi continua.}
\matrix{conditiontext=Hai utilizzato i numeri dati
Le operazioni sono corertte
Hai trovato il risultato o il risultato più vicino
Il numero inserito è compreso tra \M1 e \M2}
\matrix{instruction0=Scegli un numero tra \M1 e \M2.
Non avete giocato ... }
\matrix{feedtext=La tua risposta
 Una risposta possibile}
#endif

#if defined TARGET_graphe3
\text{instruction1=Il conto è giusto o quasi giusto}
\text{instruction2=completa il diagramma mettendo le operazioni effettuati
  per arrivare alla soluzione}
#endif

#if defined TARGET_graphe0 || defined TARGET_graphe1 || defined TARGET_graphe2
\text{instruction=Ecco un diagramma per risolvere questo gioco
  <i>Il conto è giusto</i> o per trovare una soluzione vicina.
  Scrivi le eguaglianze corrispondenti}
\text{name_condition=Le eguaglianze sono corrette,
  Le eguaglianze sono quelle richieste}
\text{name_feed=La serie di operazioni è,
  Hai dimenticato alcuni passaggi.}
#endif
