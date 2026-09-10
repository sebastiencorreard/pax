#if defined TARGET_majbase
\text{name_statement1=I numeri nelle operazioni seguenti sono scritti in una certa base \(b\):}
\text{name_statement2=Dare tutte le basi possibili con questa singola
    indicazione senza cercare di trovare una soluzione
    (se ce ne è più di una, separarle con virgole):}
\text{name_hint=Cercare maggiorazioni o minorazioni di ciascuno dei numeri
   in funzione della base \(b\) e confrontarle. Per esempio,
   \(2\bullet\bullet\bullet\) è compreso tra \(2 b^3\)
   e \(3 b^3\), \(23\bullet\bullet\) è compreso tra \((2b+3)* b^2\)
   e \((2b+4)* b^2\).
   Potete utilizzare gli strumenti grafici per risolvere le equazioni più
   complesse.}
#endif
#if defined TARGET_divisiontrou
\text{name_statement=La moltiplicazione seguente, in base \(b\),
  è stata effettuata solo parzialmente. Dire in quale base è stata effettuata
  questa moltiplicazione e individuare le cifre mancanti:}
\text{name_instruction=La base è inferiore a \lim. Le cifre sono
    scritte da 0 a 9, quindi con le lettere \(A\), \(B\), ...}
\text{name_condition=è una cifra in base}
\text{name_inbase=in base}
%%% note for translators: keep commas
\text{name_solution=Una possibile soluzione è,con}
#endif
#if defined TARGET_division
%%% note for translators: keep commas
\text{name_statement=Effettuare la divisione euclidea di,nel sistema di numerazione in base \b.}
\text{name_by=per}
\text{name_quotient=Quoziente}
\text{name_remainder=Resto}
#endif
#if defined TARGET_mental
\text{name_statement=Calcolare rapidamente \( \a - \b \) in base \base
  utilizzando il metodo descritto nelle istruzioni:}
\text{name_instruction=Tutti i numeri sono scritti in base \base.}
\text{name_help1=Ecco un metodo che permette di svolgere addizioni e
    complementi a \base invece che sottrazioni:}
#endif
#if defined TARGET_mental10
\text{name_statement=Calcolare rapidamente \( \a - \b \) utilizzando il metodo
  descritto nelle istruzioni:}
\text{name_help1=Ecco un metodo che potete usare se preferite svolgere
    addizioni e complementi a 10 piuttosto che sottrazioni:}
\text{name_help5=Questo metodo funziona perfettamente anche quando i numeri
    sono scritti in base \(b\) invece che in base 10.}
#endif
#if defined TARGET_mental|| defined TARGET_mental10
\text{name_numbdig=Numero di cifre}
\text{name_of=di}
\text{name_help2=se \(p\) è il numero di cifre di \b, calcolare}
\text{name_help3=Per calcolare \(10^p - \b\): la cifra delle unità è
  il complemento a 10 della cifra delle unità, le altre sono i complementi
  a 10 meno 1.}
\text{name_help4=e elevare \(10^p\) non è troppo difficile in generale, se
  la cifra \(p+1\) non è uno 0.}
#endif
#if defined TARGET_add
\text{name_statement=Effettuare in base \b, la somma dei numeri}
\text{name_and=e}
#endif
#if defined TARGET_geonum1D
\text{name_statement=Scrivere le coordinate del numero indicato utilizzando il sistema di numerazione binario}
#endif
#if defined TARGET_geonum1D || TARGET_geonum2D
\text{name_instruction_point=Come separatore per i decimali utilizza il punto.}
#endif
#if defined TARGET_mult
\text{name_statement=In quale base la moltiplicazione seguente ha senso?}
\text{name_feedback1=C'è un'altra soluzione \(b = \b\) .}
%%% note for translators: keep commas
\text{name_feedback2=In base, si ha,La risposta è}
\text{name_feedback3=In base \(b\), tutte le cifre devono essere
  strettamente inferiori a \(b\). Questo non succederebbe qui se fosse}
#endif
#if defined TARGET_tablemult
\text{name_statement=Ecco alcune moltiplicazioni eseguite in uno stesso
    sistema di numerazione. Individua questo sistema di numerazione:
    indicandone la base \(b\) (scritta in notazione
  decimale). }
\text{name_condition=La base è corretta?}
\text{name_feedback1=Un sistema di numerazione possibile è}
%%% note for translators: keep commas
\text{name_feedback2=Nella base,che voi avete indicato,è uguale a,e non a}
%%% note for translators: keep commas
\text{name_feedback3=In un sistema di numerazione in base,le cifre sono "inferiori" a}
#endif
#if defined TARGET_mult || defined TARGET_tablemult
\text{name_base=Base}
#endif
#if defined TARGET_addition
\text{name_statement=Compilare la tavola di addizione di \n utilizzando il sistema di numerazione in base \b.}
\text{name_help=wims(record 0 of help.it)}
#endif
#if defined TARGET_entierbase
\text{name_statement1=Quanti numeri interi positivi ammettono una scrittura in base \base costituita da \n cifre?}
\text{name_statement12=Sì, ci sono \sol1 numeri interi positivi per cui la scrittura in base \base è costituita da \n cifre.}
\text{name_statement2=In quanti di questi numeri la cifra \ch appare una e una sola volta?}
\text{name_answer=Risposta}
\text{name_feedback1=Attenzione, il numero che avete dato è in realtà la cardinalità di}
\text{name_feedback2=Le sequenze di \n cifre che cominciano per 0
    non sono numeri a \n cifre.}
