target=calcul1,calcul2,calcul3,calcul4,calcul5

\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Calcul
#if defined TARGET_calcul1
 \title{TITRE 1}
 \text{form=randitem(cos(x),sin(x),tan(x))}
 \text{tform=texmath(\form)}
#endif

#if defined TARGET_calcul2
 \title{TITRE 2}
 \text{v=randint(2..9)}
 \integer{ch=randint(1..3)}
 \text{ft=item(\ch,cos,tan,sin)}
 \text{aft=item(\ch,\cos,\tan,\sin)}
 \text{form=\v/\ft(x)}
 \text{tform=\frac{\v}{\aft(x)}}
#endif

#if defined TARGET_calcul3
 \title{TITRE 3}
 \text{v=wims(values v for v=2 to 9)}
 \text{v=shuffle(\v)}
 \integer{ch=randint(1..3)}
 \text{ft=item(\ch,cos,tan,sin)}
 \text{aft=item(\ch,\cos,\tan,\sin)}
 \text{form=\v[1]*\ft(x)/\v[2]}
 \text{tform=\frac{\v[1]\aft(x)}{\v[2]}}
#endif

#if defined TARGET_calcul4
 \title{TITRE 4}
 \text{v=randint(2..9)}
 \integer{ch=randint(1..3)}
 \text{ft=item(\ch,cos,tan,sin)}
 \text{aft=item(\ch,\cos,\tan,\sin)}
 \text{form=\ft(x)*\v}
 \text{tform=\aft(x)\times\v}
#endif

#if defined TARGET_calcul5
 \title{TITRE 5}
 \text{v=wims(values v for v=2 to 9)}
 \text{v=shuffle(\v)}
 \integer{ch=randint(1..3)}
 \text{ft=item(\ch,cos,tan,sin)}
 \text{aft=item(\ch,\cos,\tan,\sin)}
 \text{form=\v[1]/\v[2]/\ft(x)}
 \text{tform=\frac{\frac{\v[1]}{\v[2]}}{\aft(x)}}
#endif

\text{angle=randint(5..85)}
\text{affform=wims(replace internal x by \angle^\circ in \tform)}
\text{A=randitem(A,B,C,D,E,F,G,H)}
\integer{ch=randint(1..3)}
\text{arr=item(\ch,au dixième,au centième,au millième)}
\real{rep=evalue(\form,x=\angle*pi/180)}
\real{rep=rint(\rep*10^\ch)/10^\ch}

\statement{
  Utiliser votre calculatrice et donner l'arrondi \arr de :
<div class="wimscenter">
 <label for="reply1">\(\A = \affform = )</label>\embed{r1,6}
</div>}

\answer{\A}{\rep}{type=numexp}
