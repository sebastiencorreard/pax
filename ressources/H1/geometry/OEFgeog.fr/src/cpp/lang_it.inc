\text{correct=La figura è corretta}
\text{penalty=Siete stati penalizzati perché alcuni oggetti non avevano il nome richiesto.}
\text{Point=Punto}
\text{Cercle=Circonferenza}

#if defined TARGET_point2 ||defined TARGET_cercle4 ||defined TARGET_cercle5 
\text{aide=Per cambiare il nome di un oggetto, cliccare con il tasto destro del mouse e selezionare "Rinomina".}
#else
\text{aide=}
#endif

#if defined TARGET_point1 
\text{name_instruction=Tracciare un punto A.}
#endif

#if defined TARGET_point2 
\text{name_instruction=Tracciare un punto B.}
#endif

#if defined TARGET_ligne1 
\text{name_instruction=Tracciare una retta (AB).}
#endif

#if defined TARGET_ligne2
\text{name_instruction=Tracciare un segmento [AB].}
#endif

#if defined TARGET_ligne3 
\text{name_instruction=Tracciare una semiretta &#91;AB&#41;.}
#endif

#if defined TARGET_cercle1 
\text{name_instruction=Tracciare una circonferenza di centro \A passante per un punto \B.}
#endif

#if defined TARGET_cercle2 
\text{name_instruction=Tracciare una circonferenza di centro A e di raggio \choix.}
#endif

#if defined TARGET_cercle3 
\text{name_instruction=Tracciare una circonferenza di centro A e di diametro \choix.}
#endif

#if defined TARGET_cercle4 
\text{name_instruction=Tracciare tre punti A, B e P.<br />Tracciare una circonferenza passante per i tre punti A, B e P.}
#endif

#if defined TARGET_cercle5 
\text{name_instruction=Tracciare una circonferenza di centro C e di raggio [CA].}
#endif
