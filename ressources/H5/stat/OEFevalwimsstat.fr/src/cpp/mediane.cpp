target=mediane1 mediane2 mediane3 mediane4 mediane5 mediane6
#include "author.inc"
#include "lang_titles.inc"
\precision{100}

\integer{range=random(20..100)}
\integer{xmin=random(0..20)}
\integer{parite=random(1,0)}
#if defined TARGET_mediane1
\integer{parite=1}
#endif
#if defined TARGET_mediane2
\integer{parite=0}
#endif
\integer{nbval=2*randint(4..7)+\parite}
\text{listval=wims(makelist x for x=\xmin to \xmin+\range)}
\text{ind=shuffle(\range)}
\text{ind=item(1..\nbval,\ind)}
\text{listval=item(\ind,\listval)}
text{listval=}
%%for{i=1 to \nbval}
%%{
%% \integer{val=random(\xmin..\xmin+\range)}
%% \text{listval=wims(append item \val to \listval)}
%% }
\text{olistval=wims(sort numeric list \listval)}
\text{xlistval=\olistval}
\integer{xmin=\xlistval[1]}

#if (defined TARGET_mediane1 || defined TARGET_mediane2 )
\text{xlistval=\listval}
\text{serie=<table class="wimsborder wimscenter"><tr>}
\for{i=1 to \nbval}{
  \text{serie=\serie <td>\xlistval[\i]</td>}
}
\text{serie=\serie </tr></table>}
\real{med=\parite=1?\olistval[(\nbval+1)/2]:(\olistval[\nbval / 2]+ \olistval[\nbval / 2 +1])/2}

\statement{
On considère la série statistique suivante :
\serie
Déterminer la médiane de cette série :<div class="wimscenter">
<label for="reply1">Médiane :</label> \embed{reply1,3}
</div>
}
\answer{Médiane}{\med}{type=numeric}
#else
\integer{efftotal=100}
 %% génération des effectifs
#include "lsteff.inc"
\text{serie=<table class="wimsborder"><tr><th>Valeurs</th>}
\for{i=1 to \nbval}{
  \text{serie=\serie <td>\xlistval[\i]</td>}
}
\text{serie=\serie</tr><tr><th>Effectifs</th>}
\for{i=1 to \nbval}{
  \text{serie=\serie <td>\lsteff[\i]</td>}
}
\text{serie=\serie </tr></table>}
#endif
%% Calcul des ecc
\text{lstecc=}
\integer{ecc=0}
\integer{imed=-1}
\rational{effm=\efftotal/2}
\for{i=1 to \nbval}{
  \integer{ecc=\ecc+\lsteff[\i]}
  \if{\ecc>\effm and \imed=-1}{
    \integer{imed=\i}}
  \text{lstecc=wims(append item \ecc to \lstecc)}
}
\integer{med=\xlistval[\imed]}
\rational{med=\lstecc[\imed-1]=\effm?(\xlistval[\imed-1]+\xlistval[\imed])/2}
#if defined TARGET_mediane3
\text{col=Effectifs cumulés croissants}
\text{lstval=\lstecc}
\text{mstep=wims(makelist r x for x=1 to \nbval+1)}
\text{mstep=wims(nospace \mstep)}
\steps{\mstep}
\statement{<p>
On considère la série statistique suivante :</p>
<table class="wimscenter wimsborder"><tr><th>Valeur</th>
\for{n=1 to \nbval}{
  <td>\xlistval[\n]</td>
}
</tr>
<tr><th>Effectif</th>
\for{n=1 to \nbval}{
  <td>\lsteff[\n]</td>
}
</tr>
<tr><th>E.C.C</th>
\for{j=2 to \nbval+1}{
  <td>\embed{reply\j,4}</td>
}
</tr></table>
<p>
Remplir la ligne des effectifs cumulés croissants (E.C.C), puis déterminer la médiane de cette série :
</p>
<div class="wimscenter"><label for="reply1">Médiane :</label> \embed{reply1,4} </div>
}
\answer{Médiane}{\med}{type=numeric}
\answer{ecc1}{\lstecc[1]}{type=numeric}
\answer{ecc2}{\lstecc[2]}{type=numeric}
\answer{ecc3}{\lstecc[3]}{type=numeric}
\answer{ecc4}{\lstecc[4]}{type=numeric}
\answer{ecc5}{\lstecc[5]}{type=numeric}
\answer{ecc6}{\lstecc[6]}{type=numeric}
\answer{ecc7}{\lstecc[7]}{type=numeric}
\answer{ecc8}{\lstecc[8]}{type=numeric}
\answer{ecc9}{\lstecc[9]}{type=numeric}
\answer{ecc10}{\lstecc[10]}{type=numeric}
\answer{ecc11}{\lstecc[11]}{type=numeric}
\answer{ecc12}{\lstecc[12]}{type=numeric}
\answer{ecc13}{\lstecc[13]}{type=numeric}
\answer{ecc14}{\lstecc[14]}{type=numeric}
\answer{ecc15}{\lstecc[15]}{type=numeric}
#endif
#if (defined TARGET_mediane4 || defined TARGET_mediane5 || defined TARGET_mediane6 )
\text{col=Effectifs cumulés croissants}
\text{lstval=\lstecc}
\text{mstep=wims(makelist r x for x=1 to \nbval+2)}
\text{mstep=wims(nospace \mstep)}

