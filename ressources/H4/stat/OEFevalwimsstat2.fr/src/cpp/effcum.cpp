target=effcum1 effcum2 effcum3 effcum4 effcum5
\precision{100}
\computanswer{no}
\integer{range=random(20..100)}
\integer{xmin=random(0..50)}
\integer{parite=random(1,2)}
\integer{parite=2}
\integer{nbval=2*randint(3,4)+\parite}
\text{listval=}
\for{i=1 to \nbval+1}
 {
 \integer{val=random(\xmin..\xmin+\range)}
 \text{listval=wims(append item \val to \listval)}
 }
\text{xlistval=wims(sort numeric list \listval)}
\text{xlistval=wims(listuniq \xlistval)}
\integer{nbval=items(\xlistval)-1}
\integer{xmin=\xlistval[1]}
\integer{xmax=\xlistval[\nbval+1]}

 ## génération des effectifs
\text{lsteff=}
\integer{efftotal=0}
\for{i=1 to \nbval}
  {
   \integer{eff=random(0..20)}
   \integer{efftotal=\efftotal+\eff}
   \text{lsteff=wims(append item \eff to \lsteff)}
  }
  ## Détermination de la médiane
\integer{ecc=0}
\integer{ecd=\efftotal}
\integer{Medg=-1}
\text{lstecc=}
\text{lstecd=}
\real{effMed=\efftotal/2}
\integer{rangMed=ceil(\effMed)}
\text{lstecd=wims(append item \ecd to \lstecd)}

\for{i=1 to \nbval}
 {
 \integer{ecc=\ecc+\lsteff[\i]}
 \integer{ecd=\ecd-\lsteff[\i]}
 \text{lstecc=wims(append item \ecc to \lstecc)}
 \text{lstecd=wims(append item \ecd to \lstecd)}
 \if{\ecc>\effMed and \Medg<0}
   {
   \integer{Medg=\xlistval[\i]}
   \integer{imed=\i}
   \integer{Medd=\xlistval[\i+1]}
   }
 }
   \real{xmed=(\effMed-\lstecc[\imed-1])/(\lstecc[\imed]-\lstecc[\imed-1])*(\Medd-\Medg)+\Medg}


\text{mstep=wims(makelist r x for x=1 to \nbval+1)}
\text{mstep=wims(nospace \mstep)}
#if defined TARGET_effcum1
\title{ Effectifs cumulés 1}
\text{col=Effectifs cumulés croissants}
\text{lstval=\lstecc}
\steps{\mstep}
#endif
#if defined TARGET_effcum2
\title{ Effectifs cumulés 2}
\text{col=Effectifs cumulés décroissants}
\text{lstval=\lstecd}
\steps{\mstep}
#endif
#if defined TARGET_effcum3
\title{ Effectifs cumulés 3}
\text{col=Effectifs cumulés croissants}
\text{lstval=\lstecc}
\steps{\mstep}
#endif
#if defined TARGET_effcum4
\title{ Effectifs cumulés 4}
\text{col=Effectifs cumulés décroissants}
\text{lstval=\lstecd}
\steps{\mstep}
#endif
#if defined TARGET_effcum5
\title{ Effectifs cumulés 5}
\text{col=Effectifs cumulés croissants}
\text{col2=Effectifs cumulés décroissants}
\text{lstval=\lstecc}
\text{lstval2=\lstecd}
\text{mstep=wims(makelist r x for x=1 to 2*\nbval+4)}
\text{mstep=wims(nospace \mstep)}
\steps{\mstep}
#endif

