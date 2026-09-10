#if defined TARGET_histo
  \text{name_header=Intervals, Freqüències, Histograma}
  \text{name_instruction0=A continuació es mostra una sèrie de dades&nbsp;}
  \text{name_instruction=Entre els histogrames següents, trieu el qual representa la sèrie de dades.}
#endif
#if defined TARGET_ajustement
  \text{question=lineal, parabòlic, exponencial, logarítmic}
  \text{name_instruction0=Considereu el següent núvol de punts&nbsp;}
 %%% leave the comma
  \text{name_instruction=La funció de \(x) que millor representa a \(y) sembla ser de tipus,}
  \text{name_feedback=A continuació es mostra en vermell la corba d'ajust de tipus \question[\choix]}
  \text{name_prompt=Ajust}
#endif
#if defined TARGET_repstat
  \text{name_header=Valors}
  \text{name_eff=Freqüències}
  \text{name_listechoix= de l'histograma de freqüències,
  de l'histograma de freqüències acumulades,
  de l'histograma de freqüències acumulades decreixents,
  del polígon de freqüències,
  del polígon de freqüències acumulades,
  del polígon de freqüències acumulades decreixents}
  \text{name_instruction0= A continuació es mostren les freqüències d'una sèrie de dades que prenen valors d'1 a \cnt i un diagrama de dades construït a partir d'aquesta sèrie}
  \text{name_instruction=De quin es tracta&nbsp;}
  \text{name_prompt=Es tracta}
#endif