\integer{xmax=item(-1,\xlistval)+10}
\text{xlistval=wims(append item \xmax to \xlistval)}
\text{serie=<table class="wimsborder"><tr><th>Classe</th><th>Effectif</th></tr>}
\for{i=1 to \nbval}
 {
\text{serie=\serie
<tr><td>&#91; \xlistval[\i] ; \xlistval[\i+1] &#91; </td><td>\lsteff[\i]</td></tr>
}
}
\text{serie=\serie </table>}
%% détermination de la classe médiane
\integer{imed=-1}
\integer{effMedg=0}
\integer{effMedd=0}
\for{i=1 to \nbval}
  {
  \if{\imed=-1}
    {
    \if{\lstecc[\i]>\efftotal/2 and \imed=-1}
     {
     \integer{imed=\i}
     \integer{effMedd=\lstecc[\i]}
     \integer{effMedg=\effMedd-\lsteff[\i]}
     \integer{Medg=\xlistval[\imed]}
     \integer{Medd=\xlistval[\imed+1]}
     }
    }
   }
\real{xmed=\Medg+(\efftotal/2 - \effMedg)*(\Medd-\Medg)/(\effMedd-\effMedg)}
#if defined TARGET_mediane4
\text{mstep=wims(makelist r x for x=1 to \nbval+2)}
\text{mstep=wims(nospace \mstep)}
\steps{\mstep}
\integer{ampmed=\Medd-\Medg}
\integer{effmed=\lsteff[\imed]}
\integer{ecart=\lstecc[\imed]-\efftotal/2}
\statement{<p>
Voici le tableau des effectifs d'une série statistique regroupée par classe :
</p>
<table class="wimscenter wimsborder"><tr><th>Valeur</th>
\for{n=1 to \nbval}{
<td>&#91;\xlistval[\n];\xlistval[\n+1]&#91;</td>
}
</tr>
<tr><th>Effectif</th>
\for{n=1 to \nbval}{
  <td>\lsteff[\n]</td>
}
</tr>
<tr><th>E.C.C</th>
\for{j=3 to \nbval+2}{
  <td>\embed{reply\j,4}</td>
}
</tr></table>
<ol>
<li>Remplir la ligne des effectifs cumulés croissants (E.C.C).</li>
<li>Déterminer la classe médiane de cette série :
<div class="wimscenter"><label for="reply1">Classe médiane :</label> &#91; \embed{reply1,3}; \embed{reply2,3} &#91;</div>
</li>
</ol>
}
\answer{Classe médiane borne gauche}{\Medg}{type=numeric}
\answer{Classe médiane borne droite}{\Medd}{type=numeric}
\answer{ecc1}{\lstecc[1]}{type=numeric}
\answer{ecc2}{\lstecc[2]}{type=numeric}
\answer{ecc3}{\lstecc[3]}{type=numeric}
\answer{ecc4}{\lstecc[4]}{type=numeric}
\answer{ecc5}{\lstecc[5]}{type=numeric}
\answer{ecc6}{\lstecc[6]}{type=numeric}
\answer{ecc7}{\lstecc[7]}{type=numeric}
\answer{ecc8}{\lstecc[8]}{type=numeric}
\answer{ecc9}{\lstecc[9]}{type=numeric}
\answer{ecc10}{\lstecc[10]}{type=numeric}
\answer{ecc11}{\lstecc[11]}{type=numeric}
\answer{ecc12}{\lstecc[12]}{type=numeric}
\answer{ecc13}{\lstecc[13]}{type=numeric}
\answer{ecc14}{\lstecc[14]}{type=numeric}
\answer{ecc15}{\lstecc[15]}{type=numeric}
#endif
#if defined TARGET_mediane5
%% préparation du dessin
\text{image=
 xrange \xmin-15,\xmax+5
 yrange -20,\efftotal+5
 arrow \xmin-5,0,\xmax+5,0,10,black
 arrow \xmin-5,-5,\xmin-5,\efftotal+5,10,black
 segment \xlistval[1],0,\xlistval[2],\lstecc[1],blue
 dpolyline orange,\xmin-5,\lstecc[1],\xlistval[2],\lstecc[1],\xlistval[2],0
 text black,\xlistval[1],-13,medium,\xlistval[1]
 text black,\xlistval[2],-3,medium,\xlistval[2]
 text black,\xmin-12,\lstecc[1],medium,\lstecc[1]
}
\integer{xoff=12}
\integer{yoff=3}
\for{i=2 to \nbval}
 {
 \integer{xoff=\xoff=12?7:12}
 \integer{yoff=\yoff=3?13:3}
 \text{image=\image
 segment \xlistval[\i],\lstecc[\i-1],\xlistval[\i+1],\lstecc[\i],blue
 dpolyline orange,\xmin-5,\lstecc[\i],\xlistval[\i+1],\lstecc[\i],\xlistval[\i+1],0
 text black,\xlistval[\i+1],-\yoff,medium,\xlistval[\i+1]
 text black,\xmin-\xoff,\lstecc[\i],medium,\lstecc[\i]
 }
}
\text{image=\image
 dpolyline green,\xmin-5,\efftotal/2,\xmed,\efftotal/2,\xmed,0
}

