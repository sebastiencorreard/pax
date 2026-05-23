target=lecture2,lecture3
#define TITRE Tableau d'effectifs
#include "author.inc"

\text{donnees=wims(randrecord src/stat.don)}
\text{tmp=row(1,\donnees)}
\integer{eff=randint(\tmp[1]..\tmp[2])}
\text{tmp=row(2,\donnees)}
\integer{nb=randint(\tmp[1]..\tmp[2])}
\text{enonce=row(3,\donnees)}
\text{nameclass=row(4,\donnees)}
\text{borne=row(5,\donnees)}
\text{E=slib(generator \nb,\eff)}

#if #TARGET(lecture2)
 \title{TITRE 2}
 \text{type=Utiliser le graphique pour compléter le tableau ci-dessous}
 \text{ddessin=}
 \for{k=0 to \nb-1}{
  \text{ddessin=wims(append item \k,\E[\k+1] to \ddessin)}
 }
 \text{dessin=slib(lgbrisee \nameclass,Effectifs,\ddessin)}
 \text{grdon=draw(300,300
\dessin)}
 \text{grdon=<img src="\grdon" alt="">}
#endif
#if #TARGET(lecture3)
 \title{TITRE 3}
 \text{type=Utiliser le graphique pour compléter le tableau ci-dessous}
 \text{ddessin=}
 \for{k=0 to \nb-1}{
  \text{ddessin=wims(append item \k,\E[\k+1] to \ddessin)}
 }
 \text{dessin=slib(baton \nameclass,Effectifs,\ddessin)}
 \text{grdon=draw(300,300
\dessin)}
 \text{grdon=<img src="\grdon" alt="">}
#endif

\text{r=item(1 to \nb,r1,r2,r3,r4,r5,r6,r7,r8)}
\steps{\r}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\grdon</div>
 <div class="medium_size text_col">
\enonce
<p>\type.</p>
  <table class="wimscenter wimsnorder">
   <tr>
    <th>\nameclass</th>
    \for{l=0 to \nb-1}{<td>\l</td>}
   </tr><tr>
    <th>Effectifs</th>
    \for{l=1 to \nb}{<td>\embed{\r[\l],5}</td>}
   </tr>
  </table>
   </div>
</div>
}

\answer{Effectif 1}{\E[1]}{type=numexp}
\answer{Effectif 2}{\E[2]}{type=numexp}
\answer{Effectif 3}{\E[3]}{type=numexp}
\answer{Effectif 4}{\E[4]}{type=numexp}
\answer{Effectif 5}{\E[5]}{type=numexp}
\answer{Effectif 6}{\E[6]}{type=numexp}
\answer{Effectif 7}{\E[7]}{type=numexp}
\answer{Effectif 8}{\E[8]}{type=numexp}
