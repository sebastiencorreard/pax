#if defined TARGET_histo
  \text{name_header=Intervalos,Frecuencias,Histograma}
  \text{name_instruction0=A continuación se muestra una serie de datos&nbsp;}
  \text{name_instruction=Entre los histogramas siguientes, escoja el que representa la serie de datos.}
#endif
#if defined TARGET_ajustement
  \text{question=lineal, parabólico,exponencial,logarítmico}
  \text{name_instruction0=Considere la siguiente nube de puntos&nbsp;}
 %%% leave the comma
  \text{name_instruction=La función de \(x) que mejor representa a \(y) parece ser de tipo,}
  \text{name_feedback=A continuación se muestra en rojo la curva de ajuste de tipo \question[\choix]}
  \text{name_prompt=Ajuste}
#endif
#if defined TARGET_repstat
  \text{name_header=Valores}
  \text{name_eff=Frecuencias}
  \text{name_listechoix= del histograma de frecuencia,
  del histograma de frecuencia acumulada,
  del histograma de frecuencias acumuladas decrecientes,
  del polígono de frecuencias,
  del polígono de frecuencias acumuladas,
  del polígono de frecuencias acumuladas decrecientes}
  \text{name_instruction0=A continuación se muestran las frecuencias de una serie de datos que toman valores de 1 a \cnt y un diagrama de datos construido a partir de esta serie}
  \text{name_instruction=¿De cuál se trata&nbsp;}
  \text{name_prompt=Se trata}
#endif
