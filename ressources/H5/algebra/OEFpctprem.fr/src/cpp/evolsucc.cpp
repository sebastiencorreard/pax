target=evolsucc1 evolsucc2 evolsucc2b evolsucc3 evolsucc4 evolsucc5

\author{Régine, Mangeard;Fabien, Sommier}
\email{regine@mangeard.fr,fabien.sommier@gmail.com}
\format{html}
\precision{100}
#define TITLE Évolutions successives
\text{verbe=augmente,baisse}
\text{verbeinf=augmenter,baisser}
\text{evol=hausse,baisse}
\integer{k1=randint(1,2)}
\integer{av=randint(1000..3000)}
\integer{t1=randint(10..90)}
\real{cm1=\k1=1?1+\t1/100:1-\t1/100}

#if !defined TARGET_evolsucc4
\integer{k2=randint(1,2)}
\integer{t2=randint(10..90)}
# else
\integer{k2=3-\k1}
\integer{t2=\t1}
#endif
\real{cm2=\k2=1?1+\t2/100:1-\t2/100}
\real{cm=\cm1*\cm2}
#if !defined TARGET_evolsucc4
\if{\cm=1}
 {
 \integer{k2=3-\k2}
 \rational{cm2=\k2=1?1+\t2/100:1-\t2/100}
 \rational{cm=\cm1*\cm2}
 }
#endif
\integer{k=\cm>1?1:2}
\real{ts=(\cm-1)*100}
\real{t=\k=1?(\cm-1)*100:(1-\cm)*100}
\rational{nv=\av*\cm}
\integer{nv0=\nv}
\real{nv2=round(\nv*100)/100}
\text{t_aff=slib(numeration/ecriturenombre \t,comma tex)}
\text{cm_aff=slib(numeration/ecriturenombre \cm,comma tex)}
\text{cm1_aff=slib(numeration/ecriturenombre \cm1,comma tex)}
\text{cm2_aff=slib(numeration/ecriturenombre \cm2,comma tex)}
\text{nv2_aff=slib(numeration/ecriturenombre \nv2,comma tex)}
\if{\nv2!=\nv}
  {\text{arrond=euros (valeur arrondie au centime).}}
  {\text{arrond=euros.}}

#if defined TARGET_evolsucc1 || defined TARGET_evolsucc2
\text{av_aff=slib(numeration/ecriturenombre \av,tex)}
#endif

#if defined TARGET_evolsucc1 || defined TARGET_evolsucc2 || defined TARGET_evolsucc2b || defined TARGET_evolsucc3 || defined TARGET_evolsucc4
\text{tcm1=\k1=1?\(CM1= 1+\frac{\t1}{100}\) : \(CM1= 1-\frac{\t1}{100}\) }
\text{tcm2=\k2=1?\(CM2= 1+\frac{\t2}{100}\) : \(CM2= 1-\frac{\t2}{100}\) }
text{tcm=\k=1?\(CM= CM1 \times CM2 = \cm > 1\) donc hausse: \(CM= CM1 \times CM2 = \cm > 1\) donc baisse}
\text{tcm=<span class="nowrap">\(CM= CM1 \times CM2\).</span><br> <span class="nowrap">\(CM= \cm_aff\).</span>}
\text{tsol=<p>Dans le cas d'évolutions successives, on peut calculer les différents coefficients multiplicateurs
associés aux différentes évolutions, puis calculer le coefficient multiplicateur global.</p>
<p>Appelons CM1 le coefficient multiplicateur correspondant à la première évolution et CM2 celui de la deuxième.</p>
<p>  \tcm1  d'où \(CM1 = \cm1_aff\) et \tcm2 d'où <span class="nowrap">\(CM2 = \cm2_aff\).</span> </p>
<p> Le coefficient multiplicateur global est \tcm</p>}

# if defined TARGET_evolsucc1
\title{TITLE 1}
\text{tsol=\tsol
<p>Le nouveau prix en euros est donc \(\av_aff \times \cm_aff\)
ce qui donne \(\nv2_aff\) \arrond </p>
}
# endif

