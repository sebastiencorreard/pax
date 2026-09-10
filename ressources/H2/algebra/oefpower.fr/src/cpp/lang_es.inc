#if defined TARGET_ppower11 || defined TARGET_ppower12 || defined TARGET_ppower13 || defined TARGET_ppower01 || defined TARGET_ppower02
\text{name_statement=Calcular sin calculadora}
#endif
#if defined TARGET_powerneg
\matrix{name_statement=El número,es
  Escribalo en forma de productos de potencia}
\text{name_choix=positivo, negativo}
\matrix{name_feed=¿-Observaste bien si,el exponente,los exponentes
del número negativo,es par o impar
de los números negativos,son pares o impares
El signo de ceste exponente,El signo de ces estos exponentes,no tiene por el contrario importancia.
Los productos de números positivos, las potencias de números positivos son siempre positivos.}
#endif
#if defined TARGET_defecritscien
\text{name_statement=Dar la escritura científica del número}
#endif
#if defined TARGET_defpuisdix
\text{name_statement=Determinar el valor del número}
\text{name_instruction=On écrira la réponse sous la forme d'un nombre entier ou décimal.}
#endif
#if defined TARGET_defpuisnb
\text{name_statement=Determinar el valor del número}
#endif
#if defined TARGET_defpuisnb2
\text{name_statement=Determinar el valor del número}
\text{name_instruction=Dar el resultado en forma de un entero o de una fracción irreducible. }
#endif
#if defined TARGET_encadr
\text{name_statement=Dar un encuadre del número , por potencias de 10 consecutivas. }
\text{name_answer1=Exponent } inférieur
\text{name_answer2=Exponent } supérieur
\text{name_hint=Pueden en primer lugar escribir el número utilizando la notación científica.}
#endif
#if defined TARGET_operation1 || defined TARGET_operation2
\text{name_statement=Completar la igualdad para que esté comprobada}
\text{name_instruction=Dar el resultado en la forma}
#endif
#if defined TARGET_ordregrandeur
\text{name_statementDeterminar un orden de magnitud del número A siguiente,
  como eso se mostró en el curso}
\text{name_instruction=Si es necesario, el exponente de la potencia puede ser cero. }
#endif
#if defined TARGET_tabpuis
\text{name_statement=Completa el cuadro}
\text{name_feed=¡Atención! Se tiene siempre}
#endif
#if defined TARGET_tabpuis2
\text{name_statement=Completa el cuadro}
\text{name_feed=¡Atención! en general \(a^m*a^n\) es diferente de \(a^{m n}\).}
\text{name_warning=¡Atención! }
#endif
#if defined TARGET_decimal
\matrix{name_statement=Escribir el número, de dos maneras
  en notación científica
  de la forma,con a un número entero no múltiple de 10}
\text{name_answer=notación científica,exponente,\(a\), exponente}
#endif
#if defined TARGET_power
\text{name_statement1=Escribir}
\text{name_statement2=en forma de una potencia
  de un entero (con la mayor potencia posible)}
\text{name_hint=Simplifica en primer lugar la fracción.}
\text{name_feedback1=¿respetaste bien la regla?&nbsp;}
\text{name_feedback2=No se debe confundir}
\text{name_and=and}
#endif
#if defined TARGET_power10
\text{name_statement=Escribir el número siguiente de la forma }
\text{name_answer=exposant}
#endif
