target=frecum1,frecum2,frecum3,frecum4
#define TITRE Fréquences cumulées
#include "author.inc"

\integer{nb=randint(4..5)}
\text{fre=slib(generator \nb,100)}

#if #TARGET(frecum1)
 \title{TITRE 1}
 \text{donnees=wims(randrecord src/stat2.don)}
 \integer{eff=randint(2..5)*100}
 \text{tmp=row(2,\donnees)}
 \integer{min=1}
 \integer{max=\min+\nb}
 \text{enonce=row(4,\donnees)}
 \text{nameclass=row(5,\donnees)}
 \text{question=Calculer les fréquences cumulées croissantes.}
 \text{et=wims(values v for v=\min to \max)}
 \integer{type=1}
 \text{nametype0=Effectifs}
 \text{E=}
 \for{i=1 to \nb}{
  \integer{tmp=\fre[\i]*\eff/100}
  \text{E=wims(append item \tmp to \E)}
 }
 \text{Eaff=\E}
 \integer{supertype=0}
#endif
#if #TARGET(frecum2)
 \title{TITRE 2}
 \text{donnees=wims(randrecord src/stat3.don)}
 \text{tmp=row(1,\donnees)}
 \integer{eff=randint(\tmp[1]..\tmp[2])}
 \integer{int=row(4,\donnees)}
 \text{tmp=row(2,\donnees)}
 \integer{min=randint(\tmp[1]..\tmp[2])*\int}
 \integer{max=\min+\nb*\int}
 \text{enonce=row(5,\donnees)}
 \text{nameclass=row(6,\donnees)}
 \text{name=row(7,\donnees)}
 \text{question=Calculer les fréquences cumulées décroissantes.}
 \text{et=}
 \for{i=1 to \nb}{
  \integer{em=\min+(\i-1)*\int}
  \integer{eM=\min+\i*\int}
  \text{et=wims(append item \(\em \leq \name < \eM) to \et)}
 }
 \integer{type=2}
 \text{E=}
 \for{i=1 to \nb}{
  \integer{tmp=\fre[\i]*\eff/100}
  \text{E=wims(append item \tmp to \E)}
 }
 \text{Eaff=\E}
 \text{nametype0=Effectifs}
 \integer{supertype=1}
#endif

#if #TARGET(frecum3)
 \title{TITRE 3}
 \text{donnees=wims(randrecord src/stat3.don)}
 \text{tmp=row(1,\donnees)}
 \integer{eff=100}
 \integer{int=row(4,\donnees)}
 \text{tmp=row(2,\donnees)}
 \integer{min=randint(\tmp[1]..\tmp[2])*\int}
 \integer{max=\min+\nb*\int}
 \text{enonce=row(5,\donnees)}
 \text{nameclass=row(6,\donnees)}
 \text{name=row(7,\donnees)}
 \text{question=Calculer les fréquences cumulées croissantes.}
 \text{et=}
 \for{i=1 to \nb}{
  \integer{em=\min+(\i-1)*\int}
  \integer{eM=\min+\i*\int}
  \text{et=wims(append item \(\em \leq \name < \eM) to \et)}
 }
 \integer{type=1}
 \text{E=\fre}
 \text{Eaff=wims(replace internal , by %, in \fre)%}
 \text{nametype0=Fréquences}
 \integer{supertype=1}
#endif
#if #TARGET(frecum4)
 \title{TITRE 4}
 \text{donnees=wims(randrecord src/stat2.don)}
 \integer{eff=randint(2..5)*100}
 \integer{eff=100}
 \text{tmp=row(2,\donnees)}
 \integer{min=1}
 \integer{max=\min+\nb}
 \text{enonce=row(4,\donnees)}
 \text{nameclass=row(5,\donnees)}
 \text{question=Calculer les fréquences cumulées décroissantes.}
 \text{et=wims(values v for v=\min to \max)}
 \integer{type=2}
 \text{nametype0=fréquences}
 \text{E=\fre}
 \text{Eaff=wims(replace internal , by %, in \fre)%}
 \integer{supertype=0}
#endif
\text{nametype=item(\type,Fréquences cumulées croissantes,Fréquences cumulées décroissantes)}

\integer{to=\type=1?0:\eff}
\text{sg=\type=1?+:-}
\integer{res=\to/\eff*100}
\for{k=1 to \nb}{
 \integer{to=\to\sg\E[\k]}
 \integer{tmp=\to/\eff*100}
 \text{res=\res,\tmp}
}
\text{res=\type=1?item(2 to -1,\res)}

\text{r=item(1 to \nb,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10)}
\steps{\r}

\statement{
\enonce<br>
<p>\question </p>
  <table class="wimscenter wimsborder">
   <tr>
    <th>\nameclass</th>
    \for{l=1 to \nb}{<td>\et[\l]</td>}
   </tr><tr>
    <th>\nametype0</th>
    \for{l=1 to \nb}{<td>\Eaff[\l]</td>}
   </tr><tr>
    <th>\nametype</th>
    \for{l=1 to \nb}{<td>\embed{\r[\l],5} %</td>}
   </tr>
  </table>
}

\answer{1}{\res[1]}{type=numexp}
\answer{2}{\res[2]}{type=numexp}
\answer{3}{\res[3]}{type=numexp}
\answer{4}{\res[4]}{type=numexp}
\answer{5}{\res[5]}{type=numexp}
\answer{6}{\res[6]}{type=numexp}
\answer{7}{\res[7]}{type=numexp}
\answer{8}{\res[8]}{type=numexp}
\answer{9}{\res[9]}{type=numexp}
\answer{10}{\res[10]}{type=numexp}
