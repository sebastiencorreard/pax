target=amstutz4

\author{Jérome, Amstutz}
\email{jeromeamstutz@yahoo.fr}

#include "author.inc"
#include "lang_color.inc"

\text{ce=black,grey,green,blue}

\text{num=shuffle(4)}
\text{ce=item(\num,\ce)}
\text{cf=item(\num,\cf)}


\text{size=200}
\text{r=25} rayon des arc de cercle
\integer{a=randint(10..50)*randitem(-1,1)}
\integer{a1=randitem(-1,1)}
\text{p=randitem(0,1)}
\text{b=150}

\real{ag=180*atan((\a-(\a1/2))/(1+(\a*\a1/2)))/acos(-1)}
#include "lang_amstutz4.inc"
\title{TITLE}
\title_en{TITLE_en}

\if{\p=0}{

 \if{\a1>0}{
 \text{x5=-50}
 \real{y5=-25+\size/2}
 \real{x6=\size}
 \real{y6=\size}
 }
 {
 \text{x5=-50}
 \text{y5=125}
 \text{x6=\size}
 \text{y6=0}
 }
\text{e=\name_instruction1 ?}
 \text{bp=\name_prop[1]}
 \text{mp=\name_prop[2],\name_prop[3],\name_prop[4]}
\if{\a>0}
{
 \text{x1=-50}
 \real{y1=\a*\x1}
 \text{x2=\size}
 \text{y2=simplify(\a*\x2)}
 \text{x3=-50}
 \real{y3=\a*\x3+\a*-\b}
 \text{x4=\size}
 \real{y4=\a*\x4+\a*-\b}
 \real{xi=(\size)/(2*\a-\a1)}
 \real{yi=\a*\xi}
 \real{xi1=(\size+2*\a*\b)/(2*\a-\a1)}
 \real{yi1=(\a*\xi1)+(\a*-\b)}
}
{
 \text{x1=-50}
 \real{y1=(\a*\x1)+\size}
 \text{x2=\size}
 \text{y2=simplify(\a*\x2+\size)}
 \text{x3=-50}
 \real{y3=\a*\x3+\a*-\b}
 \text{x4=\size}
 \real{y4=\a*\x4+\a*-\b}
 \real{xi=\size/(\a1-2*\a)}
 \real{yi=\a*\xi+\size}
 \real{xi1=((-\size)-2*\a*\b)/(\a1-2*\a)}
 \real{yi1=\a*\xi1+(\a*-\b)}



}}
{\integer{a2=randint(100..1000)/100}
\integer{a3=randint(-1000..-100)/100}
\integer{a4=randint(-99..-10)/100}
\text{b2=randint(10..150)}
\text{b3=randint(151..200)}
\text{b4=randint(151..200)}
\text{x1=-50}
\real{y1=\a2*\x1+\b2}
\text{x2=\size}
\text{y2=simplify((\a2*\x2)+\b2)}
\text{x3=-50}
\real{y3=(\a3*\x3)+\b3}
\text{x4=\size}
\text{y4=simplify((\a3*\x4)+\b3)}
\text{x5=-50}
\real{y5=(\a4*\x5)+\b4}
\text{x6=\size}
\text{y6=simplify((\a4*\x6)+\b4)}
\real{xi=-100}
\real{yi=-100}
\real{xi1=-100}
\real{yi1=-100}

\text{e=\name_instruction2}
\text{mp=\name_prop[1],\name_prop[2],\name_prop[3]}
\text{bp=\name_prop[4]}}

\if{\ag>0}{

\real{angle=180*atan(\a1/2)/(acos(-1))}
\real{angle1=\angle+\ag}
}
{
\real{angle=180*atan(\a1/2)/(acos(-1))}
\real{angle=360+\angle}
\real{angle1=180*atan(-\a)/acos(-1)}
\real{angle1=abs(\angle1)}
}

\text{droites=
segment \x1,\y1,\x2,\y2,\ce[1]
segment \x3,\y3,\x4,\y4,\ce[2]
segment \x5,\y5,\x6,\y6,\ce[3]
arc \xi,\yi,\r,\r,\angle,\angle1,red
arc \xi1,\yi1,\r,\r,\angle,\angle1,red

}

\text{dessin=draw(\size,\size
range -50,\size,0,\size
linewidth 2
\droites)}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\dessin" alt=""></div>
 <div class="medium_size text_col">
\e ?
</div></div>
}

\choice{}{\bp}{\mp}
