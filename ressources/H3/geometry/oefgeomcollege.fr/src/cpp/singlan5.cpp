target=singlan5

\author{Gaëlle, Singlan}
\email{gaelle.singlan@orange.fr}
#include "author.inc"
#include "lang_singlan5.inc"

\title{TITLE}
\title_en{TITLE_en}
\computeanswer{no}
\range{-5..5}
\precision{10000}

\text{L=shuffle(A,B,C,D,E,F,G,I,J,K,L,M,N,O,P,K,R,S,T,U,V,W,X,Y,Z)}
\integer{b=randint(80..200)}
\integer{c1=randint(25..(\b-5))}
\real{c2=rint(sqrt((\b-\c1)*(\c1-20))+20)}
\real{c3=rint(random(50..180))}
\real{c3= \c2=\c3? \c3+5}
\real{d1=(\b-20)/10}

\integer{n=randitem(1,2)}

\if{\n=1}{
  \text{dess=draw(\b+20,\c2+20
    triangle 20,20,\b,20,\c1,\c2,black
    text black,10,10,medium,\L[1]
    text black,\b+10,10,medium,\L[2]
    text black,\c1,\c2+5,medium,\L[3]
    )}
  \real{d2=rint(sqrt((\c1-20)^2+(\c2-20)^2))/10}
  \real{d3=rint(sqrt((\b-\c1)^2+(\c2-20)^2))/10}

  \text{rep1=\name_instruction[13;1]}
  \text{rep2=\(\frac{\L[1]\L[3] \times \L[2]\L[3]}{2})}
  \text{liste=\rep2,\(\frac{\L[1]\L[3] \times \L[1]\L[2]}{2}),\(\L[1]\L[2] \times \L[1]\L[3] \times \L[2]\L[3]),\(\frac{\L[1]\L[2] \times \L[2]\L[3]}{2}),\(\L[1]\L[3] \times \L[2]\L[3]),\(\L[1]\L[3] \times \L[1]\L[2]),\(\L[1]\L[2] \times \L[2]\L[3])}
  \text{rep3=rint(((\d2*\d3)/2)*100)/100}

}{
   \text{dess=draw(\b+20,\c3+20
     triangle 20,20,\b,20,\c1,\c3,black
     text black,10,10,medium,\L[1]
     text black,\b+10,10,medium,\L[2]
     text black,\c1,\c3+5,medium,\L[3]
    )}
   \text{dessuite=draw(\b+20,\c3+20
     triangle 20,20,\b,20,\c1,\c3,black
     text black,10,10,medium,\L[1]
     text black,\b+10,10,medium,\L[2]
     text black,\c1,\c3+5,medium,\L[3]
     segment \c1,20,\c1,\c3,brown
     square \c1,20,5,brown
     text brown,\c1,5,medium,H
    )}
   \real{d2=rint(sqrt((\c1-20)^2+(\c3-20)^2))/10}
   \real{d3=rint(sqrt((\b-\c1)^2+(\c3-20)^2))/10}
   \real{h1=(\c3-20)/10}
   \real{h2=(\c1-20)/10}
   \real{h3=(\b-\c1)/10}

  \text{rep1=\name_instruction[13;2]}
  \text{rep2=\(\frac{H\L[3] \times \L[1]\L[2]}{2})}
  \text{liste=\rep2,\(\frac{H\L[2] \times \L[1]\L[3]}{2}),\(H\L[2] \times H\L[3] \times H\L[1]),\(\frac{H\L[1] \times \L[2]\L[3]}{2})}
  \text{rep3=rint(((\d1*\h1)/2)*100)/100}
}
\text{t1=\L[1]\L[2] = \d1 cm}
\text{t2=\L[1]\L[3] = \d2 cm}
\text{t3=\L[2]\L[3] = \d3 cm}
\text{T=shuffle(\t1,\t2,\t3)}

\text{l1=\L[3]H = \h1 cm}
\text{l2=\L[1]H = \h2 cm}
\text{l3=H\L[2] = \h3 cm}
\text{H=shuffle(\l1,\l2,\l3)}

\steps{c1
r1,r2}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
\if{\n=1}{
<img src="\dess" alt=""></div>
 <div class="medium_size text_col">

 \if{\step=1}{
\name_instruction[1;] \L[1]\L[2]\L[3],
\name_instruction[2;]: \T[1], \T[2] et \T[3].
<br>
<div class="wims_instruction">\name_instruction[3;] \L[3]. </div>
<br>
\name_instruction[4;] \L[1]\L[2]\L[3] \name_instruction[5;]? \embed{c1}
 }{
    \name_instruction[1;] \L[1]\L[2]\L[3],
    \name_instruction[2;] : \T[1], \T[2] et \T[3].
 <div class="wims_instruction">\name_instruction[3;] \L[3]. </div>
  <div> \name_instruction[6;] \L[1]\L[2]\L[3] ?</div>
 <div class="wimscenter">\embed{r1}</div>
  <br>\name_instruction[7;] \L[1]\L[2]\L[3] \name_instruction[8;] \embed{r2} cm².
  <div class="wims_instruction">\name_instruction[9;]</div>
 }
}{
 \if{\step=1}{
  <img src="\dess" alt=""></div>
  <div class="medium_size text_col">
  \name_instruction[1;] \L[1]\L[2]\L[3], \name_instruction[2;] : \T[1], \T[2] et \T[3].
   <div class="wims_instruction">\name_instruction[10;]</div>
  <div> \name_instruction[4;] \L[1]\L[2]\L[3] \name_instruction[5;] ? \embed{c1}
    </div>
 }{
 <img src="\dessuite" alt=""></div>
 <div class="medium_size text_col">
  \name_instruction[1;] \L[1]\L[2]\L[3], \name_instruction[2;] : \T[1], \T[2] et \T[3].
  <div class="wims_instruction">\name_instruction[10;]</div>
  <br> \name_instruction[11;] \L[3].
  <br> \name_instruction[12;] : \H[1], \H[2] et \H[3].
  <br> \name_instruction[6;] \L[1]\L[2]\L[3] ? \embed{r1}
  <br> <label for="reply3">\name_instruction[7;] \L[1]\L[2]\L[3] \name_instruction[8;]</label> \embed{r2} cm².
  <div class="wims_instruction">\name_instruction[9;]</div>
   }
  }
</div></div>
}

\choice{}{\rep1}{\name_instruction[13;]}{options=shuffle}
\answer{}{1;\liste}{type=checkbox}{options=shuffle}
\answer{}{\rep3}{type=numeric}
