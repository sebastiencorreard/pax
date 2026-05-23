target=perpendiculaire1 perpendiculaire2 perpendiculaire3 perpendiculaire4 perpendiculaire5

\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100000}
#include "lang_titles.inc"
#include "lang.inc"
\text{lettres=shuffle(A,B,C,D,E,F,G,H,J,K,L,M,N)}
text{lettres=A,B,C,D,E,F,G,H,J,K,L,M,N}
\text{A=\lettres[1]}
\text{B=\lettres[2]}
\text{C=\lettres[3]}
\text{D=\lettres[4]}
\text{E=\lettres[5]}
\text{F=\lettres[6]}
\text{G=\lettres[7]}
\text{H=\lettres[8]}
#if defined TARGET_perpendiculaire1
 \integer{h=random(300..400)}
 \integer{l=\h}
 \integer{p=\h/2}
 \integer{x=\p+\l}
 \integer{y=\p+\h}
 \text{enonce=\A\B\C\D\E\F\G\H \name_enonce}
 \text{list1=shuffle(\((\A\B)\perp(\B\C)\),\((\A\B)\perp(\A\D)\),\((\G\H)\perp(\F\G)\),\((\E\H)\perp(\H\G)\))}
 \text{list2=shuffle(\((\A\D)\perp(\D\H)\),\((\A\E)\perp(\E\H)\),\((\G\C)\perp(\B\C)\),\((\D\A)\perp(\D\C)\))}
 \text{list3=shuffle(\((\A\B)\perp(\B\H)),\((\A\H)\perp(\H\D)),\((\A\D)\perp(\B\D)),\((\F\G)\perp(\G\A)\))}
 \text{choix=randrow(2,2,2
1,2,3
2,1,3
1,1,4
3,1,2
1,3,2)}
 \text{list=item(1 to \choix[1],\list1),item(1 to \choix[2],\list2),item(1 to \choix[3],\list3)}
 \text{good=wims(values v for v=1 to \choix[1]+\choix[2])}
#endif
#if defined TARGET_perpendiculaire2
\text{name_enonce=\name_enonce}
 \integer{h=random(300..400)}
 \integer{l=\h}
 \integer{p=\h/2}
 \integer{x=\p+\l}
 \integer{y=\p+\h}
 \text{enonce=\A\B\C\D\E\F\G\H \name_enonce}
 \text{list1=shuffle(\((\A\B)\perp(\B\C)\),\((\A\B)\perp(\A\D)\),\((\G\H)\perp(\F\G)\),\((\E\H)\perp(\H\G)\))}
 \text{list2=shuffle(\((\A\H)\perp(\E\D)\),\((\D\G)\perp(\C\H)\),\((\B\D)\perp(\A\C)\),\((\A\F)\perp(\B\E)\))}
 \text{list3=shuffle(\((\A\B)\perp(\B\H)\),\((\A\H)\perp(\H\D)\),\((\A\D)\perp(\B\D)\),\((\F\G)\perp(\G\A)\))}
 \text{choix=randrow(2,2,2
1,2,3
2,1,3
1,1,4
3,1,2
1,3,2)}
 \text{list=item(1 to \choix[1],\list1),item(1 to \choix[2],\list2),item(1 to \choix[3],\list3)}
 \text{good=wims(values v for v=1 to \choix[1]+\choix[2])}
#endif
#if defined TARGET_perpendiculaire3
 \integer{h=random(300..400)}
 \integer{l=random(100..200)}
 \integer{p=random(200..300)}
 \integer{x=\p+\l}
 \integer{y=\p+\h}
 \text{enonce=\A\B\C\D\E\F\G\H \name_enonce}
 \text{list1=shuffle(\((\A\B)\perp(\B\C)\),\((\A\B)\perp(\A\D)\),\((\G\H)\perp(\F\G)\),\((\E\H)\perp(\H\G)\))}
 \text{list2=shuffle(\((\A\B)\perp(\B\G)\),\((\D\C)\perp(\F\C)\),\((\B\F)\perp(\F\H)\),\((\A\F)\perp(\F\G)\))}
 \text{list3=shuffle(\((\A\B)\perp(\B\H)\),\((\A\H)\perp(\H\D)\),\((\A\C)\perp(\B\D)\),\((\D\G)\perp(\C\H)\))}
 \text{choix=randrow(2,2,2
1,2,3
2,1,3
1,1,4
3,1,2
1,3,2)}
 \text{list=item(1 to \choix[1],\list1),item(1 to \choix[2],\list2),item(1 to \choix[3],\list3)}
 \text{good=wims(values v for v=1 to \choix[1]+\choix[2])}
#endif

#if defined TARGET_perpendiculaire4
 \integer{h=random(300..400)}
 \integer{l=random(100..200)}
 \integer{p=random(200..300)}
 \integer{x=\p+\l}
 \integer{y=\p+\h}
 \text{enonce=A\B\C\D\E\F\G\H \name_enonce}
 \text{list1=shuffle(\((\A\B)\perp(\B\C)\),\((\A\B)\perp(\A\D)\),\((\G\H)\perp(\F\G)\),\((\E\H)\perp(\H\G)\))}
 \text{list2=shuffle(\((\A\B)\perp(\C\G)\),\((\D\C)\perp(\A\E)\),\((\B\F)\perp(\G\H)\),\((\A\F)\perp(\E\H)\))}
 \text{list3=shuffle(\((\A\B)\perp(\C\E)\),\((\A\H)\perp(\C\G)\),\((\A\C)\perp(\E\G)\),\((\D\G)\perp(\B\F)\))}
 \text{choix=randrow(2,2,2
1,2,3
2,1,3
1,1,4
3,1,2
1,3,2)}
 \text{list=item(1 to \choix[1],\list1),item(1 to \choix[2],\list2),item(1 to \choix[3],\list3)}
 \text{good=wims(values v for v=1 to \choix[1]+\choix[2])}
#endif
#if defined TARGET_perpendiculaire1 || defined TARGET_perpendiculaire2 || defined TARGET_perpendiculaire3 || defined TARGET_perpendiculaire4
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
#if defined TARGET_perpendiculaire5
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
 \text{list1=shuffle(\((SO)\perp(\A\C)\),\((SO)\perp(\B\D)\),\((\A\C)\perp(\B\D)\),\((\B\A)\perp(\A\D)\))}
 \text{list2=shuffle(\((SO)\perp(\A\D)\),\((SO)\perp(\A\B)\),\((SO)\perp(\B\C)\),\((SO)\perp(\C\D)\))}
 \text{list3=shuffle(\((S\A)\perp(\A\D)\),\((S\C)\perp(\D\C)\),\((S\A)\perp(S\B)\),\((S\B)\perp(\B\C)\))}
 \text{choix=randrow(2,2,2
1,2,3
2,1,3
1,1,4)}
 \text{list=item(1 to \choix[1],\list1),item(1 to \choix[2],\list2),item(1 to \choix[3],\list3)}
 \text{good=wims(values v for v=1 to \choix[1]+\choix[2])}
#endif

\integer{nblist=items(\list)}
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
