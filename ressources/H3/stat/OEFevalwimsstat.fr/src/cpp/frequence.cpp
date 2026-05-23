target=frequence1,frequence2,frequence3,frequence4
#define TITRE Fréquences
#include "author.inc"

#if #TARGET(frequence1)
 \title{TITRE 1}
 \integer{ch=randitem(1,3)}
 \text{donnees=wims(record \ch of src/stat2.don)}
 \text{tmp=row(1,\donnees)}
 \integer{eff=randint(2..5)*100}
 \integer{min=1}
 \integer{max=4}
 \text{enonce=row(4,\donnees)}
 \text{nameclass=row(5,\donnees)}
 \text{et=wims(values v for v=\min to \max)}
 \integer{nb=\max-\min+1}
 \text{compenonce=L'effectif total de la série statistiques est de \eff.<br>}
#endif
#if #TARGET(frequence2)
 \title{TITRE 2}
 \text{donnees=wims(randrecord src/stat3.don)}
 \text{tmp=row(1,\donnees)}
 \integer{eff=randint(2..5)*100}
 \integer{int=row(4,\donnees)}
 \text{tmp=row(2,\donnees)}
 \integer{min=randint(\tmp[1]..\tmp[2])*\int}
 \integer{max=\min+4*\int}
 \text{enonce=row(5,\donnees)}
 \text{nameclass=row(6,\donnees)}
 \text{name=row(7,\donnees)}
 \text{et=wims(values v for v=\min to \max)}
 \integer{nb=4}
 \text{compenonce=L'effectif total de la série statistiques est de \eff.<br>}
 \text{et=}
 \for{i=1 to \nb}{
  \integer{em=\min+(\i-1)*\int}
  \integer{eM=\min+\i*\int}
  \text{et=wims(append item \(\em \leq \name < \eM) to \et)}
 }
#endif

#if #TARGET(frequence3)
 \title{TITRE 3}
 \integer{ch=randitem(1,3)}
 \text{donnees=wims(record \ch of src/stat2.don)}
 \text{tmp=row(1,\donnees)}
 \integer{eff=randint(2..5)*100}
 \integer{min=1}
 \integer{max=4}
 \text{enonce=row(4,\donnees)}
 \text{nameclass=row(5,\donnees)}
 \text{et=wims(values v for v=\min to \max)}
 \integer{nb=\max-\min+1}
 \text{compenonce=}
#endif

#if #TARGET(frequence4)
 \title{TITRE 4}
 \text{donnees=wims(randrecord src/stat3.don)}
 \text{tmp=row(1,\donnees)}
 \integer{eff=randint(2..5)*100}
 \integer{int=row(4,\donnees)}
 \text{tmp=row(2,\donnees)}
 \integer{min=randint(\tmp[1]..\tmp[2])*\int}
 \integer{max=\min+4*\int}
 \text{enonce=row(5,\donnees)}
 \text{nameclass=row(6,\donnees)}
 \text{name=row(7,\donnees)}
 \text{et=wims(values v for v=\min to \max)}
 \integer{nb=4}
 \text{compenonce=}
 \text{et=}
 \for{i=1 to \nb}{
  \integer{em=\min+(\i-1)*\int}
  \integer{eM=\min+\i*\int}
  \text{et=wims(append item \(\em \leq \name < \eM) to \et)}
 }
#endif


\text{res=slib(generator \nb,100)}
\text{E=}
\for{i=1 to \nb}{
 \integer{tmp=\res[\i]*\eff/100}
 \text{E=wims(append item \tmp to \E)}
}
\text{r=r1,r2,r3,r4}


\statement{
\enonce.<br>
\compenonce
<p>Calculer les fréquences.</p>
  <table class="wimscenter wimsborder">
   <tr>
    <th>\nameclass</th>
    \for{l=1 to \nb}{<td>\et[\l]</td>}
   </tr><tr>
    <th>Effectifs</th>
    \for{l=1 to \nb}{<td>\E[\l]</td>}
   </tr><tr>
    <th>Fréquences</th>
    \for{l=1 to \nb}{<td>\embed{\r[\l],5}%</td>}
   </tr>
  </table>
}

\answer{1}{\res[1]}{type=numexp}
\answer{2}{\res[2]}{type=numexp}
\answer{3}{\res[3]}{type=numexp}
\answer{4}{\res[4]}{type=numexp}
