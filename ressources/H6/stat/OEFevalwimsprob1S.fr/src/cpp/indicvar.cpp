target=indicvar1 indicvar2 indicvar3 indicvar4 indicvar5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\computeanswer(yes)

#if defined TARGET_indicvar1
\title{Variable aléatoire et indicateurs 1}
\integer{m=randint(3..10)}
\integer{k=randint(3..10)}
\text{esps=m-\m}
\text{espt=\k*m}
\statement{<p>
On considère l'univers \(\Omega=\{e_1,e_2,\cdots,e_n\}) où les \(e_i\) sont des réels différents.  On munit  l'univers  \(\Omega\) de la loi de probabilité décrite par le tableau suivant :
 </p>
<table class="wimsborder wimscenter"><tr><td>
 \(e_1) </td><td>\(e_2\)</td><td>\(\cdots\)</td><td>\(e_n\)</td></tr>
<tr><td>\(p_1) </td><td>\(p_2\)</td><td>\(\cdots\)</td><td>\(p_n\)</td></tr></table>
<p>
On appelle \(m\) son espérance.<br>
On considère la variable aléatoire S qui à l'éventualité \(e_i\) associe
 le réel \(e_i-\m\), dont la loi de probabilité est :</p>
<table class="wimsborder wimscenter"><tr><td>
 \(e_1- \m\) </td><td>\(e_2-\m\)</td><td>\(\cdots\)</td><td>\(e_n-\m\)</td></tr>
<tr><td>\(p_1\) </td><td>\(p_2\)</td><td>\(\cdots)</td><td>\(p_n\)</td></tr></table>
et la variable aléatoire \(T\) qui à l'éventualité
\(e_i\) associe le réel \(\k e_i\), dont la loi de probabilité est :
<table class="wimsborder wimscenter"><tr><td>
 \(\k e_1\) </td><td>\(\k e_2\)</td><td>\(\cdots\)</td><td>\(\k e_n\)</td></tr>
<tr><td>\(p_1\) </td><td>\(p_2\)</td><td>\(\cdots\)</td><td>\(p_n\)</td></tr></table>

Calculer l'espérance des variables \(S\) et \(T\), en fonction des réels \(e_i\),\(p_i\) et \(m\).
<div class="wimscenter"> <label for="reply1">\(E(S) =\)</label> \embed{reply1,3}<br>
<label for="reply1">\(E(T) =\)</label> \embed{reply2,3}
</div>
}
\answer{E(S)}{\esps}{type=algexp}
\answer{E(T)}{\espt}{type=algexp}
#endif

#if defined TARGET_indicvar2
\title{Variable aléatoire et indicateurs 2}
\rational{pA=1/2}
\rational{pB=1/4}
\rational{pC=1/8}
\rational{pD=1/8}
\integer{q=-randint(15..25)}
\integer{m=randint(2..4)}
\integer{n=ceil(-\m/2-1/4-\q/4)}
\rational{g=\n/2+\m/4+(1+\q)/8}
\integer{n=\g=0?\n+1}
\statement{<p>
On lance au plus trois fois une pièce bien équilibrée ; la partie s'arrête dès que l'on a obtenu "Pile".<br>
Les issues possibles de cette expérience peuvent s'écrire : </p>
<table class="wimsborder wimscenter"><tr><td>P</td><td>FP</td><td>FFP</td><td>FFF</td></tr></table>
<div class="wims_question">
Ces quatres issues sont-elles équiprobables ? \embed{reply1}
<p>
Calculer les probabilités des événements suivants :</p>
<ul>
<li> A : <span class="wims_emph">"Obtenir pile au premier lancer"</span> <label for="reply2"> \(P(A) = \)</label>\embed{reply2,5}</li>
<li> B :  <span class="wims_emph">"Obtenir pile au second lancer"</span> <label for="reply3"> \(P(B) = \)</label>\embed{reply3,5}</li>
<li> C :  <span class="wims_emph">"Obtenir pile au troisième lancer"</span><label for="reply4"> \(P(C) = \)</label>\embed{reply4,5}</li>
<li> D :  <span class="wims_emph">"Ne pas obtenir pile"</span> <label for="reply5"> \(P(D)=\)</label>\embed{reply5,5}</li>
</ul>
<div class="wims_instruction">Donner les valeurs exactes.</div>
</div>
Soit \(X\) la variable aléatoire qui à l'événement A associe \(n\) points (\(n\) entier),
 à l'événement B  \m points,  à l'événement C 1 point et à l'événement D \q points.
 <div class="wims_question">
Calculer à partir de quelle valeur de \(n\) le jeu est favorable au joueur.
<div class="wimscenter"> à partir de \(n = \)\embed{reply6,3}</div>
</div>
}
\answer{Issues équiprobables}{2;Oui,Non}{type=radio}
\answer{P(A)}{\pA}{type=numexp}{option=noreduction}
\answer{P(B)}{\pB}{type=numexp}{option=noreduction}
\answer{P(C)}{\pC}{type=numexp}{option=noreduction}
\answer{P(D)}{\pD}{type=numexp}{option=noreduction}
\answer{n}{\n}{type=numexp}
\hint{On considère que le jeu est favorable au joueur si l'espérance du nombre de points qu'il obtient au jeu est strictement positive.}
#endif