#if (defined TARGET_effcum3  || defined TARGET_effcum4 )
## préparation du dessin
#if defined TARGET_effcum3
\text{image=
 xrange \xmin-15,\xmax+5
 yrange -10,\efftotal+5
 arrow \xmin-5,0,\xmax+5,0,10,black
 arrow \xmin-5,-5,\xmin-5,\efftotal+5,10,black
 segment \xlistval[1],0,\xlistval[2],\lstval[1],blue
 dpolyline orange,\xmin-5,\lstval[1],\xlistval[2],\lstval[1],\xlistval[2],0
 text black,\xlistval[1],-5,medium,\xlistval[1]
 text black,\xlistval[2],-3,medium,\xlistval[2]
 text black,\xmin-12,\lstval[1],medium,\lstval[1]
}
\integer{xoff=12}
\integer{yoff=3}
\for{i=2 to \nbval}
 {
 \integer{xoff=\xoff=12?7:12}
 \integer{yoff=\yoff=3?5:3}
 \text{image=\image
 segment \xlistval[\i],\lstval[\i-1],\xlistval[\i+1],\lstval[\i],blue
 dpolyline orange,\xmin-5,\lstval[\i],\xlistval[\i+1],\lstval[\i],\xlistval[\i+1],0
 text black,\xlistval[\i+1],-\yoff,medium,\xlistval[\i+1]
 text black,\xmin-\xoff,\lstval[\i],medium,\lstval[\i]
 }
}
#else
\text{image=
 xrange \xmin-15,\xmax+5
 yrange -10,\efftotal+5
 arrow \xmin-5,0,\xmax+5,0,10,black
 arrow \xmin-5,-5,\xmin-5,\efftotal+5,10,black
}
\integer{xoff=12}
\integer{yoff=3}
\for{i=1 to \nbval}
 {
 \integer{xoff=\xoff=12?7:12}
 \integer{yoff=\yoff=3?5:3}
 \text{image=\image
 segment \xlistval[\i],\lstval[\i],\xlistval[\i+1],\lstval[\i+1],blue
 dpolyline orange,\xmin-5,\lstval[\i],\xlistval[\i],\lstval[\i],\xlistval[\i],0
 text black,\xlistval[\i],-\yoff,medium,\xlistval[\i]
 text black,\xmin-\xoff,\lstval[\i],medium,\lstval[\i]
 }
}
 \integer{xoff=\xoff=12?7:12}
 \integer{yoff=\yoff=3?5:3}
\text{image=\image
 segment \xlistval[\nbval],\lstval[\nbval],\xlistval[\nbval+1],0,blue
 text black,\xlistval[\nbval+1],-\yoff,medium,\xlistval[\nbval+1]
}
#endif
\statement{
On a représenté le polygone des \col de la série statistique suivante:
<table><tr><td>
<table class="wimscenter wimsborder"><tr><th>Classe</th><th>Effectifs</th></tr>
\for{kk=2 to \nbval+1}
 {
<tr><td>&#91; \xlistval[\kk-1]; \xlistval[\kk] &#91;</td>
<td>\embed{reply\kk,4}</td></tr>
 }
</table>
</td><td>\draw{400,400}{\image}</td></tr></table>
Remplir le tableau des effectifs de cette série:<p>
Quel est l'effectif total? \embed{reply1,3}.
</p>
}
\answer{effectif total}{\efftotal}{type=numeric}
\answer{valeur 1}{\lsteff[1]}{type=numeric}
\answer{valeur 2}{\lsteff[2]}{type=numeric}
\answer{valeur 3}{\lsteff[3]}{type=numeric}
\answer{valeur 4}{\lsteff[4]}{type=numeric}
\answer{valeur 5}{\lsteff[5]}{type=numeric}
\answer{valeur 6}{\lsteff[6]}{type=numeric}
\answer{valeur 7}{\lsteff[7]}{type=numeric}
\answer{valeur 8}{\lsteff[8]}{type=numeric}
\answer{valeur 9}{\lsteff[9]}{type=numeric}
\answer{valeur 10}{\lsteff[10]}{type=numeric}
#endif

