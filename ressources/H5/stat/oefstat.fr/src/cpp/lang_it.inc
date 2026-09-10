#if defined TARGET_histo
  \text{name_header=Intervallo,Frequenze,Istogramma}
  \text{name_instruction0=Ecco una serie di dati}
  \text{name_instruction=Selezionare tra i grafici qui sotto l'istogramma che rappresenta questa serie di dati.}
#endif
#if defined TARGET_ajustement
  \text{question=lineare,parabolico,esponenziale,logaritmico}
  \text{name_instruction0=Considera il seguente insieme di dati puntuali}
 %%% leave the comma
  \text{name_instruction=Una approssimazione di \(y) rispetto a \(x) di tipo,sembra adattarsi a questi dati}
  \text{name_feedback=Ecco in rosso una curva approssimante di tipo \question[\choix]}
  \text{name_prompt=Andamento}
#endif
#if defined TARGET_repstat
  \text{name_header=Valori}
  \text{\name_eff=Frequenze}
  \text{name_listechoix=l'istogramma delle frequenze,
  l'istogramma delle frequenze cumulate,
  l'istogramma delle frequenze cumulate decrescenti,
  il grafico a linea delle frequenze,
  il grafico a linea delle frequenze cumulate,
  il grafico a linea delle frequenze cumulate decrescenti}
  \text{name_instruction0=Ecco le frequenze di una serie di dati statistici a
  valori tra 1 e \cnt e un diagramma statistico costruito a partire da questi dati.}
  \text{name_instruction=Che tipo di diagramma è}
  \text{name_prompt=Il diagramma è}
#endif
