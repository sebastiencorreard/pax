#if defined TARGET_symax2 || defined TARGET_symcen2
\text{name_solution1=Applicando la \action il modulo \(\K[1]\) si sovrappone al modulo <span class="nowrap">\(\K[2]\).</span>}
\text{name_solution2=Il simmetrico rispetto \nom del modulo \(\K[1]\) è il modulo  <span class="nowrap">\(\K[2]\).</span>}
#endif


#if defined TARGET_rota2
\text{name_solution=<p>Dobbiamo quindi contare \coef \saut \name_sens_list[\choix] tra il modulo di partenza \depart e quello di arrivo.<p>
Contiamo perciò \coef \saut \name_sens_list[\choix] a partire dal modulo \depart. Si ottiene il modulo \goodrep.
<p>\name_conclusion: L'immagine del modulo \depart tramite la rotazione di centro \(O\), di angolo \(\angle[\coef]^{\circ}\) \name_sens_list[\choix] è il modulo \goodrep.</p>}
#endif
#if defined TARGET_rota2bis
\text{name_solution1=Contiamo \coef \saut \name_sens_list[\choix] da fare tra il modulo di partenza \depart e il modulo di arrivo \listdeca[\depart]}
\text{name_solution2=L'angolo della rotazione di centro \(O\) \name_sens_list[\choix] che trasforma il modulo \depart in \listdeca[\depart] è <span class="nowrap">\(\goodrep^{\circ}\).</span>}
#endif
#if defined TARGET_symax1
\text{name_solution=Applicando la riflessione rispetto alla retta \((DH)\), il quadrato \(\K[1]\) si sovrappone \sol
<p>\name_conclusion: Il simmetrico rispetto alla retta \((DH)\) del quadrato \(\K[1]\) è il quadrato <span class="nowrap">\(\K[2]\).</span>}
#endif
#if defined TARGET_symcen1
\text{name_solution=Applicando una simmetria centrale rispetto al punto \(O\) il quadrato \(\K[1]\) si sovrappone al quadrato <span class="nowrap">\(\K[2]\).</span>
<p>\name_conclusion: Il simmetrico rispetto al punto \(O\) del quadrato \(\K[1]\) è il quadrato <span class="nowrap">\(\K[2]\).</span>}
#endif
#if defined TARGET_rota1
\text{name_solution=Contiamo \absecart \saut \sens per andare dal quadrato \dep[1] al quadrato \dep[2].
<p>Dobbiamo quindi contare \absecart \saut nello stesso senso a partire dal quadrato <span class="nowrap">\(\K[1]\).</span> Si ottiene il quadrato <span class="nowrap">\(\K[2]\).</span></p>
La rotazione di centro <span class="nowrap">\(O\) </span>che trasforma il quadrato \(\dep[1]\) nel quadrato <span class="nowrap">\(\dep[2]\) </span>trasforma il quadrato \(\K[1]\) nel quadrato <span class="nowrap">\(\K[2]\).</span>}
#endif
#if defined TARGET_symax5
\text{name_solution=Applicando la riflessione rispetto alla retta <span class="nowrap">\((\axe)\),</span> l'aquilone \(\K[1]\) si sovrappone all'aquilone <span class="nowrap">\(\K[2]\).</span>
<p>\name_conclusion: Applicando la simmetria di asse <span class="nowrap">\((\axe)\)</span> l'immagine dell'aquilone \(\K[1]\) è l'aquilone <span class="nowrap">\(\K[2]\).</span></p>}
#endif
#if defined TARGET_symcen5
\text{name_solution=Applicando la simmetria centrale rispetto al punto <span class="nowrap">\(J\),</span> l'aquilone \(\K[1]\) si sovrappone all'aquilone <span class="nowrap">\(\K[2]\).</span>
<p>\name_conclusion: Applicando la simmetria centrale <span class="nowrap">\(J\),</span> l'immagine dell'aquilone \(\K[1]\) è l'aquilone <span class="nowrap">\(\K[2]\).</span></p>}
#endif
#if defined TARGET_symax6
\text{name_solution=Applicando la simmetria di asse <span class="nowrap">\((\axe)\),</span>
<p>il punto \(\ptdep[1]\) ha per immagine il punto <span class="nowrap">\(\ptar[1]\),</span></p>
<p>il punto \(\ptdep[2]\) ha per immagine il punto <span class="nowrap">\(\ptar[2]\),</span></p>
<p>quindi l'immagine del segmento \([\ptdep[1]\ptdep[2]]\) è il segmento <span class="nowrap">\([\ptar[1]\ptar[2]]\).</span></p>}
#endif
#if defined TARGET_symcen6
\text{name_solution=Applicando la simmetria centrale O,
<p>il punto \(\tdep[1]\) ha per immagine il punto <span class="nowrap">\(\tar[1]\),</span></p>
il punto \(\tdep[2]\) ha per immagine il punto <span class="nowrap">\(\tar[2]\),</span>
<p>il punto \(\tdep[3]\) ha per immagine il punto <span class="nowrap">\(\tar[3]\),</span></p>
<p>il punto \(\tdep[4]\) ha per immagine il punto <span class="nowrap">\(\tar[4]\),</span></p>
<p>il simmetrico del quadrilatero \(\K\) è il quadrilatero <span class="nowrap">\(\quadrep[1]\).</span></p>}
#endif
#if defined TARGET_rota6
\text{name_solution=Applicando la rotazione di centro O che trasforma il triangolo \(\A[2]\) nel triangolo <span class="nowrap">\(\A[3]\),</span>
<p>l'immagine del punto \(\ptA[1]\) è <span class="nowrap">\(\t[1]\),</span></p>
<p>l'immagine del punto \(\ptA[2]\) è <span class="nowrap">\(\t[2]\),</span></p>
<p>l'immagine del punto \(\ptA[3]\) è <span class="nowrap">\(\t[3]\),</span></p>
quindi l'immagine del triangolo \(\A[1]\) è il triangolo <span class="nowrap">\(\trirep[1]\).</span>}
#endif
#if defined TARGET_trans2
\text{name_solution=Il quadrilatero \(\pt[1]\pt[2]\quest[1;2]\quest[1;1]\) è un parallelogramma quindi la traslazione
che trasforma il punto \(\pt[1]\) nel punto \(\pt[2]\)
trasforma anche il punto \(\quest[1;1]\) nel punto <span class="nowrap">\(\quest[1;2]\).</span>
</p>
<p>Il quadrilatero \(\pt[1]\pt[2]\quest[2;2]\quest[2;1]\) è un parallelogramma quindi la traslazione
che trasforma il punto \(\pt[1]\) nel punto \(\pt[2]\) trasforma anche
il punto \(\quest[2;1]\) nel punto <span class="nowrap">\(\quest[2;2]\).</span></p>
Il quadrilatero \(\pt[1]\pt[2]\quest[3;2]\quest[3;1]\) è un parallelogramma quindi la traslazione
che trasforma il punto \(\pt[1]\) nel punto \(\pt[2]\) trasforma anche il punto
\(\quest[3;1]\) nel punto <span class="nowrap">\(\quest[3;2]\).</span></p>
<p>Il quadrilatero \(\pt[1]\pt[2]\quest[4;2]\quest[4;1]\) è un parallelogramma quindi la traslazione
che trasforma il punto \(\pt[1]\) nel punto \(\pt[2]\) trasforma anche il punto \(\quest[4;1]\)
nel punto <span class="nowrap">\(\quest[4;2]\).</span></p>}
#endif

#if defined TARGET_trans1 || defined TARGET_trans2 || defined TARGET_trans3im || defined TARGET_trans3ant || defined TARGET_trans7
\text{name_hint=Una traslazione è una trasformazione geometrica che corrisponde all'idea intuitiva di «scivolamento» di un oggetto,
senza rotazione, né ribaltamento, né deformazione di tale oggetto.
<p>Per esempio, la figura blu è l'immagine della figura rossa tramite la traslazione che trasforma il punto \(A\) in <span class="nowrap">\(A^{'}\).</span></p>
<div class="wimscenter"><img src="\imagedir/hinttrans2.png" alt="Traslato di cocotte"></div>
<p>L'immagine di \(A\) è \(A^{'}\), l'immagine di \(C\) è \(C^{'}\), l'immagine di \(H\) è \(H^{'}\).</p>
I quadrilateri \(A A^{'}C^{'}C\) e \(A A^{'}H^{'}H\) sono parallelogrammi.}
#endif
#if defined TARGET_associerapportsitu
\text{name_hint=Consideriamo un'omotetia di rapporto \(k\) dove \(k\) indica un numero diverso da zero.
<ul>
  <li>Se \(k > 1\) allora l'omotetia è un ingrandimento con inversione.</li>
  <li>Se \(0 < k < 1\) allora l'omotetia è una riduzione senza inversione.</li>
  <li>Se \(-1 < k < 0\) allora l'omotetia è una riduzione con inversione.</li>
  <li>Se \(k< -1\) allora l'omotetia è un ingrandimento con inversione.</li>
</ul>}
#endif
#if defined TARGET_symax3
\text{name_solution=Applicando la riflessione rispetto alla retta <span class="nowrap">\((\axe[1])\),</span> il modulo \(\K[1]\) si sovrappone al modulo <span class="nowrap">\(\K[2]\).</span>
<p>\name_conclusion: Il simmetrico del modulo \(\K[1]\) rispetto alla retta \((\axe[1])\) è il modulo <span class="nowrap">\(\K[2]\).</span></p>}
#endif

