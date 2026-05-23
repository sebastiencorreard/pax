#if defined TARGET_classer1 || defined TARGET_classer2 || defined TARGET_classer3 || defined TARGET_classer4
\text{name_enonce=Classificare le funzioni seguenti in base alla loro natura}
\text{name_type=Funzioni lineari,
  Funzioni affini,
  Funzioni non affini,
  non lineari}
#endif
#if defined TARGET_eqdroite
\matrix{name_enonce=La retta \(d) passa per i punti,e
Essendo, la retta \(d\) ammette una equazione della forma}
\text{name_question=Completa l'equazione di}
\text{name_answer=Espressione}
#endif
#if defined TARGET_imagecoord1 || defined TARGET_imagecoord2
\text{name_feed=Ecco la risposta}
# if defined TARGET_imagecoord1
\text{name_enonce=Ecco una rappresentazione grafica della funzione \(g\).
  Sull'asse delle ordinate, clicca sul punto di ordinata}
# endif
# if defined TARGET_imagecoord2
\text{name_enonce=Ecco una rappresentazione grafica della funzione \(f\).
  Sull'asse delle ascisse, clicca sul punto di ascissa \(x\) tale che}
# endif
#endif
#if defined TARGET_qcmfonct
\text{name_question=Qual è la funzione \(f\) la cui rappresentazione grafica
    è qui sotto? Indica una espressione di \(f(x)\).}
#endif
#if defined TARGET_qcmequa
\text{name_question=Qual è l'equazione esplicita della retta qui sotto}
#endif
#if defined TARGET_CORequa3 || defined TARGET_CORfonct3 || defined TARGET_CORequa4|| defined TARGET_CORfonct4 || defined TARGET_CORequa5 || defined TARGET_CORfonct5
\text{co=red;#;rosso,green;#;verde,yellow;#;giallo,purple;#;viola,blue;#;blu,black;#;nero}
\text{name_question1=Metti in corrispondenza ogni funzione con il colore della sua rappresentazione grafica nel disegno a fianco.}
\text{name_question2=Metti in relazione ogni equazione con il colore della retta corrispondente nel disegno a fianco.}
\text{name_answer=Risposta}
#endif
#if defined TARGET_graphima || defined TARGET_graphant
\text{name_enonce=La rappresentazione grafica della funzione affine,
  è la seguente}
\text{name_answer=La tua risposta}
# if defined TARGET_graphima
\text{name_question=Quale numero è l'immagine di,tramite}
\text{name_ans=L'immagine di,tramite la funzione,è}
\text{name_sol1=L'immagine di,tramite la funzione,è per definizione
  <b>l'ordinata</b> del punto sulla retta la cui ascissa è}
\text{name_sol2=Si prende quindi il punto della retta la cua ascissa è,
  quindi si legge la sua ordinata.}
# endif
# if defined TARGET_graphant
\text{name_question=Quale numero ha per immagine,tramite la fuzione}
\text{name_ans=Il numero che ha per immagine,tramite la funzione,è}
\text{name_sol1=Il numero che ha per immagine,tramite la funzione,è per definizione
  <b>l'ascissa</b> del punto della retta la cui ordinata è}
\text{name_sol2=Si prende quindi il punto della retta la cui ordinata è,
  quindi si legge la sua ascissa.}
\text{name_cond=Immagine}
# endif
#endif
#if defined TARGET_fnctaff1
\text{name_enonce=L'immagine di, rispetto alla funzione affine , è ,
  e l'immagine di, rispetto alla stessa funzione è}
\text{name_enonce2=La funzione, si può scrivere nella forma }
\text{name_question=Qual è questa  formulazione}
\text{name_answer=Espressione}
#endif
#if defined TARGET_fnctaff2
\text{bad=Sì,No}
\matrix{name_enonce=La tabella seguente fornisce le immagini di tre numeri rispetto alla funzione FFFF
La tabella seguente fornisce l'immagine rispetto alla funzione FFFF di tre numeri}
\text{name_question=può essere una funzione affine}
\text{name_answer=La tua risposta}
#endif
#if defined TARGET_fnctaff3 || defined TARGET_fnctaff4
\text{name_don=L'immagine tramite,di,è}
\text{name_enonce=è una funzione affine tale che l'immagine di,
  è, e l'immagine di, è}
\text{name_aim=L'obiettivo è trovare l'espressione della funzione,
  La funzione è affine, si devono quindi trovare due numeri \(a\) e
  \(b\) tali che,per ogni numero}
# if defined TARGET_fnctaff3
\text{name_inst=Puoi utilizzare la calcolatrice cliccando sul link in
  fondo a questa pagina.}
\text{name_resolv=Per risolvere questo esercizio, rispondi alle domande seguenti}
\text{name_and=e}
\text{name_quest=Domanda,La tua risposta,Traduci la frase,
  in una equazione che coinvolge}
\text{name_sentence=L'immagine tramite, di, è}
\text{name_question=Risolvi il sistema di equazioni, di incognite \(a\)
  e \(b\), formato dalle due equazioni precedenti.}
\text{name_answer=Prima equazione,Seconda equazione}
# endif
# if defined TARGET_fnctaff4
\text{name_resolv=Per risolvere questo esercizio, rispondi alle domande seguenti}
\text{name_and=e}
\text{name_quest=Domanda,La tua risposta}
\text{name_question=Per una funzione affine,
  il rapporto, con \(u\) e \(v\) due numeri qualsiasi distinti,
  è uguale al coefficiente angolare della funzione,
  Ricavare il valore di \(a\).}
\text{name_deduc=Si deduce quindi che l'equazione della funzione,
  è della forma}
\text{name_question2=Ricava una equazione di primo grado nell'incognita \(b\) dall'affermazione}
\text{name_question3=Trova il valore di \(b\) risolvendo l'equazione della domanda 2.}
\text{name_answer=Equazione}
# endif
#endif
