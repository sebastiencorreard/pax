  <img src="\url2" alt="\turl2"><br>
   <ul class="wims_nopuce">
<li>Pourcentage d'augmentation</li>
<li>\(\large{ \vi\; \overset{\phantom{xx}+\p\%\phantom{xx}}{\underset{\times \k}{\mapsto}}\; \vf})</li>
#if defined TARGET_percentref2
<li>\(\large{ x\; \underset{\phantom{xx}: \k \phantom{xx}}{\leftarrow}\; y})</li>
#endif
 </ul>
 <ul class="wims_nopuce">
<li>Pourcentage d'augmentation</li>
<li>\(\large{ x\; \overset{\phantom{xx}+p\%\phantom{xx}}{\underset{\times (1+p/100)}{\mapsto}}\; y})</li>
#if defined TARGET_percentref2
<li>\(\large{ x\; \underset{\phantom{xx}:(1+p/100)\phantom{xx}}{\leftarrow}\; y})</li>
#endif
 </ul>
#if defined TARGET_augm
<p>Le coefficient multiplicateur est \(\frac{y}{x})</p>
<p>Le taux est \(\frac{y - x}{x}) ou \(\frac{Valeur_finale - Valeur_initiale}{Valeur_initiale}).</p>
<p>Et le pourcentage est \(p) % avec \(p = \frac{y - x}{x}\times 100) ou \(p = \frac{Valeur_finale - Valeur_initiale}{Valeur_initiale}\times 100).</p>
#endif
#if defined TARGET_coeff1
<p>Après une augmentation de \p %, une action qui valait \vi &euro; vaut \vf &euro;.</p>
<p>Pour augmenter une quantité de \p %, il suffit de la multiplier par \k.</p>
<p>Pour augmenter une quantité de \(p) %, il suffit de la multiplier par \fk.</p>
#endif
#if defined TARGET_percentref2
<p>Si une action vaut \vf &euro; après une augmentation de \p % alors sa valeur initiale était de \vi &euro;</p>
<p>Pour augmenter une quantité de \p %, il suffit de la multiplier par \k.</p>
<p>Pour obtenir la valeur initiale à partir de la valeur finale \(y) obtenue après une augmentation de \(p) %,
on divise \(y) par le coefficient multiplicateur \(( 1 + \frac{p}{100})).</p>
<p>\(x = \frac{y}{1 + p/100})</p>
#endif
