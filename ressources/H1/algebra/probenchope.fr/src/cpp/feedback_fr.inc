\text{name_feed1=Votre expression n'est pas assez longue,vous devez utiliser plus d'étiquettes.}

#if defined TARGET_pile
\text{name_feed=<b>Votre réponse n'est pas correcte.</b> 
<p>En effet, pour trouver le coût d'une pile, on commence par calculer le coût des piles : \(\tdon1 \minus \tdon2\) pour ensuite diviser le résultat par \(\tdon3\).</p>
Dans votre expression \(\tdon1 \minus \tdon2 \div \tdon3\), la division étant prioritaire sur la soustraction, vous devez commencer par la division : \(\tdon2 \div \tdon3\) puis soustraire le résultat à \(\tdon1\).
<p>Ce qui n'est pas ce qu'on veut car on veut effectuer d'abord \(\tdon1 \minus \tdon2\) avant de diviser par \(\tdon3\).</p>
Pour cela, on met des parenthèses autour de \(\tdon1 \minus \tdon2\), l'expression correcte est alors \((\tdon1 \minus \tdon2) \div \tdon3\).
</div>}
#endif
