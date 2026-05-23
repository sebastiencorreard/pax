target=drcadran
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\rational{p=random(randint(1..3)*random(1,-1),1/randint(1..3)*random(1,-1))}
\integer{a= randint(1..3)*random(1,-1)}
\rational{b=\p*(\a)}
\text{d=simplify((\p)*x)}
\text{d_tex=texmath(\d)}
\text{choix=I,II,III,IV}

\text{\rep= \b>0 and \a>0? item(1,\choix)}
\text{\rep= \b>0 and \a<0? item(2,\choix)}
\text{\rep= \b<0 and \a<0? item(3,\choix)}
\text{\rep= \b<0 and \a>0? item(4,\choix)}
\statement{\name_enonce
<p class="wimscenter">\(x \mapsto \d_tex\). </p>
\name_enonce2 \a.
\name_question:
<div class="wimscenter"> \draw{200,200}{xrange -8.2,8.2
yrange -8.2,8.2
parallel -8,-8,8,-8,0,1,20, grey
parallel -8,-8,-8,8,1,0,20, grey
hline 0,0,black
arrow 0,0,1,0,8, black
arrow 0,0,0,1,8, black
vline 0,0,black
text black, 5,7,medium,(I)
 text black,-7,7,medium,(II)
 text black,-7,-5,medium,(III)
 text black,5,-5,medium,(IV)
}
</div>}
\choice{\name_answer}{\rep}{\choix}
\hint{\name_hint:
<div class="wimscenter"> \draw{200,200}{xrange -8.2,8.2
yrange -8.2,8.2
parallel -8,-8,8,-8,0,1,20, grey
parallel -8,-8,-8,8,1,0,20, grey
hline 0,0,black
arrow 0,0,1,0,8, black
arrow 0,0,0,1,8, black
vline 0,0,black
text black, 5,7,medium,(I)
 text black,-7,7,medium,(II)
 text black,-7,-5,medium,(III)
 text black,5,-5,medium,(IV)
 plot red , \p*x
}
</div>}
\feedback{1=1}{
<div class="wimscenter"> \draw{200,200}{xrange -8.2,8.2
yrange -8.2,8.2
parallel -8,-8,8,-8,0,1,20, grey
parallel -8,-8,-8,8,1,0,20, grey
hline 0,0,black
arrow 0,0,1,0,8, black
arrow 0,0,0,1,8, black
vline 0,0,black
ttext black, 5,7,medium,(I)
 text black,-7,7,medium,(II)
 text black,-7,-5,medium,(III)
 text black,5,-5,medium,(IV)
 disk \a,\b,7,blue
 text black,\a,\b,medium,A
 plot red, \p*x
}
</div>}
