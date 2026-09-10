target=oefrecpatron1

#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\text{coul=black,white}
\integer{dim=80}

\matrix{pats=6,1,2,3,6,10,14,1
5,1,2,3,6,10,2
5,2,5,6,7,10,2
6,1,2,6,7,11,12,1
6,2,5,6,10,11,14,1
6,1,2,6,10,11,15,1
6,6,9,10,11,12,14,1
6,1,2,6,9,10,11,2
7,2,6,9,10,11,12,14,2
6,1,2,6,10,14,15,1
5,5,6,10,11,15,2
6,5,6,10,14,15,16,2
6,3,7,8,10,11,14,1
6,2,5,6,7,11,12,1
6,6,7,9,10,11,12,2
6,2,5,6,7,8,11,1
6,5,6,7,8,10,14,2
7,1,2,3,4,8,12,16,2
6,2,3,6,7,10,11,2
6,2,6,10,13,14,15,1}

\integer{ch=randint(1..20)}
\text{pat=row(\ch,\pats)}
\text{coord=}
\for{i=2 to \pat[1]+1}{
  \integer{v=floor((\pat[\i]-1)/4)}
  \integer{x=50+(\pat[\i]-4*\v-1)*\dim}
  \integer{y=40+\v*\dim}
  \text{coord=wims(append item \x to \coord)}
  \text{coord=wims(append item \y to \coord)}
}
\if{\pat[1]=5}{\integer{dim1=0}   \integer{dim2=0}}
\if{\pat[1]=6}{\integer{dim1=80}   \integer{dim2=0}}
\if{\pat[1]=7}{\integer{dim1=80}   \integer{dim2=80}}
\text{rep=\pat[\pat[1]+2]}

\text{patron=draw(420,400
square \coord[1],\coord[2],\dim,\coul[1]
square \coord[3],\coord[4],\dim,\coul[1]
square \coord[5],\coord[6],\dim,\coul[1]
square \coord[7],\coord[8],\dim,\coul[1]
square \coord[9],\coord[10],\dim,\coul[1]
square \coord[11],\coord[12],\dim1,\coul[1]
square \coord[13],\coord[14],\dim2,\coul[1]
)}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\patron" alt=""></div>
 <div class="medium_size text_col">
\name_enonce: \embed{r1}
</div></div>}
\answer{}{\rep;\name_choix}{type=menu}
