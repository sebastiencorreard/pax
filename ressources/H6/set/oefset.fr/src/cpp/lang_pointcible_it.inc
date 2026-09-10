\title_it{GGG Posizioni di punti aleatori}

\text{poss1=centro,bordo}
\text{name_shape=cerchio,quadrato}
\text{name_data=diametro,lato}
\text{t0=\name_shape[\k]}
\text{t1=\name_data[\k]}
\text{ieme=\n=1 ? del : dell'\(i\)-esimo}
\text{poss2=inferiore o uguale a,strettamente superiore a, compreso tra \d0 e }
\matrix{choixA=la distanza \ieme punto dal 
  del \t0 è 
 \d mm}
\text{poss=no,sì}

\text{name_rep=non è,è}
\matrix{name_pointbleu=Il punto blu marca la posizione del punto scelto.
I punti blu marcano la posizione dei punti scelti.}
\text{name_point=un punto,due punti,punti}


\text{comdess=la zona colorata in verde (bordi compresi) rappresenta l'insieme dei punti del \t0 la cui distanza dal }

\matrix{name_event=per \(i\in \{1,...,\n\}\), si indica con <b>\(A_i\)</b> l'evento
si indica con <b>\(A\)</b> l'evento
per \(i\in \{1,2\}\), si indica con <b>\(A_i\)</b> l'evento
}

\text{pts=\n>2 ? \n \name_point[3]:\name_point[\n]}
\text{name_instruction=Scegliendo a caso \pts all'interno del \t0 disegnato in marrone (centrato in 0 e il cui \t1 misura \diam mm) }

\text{name_help1=La distanza considerata è la distanza euclidea nel piano: se \(m_1 = (x_1,y_1)\)
 e \(m_2 = (x_2,y_2)\) sono due punti del piano, la distanza tra \(m_1\) e \(m_2\) è \(d(m_1,m_2)\) = \(\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}\).}
\text{name_help2=La distanza di un punto \(m\) da un insieme \(E\) è definita come l'estremo inferiore delle distanze tra \(m) e un punto \(e) di \(E\)}

\text{name_question=L'evento, si è verificato}
\text{name_remark=Nota}
