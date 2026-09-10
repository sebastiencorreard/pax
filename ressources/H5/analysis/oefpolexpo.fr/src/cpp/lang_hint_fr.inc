%%%HINT %%%

\text{hint_1=
# if defined TARGET_1k_exp || defined TARGET_4Qexp_k
Soit \(k\) un réel et soit \(u\) une fonction dérivable sur un intervalle <span class="nowrap">\(\mathrm{I}\).</span><br>
La fonction \(v \,: \x \mapsto k\times  u(\x)\) est dérivable sur \(\mathrm{I}\) et on a \(v^'(\x) = k \times u^'(\x)\) pour tout réel \(\x\) appartenant à <span class="nowrap">\(\mathrm{I}\).</span>
# endif
# if defined TARGET_2aff_exp || defined TARGET_3secdeg_exp
Soit \(u\) et \(v\) deux fonctions dérivables sur un intervalle <span class="nowrap">\(\mathrm{I}\).</span><br>
La fonction \(P \,: \x \mapsto u(\x) \times v(\x)\) est dérivable sur \(\mathrm{I}\) et on a&nbsp;: \(P^'(\x) = u^'(\x) \times v(\x) + u(\x) \times v^'(\x)\) pour tout réel \(\x\) appartenant à <span class="nowrap">\(\mathrm{I}\).</span>
# endif
# if defined TARGET_5Qexp_aff || defined TARGET_6Qexp_secdeg
Soit \(u\) et \(v\) deux fonctions dérivables sur un intervalle <span class="nowrap">\(\mathrm{I}\),</span>
la fonction \(v\) ne s'annulant pas sur l'intervalle <span class="nowrap">\(\mathrm{I}\).</span><br>
La fonction \(Q \,: \x \mapsto \frac{u(\x)}{v(\x)}\) est dérivable sur \(\mathrm{I}\) et on a&nbsp;: \(Q^'(\x) = \frac{u^'(\x) \times v(\x) - u(\x) \times v^'(\x)}{\left(v(\x)\right)^2}\) pour tout réel \(\x\) appartenant à <span class="nowrap">\(\mathrm{I}\).</span>
# endif
}

\text{hint_2=
Soit \(m\) et \(p\) deux nombres réels.<br>
La fonction \(w \,: \x \mapsto \mathrm{e} ^{m \x + p}\) est dérivable sur \(\mathbb{R}\) et on a \(w^'(\x) = m \times \mathrm{e}^{m \x + p}\) pour tout réel <span class="nowrap">\(\x\).</span>
}
