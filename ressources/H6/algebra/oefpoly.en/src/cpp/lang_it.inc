#if defined TARGET_mindeggcd2 || defined TARGET_rootcomp || defined TARGET_rerootdeg2 || defined TARGET_rootcnt
\text{comma=}
#endif

#if defined TARGET_relrtdeg2
\text{name_statement1=Siano \(r_1), \(r_2) le due radici del polinomio}
\text{name_statement2=dove \(a) è un coefficiente reale. Qual è il valore di}
\text{name_hint1=Abbiamo}
\text{name_hint2=Ora usa la relazione tra le radici e i coefficienti del polinomio}
#endif

#if defined TARGET_relrtdeg3
\text{name_statement1=Siano \(r_1\), \(r_2\), \(r_3\) le tre radici del polinomio}
\text{name_statement2=dove \(a) è un coefficiente reale non nullo. Qual è il valore di}
#endif

#if defined TARGET_relrtdeg2 || defined TARGET_relrtdeg3
\text{name_instruction=Questo valore è una funzione di}
#endif

#if defined TARGET_mindeggcd2 || defined TARGET_deggcd || defined TARGET_mindeggcdn
note for translators: in the following keep commas
\text{name_statement=Sia,un polinomio di grado,a coefficienti,avente,radici reali e,radici complesse differenti (non contate con molteplicità),Sia}
#endif

#if defined TARGET_mindeggcd2 || defined TARGET_deggcd || defined TARGET_mindeggcdn || defined TARGET_rootcnt || defined TARGET_givderiv
\text{name_gcd=MCD}
#endif

