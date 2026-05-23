target=calculd1 calculd4
\keywords{distance}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{let=shuffle(A,B,C,E,F,G)}
\text{A=\let[1]}
\text{B=\let[2]}
\text{C=\let[3]}
\real{th=random(-pi/4..7*pi/4)}
\integer{xA=0}
\integer{yA=0}
\real{xA=\th<=pi/4?-1:\xA}
\real{xA=\th>3*pi/4 and \th<5*pi/4?+0.2:\xA}
\real{yA=\th>=5*pi/4?1:\yA}
\real{yA=\th>pi/4 and \th<3*pi/4?-0.1:\yA}
\integer{xB=0}
\integer{yB=0}
\real{xB=\th<=pi/4?0.2:\xB}
\real{xB=\th>3*pi/4 and \th<5*pi/4?-1:\xB}
\real{yB=\th>=5*pi/4?-0.1:\yB}
\real{yB=\th>pi/4 and \th<3*pi/4?1:\yB}
\real{r=random(3..7)}
\real{r=rint(\r*100)/100}
\text{ch=randitem(1,2,3,4,5)}
\text{color=item(\ch,red,blue,green,purple,brown)}
\text{colorname=item(\ch,\name_color)}
\text{a=randint(3..7)}
\text{ch=shuffle(1,-1)}
\real{x1=\r*cos(\th)-\ch[1]*\a*sin(\th)}
\real{y1=\r*sin(\th)+\ch[1]*\a*cos(\th)}
\real{x2=\r*cos(\th)+\ch[1]*\a*sin(\th)}
\real{y2=\r*sin(\th)-\ch[1]*\a*cos(\th)}
\real{xmin=min(\x2,\x1)}
\real{ymin=min(\y2,\y1)}
\real{xmax=max(\x2,\x1)}
\real{ymax=max(\y2,\y1)}
\real{d=rint(sqrt((\x1)^2+(\y1)^2)*10)/10}
\integer{angle=arctan(\r/\a)/pi*180}
\real{rep=rint(\d*cos((90-\angle)/180*pi)*10)/10}
\real{min=min(\xmin,\ymin)-2}
\real{max=max(\xmax,\ymax)+2}
\real{b=0.5}

\text{enonce=\name_enonce[1] \angle \name_enonce[2] \d cm}
\text{enonce=wims(replace internal AAAA by \A in \enonce)}
\text{enonce=wims(replace internal BBBB by \B in \enonce)}
\text{enonce=wims(replace internal CCCC by \C in \enonce)}

\text{question=wims(replace internal AAAA by \A in \name_question)}
#if defined TARGET_calculd1
 \text{dessin=fpoly grey,\r*cos(\th),\r*sin(\th),\r*cos(\th)+\b*sin(\th),\r*sin(\th)-\b*cos(\th),(\r-\b)*cos(\th)+\b*sin(\th),(\r-\b)*sin(\th)-\b*cos(\th),(\r-\b)*cos(\th),(\r-\b)*sin(\th)
linewidth=2
dsegment 0,0,\r*cos(\th),\r*sin(\th),black}
#endif
#if defined TARGET_calculd4
 \text{dessin=linewidth=2}
#endif

\text{dessin=range \min,\max,\min,\max
fcircle 0,0,5,black
text black,\xA,\yA,medium,\A
text black,\x1+\xB,\y1+\yB,medium,\B
text black,\x2+\xB,\y2+\yB,medium,\C
segment 0,0,\x1,\y1,black
\dessin
line \r*cos(\th)+20*sin(\th),\r*sin(\th)-20*cos(\th),\r*cos(\th)-20*sin(\th),\r*sin(\th)+20*cos(\th),\color
fcircle \x2,\y2,5,black}

\text{image=draw(300,300
\dessin)}

\statement{
<div class="float_left"><img src="\image" alt=""></div>
<div class="float_left">\enonce.
   \question \colorname&nbsp;?</div>
   <div class="clearall">
   <b>\name_answer:</b> \embed{r1,5} cm.
   </div>
   <div class="wims_instruction">
   \name_inst
   </div>
}

\answer{}{\rep}{type=numexp}
