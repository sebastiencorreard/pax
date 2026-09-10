target=proportion1 proportion2 proportion3 proportion4 proportion5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{100}
#define TITLE Proportion
#if defined TARGET_proportion1
\title{TITLE 1}
\integer{an=random(2004,2005,2006,2007)}
\integer{t=randint(4000..6000)/2}
\integer{t=2*\t}
\integer{p=randint(1000..3000)/2}
\integer{p=2*\p}
\rational{rep1=simplify(\p / \t)}
\integer{e=\t-\p}
\integer{rep2=\rep1*1000}
\real{rep2=\rep2/10}
\statement{
  <p>
    En \an, un musée a reçu \t visiteurs dont \e étrangers.
  </p>
  <ol>
  <li><label for="reply1">
  Calculer la proportion de visiteurs français en \an sous forme de fraction irréductible&nbsp;:
  </label>\embed{reply1}</li>
  <li>
  <label for="reply2">Exprimer ensuite ce résultat sous forme de pourcentage ( à 0.1 % près):</label>
  \embed{reply2,4}</li>
  </ol>
}
\answer{fraction}{\rep1}{type=numexp}
\answer{pourcentage}{\rep2}{type=numeric}
\solution{La proportion est le rapport \(\frac{partie}{total}\) soit \(\frac{\p}{\t}\)}
#endif

#if defined TARGET_proportion2
\title{TITLE 2}
\integer{p=randint(5..20)}
\integer{t=randint(30000..90000)}
\integer{k=randint(1,2)}
\text{quest=\k=1?chômeurs: non chômeurs}
\integer{rep1=\k=1?\t*\p/ 100:\t*(1-\p/100)}
\text{solu=\k=1?Le nombre de \quest est donné par \(N=\frac{\p}{100}\times \t=\rep1\) (résultat arrondi à l'unité):
  Le nombre de <b>\quest</b> est donné par \(N=\left(1-\frac{\p}{100}\right)\times \t=\rep1\) (résultat arrondi à l'unité)}
\statement{
<p>
  Dans une ville, la proportion de chômeurs est égale à
\(\frac{\p}{100}\) de la population active.<br>
 La population d'actifs est de \t.
</p><p>
  <label for="reply1">Combien y a-t-il de \quest&nbsp;?</label> \embed{reply1}
</p>
<div class="wims_instruction">Arrondir à l'unité.</div>
}
\answer{Réponse : }{\reponse}{type=numeric} la réponse attendue est rep1
\text{testentier=\reponse=round(\reponse) ? 1:0}
\real{di=abs(\reponse-\rep1)}
\text{testar=\di<=1 and \di<>0 ? 1:0}
\condition{di inf 1}{\di<=1}{weight=19}{option=hide}
\condition{Bonne réponse}{\di=0}{weight=1}
\feedback{\testentier=0}{Attention : la réponse doit être un nombre entier. }
\feedback{\testar=1}{Vous avez sans doute effectué le bon calcul mais vous avez mal arrondi le résultat.}
\solution{
\solu}
#endif

#if defined TARGET_proportion3 || defined TARGET_proportion4
# if defined TARGET_proportion3
\title{TITLE 3}
# else
\title{TITLE 4}
# endif
\text{data=un tiers,1/3,
deux tiers,2/3,
un quart,1/4,
trois quarts,3/4,
un cinquième,1/5,
deux cinquièmes,2/5,
trois cinquièmes,3/5,
quatre cinquièmes,4/5,
un sixième,1/6,
cinq sixièmes,5/6,
deux septièmes,2/7,
cinq septièmes,5/7,
un neuvième,1/9}
\text{cedata=randomrow(\data)}
\text{part=\cedata[1]}
\text{x=\cedata[2]}
\text{tx=wims(replace internal / by , in \x)}
\text{livre=\tx[1]=1?\tx[1] livre sur \tx[2]:\tx[1] livres sur \tx[2]}
\rational{part2=1-\tx[1]/\tx[2]}
\integer{t=randint(5..10)*\tx[2]}
\integer{p2=\t*(1-\x)}
\integer{rep1=\t-\p2}
\statement{
<p>
# if defined TARGET_proportion3
  Dans un groupe, la proportion de filles est de \part et il y a \p2 garçons.
</p>
  Combien y a-t-il de filles ?
  <div>
  <label for="reply1">Réponse :</label> \embed{reply1}.
  </div>
}
\answer{filles}{\rep1}{type=numeric}
\solution{La proportion de garçons est de \(1 - \frac{\tx[1]}{\tx[2]}=\part2\)<br>
  Comme il y a \p2 garçons, le total vaut \(\frac{\p2}{\part2}=\t\)<br>
  Il y a donc \(\t - \p2=\rep1\) filles}
# else
  Dans la chambre de Luc, il y a \rep1 BD. On sait que \livre sont des BD.
  </p>
  Combien Luc a-t-il de livres au total ?
  <div>
  <label for="reply1">Réponse</label> : \embed{reply1}.
  </div>
}
\answer{livres}{\t}{type=numeric}
\solution{On utilise la formule \(partie = part \times total\) qui donne \(total = \frac{partie}{part}=\rep1 \times \frac{\tx[2]}{\tx[1]}=\t\)}
# endif
#endif

#if defined TARGET_proportion5
\title{TITLE 5}
\integer{an=random(2004,2005,2006,2007)}
\integer{t=randint(30..60)}
\integer{x1=randint(25..50)}
\integer{x2=randint(20..40)}
\integer{x3=100-\x1-\x2}
\integer{p1=\x1*\t*10}
\integer{p2=\x2*\t*10}
\integer{p3=\x3*\t*10}
\integer{tp=\p1+\p2+\p3}
\integer{x=randint(10..20)*100}
\integer{rep1=\x1*\x/100}
\integer{rep2=\x2*\x/100}
\integer{rep3=\x3*\x/100}

\statement{
<p>
  M.Albert a investi \p1 euros dans une entreprise, M.Bigart \p2
  euros et Mme Carrier \p3 euros.</p><p>
 En \an, les bénéfices ont été de \x euros. Chacun
 reçoit une part proportionnelle au capital investi.
</p><p>
 Calculer les trois parts.
 </p>
<ul><li>
  <label for="reply1">Part de M. Albert&nbsp;:</label> \embed{reply1}
  </li><li>
  <label for="reply2">Part de M. Bigart&nbsp;:</label> \embed{reply2}
  </li><li>
  <label for="reply3">Part de Mme Carrier&nbsp;:</label> \embed{reply3}
  </li></ul>
}
\answer{part 1}{\rep1}{type=numeric}
\answer{part 2}{\rep2}{type=numeric}
\answer{part 3}{\rep3}{type=numeric}
\solution{
<ul><li>Le total investi par ces 3 personnes est \(\p1+\p2+\p3=\tp\)
</li><li>
  La part de M. Albert est donc de \(\frac{\p1}{\tp}\times \x = \rep1\)
</li><li>
  La part de M. Bigart est donc de \(\frac{\p2}{\tp}\times \x = \rep2\)
</li><li>
  La part de Mme Carrier est donc de \(\frac{\p3}{\tp}\times \x = \rep3\)
</li></ul>}
#endif