#if defined TARGET_indicvar4
\title{Variable aléatoire et indicateurs 4}
\text{al=400,500,1000}
\integer{k=randint(1..3)}
\integer{a=\al[\k]}
\text{max1l=8,8,9}
\integer{max1=\max1l[\k]}
\integer{max2=6}
\rational{pg1=1-1/2^\max1}
\rational{pg2=1-1/2^\max2}
\text{lststr=Stratégie 1, Stratégie 2, Les deux stratégies sont équivalentes}
\real{sigx=(2^\max1-1)^2/2^\max1+1^2*(2^\max1-1)/2^\max1}
\real{sigx=sqrt(\sigx)}
\text{gy=1,2,5,14,41,122,-364}
\text{py=1/2,1/4,1/8,1/16,1/32,1/64,1/64}
\real{sigy=0}
\real{ey=0}
\for{i=1 to 7}
 {
 \real{ey=\ey+\py[\i]*\gy[\i]}
 \real{sigy=\sigy+\py[\i]*(\gy[\i])^2}
 }
\real{sigy=\sigy-(\ey)^2}
\real{sigy=sqrt(\sigy)}
\statement{<p>
Un joueur joue au jeu de pile ou face avec la règle suivante :<br>
Si Face sort, il perd sa mise, si Pile sort, il gagne le double de sa mise.<br>
Sa mise initiale est de 1 euro et il dispose au départ d'un capital de \a euros.
La partie s'arrête dès qu'il gagne ou qu'il ne peut plus miser.</p>
Voici deux stratégies :
<ul>
 <li><b>Stratégie 1 : il double sa mise s'il perd.</b><br>
<label for="reply1"> Quel est le nombre maximal de parties qu'il peut jouer ?</label> \embed{reply1,3}<br>
<label for="reply2"> Quelle est la probabilité de gagner la partie ?</label> \embed{reply2,5}<br>
 Soit \(X\) la variable aléatoire qui comptabilise le gain (ou la perte) réalisé(e).<br>
 Déterminer la loi de \(X\) et calculer son espérance mathématique et son écart type.<br>
 <table class="wimsnoborder wimscenter"><tr><td>\(E(X)=\)\embed{reply3,5}</td>
 <td>\(\sigma(X)=\)\embed{reply4,5}</td></tr></table>
 </li>
 <li><b>Stratégie 2 : il triple sa mise s'il perd.</b><br>
<label for="reply5">Quel est le nombre maximal de parties qu'il peut jouer ?</label>\embed{reply5,3}<br>
<label for="reply6">Quelle est la probabilité de gagner la partie ?</label>\embed{reply6,5}<br>
Soit \(Y\) la variable aléatoire qui comptabilise le gain (ou la perte) réalisé(e).<br>
Déterminer la loi de Y et calculer son espérance mathématique et son écart type.
<table class="wimsnoborder wimscenter"><tr><td>\(E(Y)=\)\embed{reply7,5}</td>
<td>\(\sigma(Y)=\)\embed{reply8,5}</td></tr></table>
</li>
 <li><b>Comparaison des deux stratégies.</b><br>
Avec quelle stratégie a-t-on le plus de chance de gagner ?<br> \embed{reply9}<br>
Avec quelle stratégie peut-on espérer le plus gagner ?<br> \embed{reply10}<br>
Avec quelle stratégie peut-on réaliser le gain le plus important ?<br> \embed{reply11}<br>
Quelle stratégie est la plus risquée ?<br> \embed{reply12}<br>
</li></ul>
}
\answer{Statégie 1 : nb max de partie}{\max1}{type=numeric}
\answer{Stratégie 1 : probabilité perte}{\pg1}{type=numexp}
\answer{E(X)}{0}{type=numeric}
\answer{\(\sigma(X))}{\sigx}{type=numeric}
\answer{Statégie 2 : nb max de partie}{\max2}{type=numeric}
\answer{Stratégie 2 : probabilité perte}{\pg2}{type=numexp}
\answer{E(Y)}{0}{type=numeric}
\answer{\(\sigma(Y))}{\sigy}{type=numeric}
\answer{chance de gagner}{1;\lststr}{type=radio}
\answer{espérance maximale}{3;\lststr}{type=radio}
\answer{gain maximal}{2;\lststr}{type=radio}
\answer{risque maximal}{2;\lststr}{type=radio}

