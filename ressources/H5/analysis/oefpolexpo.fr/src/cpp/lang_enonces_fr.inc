\text{enonce = On considère la fonction \(\f \,: \x \mapsto \fonc_disp\) définie et dérivable sur <span class="nowrap">\(\Int\).</span>}
\text{question = Déterminer une expression algébrique de la fonction dérivée de <span class="nowrap">\(\f\).</span>}
\text{retour = Vous avez répondu&nbsp;:}
\text{rep_good_0 =Votre réponse est correcte.}
\text{rep_good_1 = On a bien&nbsp;: }
\text{rep_bad_0 = Votre réponse n'est pas correcte.<br>En effet, on a&nbsp;:} 
\text{rep_bad_1 = Votre démarche semble juste mais l'expression de \(\f^{'}\) demandée est en fonction de la variable <span class="nowrap">\(\x\).</span><br>En effet, on a&nbsp;:}

\text{feed0=Attention, l'expression de \(\f^{'}\) demandée est en fonction de la variable <span class="nowrap">\(\x\).</span>} 

# if defined TARGET_6Qexp_secdeg || defined TARGET_5Qexp_aff
 
 \text{feed1=Vous semblez avoir commis une erreur sur <strong>la dérivée d'un quotient</strong>.<br>
 On rappelle que si \(u\) et \(v\) sont deux fonctions dérivables sur un intervalle <span class="nowrap">\(\mathrm{I}\),</span> 
 \(v\) ne s'annulant pas sur <span class="nowrap">\(\mathrm{I}\),</span>  alors la fonction \(Q \,: \x \mapsto \frac{u(\x)}{v(\x)}\) est dérivable 
 sur \(\mathrm{I}\) et on a&nbsp;:
 \(Q^'(\x) = \frac{u^'(\x) \times v(\x) - u(\x) \times v^'(\x)}{\left(v(\x)\right)^2}\) pour tout réel \(\x\) appartenant à <span class="nowrap">\(\mathrm{I}\).</span>}
#else
 \text{feed1=Vous semblez avoir commis une erreur sur <strong>la dérivée d'un produit</strong>.<br>
 On rappelle que si \(u\) et \(v\) sont deux fonctions dérivables sur un intervalle \(\mathrm{I}\) alors la fonction 
 \(P \,: \x \mapsto u(\x) \times v(\x)\) est dérivable sur \(\mathrm{I}\) et on a&nbsp;:
 \(P^'(\x) = u^'(\x) \times v(\x) + u(\x) \times v^'(\x)\) pour tout réel \(\x\) appartenant à <span class="nowrap">\(\mathrm{I}\).</span>}
#endif

\text{feed2= Vous semblez avoir commis une erreur sur la dérivée de  <span class="nowrap">\(\x \mapsto \mathrm{e}^{\expoaff}\).</span><br>
    On rappelle que si \(m\) et \(p\) sont deux nombres réels alors la fonction \(w \,: \x \mapsto \mathrm{e} ^{m \x + p}\) est dérivable sur \(\mathbb{R}\) et on a&nbsp;: 
     \(w^'(\x) = m \times \mathrm{e}^{m \x + p}\) pour tout réel <span class="nowrap">\(\x\).</span>}
     
\text{feed3=    
Rappels :<br>
<ul class="euler_ul">
  <li>
   # if defined TARGET_6Qexp_secdeg || defined TARGET_5Qexp_aff
    Soit \(u\) et \(v\) deux fonctions dérivables sur un intervalle <span class="nowrap">\(\mathrm{I}\),</span>
    \(v\) ne s'annulant pas sur <span class="nowrap">\(\mathrm{I}\).</span><br>
    La fonction \(Q \,: \x \mapsto \frac{u(\x)}{v(\x)}\) est dérivable 
     sur \(\mathrm{I}\) et on a&nbsp;:
     \(Q^'(\x) = \frac{u^'(\x) \times v(\x) - u(\x) \times v^'(\x)}{\left(v(\x)\right)^2}\) pour tout réel \(\x\) appartenant à <span class="nowrap">\(\mathrm{I}\).</span>
   #else
    Soit \(u\) et \(v\) deux fonctions dérivables sur un intervalle <span class="nowrap">\(\mathrm{I}\).</span><br>
    La fonction \(P \,: \x \mapsto u(\x) \times v(\x)\) est dérivable sur \(\mathrm{I}\) et on a&nbsp;:
     \(P^'(\x) = u^'(\x) \times v(\x) + u(\x) \times v^'(\x)\) pour tout réel \(\x\) appartenant à <span class="nowrap">\(\mathrm{I}\).</span>
   #endif
  </li>
  <li>
    Soit \(m\) et \(p\) deux nombres réels, la fonction \(w \,: \x \mapsto \mathrm{e} ^{m \x + p}\) est dérivable sur \(\mathbb{R}\) et on a \(w^'(\x) = m \times \mathrm{e}^{m \x + p}\) pour tout réel <span class="nowrap">\(\x\).</span>
  </li>
</ul>}
