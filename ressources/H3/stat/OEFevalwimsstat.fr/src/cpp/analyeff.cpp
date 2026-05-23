target=analyeff1,analyeff2,analyeff3,analyeff4,analyeff5
#define TITRE Interprétation des effectifs
#include "author.inc"

#if #TARGET(analyeff1)
 \title{TITRE 1}
 \text{donnees=wims(randrecord src/stat2.don)}
 \text{tmp=row(1,\donnees)}
 \integer{eff=randint(\tmp[1]..\tmp[2])}
 \text{tmp=row(2,\donnees)}
 \integer{min=randint(\tmp[1]..\tmp[2])}
 \text{tmp=row(3,\donnees)}
 \integer{max=randint(\tmp[1]..\tmp[2])}
 \text{enonce=row(4,\donnees)}
 \text{nameclass=row(5,\donnees)}
 \text{question=row(6,\donnees)}
 \text{et=wims(values v for v=\min to \max)}
 \integer{nb=\max-\min+1}
 \integer{supertype=0}
 \text{valstep=r1}
#endif
#if #TARGET(analyeff2)
 \title{TITRE 2}
 \text{donnees=wims(randrecord src/stat2.don)}
 \text{tmp=row(1,\donnees)}
 \integer{eff=randint(\tmp[1]..\tmp[2])}
 \text{tmp=row(2,\donnees)}
 \integer{min=randint(\tmp[1]..\tmp[2])}
 \text{tmp=row(3,\donnees)}
 \integer{max=randint(\tmp[1]..\tmp[2])}
 \text{enonce=row(4,\donnees)}
 \text{nameclass=row(5,\donnees)}
 \text{question=row(7,\donnees)}
 \text{et=wims(values v for v=\min to \max)}
 \integer{nb=\max-\min+1}
 \integer{supertype=0}
 \text{valstep=r2}
#endif

#if #TARGET(analyeff3)
 \title{TITRE 3}
 \text{donnees=wims(randrecord src/stat2.don)}
 \text{tmp=row(1,\donnees)}
 \integer{eff=randint(\tmp[1]..\tmp[2])}
 \text{tmp=row(2,\donnees)}
 \integer{min=randint(\tmp[1]..\tmp[2])}
 \text{tmp=row(3,\donnees)}
 \integer{max=randint(\tmp[1]..\tmp[2])}
 \text{enonce=row(4,\donnees)}
 \text{nameclass=row(5,\donnees)}
 \text{question=row(8,\donnees)}
 \text{et=wims(values v for v=\min to \max)}
 \integer{nb=\max-\min+1}
 \integer{supertype=0}
 \text{valstep=r3}
#endif

#if #TARGET(analyeff4)
 \title{TITRE 4}
 \text{donnees=wims(randrecord src/stat3.don)}
 \text{tmp=row(1,\donnees)}
 \integer{eff=randint(\tmp[1]..\tmp[2])}
 \integer{int=row(4,\donnees)}
 \text{tmp=row(2,\donnees)}
 \integer{min=randint(\tmp[1]..\tmp[2])*\int}
 \text{tmp=row(3,\donnees)}
 \integer{max=randint(\tmp[1]..\tmp[2])*\int}
 \text{enonce=row(5,\donnees)}
 \text{nameclass=row(6,\donnees)}
 \text{name=row(7,\donnees)}
 \text{question=row(9,\donnees)}
 \integer{nb=(\max-\min+1)/\int}
 \text{et=}
 \for{i=1 to \nb}{
  \integer{em=\min+(\i-1)*\int}
  \integer{eM=\min+\i*\int}
  \text{et=wims(append item \(\em \leq \name < \eM) to \et)}
 }
 \integer{supertype=1}
 \text{valstep=r2}
#endif

#if #TARGET(analyeff5)
 \title{TITRE 5}
 \text{donnees=wims(randrecord src/stat3.don)}
 \text{tmp=row(1,\donnees)}
 \integer{eff=randint(\tmp[1]..\tmp[2])}
 \integer{int=row(4,\donnees)}
 \text{tmp=row(2,\donnees)}
 \integer{min=randint(\tmp[1]..\tmp[2])*\int}
 \text{tmp=row(3,\donnees)}
 \integer{max=randint(\tmp[1]..\tmp[2])*\int}
 \text{enonce=row(5,\donnees)}
 \text{nameclass=row(6,\donnees)}
 \text{name=row(7,\donnees)}
 \text{question=row(10,\donnees)}
 \integer{nb=(\max-\min+1)/\int}
 \text{et=}
 \for{i=1 to \nb}{
  \integer{em=\min+(\i-1)*\int}
  \integer{eM=\min+\i*\int}
  \text{et=wims(append item \(\em \leq \name < \eM) to \et)}
 }
 \integer{supertype=1}
 \text{valstep=r3}
#endif

\text{E=slib(generator \nb,\eff)}
\integer{toc=0}
\integer{tod=\eff}
\text{crois=\toc}
\text{decrois=\tod}
\for{k=1 to \nb}{
 \integer{toc=\toc+\E[\k]}
 \integer{tod=\tod-\E[\k]}
 \text{crois=\crois,\toc}
 \text{decrois=\decrois,\tod}
}
\text{crois=item(2 to -1,\crois)}
\integer{ch=randint(2..\nb)}
\if{\supertype=0}{
 \integer{ch=\et[\ch]=1?\ch+1}
 \text{question=wims(replace internal NNNN by \et[\ch] in \question)}
}{
 \integer{borne=r2 isin \valstep?\min+\ch*\int:\min+(\ch-1)*\int}
 \text{question=wims(replace internal NNNN by \borne in \question)}
}
\steps{\valstep}

\statement{
\enonce.
<p>\question ?</p>
  <table class="wimscenter wimsborder">
   <tr>
    <th>\nameclass</th>
    \for{l=1 to \nb}{<td>\et[\l]</td>}
   </tr><tr>
    <th>Effectifs</th>
    \for{l=1 to \nb}{<td>\E[\l]</td>}
   </tr><tr>
    <th>Effectifs cumulés croissants</th>
    \for{l=1 to \nb}{<td>\crois[\l]</td>}
   </tr><tr>
    <th>Effectifs cumulés décroissants</th>
    \for{l=1 to \nb}{<td>\decrois[\l]</td>}
   </tr>
  </table>
}

\answer{Réponse}{\E[\ch]}{type=numexp}
\answer{Réponse}{\crois[\ch]}{type=numexp}
\answer{Réponse}{\decrois[\ch]}{type=numexp}
