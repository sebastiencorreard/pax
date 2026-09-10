
#if defined TARGET_cubrt
/* note for translators: keep commas */
\text{name_statement=Calcolare una radice cubica \(w\) del numero complesso,e dire quali siano la sua parte reale e immaginaria}
#endif

#if defined TARGET_tworoots || defined TARGET_tworoots2
\text{impur=immaginairio puro}
\text{real=reale}
\text{zero=uguale a zero}
\text{nor=né reale né immaginario}
#endif

#if defined TARGET_tworoots
/* note for translators: keep commas */
\text{name_statement=Siano,le due radici di un polinomio,dove \(p \) è,e \(q\) è reale. Supponiamo che \(z_1\) e \(z_2\) non siano né reali né immaginari puri. Allora \(z_1 - z_2\) è un numero}
#endif

#if defined TARGET_tworoots2
/* note for translators: keep commas */
\text{name_statement=Siano,le due radici di un polinomio,dove,è un numero reale. Allora \(z_1 - z_2\) è un numero}
#endif

#if defined TARGET_eqmod
\text{name_statement=Risolvere in \(\mathbb{C}\) l'equazione} /*'*/
/* note for translators: keep commas */
\text{name_instruction=Inserire,se pensate che l'equazione non abbia soluzione} /*'*/
/* note for translators: keep commas */
\text{name_hint=Nel piano complesso,l'origine e i punti corrispondenti ai numeri,formano un parallelogramma (perché?)} /*'*/
#endif

#if defined TARGET_modsum
\text{name_yesno=Sì,No}
\text{name_statement=Possono esistere due numeri complessi \(z_1\) e \(z_2\) tali che}
\text{name_hint=Quali sono le condizioni che le lunghezze dei 3 lati di un
 triangolo devono verificare?}
\text{name_answer=La vostra risposta}
#endif
#if defined TARGET_modsum2
\text{name_and=e}
/* note for translators: keep commas */
\text{name_statement=Siano,due numeri complessi con,gradi,Calcolare il modulo di}
\text{name_hint=Ricordatevi del teorema del coseno: se un triangolo ha
i tre lati di lunghezza \(a\), \(b\), \(c\) e se
\(A\) indica l'angolo opposto al lato \(a\), allora}
#endif

#if defined TARGET_sumofj
/* note for translators: keep commas */
\text{name_statement=Sia,Calcolare la somma}
#endif

#if defined TARGET_cbrt
\text{name_style=un numero complesso tale che,una radice (complessa) del polinomio}
/* note for translators: keep commas */
\text{name_statement=Sia,Qual è il numero}
#endif

#if defined TARGET_arggiven
/* note for translators: keep commas */
\text{name_statement=Calcolare la parte reale e la parte immaginaria del numero complesso \(z\) avente,come modulo e,come argomento}
#endif

#if defined TARGET_pentaroot
/* note for translators: keep commas */
\text{name_statement=Siano,le 4 radici (complesse) del polinomio,Qual è il numero}
#endif

#if defined TARGET_argask
\text{name_statement=Dare il modulo e l'argomento del numero complesso}
\text{name_condition=è un argomento di}
#endif

#if defined TARGET_quadouble
/* note for translators: keep commas */
\text{name_statement=Per quale valore complesso \(w\) il polinomio,ha una radice doppia (complessa)}
\text{name_answer=La radice doppia}
#endif

#if defined TARGET_quadouble2
\text{name_and=e}
/* note for translators: keep commas */
\text{name_statement=Per quali vaori reali di,il polinomio,ha una radice doppia (complessa)}
\text{name_answer=La radice doppia}
#endif

#if defined TARGET_argsum
/* note for translators: keep commas */
\text{name_statement=Siano,Calcolare il modulo e l'argomento di}
\text{name_condition=è l'argomento di}
#endif

#if defined TARGET_pythagorus || defined TARGET_pythagorus2
\text{name_and=e}
/* note for translators: keep commas */
\text{name_statement=Siano,due numeri complessi con,Qual è il valore di}
\text{name_answer=La vostra risposta}
\text{name_hint=Pensate al teorema di Pitagora!  Qual è la differenza tra}
#endif

#if defined TARGET_fraction || defined TARGET_fraction2
\text{name_statement=Calcolare parte reale e parte immaginaria del
seguente numero complesso}
\text{name_answer1=Parte reale}
\text{name_answer2=Parte immaginaria}
#endif

#if defined TARGET_rootcoef
\text{name_statement1=Sia \(P(X)=X^2 + p X + q\) un polinomio dove i
coefficienti \(p\) e \( q\) sono reali. Sappiamo che \(P\) ha una radice
complessa \( z\) di cui la parte immaginaria è uguale a}
\text{name_statement2=In questo caso, si ha una relazione tra i coefficenti
\( p\) e \(q\). Determinare questa relazione scrivendo \( q\) in
funzione di \(p\).}
/* note for translators: keep commas */
\text{name_solution=Se,l'altra radice di \(P\) è,Quindi,dove,Quindi} /*'*/
#endif



#if defined TARGET_sqrt
/* note for translators: keep commas */
\text{name_statement=Determinare una radice quadrata \(w\) del numero complesso,
fornendo parte reale e parte immaginaria}
#endif

#if defined TARGET_modmax
/* note for translators: keep commas */
\text{name_statement=Tra tutti i numeri complessi \(z\) di modulo,
trovare quello per il quale il modulo di,è massimo}
#endif
#if defined TARGET_maxmod
\text{name_list_maxmin=massimo,minimo}
/* note for translators: keep commas */
\text{name_statement=Qual è il,del modulo,dove \(z\) è un numero complesso di modulo}
\text{name_answer=del modulo}
#endif

#if defined TARGET_Trianglequilat
\text{name_and=e}
/* note for translators: keep commas */
\text{name_statement=Se \(A\) e \(B\) sono dei punti del piano corrispondenti a,
trovare il numero complesso corrispondente al punto \(M\) tale che il triangolo \(ABM\) sia equilatero}
\text{name_hint=\(AM\) è l'immagine di \(AB\) attraverso una rotazione. Quale?}
#endif

#if defined TARGET_quadpoly
\text{name_statement=Calcolare le due radici del polinomio}
\text{name_instruction=Potete fornire le due radici \(r1\) e \(r2\) nell'ordine che preferite.} /*'*/
\text{name_condition1=è una radice}
\text{name_condition2=è l'altra radice} /*'*/
#endif

#if defined TARGET_sumofi
\text{name_statement=Calcolare la somma}
#endif

#if defined TARGET_suminv
/* note for translators: keep commas */
\text{name_statement=Sia \(z\) un numero complesso con,Calcolare}
#endif

#if defined TARGET_sumroot
/* note for translators: keep commas */
\text{name_statement=Sia,Qual è il valore di}
\text{name_hint=è una radice del polinomio}
#endif


#if defined TARGET_powerconj
/* note for translators: keep commas */
\text{name_statement=Quanti sono i numeri complessi \(z\) tali che,è uguale al coniugato di \(z\)}
\text{name_answer=I numeri}
/* note for translators: keep commas */
\text{name_solution=Sia \(w\) il coniugato di \(z\).  Osserviamo subito che,
implica \(|z|=1\) o 0. Quando \(|z|=1\) abbiamo,
quindi i numeri complessi \(z\) che verificano la condizione del problema sono esattamente le radici del polinomio}
\text{name_or=ou}
#endif


