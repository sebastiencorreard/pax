target=etendue4 etendue5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{donnees=wims(randrecord src/stat2.don)}
\integer{eff=randint(20..40)}
\integer{nb=randint(4..8)}
\text{enonce=row(4,\donnees)}
\text{nameclass=row(5,\donnees)}
\text{E=slib(generator \nb,\eff)}
#if defined TARGET_etendue4
\integer{min=randint(0..3)}
 \text{ddessin=}
 \for{k=0 to \nb-1}{
  \text{ddessin=wims(append item \min+\k,\E[\k+1] to \ddessin)}
 }
\text{dessin=slib(lgbrisee \nameclass,\name_head[1],\ddessin)}
\integer{sol=\nb-1}
#endif
#if defined TARGET_etendue5
\integer{min=randint(1..3)}
\text{ddessin=\min,\E[1]}
\integer{\max=\min}
\for{k=2 to \nb}{
  \integer{max=\max+randint(1..2)}
  \text{ddessin=wims(append item \max,\E[\k] to \ddessin)}
}
\text{dessin=slib(baton \nameclass,\name_head[1],\ddessin)}
\integer{sol=\max-\min}
#endif
\text{grdon=draw(300,300
\dessin)}
\text{grdon=<img src="\grdon" alt="">}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\grdon</div>
 <div class="medium_size text_col">
 \enonce<br>
\name_enonce
 </div>
</div>
}
\answer{\name_answer}{\sol}{type=auto}