#if defined TARGET_deggcd
\text{name_derivative=la derivata di}
\text{name_question=Qual è il grado di}
\text{name_answer=Grado di}
\text{name_hint=Le radici del MCD(\(P(x),P'(x))) sono esattamente
le radici multiple di \(P\).}
#endif

#if defined TARGET_mindeggcd2
\text{name_derivative=la derivata seconda di}
\text{name_question=Qual è il minimo possibile per il grado di}
\text{name_answer=Minimo di}
\text{name_hint=Le radici multiple di \(P\) con molteplicità \( >2 \) sono tra le radici di \(MCD(P(x),P''(x))\).}
#endif

#if defined TARGET_mindeggcdn
note for translators: in the following keep commas
\text{name_derivative=la derivata di ordine,di}
\text{name_question=Qual è il minimo dei gradi di}
\text{name_answer=Minimo di}
#endif

#if defined TARGET_stadouble
\text{name_statement=Qual è il tipo di radici del polinomio di grado 2 qui sotto}
\text{name_choice=Tipo di radici}
\text{name_type_list=una radice reale una radice complessa non reale,una radice doppia reale,una radice doppia non reale,due radici semplici reali,due radici complesse coniugate}
#endif

#if defined TARGET_parmdeg2
\text{name_type_list=due radici semplici reali,
  due radici complesse coniugate,
  una radice doppia}
note for translators: in the following keep commas
\text{name_statement=Per quali valori del parametro reale,il polinomio,ha}
\text{name_choice=La condizione}
\text{name_answer=Dove}
#endif

#if defined TARGET_parmdeg2b
note for translators: in the following keep commas
\text{name_statement=Per quali valori del parametro reale,il polinomio,ha una radice uguale a,a condizione che}
#endif


#if defined TARGET_givderiv
note for translators: in the following keep commas
\text{name_statement=Trova il polinomio,tale che,dove,è il polinomio derivato di,il grado di,è il più piccolo possibile}
note for translators: in the following keep commas
\text{name_instruction=Puoi inserire il polinomio fattorizzato o meno,Scrivi,per}
\text{name_andsoon=ecc}
#endif

#if defined TARGET_diffeqn
note for translators: in the following keep commas
\text{name_statement=Trova il polinomio,tale che,e che}
note for translators: in the following keep commas
\text{name_instruction=Scrivi,per}
\text{name_andsoon=ecc}
#endif

#if defined TARGET_givrtdeg3
note for translators: in the following keep commas
\text{name_statement=Trova il polinomio,sapendo che,sono reali e che,ne è una radice}
\text{name_answer=La radice reale}
#endif

#if defined TARGET_rootcomp
\text{name_item_list=è una radice di,è una radice di,è anche una radice di}
note for translators: in the following keep commas
\text{name_statement=Siano,un polinomio,un altro polinomio,Considera i polinomi composti,Completa}
note for translators: in the following keep commas
\text{name_question=Se,è una radice di,allora}
\text{name_answer=Il numero da completare}
#endif


#if defined TARGET_rootmultsum || defined TARGET_rootcnt
\text{name_of=di}
#endif

#if defined TARGET_rootmultsum || defined TARGET_degsum
\text{name_statement1=Siano \(P(X)\) e \(Q(X)\) due polinomi. Completa}
#endif

#if defined TARGET_rootmultsum
\text{name_sup=maggiore o uguale a m}
\text{name_inf=minore o uguale a m}
\text{name_equ=uguale a m}
note for translators: in the following keep commas
\text{name_statement2=Se,è una radice di molteplicità,e una radice di molteplicità,allora,è una radice di molteplicità}
\text{name_choice=La molteplicità è}
\text{name_answer=Dove}
#endif

#if defined TARGET_degsum
\text{\name_sup=maggiore o uguale a un numero d}
\text{\name_inf=minore o uguale a un numero d}
\text{\name_equ=uguale a un numero d}
note for translators: in the following keep commas
\text{name_statement2=Se,allora,è un polinomio di grado}
\text{name_choice=Il grado è}
\text{name_answer=Dove}
#endif

#if defined TARGET_tripledeg3 || defined TARGET_tripledeg3b || defined TARGET_rootcomp || defined TARGET_quadpoly || defined TARGET_givrtdeg3 || defined TARGET_degsum
\text{name_and=e}
#endif

#if defined TARGET_tripledeg3 || defined TARGET_tripledeg3b
note for translators: in the following keep commas
\text{name_statement=Per quali valori dei parametri reali,il polinomio,ha una radice tripla}
\text{name_answer=La radice tripla}
\text{name_condition=è una radice tripla}
#endif

#if defined TARGET_tripledeg3
\text{name_hint1=Se \(r\) è una radice tripla di \(P\), allora}
\text{name_hint2=è dunque una radice (reale) del polinomio}
\text{name_where=dove}
#endif

#if defined TARGET_tripledeg3b
\text{name_instruction=La soluzione non è necessariamente unica.}
#endif

#if defined TARGET_trinomefact
\text{name_step=Passo}
\text{name_statement1=Scomponiamo}
\text{name_statement2=Mettiamo i termini contenenti la \(x\) a formare un quadrato perfetto}
\text{name_statement3=Abbiamo}
\text{name_statement4=Quindi}
\text{name_statement5=Ora applichiamo la formula}
\text{name_result=Risultato}
\text{name_instruction=È necessario inserire le espressioni semplificate.}
\text{name_answer1=Termine noto nello sviluppo del quadrato}
\text{name_answer2=Termine costante nel quadrato}
\text{name_answer3=Termine per compensare}
#endif

#if defined TARGET_quadpoly
\text{name_statement=Calcola le due radici del polinomio}
\text{name_instruction=Puoi inserire le due radici \(\r1\) \name_and \(\r2\) in qualunque ordine.}
\text{name_condition1=è una radice}
\text{name_condition2=è l'altra radice}
#endif

#if defined TARGET_rootdeg2
\text{name_statement1=Trova le due radici}
\text{name_statement2=del polinomio}
\text{name_instruction=Le radici sono reali e l'ordine delle radici non ha imporanza.}
\text{name_condition1=è una radice}
\text{name_condition2=Non ci sono altre radici}
#endif

#if defined TARGET_rootcnt
note for translators: in the following keep commas
\text{name_statement=Sia,un polinomio di grado,a coefficienti,e sia,il polinomio derivato di,Sappiamo che,è un polinomio di grado}
note for translators: in the following keep commas
\text{name_question=Qual è il numero di radici,distinte,}
\text{name_note=sia reali che complesse}
\text{name_answer=Numero di radici distinte}
\text{name_hint=Le radici di \(MCD(P(x),P'(x))\) sono esattamente
le radici multiple di \(P(x)).}
#endif

#if defined TARGET_rerootdeg2
note for translators: in the following keep commas
\text{name_statement=Sia,un polinomio a coefficienti reali,avente due radici complesse coniugate,Qual è la parte reale di una radice}
#endif

#if defined TARGET_degmult || defined TARGET_mindeggcd2 || defined TARGET_deggcd || defined TARGET_mindeggcdn || defined TARGET_rootcnt
\text{name_type_list=reali,complessi}
#endif

#if defined TARGET_degmult
note for translators: in the following keep commas
\text{name_statement=Qual è il grado minimo di un polinomio,a coefficienti,che ammette}
\text{name_request1=come radice di molteplicità}
\text{name_request2=come radice di molteplicità}
note for translators: in the following keep commas
\text{name_instruction=Scrivi,se pensi che un tale polinomio non esiste}
\text{name_answer=Minimo dei gradi}
#endif

#if defined TARGET_findmult3 || defined TARGET_findmult4 || defined TARGET_findmult5 || defined TARGET_findmult6
\text{name_statement=Il polinomio seguente ha una radice multipla. Trova questa radice}
\text{name_answer=La radice multipla}
#endif

#if defined TARGET_multiplicity3 || defined TARGET_multiplicity4 || defined TARGET_multiplicity5 || defined TARGET_multiplicity6
note for translators: in the following keep commas
\text{name_statement=Il numero,è una radice del polinomio seguente}
\text{name_statement2=Calcola la sua molteplicità}
\text{name_answer=La molteplicità di}
#endif

#if defined TARGET_multparm3 || defined TARGET_multparm4
\text{name_statement=Trova un valore di \(m\) per cui il polinomio seguente abbia una radice multipla e trova questa radice multipla.}
\text{name_warning=ATTENZIONE}
\text{name_instruction=Questo esercizio non accetta risposte approssimate! C'è una soluzione che è un numero intero. Trovala!}
\text{name_answer=La radice multipla}
\text{name_condition=è una radice multipla di}
\text{name_feedback1=non è nemmeno una radice di}
\text{name_feedback2=È proprio sbagliato.}
\text{name_feedback3=è effettivamente una radice di}
\text{name_feedback4=Perché ci sia una radice multipla, si deve avere}
\text{name_feedback5=sia anche una radice della derivata di}
\text{name_feedback6=che non è quello che si verifica. Controlla meglio i calcoli.}
#endif
