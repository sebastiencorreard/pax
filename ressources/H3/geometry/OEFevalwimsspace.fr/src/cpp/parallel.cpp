target=parallel1 parallel2 parallel3 parallel4 parallel5
#include "author.inc"
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100000}
#include "lang_titles.inc"
#include "lang.inc"

\text{lettres=shuffle(A,B,C,D,E,F,G,H,J,K,L,M,N)}
\text{A=\lettres[1]}
\text{B=\lettres[2]}
\text{C=\lettres[3]}
\text{D=\lettres[4]}
\text{E=\lettres[5]}
\text{F=\lettres[6]}
\text{G=\lettres[7]}
\text{H=\lettres[8]}

#if defined TARGET_parallel1
 \integer{h=random(300..400)}
 \integer{l=\h}
 \integer{p=\h/2}
 \integer{x=\p+\l}
 \integer{y=\p+\h}
 \text{enonce=\A\B\C\D\E\F\G\H \name_enonce}
 \text{list1=shuffle((\A\B)//(\D\C),(\A\E)//(\D\H),(\B\F)//(\C\G),(\E\F)//(\H\G),(\E\H)//(\A\D))}
 \text{list2=shuffle((\A\B)//(\E\H),(\A\C)//(\C\D),(\A\D)//(\D\G),(\D\G)//(\B\D))}
#endif
#if defined TARGET_parallel2
  \integer{h=random(300..400)}
 \integer{l=random(100..200)}
 \integer{p=random(200..300)}
 \integer{x=\p+\l}
 \integer{y=\p+\h}
 \text{enonce=\A\B\C\D\E\F\G\H \name_enonce}
 \text{list1=shuffle((\A\B)//(\H\G),(\A\E)//(\C\G),(\B\F)//(\D\H),(\E\F)//(\D\C),(\A\B)//(\H\G),(\D\C)//(\E\D))}
 \text{list2=shuffle((\A\B)//(\E\H),(\A\C)//(\C\D),(\A\D)//(\D\G),(\D\G)//(\B\D))}
#endif
#if defined TARGET_parallel3
 \integer{h=random(300..400)}
 \integer{l=\h}
 \integer{p=\h/2}
 \integer{x=\p+\l}
 \integer{y=\p+\h}
 \text{enonce=\A\B\C\D\E\F\G\H \name_enonce}
 \text{list1=shuffle((\A\B)//(\D\C),(\A\E)//(\D\H),(\B\F)//(\C\G),(\E\F)//(\H\G),(\E\H)//(\A\D))}
 \text{list2=shuffle((\A\B)//(\C\G),(\A\C)//(\D\H),(\A\D)//(\B\F),(\D\G)//(\A\C))}
#endif
#if defined TARGET_parallel4
 \integer{h=random(300..400)}
 \integer{l=random(100..200)}
 \integer{p=random(200..300)}
 \integer{x=\p+\l}
 \integer{y=\p+\h}
 \text{enonce=\A\B\C\D\E\F\G\H \name_enonce}
 \text{list1=shuffle((\A\B)//(\H\G),(\A\E)//(\C\G),(\B\F)//(\D\H),(\E\F)//(\D\C),(\A\B)//(\H\G),(\D\C)//(\E\D))}
 \text{list2=shuffle((\A\B)//(\C\G),(\A\C)//(\D\H),(\A\D)//(\B\F),(\D\G)//(\A\C))}
#endif
#if defined TARGET_parallel1  || defined TARGET_parallel2  || defined TARGET_parallel3  || defined TARGET_parallel4
 \real{e=0.6}
 \text{dessin=segment 20,20+\e*\p,20,(\h+\p)*\e+20,black
segment 20,(\h+\p)*\e+20,20+\l*\e,(\h+\p)*\e+20,black
segment 20+\l*\e,(\h+\p)*\e+20,20+\l*\e,20+\e*\p,black
segment 20+\l*\e,20+\e*\p,20,20+\e*\p,black
segment 20,20+\e*\p,20+\e*\p,20,black
dsegment 20,(\h+\p)*\e+20,20+\e*\p,20+\h*\e,black
segment 20+\l*\e,(\p+\h)*\e+20,(\l+\p)*\e+20,20+\h*\e,black
segment 20+\l*\e,20+\e*\p,(\l+\p)*\e+20,20,black
segment 20+\e*\p,20,(\p+\l)*\e+20,20,black
dsegment 20+\e*\p,20+\h*\e,(\l+\p)*\e+20,20+\h*\e,black
dsegment 20+\e*\p,20,20+\e*\p,20+\h*\e,black
segment (\l+\p)*\e+20,20,(\l+\p)*\e+20,20+\h*\e,black
text black,10,10+\p*\e,medium,\A
text black,10+\p*\e,10,medium,\B
text black,30+(\p+\l)*\e,10,medium,\C
text black,30+\l*\e,10+\p*\e,medium,\D
text black,10,10+(\p+\h)*\e,medium,\E
text black,10+\p*\e,10+\h*\e,medium,\F
text black,30+(\p+\l)*\e,10+\h*\e,medium,\G
text black,30+\l*\e,10+(\p+\h)*\e,medium,\H}
#endif
#if defined TARGET_parallel5
\integer{h=random(300..400)}
\integer{l=\h}
\integer{p=\h/2+10}
\integer{x=\p+\l}
\integer{y=\p+\h}

\real{e=0.6}
\integer{ox=20+\e*(\p+\l)/2}
\integer{oy=20+\e*\p/2}
\text{dessin=segment 20,(\h+\p)*\e+20,20+\l*\e,(\h+\p)*\e+20,black
segment 20+\l*\e,(\h+\p)*\e+20,20+\e*(\p+\l),20+\h*\e,black
dsegment 20+\e*(\p+\l),20+\h*\e,(\p)*\e+20,20+\h*\e,black
dsegment (\p)*\e+20,20+\h*\e,20,(\h+\p)*\e+20,black
segment \ox,\oy,20,20+\e*(\h+\p),black
segment \ox,\oy,20+\l*\e,20+\e*(\h+\p),black
segment \ox,\oy,20+(\l+\p)*\e,20+\e*(\h),black
dsegment \ox,\oy,20+(\p)*\e,20+\e*\h,black
dsegment 20,(\h+\p)*\e+20,20+\e*(\p+\l),20+\h*\e,green
dsegment (\p)*\e+20,20+\h*\e,20+\l*\e,(\h+\p)*\e+20,green
text black,\ox-3,\oy-15,medium,S
text black,\ox-5,\oy+\h*\e+10,medium,O
text black,10,10+(\p+\h)*\e,medium,\A
text black,10+\p*\e,10+\h*\e,medium,\B
text black,30+(\p+\l)*\e,10+\h*\e,medium,\C
text black,30+\l*\e,10+(\p+\h)*\e,medium,\D}
 \text{enonce=S\A\B\C\D \name_enonce}
 \text{list1=shuffle((\A\B)//(\D\C),(\A\D)//(\B\C),(\B\A)//(\C\D),(\D\A)//(\C\B))}
 \text{list2=shuffle((SO)//(\A\D),(\A\C)//(\D\B),(\A\B)//(\D\A),(S\A)//(\B\C))}
#endif
\integer{nbgood=randint(1..3)}
\integer{nblist=5}
\text{list=item(1 to \nbgood,\list1),item(1 to \nblist-\nbgood,\list2)}
\text{good=wims(values v for v=1 to \nbgood)}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{40+\e*\x,40+\e*\y}{\dessin}</div>
 <div class="medium_size text_col">
\enonce
\name_question?
<ul>
 \for{k=1 to \nblist}{<li>\embed{r1,\k}</li>}
</ul>
 </div>
</div>
}

\answer{}{\good;\list}{type=checkbox}{options=split shuffle}