#if defined TARGET_symcen3
\text{name_solution=Con una rotazione di mezzo giro attorno al punto <span class="nowrap">\(G\),</span> il modulo \(\K[1]\) si sovrappone al modulo <span class="nowrap">\(\K[2]\).</span>
<p>\name_conclusion: Il simmetrico del modulo \(\K[1]\) rispetto al punto \(G\) è il modulo <span class="nowrap">\(\K[2]\).</span></p>}
#endif
#if defined TARGET_trans3im
\text{name_solution=Il punto \(\D\) è l'immagine del punto \(\C\) tramite la traslazione che trasforma \don[11].
<p>Ciò significa che il quadrilatero \(\para\) è un parallelogramma.</p>
Si deve quindi posizionare il punto \(\D\) in modo che \(\para\) sia un parallelogramma.}
#endif
#if defined TARGET_trans3ant
\text{name_solution=Il punto \(\C\) è la preimmagine del punto \(\D\) tramite la traslazione che trasforma \don[11], il che significa che il punto \(\D\) è l'immagine del punto \(\C\) tramite questa stessa traslazione.
<p>Ciò significa che il quadrilatero \(\para\) è un parallelogramma.</p>
Si deve quindi posizionare il punto \(\C\) in modo che \(\para\) sia un parallelogramma.}
#endif
#if defined TARGET_symax4
\text{name_solution=Ricorda: Se un punto si trova sull'asse di simmetria allora è il simmetrico di se stesso.
<p>Riflettendo lungo la retta <span class="nowrap">\((\axe[1])\),</span></p>}
\text{name_solution1=il punto \(\k[1]\) si sovrappone al punto <span class="nowrap">\(\k[4]\),</span>
          	<p>il punto \(\k[2]\) si sovrappone al punto <span class="nowrap">\(\k[5]\),</span></p>
          	il punto \(\k[3]\) si sovrappone al punto <span class="nowrap">\(\k[6]\),</span>
          	<p>quindi l'immagine del triangolo \(\k[1]\k[2]\k[3]\) tramite la simmetria di asse <span class="nowrap">\((\axe[1])\)</span> è <span class="nowrap">\(\k[4]\k[5]\k[6]\).</span></p>}
\text{name_solution2=il punto \(\k[4]\) si sovrappone al punto <span class="nowrap">\(\k[1]\),</span>
          	<p>il punto \(\k[5]\) si sovrappone al punto <span class="nowrap">\(\k[2]\),</span></p>
          	il punto \(\k[6]\) si sovrappone al punto <span class="nowrap">\(\k[3]\),</span>
          	<p>quindi, tramite la simmetria di asse <span class="nowrap">\((\axe[1])\),</span> l'immagine del triangolo \(\k[4]\k[5]\k[6]\)
          	è <span class="nowrap">\(\k[1]\k[2]\k[3]\).</span></p>}
#endif

#if defined TARGET_symcen4
\text{name_solution=Applicando la simmetria di centro <span class="nowrap">\(M\),</span>}
\text{name_solution1=<p>l'immagine del punto \(\k[1]\) è il punto <span class="nowrap">\(\k[4]\),</span></p>
          	<p>l'immagine del punto \(\k[2]\) è il punto <span class="nowrap">\(\k[5]\),</span></p>
          	<p>l'immagine del punto \(\k[3]\) è il punto <span class="nowrap">\(\k[6]\),</span></p>
          	quindi l'immagine del triangolo \(\k[1]\k[2]\k[3]\) è <span class="nowrap">\(\k[4]\k[5]\k[6]\).</span>}
\text{name_solution2=<p>l'immagine del punto \(\k[4]\) è il punto <span class="nowrap">\(\k[1]\),</span></p>
          	<p>l'immagine del punto \(\k[5]\) è il punto <span class="nowrap">\(\k[2]\),</span></p>
          	<p>l'immagine del punto \(\k[6]\) è il punto <span class="nowrap">\(\k[3]\),</span></p>
          	quindi l'immagine del triangolo \(\k[4]\k[5]\k[6]\) è <span class="nowrap">\(\k[1]\k[2]\k[3]\).</span>}
#endif
#if defined TARGET_rota4
\text{name_solution=Applicando la rotazione di centro \(M\) e angolo \(90^{\circ}\) in senso \sens,
<p>l'immagine di \(\datatri[\ch;1]\) è <span class="nowrap">\(\trirep1\),</span></p>
<p>l'immagine di \(\datatri[\ch;2]\) è <span class="nowrap">\(\trirep2\),</span></p>
<p>l'immagine di \(\datatri[\ch;3]\) è \(\trirep3\)</p>
quindi l'immagine del triangolo \(\tridep\) è <span class="nowrap">\(\tri1[1]\).</span>}
#endif
#if defined TARGET_homo3
\text{name_solution=1. Non c'è inversione, il rapporto cercato è positivo.
<p>Inoltre, \(O\choix1[1]=\choix1[2]\times OA\), quindi il rapporto dell'omotetia di centro \(O\) che permette di passare dalla figura \(A\) alla figura \(\choix1[1]\) vale <span class="nowrap">\(\choix1[2]\).</span></p>
<p>2. \(\frac{\num}{\denum} \times O\choix2[1]=O\choix2[2]\), quindi l'omotetia di centro \(O\) e di rapporto \(\frac{\num}{\denum}\) permette di passare dalla figura \(\choix2[1]\) alla figura <span class="nowrap">\(\choix2[2]\).</span></p>}
#endif