#endif

#if defined TARGET_indicvar3
\title{Variable aléatoire et indicateurs 3}
\text{nbc=1,3,6,6,3,1}
\text{pbc=4,2,1,1,2,4}
\integer{nbcs=20}
\text{gains=+100,+200,-300}
\text{gains=shuffle(\gains),shuffle(\gains)}
\text{colorh=}
\text{colorv=}
\integer{pg=0}
\integer{pp=0}
\for{i=1 to 3}
 {
 \integer{g=\gains[\i]}
 \text{col=\g>0?green:red}
 \text{colorh=wims(append item \col to \colorh)}
 \integer{pg=\g>0?\pg+\nbc[\i]*\pbc[\i]}
 \integer{pp=\g<0?\pp+\nbc[\i]*\pbc[\i]}
 \integer{g=\gains[\i+3]}
 \text{col=\g>0?blue:orange}
 \text{colorv=wims(append item \col to \colorv)}
 \integer{pg=\g>0?\pg+\nbc[\i+3]*\pbc[\i+3]}
 \integer{pp=\g<0?\pp+\nbc[\i+3]*\pbc[\i+3]}
}
\integer{rep8=\pg>\pp?1:2}
\text{i1=position(-300,\gains)}
\rational{p1=(\nbc[\i1[1]]*\pbc[\i1[1]]+\nbc[\i1[2]]*\pbc[\i1[2]])/32}
\text{i2=position(+100,\gains)}
\rational{p2=(\nbc[\i2[1]]*\pbc[\i2[1]]+\nbc[\i2[2]]*\pbc[\i2[2]])/32}
\text{i3=position(+200,\gains)}
\rational{p3=(\nbc[\i3[1]]*\pbc[\i3[1]]+\nbc[\i3[2]]*\pbc[\i3[2]])/32}
\rational{esp=\p1*(-300)+\p2*100+\p3*200}
\rational{var=\p1*(-300)^2+\p2*100^2+\p3*200^2-(\esp)^2}
\real{sig=round(100*sqrt(\var))/100}
\text{dessin=
 xrange -1,18
 yrange -2,13
 fpoly black,0,3,3,3,3,4,1,4,1,6,3,6,3,7,1,7,1,9,3,9,3,10,0,10
 fpoly black,0,-1,15,-1,15,1,13,1,13,0,11,0,11,1,9,1,9,0,7,0,7,1,5,1,5,0,3,0,3,1,0,1
 fpoly black,5,3,7,3,7,4,5,4
 fpoly black,5,6,7,6,7,7,5,7
 fpoly black,5,9,7,9,7,10,5,10
 fpoly black,9,3,11,3,11,4,9,4
 fpoly black,9,6,11,6,11,7,9,7
 fpoly black,9,9,11,9,11,10,9,10
 fpoly black,13,3,15,3,15,4,13,4
 fpoly black,13,6,15,6,15,7,13,7
 fpoly black,13,9,15,9,15,10,13,10
 dsegment 0,2,15,2,magenta
 dsegment 4,5,15,5,magenta
 dsegment 4,8,15,8,magenta
 dsegment 4,2,4,10,magenta
 dsegment 8,2,8,10,magenta
 dsegment 12,2,12,10,magenta
 circle 4,2,25,magenta
 circle 4,5,25,magenta
 circle 4,8,25,magenta
 circle 8,2,25,magenta
 circle 8,5,25,magenta
 circle 8,8,25,magenta
 circle 12,2,25,magenta
 circle 12,5,25,magenta
 circle 12,8,25,magenta
 text black,3.9,2.3,medium,?
 text black,3.9,5.3,medium,?
 text black,3.9,8.3,medium,?
 text black,7.9,2.3,medium,?
 text black,7.9,5.3,medium,?
 text black,7.9,8.3,medium,?
 text black,11.9,2.3,medium,?
 text black,11.9,5.3,medium,?
 text black,11.9,8.3,medium,?
 text \colorh[1],3.2,11,medium,\gains[1]
 text \colorh[2],7.2,11,medium,\gains[2]
 text \colorh[3],11.2,11,medium,\gains[3]
 text \colorv[1],15,8,medium,\gains[4]
 text \colorv[2],15,5,medium,\gains[5]
 text \colorv[3],15,2,medium,\gains[6]
 text red,-0.8,2,medium,depart
}
\statement{
<div class="wims_columns">
  <div class="medium_size text_col">
 Le jeu consiste à s'engager dans un dédale et à le parcourir avec la règle suivante :
 on ne peut aller que vers le nord ou vers l'est, et à chaque carrefour, on choisit
 la direction en lançant une pièce : pile on va vers le Nord, face on va vers l'Est.
 A chacune des 6 sorties possibles est associé un résultat : on peut gagner 100 euros,
 200 euros ou perdre 300 euros.
 </div>
 <div class="medium_size img_col">\draw{225,225}{\dessin}</div>
</div>
<div class="wims_question">
 Déterminer le nombre d'itinéraires possibles : <label for="reply1">\embed{reply1,3}</label>
</div>
Un trajet comporte au minimum 3 étapes et au maximum 5 étapes.
<div class="wims_question">
Déterminer la probabilité d'un trajet en fonction de son nombre d'étapes :
<table class="wimsborder wimscenter">
<tr><th>Trajet comportant</th><td> 3 étapes</td><td> 4 étapes </td><td> 5 étapes </td></tr>
<tr><th>Probabilité</th><td>\embed{reply14,3}</td><td>\embed{reply15,3}</td><td>\embed{reply16,3}</td></tr>
</table>
Puis déterminer le nombre d'itinéraires possibles pour chacune des 6 sorties.
<table class="wimsborder wimscenter">
<tr><th>Sortie</th><td style="color:\colorh[1]">\gains[1]</td>
<td style="color:\colorh[2]">\gains[2]</td>
<td style="color:\colorh[3]">\gains[3]</td>
<td style="color:\colorv[1]">\gains[4]</td>
<td style="color:\colorv[2]">\gains[5]</td>
<td style="color:\colorv[3]">\gains[6]</td></tr>
<tr><th>Nb chemins</th><td>\embed{reply2,3}</td>
<td>\embed{reply3,3}</td><td>\embed{reply4,3}</td>
<td>\embed{reply5,3}</td><td>\embed{reply6,3}</td>
<td>\embed{reply7,3}</td></tr>
</table>
</div>
 On considère la variable aléatoire \(X\) qui, à chaque parcours,
 associe le gain (positif ou négatif) final.
<div class="wims_question">
 Déterminer la loi de probabilité de \(X\), son espérance mathématique et son écart type.
<table class="wimsborder wimscenter">
<tr><th>\(x\)</th><td>-300</td><td>+100</td><td>+200</td></tr>
<tr><th>\(P(X=x)\)</th><td>\embed{reply9,3}</td>
<td>\embed{reply10,3}</td><td>\embed{reply11,3}</td></tr></table>
<div class="wimscenter"> \(E(X)=\)\embed{reply12,7} et
\(\sigma(X)\)=\embed{reply13,7}<i> arrondi au centième</i></div>
 <label for="reply8">Quel est l'événement le plus probable, gagner ou perdre ?</label> \embed{reply8}
</div>

}
\answer{nb total chemins }{\nbcs}{type=numexp}
\answer{nb chemins 1}{\nbc[1]}{type=numexp}
\answer{nb chemins 2}{\nbc[2]}{type=numexp}
\answer{nb chemins 3}{\nbc[3]}{type=numexp}
\answer{nb chemins 4}{\nbc[4]}{type=numexp}
\answer{nb chemins 5}{\nbc[5]}{type=numexp}
\answer{nb chemins 6}{\nbc[6]}{type=numexp}
\answer{gagner ou perdre}{\rep8;Gagner,Perdre}{type=radio}
\answer{p1}{\p1}{type=numexp}{option=noreduction}
\answer{p2}{\p2}{type=numexp}{option=noreduction}
\answer{p3}{\p3}{type=numexp}{option=noreduction}
\answer{E(G)}{\esp}{type=numexp}{option=noreduction}
\answer{\(\sigma(G))}{\sig}{type=numeric}
\answer{Trajet à 3 étapes}{1/8}{type=numexp}
\answer{Trajet à 4 étapes}{1/16}{type=numexp}
\answer{Trajet à 5 étapes}{1/32}{type=numexp}
#endif

