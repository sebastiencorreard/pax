target=meangrp1 meangrp2 meangrp3 meangrp4 meangrp5
\precision{100}

\text{table=}
\integer{efftotal=randint(40,50,80,100)}
\integer{eff1=randint(10..\efftotal-10)}
#if defined TARGET_meangrp1 
\integer{eff2=\eff1}
#else
\integer{eff2=\efftotal-\eff1}
#endif
\text{listeff=\eff1,\eff2}
\real{moy1=randint(0..100)/10}
\real{moy2=randint(0..100)/10}
\text{listmoy=\moy1,\moy2}

#if defined TARGET_meangrp3 
\integer{nbs=5}
\text{listeff=\listeff,randint(20..50),randint(20..50),randint(20..50)}
\for{i=1 to 3}
  {\real{moyi=randint(0..100)/10}
   \text{listmoy=wims(append item \moyi to \listmoy)}
  }
#else
\integer{nbs=2}

#endif

\text{tableau=<table class="wimscenter wimsborder"><tr>
<td>&nbsp;</td><th>Effectif</th><th>Moyenne</th></tr>}
\real{moy=0}
\integer{efftotal=0}
\for{i=1 to \nbs}
 {
 \text{tableau=\tableau <tr><td>Groupe \i</td><td>\listeff[\i]</td><td>\listmoy[\i]</td></tr>}
 \real{moy=\moy+\listeff[\i]*\listmoy[\i]}
 \integer{efftotal=\efftotal+\listeff[\i]}
 }
\text{tableau=\tableau </table>}
\real{moy=\moy / \efftotal}

#if (defined TARGET_meangrp1  || defined TARGET_meangrp2  || defined TARGET_meangrp3 )
#if defined TARGET_meangrp1 
\title{Moyenne et Moyenne des sous-groupes 1}
#endif
#if defined TARGET_meangrp2 
\title{Moyenne et Moyenne des sous-groupes 2}
#endif
#if defined TARGET_meangrp3 
\title{Moyenne et Moyenne des sous-groupes 3}
#endif
\statement{
On considère une série divisée en \nbs sous-groupes dont les moyennes et les effectifs sont indiqués dans le tableau suivant:

\tableau
<p>
Calculer la moyenne de cette série:</p>
Moyenne = \embed{reply1,5}
}
\answer{moyenne}{\moy}{type=numeric}

#endif
#if defined TARGET_meangrp4 
\title{Moyenne et Moyenne des sous-groupes 4}
\statement{
On considère une série divisée en deux parties.<p>
Le premier groupe a pour effectif \eff1 et pour moyenne \moy1.</p><p>
Le deuxième groupe a pour effectif \eff2.</p>
Quelle doit être sa moyenne pour que la moyenne de la série soit \moy.<p>
Moyenne du deuxième groupe = \embed{reply1,4}</p>
}
\answer{Moyenne du deuxième groupe}{\moy2}{type=numeric}
#endif
#if defined TARGET_meangrp5 
\title{Moyenne et Moyenne des sous-groupes 5}
\statement{
On considère une série divisée en deux parties.<p>
Le premier groupe a pour effectif \eff1 et pour moyenne \moy1.</p><p>
Le deuxième groupe a pour moyenne \moy2.</p><p>
Quel doit être son effectif pour que la moyenne de la série soit \moy.</p>
Effectif du deuxième groupe = \embed{reply1,4}
}
\answer{MEffectif du deuxième groupe}{\eff2}{type=numeric}
#endif