\statement{<p>
On a représenté le polygone des effectifs cumulés croissants de la série statistique suivante :</p>
<table class="wimscenter"><tr><td>\serie
</td><td>\draw{400,400}{\image}</td></tr>
</table>
<p>Déterminer la classe médiane de cette série :</p>
<label for="reply1">Classe médiane :</label> &#91; \embed{reply1,3}; \embed{reply2,3} &#91;
<p>
Puis, en supposant une répartition uniforme de l'effectif dans chaque classe,
calculer, par interpolation linéaire, la médiane de la série :</p>
<label for="reply3">Valeur de la médiane :</label> \embed{reply3,3}
}
\answer{Classe médiane borne gauche}{\Medg}{type=numeric}
\answer{Classe médiane borne droite}{\Medd}{type=numeric}
\answer{Médiane}{\xmed}{type=numeric}
# endif
#endif


#if defined TARGET_mediane6
\text{col=Effectifs cumulés croissants}
\text{lstval=\lstecc}

\integer{xmax=item(-1,\xlistval)+10}
\text{xlistval=wims(append item \xmax to \xlistval)}
\text{serie=<table class="wimsborder"><tr><th>Classe</th><th>Effectif</th></tr>}
\for{i=1 to \nbval}{
  \text{serie=\serie
  <tr><td>&#91; \xlistval[\i] ; \xlistval[\i+1] &#91; </td><td>\lsteff[\i]</td></tr>}
}
\text{serie=\serie </table>}
%% détermination de la classe médiane
\integer{imed=-1}
\integer{effMedg=0}
\integer{effMedd=0}
\for{i=1 to \nbval}{
  \if{\imed=-1}{
    \if{\lstecc[\i]>\efftotal/2 and \imed=-1}{
      \integer{imed=\i}
      \integer{effMedd=\lstecc[\i]}
      \integer{effMedg=\effMedd-\lsteff[\i]}
      \integer{Medg=\xlistval[\imed]}
      \integer{Medd=\xlistval[\imed+1]}
    }
  }
}
\real{xmed=\Medg+(\efftotal/2 - \effMedg)*(\Medd-\Medg)/(\effMedd-\effMedg)}
\text{mstep=wims(makelist r x for x=1 to \nbval+6)}
\text{mstep=wims(nospace \mstep)}
\steps{\mstep}
\integer{ampmed=\Medd-\Medg}
\integer{effmed=\lsteff[\imed]}
\integer{ecart=\lstecc[\imed]-\efftotal/2}
\statement{<p>
Voici le tableau des effectifs d'une série statistique regroupée par classe :
</p><table class="wimscenter wimsborder"><tr><th>Valeur</th>
\for{n=1 to \nbval}{
  <td>&#91;\xlistval[\n] ; \xlistval[\n+1]&#91;</td>
}
</tr>
<tr><th>Effectif</th>
\for{n=1 to \nbval}{
  <td>\lsteff[\n]</td>
}
</tr>
<tr><th>E.C.C</th>
\for{j=7 to \nbval+6}{
 <td>\embed{reply\j,4}</td>
}
</tr></table>
<ol>
<li>Remplir la ligne des effectifs cumulés croissants (E.C.C).</li>
<li>Déterminer la classe médiane de cette série :
<div class="wimscenter"><label for="reply1">Classe médiane : </label>&#91; \embed{reply1,3}; \embed{reply2,3} &#91;</div>
</li><li>
Quels sont l'amplitude et l'effectif de cette classe :
<div class="wimscenter"><label for="reply3">Amplitude de la classe médiane :</label> \embed{reply3,4}</div>
<div class="wimscenter"><label for="reply4">Effectif de la classe médiane :</label> \embed{reply4,4}</div>
</li><li>
Quel est l'écart entre l'effectif cumulé de la classe médiane et l'effectif médian :
<div class="wimscenter"><label for="reply5">Écart :</label> \embed{reply5,4}</div>
</li><li>
Par interpolation, déterminer précisément la médiane de cette série :
<div class="wimscenter"><label for="reply6">Médiane :</label> \embed{reply6}</div>
</li>
</ol>
}
\answer{Classe médiane borne gauche}{\Medg}{type=numeric}
\answer{Classe médiane borne droite}{\Medd}{type=numeric}
\answer{Amplitude de la classe médiane}{\ampmed}{type=numeric}
\answer{Effectif de la classe mediane}{\effmed}{type=numeric}
\answer{Écart}{\ecart}{type=numeric}
\answer{Médiane}{\xmed}{type=numeric}
\answer{ecc1}{\lstecc[1]}{type=numeric}
\answer{ecc2}{\lstecc[2]}{type=numeric}
\answer{ecc3}{\lstecc[3]}{type=numeric}
\answer{ecc4}{\lstecc[4]}{type=numeric}
\answer{ecc5}{\lstecc[5]}{type=numeric}
\answer{ecc6}{\lstecc[6]}{type=numeric}
\answer{ecc7}{\lstecc[7]}{type=numeric}
\answer{ecc8}{\lstecc[8]}{type=numeric}
\answer{ecc9}{\lstecc[9]}{type=numeric}
\answer{ecc10}{\lstecc[10]}{type=numeric}
\answer{ecc11}{\lstecc[11]}{type=numeric}
\answer{ecc12}{\lstecc[12]}{type=numeric}
\answer{ecc13}{\lstecc[13]}{type=numeric}
\answer{ecc14}{\lstecc[14]}{type=numeric}
\answer{ecc15}{\lstecc[15]}{type=numeric}
\hint{Si la classe médiane est [a;b],
 notons \(ecart) l'écart entre l'effectif cumulé de la classe médiane et l'effectif médian,
 \(amp) l'amplitude de la classe médiane
et \(eff) l'effectif de cette classe.<p>
La médiane s'obtient par<br>
\(med= b- \frac{ecart}{eff}\times amp)
}
#endif
