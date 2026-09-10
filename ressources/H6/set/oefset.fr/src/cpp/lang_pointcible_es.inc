\title_es{GGG Posiciones de puntos aleatorios}

\text{poss1=centro,borde}
\text{name_shape=círculo,cuadrado}
\text{name_data=diámetro,lado}
\text{t0=\name_shape[\k]}
\text{t1=\name_data[\k]}
\text{ieme=\n=1 ? : \(i\)-ésimo}
\text{name_es=\m4=3 ? está: es }
\text{poss2= menor o igual a, estrictamente mayor a, comprendida entre \d0 y }
\matrix{choixA=la distancia del \ieme punto al 
  del \t0 \name_es 
  \d mm}
\text{poss=no,sí}

\text{name_rep=no es,es}
\matrix{name_pointbleu=El punto azul marca la posición del punto escogido.
Los puntos azules marcan las posiciones de los puntos escogidos.}
\text{name_point=un punto,dos puntos,puntos}


\text{comdess=la zona coloreada en verde (incluyendo borde) representa el conjunto de puntos del \t0 cuya distancia al }

\matrix{name_event=Para \(i\in \{1,...,\n\}\), denotemos por <b>\(A_i\)</b> el evento
Denotamos por <b>\(A\)</b> el evento
Para \(i\in \{1,2\}\), denotemos por <b>\(A_i\)</b> el evento
}

\text{pts=\n>2 ? \n \name_point[3]:\name_point[\n]}
\text{name_instruction=Escogemos al azar \pts al interior del \t0 dibujado en café (centrado en 0 y cuyo \t1 mide \diam mm). }

\text{name_help1=La distancia considerada es la distancia euclideana en el plano: si \(m_1 = (x_1,y_1)\)
 y \(m_2 = (x_2,y_2)\) son dos puntos del plano, la distancia entre \(m_1\) y \(m_2\) es \(d(m_1,m_2)\) = \(\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}\).}
\text{name_help2=La distancia de un punto \(m\) a un conjunto \(E\) se define como el ínfimo de la distancia entre \(m) y un punto \(e) de \(E\)}

\text{name_question=¿El evento, ocurre}
\text{name_remark=Observación}
