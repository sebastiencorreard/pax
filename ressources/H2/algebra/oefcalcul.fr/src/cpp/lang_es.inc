#if defined TARGET_calcul2
\text{name_statement=Calcule}
\text{name_and=y}
\text{name_feedback=La buena respuesta es,
  Tu primer resultado vale,
  Tu segundo resultado vale}
\text{name_andno=y no}
\text{name_answer=Primero,Segundo}
\text{name_instruction=Sólo debe escribir números enteros.}
#endif

#if defined TARGET_additfrac0 || defined TARGET_additfrac
\text{name_effect=Efectúe}
\matrix{name_statement=Para eso, se reduce al mismo denominador
  Luego se efectúan las multiplicaciones
  Por fin, se añaden (o retira) los numeradores
  Y se simplifica si se puede}
\text{name_feedback=Finalmente}
\text{name_oper=la suma, la resta}
#endif
#if defined TARGET_calcul
\text{data1=\a más \b multiplicado por \c,
\a más \b luego multiplica por \c,
\a más \b que en primer lugar multiplicó por \c,
\a multiplicado por \b más \c,
\a multiplicado por la suma de \b y \c,
\a más \b dividido por \c,
\a más \b que en primer lugar se dividió por \c,
\a luego divide por \b más \c ,
\a dividido por \b más \c,
\a más \b luego divide por \c,
\a dividido por \b luego añade \c
}
\text{name_statement=Se calcula,
  ¿Cuál es la expresión matemática conveniente?}
\text{name_instruction=Si hay ambigüedad, es necesario dar todas las posibilidades.}
#endif
#if defined TARGET_calcprio
\text{listechoix=la multiplicación, la adición}
\text{name_statement=Debes calcular,
  et donner le résultat sous la forme d'une fraction irréductible.,
  ¿Qué operación haces primero,
  Calcule (debes simplificar las fracciones)}
\text{name_answer=Opération}
#endif
#if defined TARGET_FractionsI || defined TARGET_FractionsII || defined TARGET_FractionsIII
\text{name_instruction=À faire sans calculatrice.}
\text{name_answer=Su respuesta}
# if defined TARGET_FractionsI
  \text{name_statement=Determinar la fracción igual a la suma}
\text{name_hint=Para añadir dos fracciones, se reduce al mismo denominador.
  En este ejemplo, el denominador común es \denom.}
# endif
# if defined TARGET_FractionsII
\text{name_statement=Determinar la fracción igual al producto}
\text{name_hint=La multiplicación de dos fracciones se efectúa multiplicando los numeradores
  y los denominadores el uno con el otro.}
# endif
# if defined TARGET_FractionsIII
\text{name_statement=Determinar la fracción igual a}
\text{name_hint=Es necesario comenzar por calcular la suma de las fracciones al numerador,
  luego el situado al denominador. Quedará a continuación por dividir dos fracciones
  (multiplica por el revés).}
# endif
#endif
#if defined TARGET_mult
\text{name_statement=Efectúa el cálculo siguiente}
#endif
#if defined TARGET_multintrus
\text{name_statement=Uno de los cálculos da un diferente resultado de los dos otros. ¿Cuál}
\text{name_answer=Su respuesta}
#endif
#if defined TARGET_opsimple || defined TARGET_opsimple2
\text{openames=adición, sustracción, multiplicación, división}
\text{operules=tomo simplemente el signo de los dos números.,
  retiro los paréntesis luego yo tomo el signo de los dos números.,
  observo quien de los dos números a la mayor distancia a cero.,
  retiro los paréntesis y luego observo quien de los dos números a la mayor distancia a cero.,
  utilizo la "regla de las señales".}
\text{name_statement=O sea la operación,
  Es una,
  Para encontrar el signo del resultado,
  ¿Cuál es el signo del resultado,
  Para calcular el resultado, debo hacer una,
  Encuentro }
#endif
#if defined TARGET_regleadd
\text{choix=la conmutatividad, la asociatividad, la regla de signo, la regla de prioridad}
\text{name_statement=¿Para pasar de la primera a la segunda línea,
  qué propiedad de la adición utilizó}
#endif
#if defined TARGET_signe
\text{name_statement=El signo de un producto de,
  factores no nulos que implican exactamente,
  factores,
  es}
\text{name_sol=positivo,négativo}
\text{name_negpos=négativos, positivos}
\text{name_answer=Signe}
#endif
#if defined TARGET_transfmult
\text{multdiv= multiplica, divide}
\text{multidivi= multiplicado, dividido}
\text{name_statement=Que pasa a ser el producto de dos números si se,
  uno por,
  y que se,
  otro por,
  esta,por}
\text{name_feed=Habría podido simplificar el resultado.}
\text{name_num=Numérateur}
\text{name_den=Dénominateur}
#endif