#endif
#if defined TARGET_numgeo1D
\text{name_statement=Posizionare sulla retta dei numeri il punto di coordinate
  <b>\nombre</b> scritto nel sistema di numerazione binario}
#endif
#if defined TARGET_numgeo2D
\text{name_statement=Posizionare nel piano il punto le cui cordinate scritte
    nel sistema di numerazione binario sono }
#endif
#if defined TARGET_borne
\text{name_list_bigsml=grande,piccolo}
\text{grand=item(\c,\name_list_bigsml)}
\text{name_statement=Trovare il più \grand numero (scritto nel sistema di
  numerazione decimale) avente \n cifre nel sistema di numerazione in base \b.}
#endif
#if defined TARGET_livre
\text{name_statement=Impaginiamo un libro e contiamo il numero di cifre utlizzate.}
\matrix{name_matrix_question=Il libro ha \page pagine. Quanti caratteri sono stati utilizzati per scrivere i numeri di pagina
Abbiamo utilizzato \caractere caratteri per scrivere i nuemri di pagina. Quante pagine ha il libro}
\text{name_characters=caratteri}
\text{name_pages=pagine}
\text{name_numberof=Numero di}
#endif
#if defined TARGET_geonum2D
\text{name_statement=Scrivere le coordinate del punto del piano indicato, scritte utilizzando la notazione binaria:}
#endif
#if defined TARGET_multiplication
\text{name_statement=Scrivere tabellina (di moltiplicazione) per
  \zn nel sistema di numerazione in base \b.}
#endif
#if defined TARGET_immatriculation
\text{name_statement1=Le nuove targhe automobilistiche Francesi sono ora in circolazione. A ogni veicolo immatricolato
    viene assegnato un numero valido per sempre. Questo numero è costituito da sette caratteri, suddivisi in tre blocchi:}
\text{name_statement2=La numerazione dei veicoli è costruita in maniera
    cronologica e a livello nazionale, da AA-001-AA a ZZ-999-ZZ, tali
    numeri costituiscono una successione nel modo seguente:}
\matrix{name_matrix_statement=Primo blocco: due lettere
    Secondo blocco: tre cifre
    Terzo blocco: due lettere
    da AA-001-AA a AA-999-AA
    quindi da AA-001-AA a AA-999-AB, etc.
    quindi da AA-001-BA a AA-999-BZ, etc.
    quindi da AB-001-AA a AZ-999-ZZ
    quindi da BA-999-AA a ZZ-999-ZZ
    }
\matrix{name_matrix_instruction1=Quanti veicoli devono essere immatricolati per avere il numero \Imat ?
Qual è il numero di veicoli immatricolati prima di arrivare al numero \Imat?
Qual è il numero di veicoli immatricolati prima di arrivare al numero \Imat?}
\text{name_instruction2=Dire qual è il numero di immatricolazione del veicolo \voit2-esimo.}
\text{name_instruction3=Quanti anni al massimo può essere utilizzato questo
    sistema di numerazione se ogni anno vengono immatricolati \N milioni di
    veicoli?}
#endif
#if defined TARGET_nbit3
\text{name_statement=Un intero \(n\) ha \N cifre in base \b .
    Dire qual è la più piccola base \(b\) nella quale tale numero ha sicuramente
    meno di \M ciffre.}
\text{name_base=base}
#endif
#if defined TARGET_changbin
\text{name_statement=Dire qual è la scrittura in base \(\b^\k\) del numero la cui scrittura in base \(\b\) è}
\text{name_instruction1=Utilizzare le <em>cifre</em>}
\text{name_instruction2=senza spazi}
\text{name_instruction3=separandole con uno spazio}
\text{name_instruction4=Non inserire spazi tra le cifre}
\text{name_answer=in base}
#endif
#if defined TARGET_musique
\text{name_statement=Scrivere il valore della seguente successione di note
  come un numero binario decimale}
\text{name_answer=Valore del tema}
\text{name_condition=La tua risposta:}
\text{name_feedback=Il valore è}
\text{name_list_notes=semiminima,minima,semibreve,croma,semicroma}
\text{name_help1=La notazione musicale corrisponde naturalmente
   a un sistema binario decimale.}
\text{name_help2=Prendiamo una semiminima come unità di base (1).
    La minima vale due semiminime, la semibreve vale quattro semiminime,
  la croma vale la metà di una semiminima, la semicroma vale un quarto di
  una semiminima.
  Nei rapporti precedenti intervegono solo potenze di 2.}
\text{name_help3=Per scrivere un valore + la metà di questo valore,
  facciamo seguire il valore da un punto. Due punti
  significano il valore + la sua metà + il suo quarto.}
\text{name_help4=Siamo quindi in un sistema binario decimale.}
\text{name_explanation=spiegazione}
#endif
#if defined TARGET_guess
\text{name_statement=Il computer ha scelto un numero tra 1 e 63.
  Dovete indovinare questo numero. Per aiutarti ti indica che questo numero
  si trova solamente sulle cartelle gialle. Qual è questo numero?}
\text{name_answer=Il numero è}
\text{name_hint=Quali numeri si trovano su ognuna cartella?}
#endif

