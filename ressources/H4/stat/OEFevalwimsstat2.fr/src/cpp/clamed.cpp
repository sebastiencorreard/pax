target=clamed1 clamed2 clamed3 clamed4 clamed5
\precision{10000}
\integer{range=random(20..100)}
\integer{xmin=random(0..50)}
\integer{parite=random(1,2)}
\integer{parite=2}
#if defined TARGET_clamed1
\integer{nbval=4+\parite}
#else
\integer{nbval=2*randint(3,4)+\parite}
#endif
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
\integer{fcc=0}
\integer{Medg=-1}
\text{lstecc=}
\text{lstfcc=}
\real{effMed=\efftotal/2}
\integer{rangMed=ceil(\effMed)}

\for{i=1 to \nbval}
 {
 \integer{ecc=\ecc+\lsteff[\i]}
 \real{fcc=\fcc+\lsteff[\i] / \efftotal}
 \text{lstecc=wims(append item \ecc to \lstecc)}
 \text{lstfcc=wims(append item \fcc to \lstfcc)}
 \if{\ecc>\effMed and \Medg<0}
   {
   \integer{Medg=\xlistval[\i]}
   \integer{imed=\i}
   \integer{Medd=\xlistval[\i+1]}
   }
 }
   \real{xmed=(\effMed-\lstecc[\imed-1])/(\lstecc[\imed]-\lstecc[\imed-1])*(\Medd-\Medg)+\Medg}


#if (defined TARGET_clamed1  || defined TARGET_clamed2  || defined TARGET_clamed5 )
\text{serie=<table class="wimscenter wimsborder"><tr><th>Classe</th><th>Effectif</th></tr>}
\for{i=1 to \nbval}
  {
  \text{serie=\serie <tr><td>&#91; \xlistval[\i]; \xlistval[\i+1] &#91;</td><td>\lsteff[\i]</td></tr>}
  }
\text{serie=\serie </table>}

#else

#if (defined TARGET_clamed3  || defined TARGET_clamed5 )
\text{col=Effectifs cumulés croissants}
\text{lstval=\lstecc}
#else
\text{col=Fréquences cumulées croissantes}
\text{lstval=\lstfcc}
#endif
\text{mstep=wims(makelist r x for x=1 to \nbval+2)}
\text{mstep=wims(nospace \mstep)}

\text{serie=<table border=1><tr><th>Classe</th><th>Effectif</th></tr>}
#endif

#if defined TARGET_clamed1
\title{Médiane et Classes 1}
#endif
#if defined TARGET_clamed2
\title{Médiane et Classes 2}
#endif
#if defined TARGET_clamed3
\title{Médiane et Classes 3}
\steps{\mstep}
#endif
#if defined TARGET_clamed4
\title{Médiane et Classes 4}
\steps{\mstep}
#endif
#if defined TARGET_clamed5
\title{Médiane et Classes 5}
## préparation du dessin
\text{image=
 xrange \xmin-15,\xmax+5
 yrange -10,\efftotal+5
 arrow \xmin-5,0,\xmax+5,0,10,black
 arrow \xmin-5,-5,\xmin-5,\efftotal+5,10,black
 segment \xlistval[1],0,\xlistval[2],\lstecc[1],blue
 dpolyline orange,\xmin-5,\lstecc[1],\xlistval[2],\lstecc[1],\xlistval[2],0
 text black,\xlistval[1],-5,medium,\xlistval[1]
 text black,\xlistval[2],-3,medium,\xlistval[2]
 text black,\xmin-12,\lstecc[1],medium,\lstecc[1]
}
\integer{xoff=12}
\integer{yoff=3}
\for{i=2 to \nbval}
 {
 \integer{xoff=\xoff=12?7:12}
 \integer{yoff=\yoff=3?5:3}
 \text{image=\image
 segment \xlistval[\i],\lstecc[\i-1],\xlistval[\i+1],\lstecc[\i],blue
 dpolyline orange,\xmin-5,\lstecc[\i],\xlistval[\i+1],\lstecc[\i],\xlistval[\i+1],0
 text black,\xlistval[\i+1],-\yoff,medium,\xlistval[\i+1]
 text black,\xmin-\xoff,\lstecc[\i],medium,\lstecc[\i]
 }
}
\text{image=\image
 dpolyline red,\xmin-5,\efftotal/2,\xmed,\efftotal/2,\xmed,0
 segment \Medg,\lstecc[\imed-1],\Medd,\lstecc[\imed],red
}

\statement{
On a représenté le polygone des effectifs cumulés croissants de la série statistique suivante:
\serie
\draw{400,400}{\image}
<p>Déterminer la classe médiane de cette série:</p>
<label for="reply1">Classe Médiane=&#91;</label> \embed{reply1,3}; \embed{reply2,3} &#91;
<p>
Puis par interpolation linéaire, calculer la médiane de la série:</p>
<label for="reply3">Valeur de la médiane:</label> \embed{reply3,3}
}
\answer{Classe Médiane borne gauche}{\Medg}{type=numeric}
\answer{Classe Médiane borne droite}{\Medd}{type=numeric}
\answer{Médiane}{\xmed}{type=numeric}
\solution{La classe médiane est \(\lbrack \Medg;\Medd \lbrack)<br>
La médiane est précisément \xmed}
#else

#if (defined TARGET_clamed3  || defined TARGET_clamed4 )
\statement{
On considère la série statistique suivante:
<table class="wimscenter wimsborder"><tr><th>Classe</th><th>Effectif</th><th> \col</th></tr>
\for{kk=3 to \nbval+2}
 {
<tr><td>&#91; \xlistval[\kk-2]; \xlistval[\kk-1] &#91;</td>
<td><label for="reply\kk">\lsteff[\kk-2]</label></td><td>\embed{reply\kk,4}</td></tr>
 }
</table>
<p>Remplir les \col et déterminer la classe médiane de cette série:</p>
<label for="reply1">Classe Médiane=&#91; \embed{reply1,3};</label> \embed{reply2,3} &#91;
}
\answer{Classe Médiane borne gauche}{\Medg}{type=numeric}
\answer{Classe Médiane borne droite}{\Medd}{type=numeric}
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
#else
\statement{
On considère la série statistique suivante:
<div class="wimscenter">\serie </div>
<p>Déterminer la classe médiane de cette série:</p>
<label for="reply1">Classe Médiane=&#91;</label> \embed{reply1,3}; \embed{reply2,3} &#91;
}
\answer{Classe Médiane borne gauche}{\Medg}{type=numeric}
\answer{Classe Médiane borne droite}{\Medd}{type=numeric}
#endif
#endif
