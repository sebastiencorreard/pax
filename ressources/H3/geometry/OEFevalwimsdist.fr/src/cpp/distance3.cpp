target=distance3 distance5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{A=randitem(A,B,C,E,F,G)}
\real{th=random(0..2*pi)}
\integer{xA=\th<3*pi/2 and \th>pi/2?+1:-1}
\integer{yA=\th<pi?+1:-1}
\real{r=random(3..7)}
\real{r=rint(\r*100)/100}
\text{ch=shuffle(1,2,3,4,5)}
\text{color=wims(item \ch of red,blue,green,purple,brown)}
\text{colorname=wims(item \ch of \name_color)}
#if defined TARGET_distance3
\text{cntv=5}
#endif
#if defined TARGET_distance5
\text{cntv=6}
#endif
\integer{cntv1=\cntv-1}
\text{a=wims(values 2*v for v=1 to \cntv)}
\text{a=shuffle(\a)}
\text{a=item(1 to \cntv1,\a)}
#if defined TARGET_distance3
\text{a=shuffle(\a,0)}
#endif

\real{xmin=0}
\real{ymin=0}
\real{xmax=0}
\real{ymax=0}
\text{dessin=fcircle 0,0,5,black
text black,\xA,0,medium,\A}
\text{longueur=<ul>}
\integer{rep=1000}
#if defined TARGET_distance5
\integer{rep2=0}
#endif
\for{k=1 to 5}{
 \integer{ch=randitem(1,-1)}
 \real{x=\r*cos(\th)-\ch*\a[\k]*sin(\th)}
 \real{y=\r*sin(\th)+\ch*\a[\k]*cos(\th)}
 \real{xmin=min(\xmin,\x)}
 \real{ymin=min(\ymin,\y)}
 \real{xmax=max(\xmax,\x)}
 \real{ymax=max(\ymax,\y)}
 \real{d=rint(sqrt((\x)^2+(\y)^2)*100)/100}
 \real{rep=min(\rep,\d)}
#if defined TARGET_distance5
 \real{rep2=max(\rep2,\d)}
#endif
 \text{longueur=\longueur<li>\name_segment <span style="color:\color[\k]">\colorname[\k]</span> : \d cm.</li>}
 \text{dessin=\dessin
segments \color[\k],0,0,\x,\y}
}
\text{longueur=\longueur</ul>}
\real{min=min(\xmin,\ymin)-2}
\real{max=max(\xmax,\ymax)+2}
\real{b=0.5}
\text{fpoly=}
#if defined TARGET_distance3
\text{fpoly=fpoly grey,\r*cos(\th),\r*sin(\th),\r*cos(\th)+\b*sin(\th),\r*sin(\th)-\b*cos(\th),(\r-\b)*cos(\th)+\b*sin(\th),(\r-\b)*sin(\th)-\b*cos(\th),(\r-\b)*cos(\th),(\r-\b)*sin(\th)}
#endif
\text{dessin=range \min,\max,\min,\max
\dessin
\fpoly
linewidth 2
line \r*cos(\th)+20*sin(\th),\r*sin(\th)-20*cos(\th),\r*cos(\th)-20*sin(\th),\r*sin(\th)+20*cos(\th),black}
\text{image=draw(300,300
\dessin)}
\text{name=slib(lang/fname fr,boy)}

#if defined TARGET_distance5
\text{good=1}
\text{bad=\name_bad[1] \rep,
  \name_bad[2] \rep,
  \name_bad[3] \rep,
  \name_bad[1] \rep2,
  \name_bad[3] \rep2,
  \name_bad[2] \rep2}
#endif
\text{question=wims(replace internal AAAA by \A in \name_question)}
\statement{
<div class="grid-x grid-margin-x">
  <div class="cell small-12 medium-6 large-6">
\name \name_enonce:
\longueur
  <div class="wims_question">\question?</div>
  </div>
  <div class="cell small-12 medium-6 large-6">
  <div class="wimscenter"><img src="\image" alt=""></div>
  </div>
</div>
<br class="clearall">
#if defined TARGET_distance3
  <b>\name_answer:</b> \embed{r1,5} cm.
#endif
#if defined TARGET_distance5
  <ul>
  \for{l=1 to 6}{<li>\embed{r1,\l}</li>}
</ul>
#endif
}


#if defined TARGET_distance3
\answer{}{\rep}{type=numexp}
#endif
#if defined TARGET_distance5
\answer{}{\good;\bad}{type=radio}{option=shuffle}
#endif
