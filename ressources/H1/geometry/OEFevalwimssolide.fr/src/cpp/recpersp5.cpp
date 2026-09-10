target=oefrecpersp5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{pa=0}
\integer{pb=4}
\integer{x=12}
\integer{y=2}
\integer{z=8}

\text{l=segment,dsegment}
\matrix{t=2,1,2,1,1,1,1,1,2,1,1,1,1
2,1,1,2,1,1,1,1,1,1,2,1,2
1,2,1,2,1,1,1,1,1,1,1,2,2
1,1,1,1,1,2,1,2,1,1,1,2,1
1,1,1,1,2,1,2,1,2,1,1,1,2
1,1,1,1,1,2,2,1,1,2,1,1,2
2,1,1,1,2,1,1,1,2,1,1,1,2
1,1,2,1,1,1,1,1,2,1,1,1,2
}

\integer{ang=random(0,90)}
\integer{c=randint(1..8)}
\text{t=row(\c,\t)}
\text{pave=draw(200,200
xrange -10,10
yrange -10,10
rotate \ang
\l[\t[1]] \pa-\x/2+\y,\pb-\y,\pa+\x/2+\y,\pb-\y,black
\l[\t[2]] \pa-\x/2-\y,\pb+\y,\pa+\x/2-\y,\pb+\y,black
\l[\t[3]] \pa-\x/2-\y,\pb+\y,\pa-\x/2+\y,\pb-\y,black
\l[\t[4]] \pa+\x/2-\y,\pb+\y,\pa+\x/2+\y,\pb-\y,black

\l[\t[5]] \pa-\x/2+\y,\pb-\y-\z,\pa+\x/2+\y,\pb-\y-\z,black
\l[\t[6]] \pa-\x/2-\y,\pb+\y-\z,\pa+\x/2-\y,\pb+\y-\z,black
\l[\t[7]] \pa-\x/2-\y,\pb+\y-\z,\pa-\x/2+\y,\pb-\y-\z,black
\l[\t[8]] \pa+\x/2-\y,\pb+\y-\z,\pa+\x/2+\y,\pb-\y-\z,black

\l[\t[9]] \pa-\x/2+\y,\pb-\y,\pa-\x/2+\y,\pb-\y-\z,black
\l[\t[10]] \pa-\x/2-\y,\pb+\y,\pa-\x/2-\y,\pb+\y-\z,black
\l[\t[11]] \pa+\x/2+\y,\pb-\y,\pa+\x/2+\y,\pb-\y-\z,black
\l[\t[12]] \pa+\x/2-\y,\pb+\y,\pa+\x/2-\y,\pb+\y-\z,black
)}

\text{form=<img src="\pave" alt="">}
\statement{<div class="wims_columns">
 <div class="medium_size img_col">\form
 </div><div class="medium_size text_col">
  \name_enonce1:
  \name_enonce2:
<div class="wimscenter">
\embed{r1,\size}
</div>
</div></div>

}
\answer{}{\t[13];\list}{type=radio}