#if defined TARGET_indicvar5
\title{Variable aléatoire et indicateurs 5}
\integer{n=randint(6..10)}
\text{noms=Bernoulli, Fermat, Gauss, Kolmogorov, Laplace, Pascal, Poincaré, Tchebychev, Markov, Galton}
\text{nomsch=item(1..\n,\noms)}
\integer{tot=\n^4}
\rational{pa=1/\n^3}
\rational{pb=\n*(\n-1)*4/\tot}
\rational{pc=\n*(\n-1)*(\n-2)*(\n-3)/\tot}
\rational{pd=1-\pa-\pb-\pc}
\text{p=\pd,\pc,\pb,\pa}
\rational{esp=0}
\rational{var=0}
\text{xval=-1,0,4,49}
\for{i=1 to 4}
 {
 \rational{esp=\esp+\p[\i]*\xval[\i]}
 \rational{var=\var+\p[\i]*(\xval[\i])^2}
 }
\rational{var=\var-(\esp)^2}
\real{sig=round(100*sqrt(\var))/100}
\integer{rep10=\esp<0?1:2}
\statement{<p>
Au casino « Royal des mathématiques » on peut jouer aux machines à sous.<br>
 Parmi toutes celles qui existent, voici celle qui emporte le plus grand succès, <b>Le Jackpot des Grands Mathématiciens : </b><br>
 Quatre rouleaux tournent indépendamment les uns des autres
et \n portraits de grands probabilistes (parmi d'autres) peuvent
 sortir (pour chacun des rouleaux) : <b>\nomsch</b>.</p>

Exemple d'une partie (après avoir mis une pièce d'1 euro et actionné la manivelle)
<div class="wimscenter"><img src="\imagedir/jackpot.gif" alt="jackpot"></div>
On joue une partie à 1 euro.
<div class="wims_question">
Quelle est la probabilité des événements suivants ?
<ul>
<li>A  "<span class="wims_emph">Obtenir quatre portraits identiques</span>" :<label for="reply1"> P(A) =</label> \embed{reply1,7}</li>
<li>B  "<span class="wims_emph">Obtenir exactement 3 portraits identiques</span>" :<label for="reply2"> P(B) =</label> \embed{reply2,7}</li>
<li>C  "<span class="wims_emph">Obtenir quatre portraits distincts</span>" : <label for="reply3">P(C) =</label> \embed{reply3,7}</li>
</ul>
<div class="wims_instruction">Entrer les valeurs exactes.</div>
</div>
On gagne :
<ul><li> 50 euros si l'événement A se réalise ;</li>
<li> 5 euros si l'événement B se réalise ;</li>
<li> et 1 euro si l'événement C se réalise. </li>
</ul>
 Dans les autres cas, on ne gagne rien.
<div class="wims_question">
Soit \(G\) la variable aléatoire donnant le gain d'une partie.
<ol>
<li> Déterminer la loi de probabilité de \(G\).
<table class="wimsborder wimscenter">
<tr><td>\(g\)</td><td>-1</td><td>0</td><td>4</td><td>49</td></tr>
<tr><td>\(P(G=g)\)</td><td>\embed{reply4,7}</td><td>\embed{reply5,7}</td><td>\embed{reply6,7}</td><td>\embed{reply7,7}</td></tr>
</table>
</li>
<li> Calculer l'espérance mathématique de \(G\) et son écart type.
<div class="wimscenter"><label for="reply8">\(E(G)=\)</label>\embed{reply8,7} et
<label for="reply9">\(\sigma(G)=\)</label>\embed{reply9,7}<i>arrondi au centième.</i>
</div></li>
<li>
<label for="reply10">Le jeu est-il rentable pour le casino ?</label> \embed{reply10}
</li></ol></div>

}
\answer{P(A)}{\pa}{type=numexp}{option=noreduction}
\answer{P(B)}{\pb}{type=numexp}{option=noreduction}
\answer{P(C)}{\pc}{type=numexp}{option=noreduction}
\answer{P(-1)}{\p[1]}{type=numexp}{option=noreduction}
\answer{P(0)}{\p[2]}{type=numexp}{option=noreduction}
\answer{P(4)}{\p[3]}{type=numexp}{option=noreduction}
\answer{P(49)}{\p[4]}{type=numexp}{option=noreduction}
\answer{E(G)}{\esp}{type=numexp}{option=noreduction}
\answer{\(\sigma(G))}{\sig}{type=numexp}
\answer{rentable}{\rep10;Oui,Non}{type=radio}
\help{On considère que le jeu est rentable pour le casino si l'espérance de \(G\) est strictement négative.}
#endif
