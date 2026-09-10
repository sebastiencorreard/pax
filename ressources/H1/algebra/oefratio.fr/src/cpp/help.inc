#if defined TARGET_ratio2confparm
\if{\n=3 or \n=6}{\hint{Une fois le tableau rempli des données de l'énoncé, on complète le tableau de proportionnalité en calculant le coefficient qui permet d'obtenir les valeurs de la seconde ligne
en multipliant les valeurs de la première ligne.}}
#endif

#if defined TARGET_ratio2 || defined TARGET_oefratio3

\hint{
\if{\step=2}{<ul><li>Dans le ratio \(a:b\), le nombre \article\enonce[\choix] est partagé en \(a+b\) parts.</li></br>
<li>\(\frac{a}{b} \times c = \frac{ a \times c}{b}\)</li>
<li>Une fois la première ligne du tableau complétée,
trouver le coefficient de proportionnalité qui permet de passer de la première
ligne à la seconde ligne.</li></ul>}}
#endif

#if defined TARGET_dessineratio
\hint{Le nombre de cases rouges et le nombre de cases jaunes sont dans le ratio \(4 : 5 \) signifie qu'à chaque fois que l'on colorie <strong>\( 4\) cases en rouge</strong>,
on doit colorier <strong>\(5\) cases en jaune</strong>. Exemple :
<div><img src="\imagedir/faireratio_hint.png" alt="Illustration d'un ratio 4 pour 5 dans une grille de 6 par 6" /></div>}
#endif
