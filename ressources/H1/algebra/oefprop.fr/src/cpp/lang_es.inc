#if defined TARGET_CDRom
\text{name_statement=J'ai acheté un lecteur de CD. J'ai payé,
  euros avec, CD qui valent chacun, euros.}
\text{name_question=Quel est le prix du lecteur&nbsp;}
\text{name_answer=Prix (en euros)}
#endif
#if defined TARGET_Tourdumonde
\text{name_statement1=El perímetro de la tierra es de aproximadamente 40 000 \(\textrm{km}\).
  Para simular una vuelta al globo terráqueo en automóvil, un piloto circula en un circuito de}
\text{name_statement2=a una velocidad media de, (incluidos descansos y
  comidas).}
\text{name_question=¿Cuánto durará su aventura en horas}
\text{name_answer=Horas}
#endif
#if defined TARGET_Tempsdeparcour
\matrix{name_statement=En coche, he recorrido
   circulando a la velocidad media de}
\text{name_question=¿Durante cuántos minutos he circulado}
\text{name_answer=Tiempo en}
#endif
#if defined TARGET_Solde
\matrix{name_statement=Con un,de descuento
  me ahorro, francos en un par de botines}
\text{name_question=¿Qué precio tenían antes de las rebajas}
\text{name_answer=Precio (en francos)}
#endif
#if defined TARGET_Pyramide
\text{name_statement=Una pirámide tiene una base cuadrada de,
  Su altura es,
  Quiero realizar una maqueta de madera a escala}
\text{name_question=¿Qué longitud tiene el lado de la base (en \(\textrm{cm}\))}
\text{name_answer=Lado de la base en \(\textrm{cm}\)}
#endif
#if defined TARGET_chelle
\text{name_statement=Un mapa de carreteras está en la escala}
\text{name_question=¿Qué distancia real  (en \(\textrm{km}\)) représenta, en el mapa}
\text{name_answer=Distancia real (en \(\textrm{km}\))}
#endif
#if defined TARGET_Courses
\matrix{name_statement=Mamá me envía a la tienda a comprar
  Cojo un paquete de,botellas.
  La cajera me dice entonces que me faltan
  Dejo una botella y vuelvo a la caja. Entonces la cajera me devuelve}
\text{name_product=zumo de naranja, zumo de manzana, Coca Cola, zumo de uvas}
\matrix{name_question=¿Qué vale una botella de
  ¿Cuánto dinero llevaba yo al principio}
\text{name_instruction=Les réponses seront données en}
\text{name_euro=euros}
\text{name_answer1=Precio de una botella}
\text{name_answer2=Mi dinero}
#endif
#if defined TARGET_Densit
\matrix{name_statement=La densidad de población de un país es de,habitantes
  Su población es,millions }
\text{name_question=¿Cuál es su área (en miles de \(\textrm{km}^2\))&nbsp;}
\text{name_answer=Área}
#endif
#if defined TARGET_DensitII
\text{name_statement=La superficie de un país es de,
  y su población es de}
\text{name_question=¿Cuál es su densidad}
\text{name_answer=Densidad(\(hab{/}\textrm{km}^2\))}
#endif
#if defined TARGET_DensitII2
\text{name_statement=La superficie de un país es de ,
 y su densidad es de,habitantes}
\text{name_question=¿Cuál es su población (en millones)}
\text{name_answer=Población}
#endif
#if defined TARGET_Molire
\text{name_statement=El profesor de francés ha comprado,ejemplares de El Avaro.,
  El librero le ha hecho un descuento de, francos por libro. Ha pagado}
\text{name_question=¿Qué vale un libro sin el descuento}
\text{name_answer=Precio}
#endif
#if defined TARGET_Poids
\text{name_statement=Un camión es,veces más pesado que un coche mientras que
  el camión es, veces más ligero que un tanque.,
  Sabiendo que el camión pesa, toneladas, calcular los pesos
  (in toneladas) del coche y del tanque.}
\text{name_answer1=Peso del coche}
\text{name_answer2=Peso del tanqu}
#endif
#if defined TARGET_Pourcentages
\matrix{name_statement=Entre los,alumnos del instituto
  dan alemán.
  dan español.}
\text{name_question1=¿Cuántos son}
\text{name_question2=¿Qué porcentaje representan}
\text{name_answer1=Número de alumnos}
\text{name_answer2=Porcentaje}
#endif
#if defined TARGET_Tapis
\text{name_incdec=sube,baja}
\matrix{name_statement=Una alfombra costaba,francos en noviembre
  el,de, en diciembre
  después,el, en enero}
\text{name_question=¿Cuál es su nuevo precio}
\text{name_answer=El nuevo precio es}
\text{name_rep= francos menos, francos más ,el mismo precio}
\text{name_euro=francos}
#endif
#if defined TARGET_DensitII2
\text{name_statement=La superficie d'un pays est de,
  et sa densité est de,habitants}
\text{name_question=Quelle est sa population (en millions)&nbsp;}
\text{name_answer=Population (en millions)}
#endif
#if defined TARGET_Essence
\text{name_statement=Un vehículo consume,litros de gasolina a los 100,
  Su depósito puede contener, litros de gasolina}
\text{name_question=¿cuál es su autonomía}
\text{name_answer=Autonomía (en \(\textrm{km}\))}
#endif
#if defined TARGET_EchelleII
\text{name_statement=Un mapa de carreteras está a escala}
\text{name_question=Para una distancia real de ,¿cuál es la distancia en el mapa}
\text{name_answer=Distancia real (en \(\textrm{cm}\))}
#endif
#if defined TARGET_echelcarte1
\text{name_enonce=Tenemos un plano a escala ,La distancia real es de}
\text{name_question2=La distancia sobre el plano será de}
#endif
#if defined TARGET_echelle1
\matrix{name_enonce=Sobre el plano, una distancia de
  se representa mediante una distancia de
  en el plano.}
\text{name_question2=La escala del plano es}
#endif
#if defined TARGET_duree1 || defined TARGET_vitesse1 || defined TARGET_distance1 || defined TARGET_echelle1 || defined TARGET_echelcarte1 || defined TARGET_duree1 || defined TARGET_echellereelle1
\matrix{name_question=Complete la tabla
  l'une des cases doit contenir le résultat final}
#endif
#if defined TARGET_echelle1 || defined TARGET_echelcarte1
\text{name_head=Distancias sobre el plano en  ,
 Distancias reales en}
#endif
#if defined TARGET_duree1
\text{name_enonce=Un vehículo circula a una velocidad media de,
  Ha recorrido una distancia de}
\text{name_head=Duración en,Distancia en}
\text{name_question2=La duración del recorrido es de}
\text{name_question3=Si lo convertimos en horas y minutos}
#endif
#if defined TARGET_vitesse1
\text{name_enonce=Un vehículo ha recorrido una distancia de,en}
\text{name_header=Duración en,Distancia en}
\text{name_question2=La velocidad media es de}
#endif
#if defined TARGET_echellereelle1
\text{name_enonce=Tenemos un plano a escala ,
  Hemos medido sobre este plano una distancia de }
\text{name_question2=La distancia real correspondiente es de}
#endif
#if defined TARGET_distance1
\text{name_enonce=Un vehículo circula a una velocidad media de,
  El viaje ha durado  }
\text{name_head=Duración en min,Distancia en km}
\text{name_question2=La distancia recurrida es de}
#endif