#if defined TARGET_effcum5
\integer{ix1=randint(2..\nbval-1)}
\integer{x1=\xlistval[\ix1]}
\integer{ix2=randint(2..\nbval-1)}
\integer{x2=\xlistval[\ix2]}
\statement{
On considère la série statistique suivante représentant le nombre de livres lus par an dans une population:
<table class="wimscenter wimsborder"><tr><th>Classe</th><th>Effectif</th><th> \col</th><th>\col2</th></tr>
\for{kk=5 to \nbval+4}
 {
<tr><td>&#91; \xlistval[\kk-4]; \xlistval[\kk-3] &#91;</td>
<td>\lsteff[\kk-4]</td>
  \for{jj=2*(\kk-2)-1  to 2*(\kk-2)}
    {
    <td>\embed{reply\jj,4}</td>
    }
</tr>

 }
</table>
<p>Remplir les effectifs cumulés croissants et décroissants de cette séries,
puis répondre aux questions suivantes:</p>
<ul>
<li> Combien de personnes lisent plus de \x1 livres par an? \embed{reply1,3}</li>
<li> Combien de personnes lisent au plus \x1 (non inclus) livres par an? \embed{reply2,3}</li>
<li> Combien de personnes lisent moins de \x2 (non inclus) livres par an? \embed{reply3,3}</li>
<li> Combien de personnes lisent au moins \x2 livres par an? \embed{reply4,3}</li>
</ul>}
\answer{plus de \x1}{\lstecd[\ix1]}{type=numeric}
\answer{au plus \x1}{\lstecc[\ix1-1]}{type=numeric}
\answer{moins de \x2}{\lstecc[\ix2-1]}{type=numeric}
\answer{au moins \x2}{\lstecd[\ix2]}{type=numeric}
\answer{coissant 1}{\lstval[1]}{type=numeric}
\answer{décroissant 1}{\lstval2[1]}{type=numeric}
\answer{coissant 2}{\lstval[2]}{type=numeric}
\answer{décroissant 2}{\lstval2[2]}{type=numeric}
\answer{coissant 3}{\lstval[3]}{type=numeric}
\answer{décroissant 3}{\lstval2[3]}{type=numeric}
\answer{coissant 4}{\lstval[4]}{type=numeric}
\answer{décroissant 4}{\lstval2[4]}{type=numeric}
\answer{coissant 5}{\lstval[5]}{type=numeric}
\answer{décroissant 5}{\lstval2[5]}{type=numeric}
\answer{coissant 6}{\lstval[6]}{type=numeric}
\answer{décroissant 6}{\lstval2[6]}{type=numeric}
\answer{coissant 7}{\lstval[7]}{type=numeric}
\answer{décroissant 7}{\lstval2[7]}{type=numeric}
\answer{coissant 8}{\lstval[8]}{type=numeric}
\answer{décroissant 8}{\lstval2[8]}{type=numeric}
\answer{coissant 9}{\lstval[9]}{type=numeric}
\answer{décroissant 9}{\lstval2[9]}{type=numeric}
\answer{coissant 10}{\lstval[10]}{type=numeric}
\answer{décroissant 10}{\lstval2[10]}{type=numeric}
#endif

#if (defined TARGET_effcum1  || defined TARGET_effcum2 )
\statement{
On considère la série statistique suivante:
<table class="wimscenter wimsborder"><tr><th>Classe</th><th>Effectif</th><th> \col</th></tr>
\for{kk=2 to \nbval+1}
 {
<tr><td>&#91; \xlistval[\kk-1]; \xlistval[\kk] &#91;</td>
<td>\lsteff[\kk-1]</td><td>\embed{reply\kk,4}</td></tr>
 }
</table>
Remplir les \col de cette série:<p>
Quel est l'effectif total? \embed{reply1,3}.
</p>
}
\answer{effectif total}{\efftotal}{type=numeric}
\answer{valeur 1}{\lstval[1]}{type=numeric}
\answer{valeur 2}{\lstval[2]}{type=numeric}
\answer{valeur 3}{\lstval[3]}{type=numeric}
\answer{valeur 4}{\lstval[4]}{type=numeric}
\answer{valeur 5}{\lstval[5]}{type=numeric}
\answer{valeur 6}{\lstval[6]}{type=numeric}
\answer{valeur 7}{\lstval[7]}{type=numeric}
\answer{valeur 8}{\lstval[8]}{type=numeric}
\answer{valeur 9}{\lstval[9]}{type=numeric}
\answer{valeur 10}{\lstval[10]}{type=numeric}
#endif