# if defined TARGET_evolsucc2 || defined TARGET_evolsucc2b
\text{ts_aff=slib(numeration/ecriturenombre \ts,comma tex)}
#   if defined TARGET_evolsucc2
\title{TITLE 2}
\text{sol2=<p>On peut calculer la valeur obtenue après les 2 évolutions&nbsp;: on obtient \(\nv2_aff\) \arrond<br>
  Ensuite, on calcule le taux d'évolution qui permet de passer de \(\av_aff\) à <span class="nowrap">\(\nv2_aff\) :</span>
  c'est une évolution de <span class="nowrap">\(\ts_aff\) %.</span></p>
<p><b>AUTRE MÉTHODE</b>&nbsp;: <br></p>}
#   else
\title{TITLE 2b (sans v.i.)}
#   endif
\text{tcm=\k=1?\(CM > 1\) donc il s'agit d'une hausse.: \(CM < 1\) donc il s'agit d'une baisse.}
\text{rq=\k=1?positif, car il s'agit d'une hausse&nbsp;: négatif car il s'agit d'une baisse (de <span class="nowrap">\(\t_aff\) %</span>)}
\text{tsol=\tsol \tcm <br>Le taux d'évolution global en pourcentage est \(t\) avec }
\text{tsol=\tsol \(t= (CM -1)\times 100\) ce qui donne <span class="nowrap">\(t=\ts_aff\) %.</span> }
\text{tsol=\tsol <br>
<i>Remarque</i> : le taux est \rq.}
# endif

# if defined TARGET_evolsucc3
\title{TITLE 3}
%%rational{cm2=1/ (\cm1)}
\real{cm2=1/ (\cm1)}
\real{cm2c=round(\cm2*10000)/10000}
\real{t2=\k1=2?(\cm2-1)*100:(1-\cm2)*100} positif
\real{t2s=(\cm2-1)*100} avec signe
\real{t2sc=round(\t2s*100)/100}
\real{t2c=round(\t2*100)/100}
\text{cm2c_aff=slib(numeration/ecriturenombre \cm2c,comma tex)}
\text{t2c_aff=slib(numeration/ecriturenombre \t2c,comma tex)}
\if{\cm2=\cm2c}
  {\text{arrond2=<span class="nowrap">\(CM2=\cm2c_aff\).</span>}
   \text{arrond3=<span class="nowrap">\(t=\t2c_aff\) %.</span>}
  }
  {\text{arrond2=\(CM2=\cm2c_aff\) (valeur arrondie au dix-millième).}
   \text{arrond3=<span class="nowrap">\(t=\t2c_aff\) %</span> (valeur arrondie au centième).}
  }
\text{rq=\k1=2?positif car il s'agit d'une hausse : négatif car il s'agit d'une baisse (de <span class="nowrap">\(\t2c_aff\) %</span>)}
\text{tsol=<p>Dans le cas d'évolutions successives, on peut calculer les différents coefficients multiplicateurs
associés aux différentes évolutions, puis calculer le coefficient multiplicateur global.</p>
<p>Appelons CM1 le coefficient multiplicateur correspondant à la première évolution, CM2 celui de la deuxième
et CM le coefficient multiplicateur global.</p>
<p>Le bien \verbe[\k1] de <span class="nowrap">\(\t1\) %</span> donc \tcm1 ce qui donne <span class="nowrap">\(CM1=\cm1_aff\).</span>
<br>Au bout des deux évolutions successives, le bien revient à son prix initial donc <span class="nowrap">\(CM=1\)</span>.
<br>On cherche donc à déterminer CM2 tel que <span class="nowrap">\(CM1 \times CM2 = 1\).</span>
<br>On en déduit que \(CM2 = \frac{1}{CM1}\) ce qui donne \arrond2</p>}

\text{tsol=\tsol <p>
  Soit \(t\) l'évolution en pourcentage correspondante.<br> \(t=(CM2-1)\times 100\) ce qui donne \arrond3
<br>
<i>Remarque</i> : le taux est \rq.</p>
}
# endif

# if defined TARGET_evolsucc1
\statement{
<p>
  Un bien de valeur \(\av_aff\) euros a subi une \evol[\k1] de <span class="nowrap">\(\t1\) %</span> puis une \evol[\k2] de <span class="nowrap">\(\t2\) %.</span>
  <br><label for="reply1">Quel est son nouveau prix ?</label>
</p>
<div class="wimscenter">\embed{reply1} euros</div>
<div class="wims_instruction">Arrondir au centime.</div>
}
\answer{Réponse :}{\reponse}{type=numexp} reponse attendue : nv2
\real{di=abs(\reponse-\nv2)}
%%text{testar=\di<=1 and \di >=0.01? 1:0}
\text{testar=\di >=0.01? 1:0}
\condition{Le raisonnement semble correct&nbsp;}{\di<=1}{weight=19}
\condition{La réponse est correctement arrondie au centime&nbsp;}{\di=0}{weight=1}
\feedback{\di<=1 and \di!=0}{Vous avez sans doute effectué le bon calcul mais vous avez mal arrondi le résultat.}
# endif

# if defined TARGET_evolsucc2 || defined TARGET_evolsucc2b
\statement{
  # if defined TARGET_evolsucc2
  <p> Un bien de valeur \(\av_aff\) euros a subi une \evol[\k1] de <span class="nowrap">\(\t1\) %</span>
  puis une \evol[\k2] de <span class="nowrap">\(\t2\) %.</span></p>
  # else
  <p>Un bien a subi une \evol[\k1] de <span class="nowrap">\(\t1\) %</span> puis une \evol[\k2]
  de <span class="nowrap">\(\t2\) %.</span></p>
  #endif
<div class="wimscenter"><label for="reply1">Il a subi globalement une</label> \embed{reply1} <label for="reply2">de</label> <span class="nowrap">\embed{reply2,4} %.</span></div>
<div class="wims_instruction">Donner la valeur exacte du taux d'évolution.</div>
}
\answer{évolution}{\k;\evol}{type=menu}{weight=1}
\answer{taux}{\t}{type=numexp}{weight=9}
# endif

# if defined TARGET_evolsucc3
\statement{<p>
  Si un bien \verbe[\k1] de <span class="nowrap">\(\t1\) %,</span> de combien doit-il \verbeinf[3-\k1] pour
  revenir à son prix initial&nbsp;?
</p>
<div class="wimscenter"><label for="reply1">Il doit \verbeinf[3-\k1] de</label> <span class="nowrap">\embed{reply1,6} %.</span></div>

<div class="wims_instruction">Arrondir à 0.01&nbsp;%.</div>
}
%%answer{}{\t2c}{type=numexp}
\answer{}{\reponse}{type=numexp}
\real{di=abs(\reponse-\t2c)}
\text{testar=\di >=0.01? 1:0}
\condition{Le raisonnement semble correct&nbsp;}{\di<=1}{weight=19}
\condition{La réponse est correctement arrondie au centième&nbsp;}{\di=0}{weight=1}
\feedback{\di<=1 and \di!=0}{Vous avez sans doute effectué le bon calcul mais vous avez mal arrondi le résultat.}
# endif

#if defined TARGET_evolsucc4
\title{TITLE 4}

\text{data=Un bien qui subit une \evol[\k1] de <span class="nowrap">\(\t1\) %</span> puis une \evol[\k2] de <span class="nowrap">\(\t2\) %</span>}

\text{lstrep=ne change pas de prix, subit une baisse, subit une augmentation}
\text{tsol=\tsol
<p>Puisque \(CM < 1\) alors le bien a subi globalement une baisse à l'issue de ces deux évolutions successives.<br>
Cette baisse est de <span class="nowrap">\(\t_aff\) %.</span>
</p>}

\statement{
<p>
  Cliquer sur la bonne réponse&nbsp;:
</p><p>
\data
</p>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{2;\lstrep}{type=radio}

#endif

\solution{\sol2 \tsol}

#endif



#if defined TARGET_evolsucc5
\title{TITLE 5}
\integer{t1=randint(2..20)}
\integer{t2=\t1+randint(5..15)}

\text{lstaff=}
\text{lstevol=}
\text{lstsol=}

 \text{evol=baisse de \t1 % <br>puis baisse de \t2 %}
 \text{lstevol=wims(append item \evol to \lstevol)}
 \real{c=(1-\t1/100)*(1-\t2/100)}
 \text{f=texmath(maxima(\c*x))}
 \text{lstaff=wims(append item \(\f\) to \lstaff)}
 \text{solu=\(x \times \left(1-\frac{\t1}{100}\right) \times \left(1-\frac{\t2}{100}\right)\)}
 \text{lstsol=wims(append item \solu to \lstsol)}

 \text{evol=hausse de \t1 % <br> puis baisse de \t2 %}
 \text{lstevol=wims(append item \evol to \lstevol)}
 \real{c=(1+\t1/100)*(1-\t2/100)}
 \text{f=texmath(maxima(\c*x))}
 \text{lstaff=wims(append item \(\f\) to \lstaff)}
 \text{solu=\(x \times \left(1+\frac{\t1}{100}\right) \times \left(1-\frac{\t2}{100}\right)\)}
 \text{lstsol=wims(append item \solu to \lstsol)}


 \text{evol=hausse de \t1 % <br>puis hausse de \t2 %}
 \text{lstevol=wims(append item \evol to \lstevol)}
 \real{c=(1+\t1/100)*(1+\t2/100)}
 \text{f=texmath(maxima(\c*x))}
 \text{lstaff=wims(append item \(\f\) to \lstaff)}
 \text{solu=\(x \times \left(1+\frac{\t1}{100}\right) \times \left(1+\frac{\t2}{100}\right)\)}
 \text{lstsol=wims(append item \solu to \lstsol)}


 \text{evol=hausse de \t1 €<br>puis baisse de \t2 %}
 \text{lstevol=wims(append item \evol to \lstevol)}
 \real{c=(1-\t2/100)}
 \text{f=texmath(maxima(\c*(x+\t1)))}
 \text{lstaff=wims(append item \(\f\) to \lstaff)}
 \text{solu=\(\left(x + \t1 \right) \times \left(1-\frac{\t2}{100}\right)\)}
 \text{lstsol=wims(append item \solu to \lstsol)}


 \text{evol=hausse de \t1 €<br>puis hausse de \t2 %}
 \text{lstevol=wims(append item \evol to \lstevol)}
 \real{c=(1+\t2/100)}
 \text{f=texmath(maxima(\c*(x+\t1)))}
 \text{lstaff=wims(append item \(\f\) to \lstaff)}
 \text{solu=\(\left(x + \t1 \right) \times \left(1+\frac{\t2}{100}\right)\)}
 \text{lstsol=wims(append item \solu to \lstsol)}


 \text{evol=baisse de \t1 €<br>puis hausse de \t2 %}
 \text{lstevol=wims(append item \evol to \lstevol)}
 \real{c=(1+\t2/100)}
 \text{f=texmath(maxima(\c*(x-\t1)))}
 \text{lstaff=wims(append item \(\f\) to \lstaff)}
 \text{solu=\(\left(x - \t1 \right) \times \left(1+\frac{\t2}{100}\right)\)}
 \text{lstsol=wims(append item \solu to \lstsol)}


 \text{evol=baisse de \t1 €<br>puis baisse de \t2 %}
 \text{lstevol=wims(append item \evol to \lstevol)}
 \real{c=(1-\t2/100)}
 \text{f=texmath(maxima(\c*(x-\t1)))}
 \text{lstaff=wims(append item \(\f\) to \lstaff)}
 \text{solu=\(\left(x - \t1 \right) \times \left(1-\frac{\t2}{100}\right)\)}
 \text{lstsol=wims(append item \solu to \lstsol)}

 \text{evol=hausse de \t1 %<br>puis baisse de \t2 €}
 \text{lstevol=wims(append item \evol to \lstevol)}
 \real{c=(1+\t1/100)}
 \text{f=texmath(maxima(\c*x-\t2))}
 \text{lstaff=wims(append item \(\f\) to \lstaff)}
 \text{solu=\(x \times \left(1+\frac{\t1}{100}\right) -\t2\)}
 \text{lstsol=wims(append item \solu to \lstsol)}

 \text{evol=hausse de \t1 %<br>puis hausse de \t2 €}
 \text{lstevol=wims(append item \evol to \lstevol)}
 \real{c=(1+\t1/100)}
 \text{f=texmath(maxima(\c*x+\t2))}
 \text{lstaff=wims(append item \(\f\) to \lstaff)}
 \text{solu=\(x \times \left(1+\frac{\t1}{100}\right) +\t2\)}
 \text{lstsol=wims(append item \solu to \lstsol)}

 \text{evol=baisse de \t1 %<br>puis hausse de \t2 €}
 \text{lstevol=wims(append item \evol to \lstevol)}
 \real{c=(1-\t1/100)}
 \text{f=texmath(maxima(\c*x+\t2))}
 \text{lstaff=wims(append item \(\f\) to \lstaff)}
 \text{solu=\(x \times \left(1-\frac{\t1}{100}\right) +\t2\)}
 \text{lstsol=wims(append item \solu to \lstsol)}


 \text{evol=baisse de \t1 %<br>puis baisse de \t2 €}
 \text{lstevol=wims(append item \evol to \lstevol)}
 \real{c=(1-\t1/100)}
 \text{f=texmath(maxima(\c*x-\t2))}
 \text{lstaff=wims(append item \(\f\) to \lstaff)}
 \text{solu=\(x \times \left(1-\frac{\t1}{100}\right) -\t2\)}
 \text{lstsol=wims(append item \solu to \lstsol)}

\text{ind=shuffle(items(\lstaff))}
\text{lstaff=\lstaff[\ind[1]],\lstaff[\ind[2]],\lstaff[\ind[3]],\lstaff[\ind[4]],\lstaff[\ind[5]]}
\text{lstevol=\lstevol[\ind[1]],\lstevol[\ind[2]],\lstevol[\ind[3]],\lstevol[\ind[4]],\lstevol[\ind[5]]}
\text{lstsol=\lstsol[\ind[1]],\lstsol[\ind[2]],\lstsol[\ind[3]],\lstsol[\ind[4]],\lstsol[\ind[5]]}
\text{matrixTab=Description d'évolution,Expression en fonction de \(x\)}
\for{gg=1 to 5}
  {\text{matrixTab=\matrixTab;\lstevol[\gg],\lstsol[\gg] \(=\) \lstaff[\gg]}
  }
\text{tabSol=slib(text/matrixhtml [\matrixTab],1 center wimsborder,TH=[1;])}
\statement{
<p>
  Un prix \(x\) (en euros) subit deux évolutions successives.<br>
  Associer à chaque description d'évolutions l'expression en \(x\) correspondante.
</p>
<div class="wimscenter">\embed{reply1,50x190x140}</div>
}
\answer{}{\lstevol;\lstaff}{type=correspond}
\solution{<div class="table-scroll">\tabSol</div>


}
#endif
