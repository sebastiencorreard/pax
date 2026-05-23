target=bloch2

\author{Gwennaëlle, Bloch}
\email{gwennlbl@gmail.com}
#include "author.inc"

\range{-5..5}
\precision{10000}

\integer{a=randint(3..12)*18}
\integer{b=randint(5..10)*18}
\integer{x=randint(3..(\b/18-1))*18}

\integer{t1=(\x-20)/18}
\integer{t2=(\a-20)/18}
\integer{t3=(\b-20)/18}
\text{image=draw(\b+20,\a+20
segment 20,20,\x,20,black
segment 20,20,20,\a,black
segment 20,\a,\b,\a,black
segment \x,20,\b,\a,black
text red,(\x+20)/2,5,medium,x
text black,6,(\a+20)/2,medium,\t2
text black,(\b+20)/2,\a+5,medium,\t3

)}

\text{c=simplify(\t2/2)}
\text{d=simplify((\t2*\t3)/2)}
\real{e=((\t1+\t3)/2)*\t2}


#include "lang_bloch2.inc"
\title{TITLE}
\title_en{TITLE_en}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\image" alt=""></div>
 <div class="medium_size text_col">
\instruction1
<p>
\instruction2
</p>
<div class="wimscenter">\(A\)=\embed{r1}</div>
<p>
\instruction3
</p>
<div class="wimscenter">\(x\)=\embed{r2}</div>
</div></div>
}

\answer{}{\c*x+\d}{type=litexp}
\answer{}{\t1}{type=numexp}
