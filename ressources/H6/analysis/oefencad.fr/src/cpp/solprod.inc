\solution{
<p><strong>Solution au cas par cas :</strong></p>
<p>\SOL</p>
#if defined TARGET_encadproduit || defined TARGET_encadproduit2
<p><strong>Solution globale</strong> : on calcule les quatre produits deux à deux des bornes \(a=\a\),
\(b=\b\) qui encadrent le réel \(x\) et des bornes \(c=\c\) et \(d=\d\)
qui encadrent le réel \(y\) :</p>
<ul>
<li>\(P_{ac} = \a \times \c = \ac\).</li>
<li>\(P_{ad} = \a \times \d = \ad\).</li>
<li>\(P_{bc} = \b \times \c = \bc\).</li>
<li>\(P_{bd} = \b \times \d = \bd\).</li>
</ul>
<p>Le nombre \(\res1\) est le plus petit et \(\res2\) est le plus grand de ces 4 produits,
d'où l'encadrement :</p>
<p class="wimscenter">\(\res1 < x \times y < \res2\).</p>
#endif
<p><em>On peut visualiser cet encadrement du produit \(x \times y\) par la figure ci-dessous.</em>
\Explication</p>
<p class="wimscenter">\draw{400,400 }{\Encadrement}</p>
}
