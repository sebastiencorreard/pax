target=oefrecpersp4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\text{size=150x150x200}

\integer{pb=120}
\integer{x=80}
\integer{y=10}
\integer{z=40}

\text{pyrcar=draw(200,200
dsegment 100-\x/2+\x/4,\pb-\x/4,100+\x/2+\x/4,\pb-\x/4,black
segment 100-\x/2-\x/4,\pb+\x/4,100+\x/2-\x/4,\pb+\x/4,black
dsegment 100-\x/2-\x/4,\pb+\x/4,100-\x/2+\x/4,\pb-\x/4,black
segment 100+\x/2-\x/4,\pb+\x/4,100+\x/2+\x/4,\pb-\x/4,black

dsegment 100-\x/2+\x/4,\pb-\x/4,100,\pb-\x/4-\x,black
segment 100-\x/2-\x/4,\pb+\x/4,100,\pb-\x/4-\x,black
segment 100+\x/2+\x/4,\pb-\x/4,100,\pb-\x/4-\x,black
segment 100+\x/2-\x/4,\pb+\x/4,100,\pb-\x/4-\x,black
)}
\text{cube=draw(200,200
dsegment 100-\x/2+\x/4,\pb-\x/4,100+\x/2+\x/4,\pb-\x/4,black
segment 100-\x/2-\x/4,\pb+\x/4,100+\x/2-\x/4,\pb+\x/4,black
dsegment 100-\x/2-\x/4,\pb+\x/4,100-\x/2+\x/4,\pb-\x/4,black
segment 100+\x/2-\x/4,\pb+\x/4,100+\x/2+\x/4,\pb-\x/4,black

segment 100-\x/2+\x/4,\pb-\x/4-\x,100+\x/2+\x/4,\pb-\x/4-\x,black
segment 100-\x/2-\x/4,\pb+\x/4-\x,100+\x/2-\x/4,\pb+\x/4-\x,black
segment 100-\x/2-\x/4,\pb+\x/4-\x,100-\x/2+\x/4,\pb-\x/4-\x,black
segment 100+\x/2-\x/4,\pb+\x/4-\x,100+\x/2+\x/4,\pb-\x/4-\x,black

dsegment 100-\x/2+\x/4,\pb-\x/4,100-\x/2+\x/4,\pb-\x/4-\x,black
segment 100-\x/2-\x/4,\pb+\x/4,100-\x/2-\x/4,\pb+\x/4-\x,black
segment 100+\x/2+\x/4,\pb-\x/4,100+\x/2+\x/4,\pb-\x/4-\x,black
segment 100+\x/2-\x/4,\pb+\x/4,100+\x/2-\x/4,\pb+\x/4-\x,black

)}

\text{cone=draw(200,200
ellipse 100,\pb+\y,\x,2*\y,black
segment 100-\x/2,\pb+\y,100,\pb-\y-\z,black
segment 100+\x/2,\pb+\y,100,\pb-\y-\z,black

)}

\text{cyl=draw(200,200
ellipse 100,\pb+\y,\x,2*\y,black
ellipse 100,\pb-\y-\z,\x,2*\y,black
segment 100-\x/2,\pb+\y,100-\x/2,\pb-\y-\z,black
segment 100+\x/2,\pb+\y,100+\x/2,\pb-\y-\z,black

)}

\text{pyrtri=draw(200,200
dsegment 100-\x/2-\y,\pb+\y,100+\y,\pb-\y,black
dsegment 100+\x/2-\y,\pb+\y,100+\y,\pb-\y,black
segment 100-\x/2-\y,\pb+\y,100+\x/2-\y,\pb+\y,black

segment 100-\x/2-\y,\pb+\y,100,\pb+\y-2*\z,black
segment 100+\x/2-\y,\pb+\y,100,\pb+\y-2*\z,black
dsegment 100+\y,\pb-\y,100,\pb+\y-2*\z,black

)}

\text{pave=draw(200,200
dsegment 100-\x/2+\y,\pb-\y,100+\x/2+\y,\pb-\y,black
segment 100-\x/2-\y,\pb+\y,100+\x/2-\y,\pb+\y,black
dsegment 100-\x/2-\y,\pb+\y,100-\x/2+\y,\pb-\y,black
segment 100+\x/2-\y,\pb+\y,100+\x/2+\y,\pb-\y,black

segment 100-\x/2+\y,\pb-\y-\z,100+\x/2+\y,\pb-\y-\z,black
segment 100-\x/2-\y,\pb+\y-\z,100+\x/2-\y,\pb+\y-\z,black
segment 100-\x/2-\y,\pb+\y-\z,100-\x/2+\y,\pb-\y-\z,black
segment 100+\x/2-\y,\pb+\y-\z,100+\x/2+\y,\pb-\y-\z,black

dsegment 100-\x/2+\y,\pb-\y,100-\x/2+\y,\pb-\y-\z,black
segment 100-\x/2-\y,\pb+\y,100-\x/2-\y,\pb+\y-\z,black
segment 100+\x/2+\y,\pb-\y,100+\x/2+\y,\pb-\y-\z,black
segment 100+\x/2-\y,\pb+\y,100+\x/2-\y,\pb+\y-\z,black

)}

\text{pyrrect=draw(200,200
dsegment 100-\x/2+\y,\pb-\y,100+\x/2+\y,\pb-\y,black
segment 100-\x/2-\y,\pb+\y,100+\x/2-\y,\pb+\y,black
dsegment 100-\x/2-\y,\pb+\y,100-\x/2+\y,\pb-\y,black
segment 100+\x/2-\y,\pb+\y,100+\x/2+\y,\pb-\y,black

dsegment 100-\x/2+\y,\pb-\y,100,\pb-2*\z,black
segment 100-\x/2-\y,\pb+\y,100,\pb-2*\z,black
segment 100+\x/2+\y,\pb-\y,100,\pb-2*\z,black
segment 100+\x/2-\y,\pb+\y,100,\pb-2*\z,black

)}

\text{prismetri=draw(200,200
dsegment 100-\x/2-\y,\pb+\y,100+\y,\pb-\y,black
dsegment 100+\x/2-\y,\pb+\y,100+\y,\pb-\y,black
segment 100-\x/2-\y,\pb+\y,100+\x/2-\y,\pb+\y,black

segment 100-\x/2-\y,\pb+\y-\z,100+\x/2-\y,\pb+\y-\z,black
segment 100+\x/2-\y,\pb+\y-\z,100+\y,\pb-\y-\z,black
segment 100-\x/2-\y,\pb+\y-\z,100+\y,\pb-\y-\z,black

segment 100-\x/2-\y,\pb+\y,100-\x/2-\y,\pb+\y-\z,black
segment 100+\x/2-\y,\pb+\y,100+\x/2-\y,\pb+\y-\z,black
dsegment 100+\y,\pb-\y,100+\y,\pb-\y-\z,black

)}

\text{form=<img src="\pyrcar" alt="">,
<img src="\cone" alt="">,
<img src="\cyl" alt="">,
<img src="\pyrtri" alt="">,
<img src="\pyrrect" alt="">,
<img src="\prismetri" alt="">}
\text{form=shuffle(\form)}


\statement{\name_enonce:
<div class="wimscenter">
\embed{r1,\size}
</div>
}
\answer{}{<img src="\pave" alt="">,<img src="\cube" alt="">,\form[1],\form[2];\rv[1],\rv[1],\rv[2],\rv[2]}{type=correspond}
