target=freqcum1 freqcum2 freqcum3 freqcum4 freqcum5
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

 ## génération des fréquences
\text{lsteff=}
\integer{efftotal=0}
\for{i=1 to \nbval}
  {
   \integer{eff=random(0..20)}
   \integer{efftotal=\efftotal+\eff}
   \text{lsteff=wims(append item \eff to \lsteff)}
  }
\text{lstfreq=}
\real{freqcum=0}
\for{i=1 to \nbval-1}
  {
  \integer{freq=\lsteff[\i]*1000 / \efftotal}
  \real{freq=\freq/10}
  \real{freqcum=\freqcum+\freq}
   \text{lstfreq=wims(append item \freq to \lstfreq)}
  }
\real{freq=100-\freqcum}
\text{lstfreq=wims(append item \freq to \lstfreq)}
\integer{ecc=0}
\integer{ecd=100}

\text{lstecc=}
\text{lstecd=}
\text{lstecd=wims(append item \ecd to \lstecd)}


\for{i=1 to \nbval}
 {
 \real{ecc=\ecc+\lstfreq[\i]}
 \real{ecd=\ecd-\lstfreq[\i]}
 \text{lstecc=wims(append item \ecc to \lstecc)}
 \text{lstecd=wims(append item \ecd to \lstecd)}
}

\text{mstep=wims(makelist r x for x=1 to \nbval)}
\text{mstep=wims(nospace \mstep)}
#if defined TARGET_freqcum1
\title{ Fréquences cumulées 1}
\text{col=Fréquences cumulées croissantes}
\text{lstval=\lstecc}
\steps{\mstep}
#endif
#if defined TARGET_freqcum2
\title{ Fréquences cumulées 2}
\text{col=Fréquences cumulées décroissantes}
\text{lstval=\lstecd}
\steps{\mstep}
#endif
#if defined TARGET_freqcum3
\title{ Fréquences cumulées 3}
\text{col=Fréquences cumulées croissantes}
\text{lstval=\lstecc}
\steps{\mstep}
#endif
#if defined TARGET_freqcum4
\title{ Fréquences cumulées 4}
\text{col=Fréquences cumulées décroissantes}
\text{lstval=\lstecd}
\steps{\mstep}
#endif
#if defined TARGET_freqcum5
\title{ Fréquences cumulées 5}
\text{col=Fréquences cumulées croissantes}
\text{col2=Fréquences cumulées décroissantes}
\text{lstval=\lstecc}
\text{lstval2=\lstecd}
\text{mstep=wims(makelist r x for x=1 to 2*\nbval+4)}
\text{mstep=wims(nospace \mstep)}
\steps{\mstep}
#endif

#if (defined TARGET_freqcum3  || defined TARGET_freqcum4 )
## préparation du dessin
#if defined TARGET_freqcum3
\text{image=
 xrange \xmin-15,\xmax+5
 yrange -10,105
 arrow \xmin-5,0,\xmax+5,0,10,black
 arrow \xmin-5,-5,\xmin-5,105,10,black
 segment \xlistval[1],0,\xlistval[2],\lstval[1],blue
 dsegment orange,\xmin-5,\lstval[1],\xlistval[2],\lstval[1],\xlistval[2],0
 text black,\xlistval[1],-5,medium,\xlistval[1]
 text black,\xlistval[2],-3,medium,\xlistval[2]
 text black,\xmin-12,\lstval[1],medium,\lstval[1]
}
\integer{xoff=12}
\integer{yoff=3}
\for{i=2 to \nbval}{
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
 yrange -10,105
 arrow \xmin-5,0,\xmax+5,0,10,black
 arrow \xmin-5,-5,\xmin-5,105,10,black
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
<table class="wimscenter wimsborder"><tr><th>Classe</th><th>Fréquences en %</th></tr>
\for{kk=1 to \nbval}
 {
<tr><td>&#91; \xlistval[\kk]; \xlistval[\kk+1] &#91;</td>
<td>\embed{reply\kk,4}</td></tr>
 }
</table>
</td><td>\draw{400,400}{\image}</td></tr></table>
<p>Remplir le tableau des fréquences de cette série:</p>
}
\answer{valeur 1}{\lstfreq[1]}{type=numeric}
\answer{valeur 2}{\lstfreq[2]}{type=numeric}
\answer{valeur 3}{\lstfreq[3]}{type=numeric}
\answer{valeur 4}{\lstfreq[4]}{type=numeric}
\answer{valeur 5}{\lstfreq[5]}{type=numeric}
\answer{valeur 6}{\lstfreq[6]}{type=numeric}
\answer{valeur 7}{\lstfreq[7]}{type=numeric}
\answer{valeur 8}{\lstfreq[8]}{type=numeric}
\answer{valeur 9}{\lstfreq[9]}{type=numeric}
\answer{valeur 10}{\lstfreq[10]}{type=numeric}
#endif

#if defined TARGET_freqcum5
\integer{ix1=randint(2..\nbval-1)}
\integer{x1=\xlistval[\ix1]}
\integer{ix2=randint(2..\nbval-1)}
\integer{x2=\xlistval[\ix2]}
\statement{
On considère la série statistique suivante représentant le nombre de livres lus par an dans une population:
<table class="wimscenter wimsborder"><tr><th>Classe</th><th>Fréquences en %</th><th> \col en %</th><th>\col2 en %</th></tr>
\for{kk=5 to \nbval+4}
 {
<tr><td>&#91; \xlistval[\kk-4]; \xlistval[\kk-3] &#91;</td>
<td>\lstfreq[\kk-4]</td>
  \for{jj=2*(\kk-2)-1  to 2*(\kk-2)}
    {
    <td>\embed{reply\jj,4}</td>
    }
</tr>

 }
</table>
<p>Remplir les fréquences cumulées croissantes et décroissantes de cette série,
puis répondre aux questions suivantes:</p>
<ul>
<li> Quel pourcentage de personnes lisent plus de \x1 livres par an? \embed{reply1,3}</li>
<li> Quel pourcentage de personnes lisent au plus \x1 (non inclus) livres par an? \embed{reply2,3}</li>
<li> Quel pourcentage de personnes lisent moins de \x2 (non inclus) livres par an? \embed{reply3,3}</li>
<li> Quel pourcentage de personnes lisent au moins \x2 livres par an? \embed{reply4,3}</li>
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

#if (defined TARGET_freqcum1  || defined TARGET_freqcum2 )
\statement{
On considère la série statistique suivante:
<table class="wimscenter wimsborder"><tr><th>Classe</th><th>Fréquences en %</th><th> \col en %</th></tr>
\for{kk=1 to \nbval}
 {
<tr><td>&#91; \xlistval[\kk]; \xlistval[\kk+1] &#91;</td>
<td>\lstfreq[\kk]</td><td>\embed{reply\kk,4}</td></tr>
 }
</table>
<p>Remplir les \col de cette série:</p>
}
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
