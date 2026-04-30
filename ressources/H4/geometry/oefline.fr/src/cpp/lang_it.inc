#if defined TARGET_equ_dr5 || defined TARGET_equ_dr4 || defined TARGET_equ_dr_mcd || defined TARGET_parallele || defined TARGET_equ_dr1 || defined TARGET_syst1 || defined TARGET_syst2 || defined TARGET_pllsec2 || defined TARGET_secnico || defined TARGET_ordonnee || defined TARGET_sys3_app || defined TARGET_abscisse
\text{name_and=e}
#endif
#if defined TARGET_equ_dr5 || defined TARGET_equ_dr_mcd || defined TARGET_eqgeqr || defined TARGET_equ_dr1 || defined TARGET_equ_dr0 || defined TARGET_equ_dr2 || defined TARGET_equ_dr4 || defined TARGET_ordonnee || defined TARGET_abscisse
\text{name_is=è}
#endif
#if defined TARGET_equ_dr_mcd
\text{name_or=o}
#endif
#if defined TARGET_pllsec2 || defined TARGET_equ_dr2 || defined TARGET_equ_dr5 || defined TARGET_equ_dr4 || defined TARGET_equ_dr0
\text{name_solution=L'equazione esplicita della retta}
#endif
#if defined TARGET_equ_dr0 || defined TARGET_equ_dr2 || defined TARGET_equ_dr5 || defined TARGET_equ_dr4
\text{name_answer1=Coefficiente angolare}
\text{name_answer2=Ordinata nell'origine}
#endif

#if defined TARGET_pllsec2
\text{name_options_list=parallele,incidenti}
\text{name_yesno=sì,no}
\text{name_statement1=Esatto, le rette sono parallele. Sono coincidenti}
\text{name_statement2=Esatto, le rette sono incidenti. Determinare le coordinate \( (x ; y) \) del punto di intersezione.}
# note for translators: semicolons are line separators
\matrix{name_statement=Nel piano descritto da un sistema di riferimento cartesiano, consideriamo le rette ; di equazione ; Le rette sono }
\text{name_answer=Coincidenti}
#endif

#if defined TARGET_equ_dr0
# note for translators: semicolons are line separators
\matrix{name_statement=Nel piano descritto da un sistema di riferimento cartesiano, consideriamo la retta ; di equazione ; Determinare il coefficiente angolare e l'ordinata nell'origine della retta}
#endif

#if defined TARGET_secnico
# note for translators: commas are separators
\text{name_statement=Il piano è descritto da un sistema di riferimento cartesiano ortonormale,Siano,le retta di equazioni rispettivamente,Sappiamo che le rette,sono incidenti in un punto,Determinare le coordinate del punto}
\text{name_answer1=Ascissa di}
\text{name_answer2=Ordinata di}
#endif

#if defined TARGET_equ_dr2
\text{name_statement1=Nel piano descritto da un sistema di riferimento cartesiano, consideriamo la retta \(\math_droite\) rappresentata in figura.
Determinare dal grafico l'ordinata nell'origine e il coefficiente angolare di quetsa retta.}
#endif

#if defined TARGET_equ_dr4
\text{name_statement1=Nel piano descritto da un sistema di riferimento cartesiano, consideriamo la retta \(\math_droite\) passante per i punti }
#endif

#if defined TARGET_equ_dr2 || defined TARGET_equ_dr4
\text{name_statement2=L'equazione in forma esplicita di}
#endif


#if defined TARGET_ordonnee
# note for translators: commas are separators
\text{name_statement=Il piano è descritto da un sistema di riferimento cartesiano ortonormale,Sia,la retta di equazione,il punto di ascissa}
\text{name_question=Determinare l'ordinata \( y_A \) del punto \( A \) nel sistema di riferimento.}
\text{name_answer=L'ordinata di}
#endif

#if defined TARGET_abscisse
# note for translators: commas are separators
\text{name_statement=Il piano è descritto da un sistema di riferimento cartesiano ortonormale,Sia,la retta di equazione,il punto di ordinata}
\text{name_question=Determinare l'ascissa \( x_A \) del punto \( A \) nel sistema di riferimento.}
\text{name_answer=L'ascissa di}
#endif

#if defined TARGET_para2
# note for translators: commas are separators
\text{name_statement=Il piano è descritto da un sistema di riferimento cartesiano ortonormale,Sia,la retta di equazione,Determinare l'equazione esplicita della retta,parallela alla retta,passante per il punto}
\text{name_answer=Equazione della retta}
\text{name_feedback1=L'equazione della retta è}
\text{name_feedback2=L'equazione data non è l'equazione di una retta parallela a}
#endif

#if defined TARGET_sys3
\text{name_statement=Risolvere il seguente sistema}
\text{name_instruction=<b>Istruzioni:</b> Le soluzioni sono numeri interi.}
#endif

#if defined TARGET_sys3_app
\text{name_option_list=gomme da masticare,liquerizie,gommose alla fragola}
\text{name_anoption_list=Una gomma da masticare,Una liquerizia,Una gommosa alla fragola}
\text{name_statement=Tre studenti comprano dolcetti}
# note for translators: commas are separators
\text{name_question=compra,e paga,euro,Calcola il prezzo di ciascun tipo di dolcetto,costa}
#endif

#if defined TARGET_equdroitevoc
\text{name_statement1=Il piano è descritto da un sistema di riferimento cartesiano ortonormale}
\text{name_statement2=Sia \((\math_droite) \) la retta di equazione}
\text{name_statement3=Determinare il coefficiente angolare della retta \( (\math_droite)\) e la sua ordinata nell'origine}
\text{name_answer1=Coefficiente angolare di}
\text{name_answer2=Ordinata nell'origine di}
\text{name_feedback=Attenzione: avete confuso il coefficiente angolare con l'ordinata nell'origine}
#endif

#if defined TARGET_equ_dr1
# note for translators: semicolons are line separators
\matrix{name_statement=Nel piano descritto da un sistema di riferimento cartesiano, consideriamo la retta ; passante per il punto ; di coordinate ; e diretta secondo il vettore ; di coordinate ; Determinare una equazione della retta ; Una possibile equazione della retta ; la sua equazione in forma esplicita è}
\text{name_answer1=Coefficiente}
\text{name_answer2=Il coefficiente angolare della retta }
\text{name_answer3=L'ordinata nell'origine della retta }
\text{name_condition1=è un vettore direttore corretto di questa retta}
# note for translators: commas are separators
\text{name_condition2=Il punto,si trova su questa retta}
# note for translators: commas are separators
\text{name_solution=Una possibile equazione della retta è,la sua equazione in forma esplicita è}
#endif

#if defined TARGET_eqgeqr
\text{name_question_list=il coefficiente angolare,l'ordinata nell'origine}
\text{name_Question_list=Il coefficiente angolare,L'ordinata nell'origine}
# note for translators: semicolons are line separators
\matrix{name_statement=Consideriamo la retta ; di equazione ; Determinare ; della retta }
\text{name_reponse=Risposta}
#endif

#if defined TARGET_equa_red
\text{name_statement=Associare le equazioni che corrispondono alla stessa retta}
#endif

#if defined TARGET_parallele
# note for translators: commas are separators
\text{name_statement=Determinare,in modo che le rette,di equazioni rispettivamente,siano parallele,Un possibile valore di }
#endif

#if defined TARGET_syst1 || defined TARGET_syst2
\text{name_statement=Risolvere il sistema seguente}
\text{name_answer=Valore di}
\text{name_solution=Le soluzioni sono}
#endif

#if defined TARGET_equ_dr5
\text{name_options_list=ascisse,ordinate}
# note for translators: semicolons are line separators
\matrix{name_statement=Nel piano descritto da un sistema di riferimento cartesiano, consideriamo la retta ; di equazione ; la retta ; parallela a ; passante per il punto}
# note for translators: semicolons are line separators
\matrix{name_question=Determinare le coordinate le punto di intersezione ; della retta ; con l'asse delle }
#endif

#if defined TARGET_pointdroite
# note for translators: semicolons are line separators
\matrix{name_statement=Nel piano descritto da un sistema di riferimento cartesiano, consideriamo la retta \(\math_droite\) di equazione ; Per quale valore di \(b\), il punto \(M\) di coordinate ; appartiene a \(\math_droite\)}
#endif

#if defined TARGET_equ_dr_mcd || defined TARGET_pllsec2
\text{name_difflevel=Questo esercizio è composto da due passi.}
#endif
#if defined TARGET_equ_dr_mcd
\text{name_options_list=parallela all'asse delle ordinate , parallela all'asse delle ascisse, non parallela ad alcun asse}
# note for translators: semicolons are line separators
\matrix{name_statement=Nel piano descritto da un sistema di riferimento cartesiano, consideriamo i punti ; La retta ; è ; Sì, la retta ; Scrivi la sua equazione ; }
\text{name_instruction=Cliccare sull'opzione corretta.}
#endif

#if defined TARGET_pointsentiers
# note for translators: semicolons are line separators
\matrix{name_statement=Determinare un punto \(M\) sulla retta \(\math_droite\) di equazione ; le cui coordinate siano <b>numeri interi</b> ; Il punto ; è una soluzione possibile }
\text{name_condition1=Il punto \(M\) appartiene a \(\math_droite\)}
\text{name_condition2=L'ascissa di \(M\) è un numero intero}
\text{name_condition3=L'ordinata di \(M\) è un numero intero}
#endif

