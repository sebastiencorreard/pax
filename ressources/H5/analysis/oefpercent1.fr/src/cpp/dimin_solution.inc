<img src="\url2" alt="\turl2">
   <ul class="wims_nopuce">
    <li>Pourcentage diminution </li>
    <li>\(\large{ \vi\; \overset{\phantom{xx}-\p\%\phantom{xx}}{\underset{\times \k}{\mapsto}}\; \vf})</li>
#if defined TARGET_percentref3
<li>\(\large{ \vi\; \underset{\phantom{xx}: \k \phantom{xx}}{\leftarrow}\; \vf})</li>
#endif
   </ul>
   <ul class="wims_nopuce">
    <li>Pourcentage diminution </li>
    <li>\(\large{ x\; \overset{\phantom{xx}-p\%\phantom{xx}}{\underset{\times (1-p/100)}{\mapsto}}\; y})</li>
#if defined TARGET_percentref3
<li>\(\large{ x\; \underset{\phantom{xx}: (1-p/100) \phantom{xx}}{\leftarrow}\; y})</li>
#endif
   </ul>
#if defined TARGET_coeff2
<p> Une action qui valait \vi &euro; diminue de \p %. Sa nouvelle valeur est \vf &euro;.</p>
<p> Pour diminuer une quantité de \p %, il suffit de la multiplier par \k.
<p> Pour diminuer une quantité de \(p) %, il suffit de la multiplier par \(\fk).</p>
<p>\(y=(1-\frac{p}{100}) x).</p>
#endif
#if defined TARGET_percentdim
<p>Lorsqu'une action passe de \vi &euro; à \vf &euro;, elle diminue de \p %.</p>
<p>Lorsqu'une quantité diminue de \(x) à \(y), elle diminue de \(x-y).</p>
<p>Le pourcentage de diminution est \(p=\frac{x-y}{x} \times 100).</p>
<p>Le taux est \(t=\frac{y-x}{x}) autrement dit \(t = \frac{Valeur_finale - Valeur_initiale}{Valeur_initiale})
  et il est négatif ce qui indique une diminution.</p>
#endif
#if defined TARGET_percentref3
<p>Si une action vaut \vf &euro; après une diminution de \p % alors sa valeur initiale était de \vi &euro;</p>
<p> Pour diminuer une quantité de \p %, il suffit de la multiplier par \k.</p>
<p>Pour obtenir la valeur initiale \(x) à partir de la valeur finale \(y) obtenue après une diminution de \(p) %,
on divise \(y) par le coefficient multiplicateur \(( 1 - \frac{p}{100})).</p>

<p>\(x=\frac{y}{1-p/100}).</p>
#endif
