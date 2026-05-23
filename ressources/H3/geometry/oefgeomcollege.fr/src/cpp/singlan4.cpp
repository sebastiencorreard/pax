target=singlan4

\author{Gaëlle, Singlan}
\email{gaelle.singlan@orange.fr}
#include "author.inc"
\computeanswer{no}
\range{-5..5}
\precision{10000}
#include "lang_singlan4.inc"

\title{TITLE}
\title_en{TITLE_en}

\text{L=shuffle(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)}
\text{m=shuffle(\L[1],\L[2],\L[3])}
\text{p=position(\m[1],\L)}
\text{q=position(\m[3],\L)}
\integer{size=200}
\integer{a=randint(30..170)}
\integer{b=randint(20..150)}

\text{dess=
  triangle 20,180,\a,\b,180,180,black
  text black,10,180,medium,\L[1]
  text black,190,180,medium,\L[2]
  text black,\a,\b-15,medium,\L[3]
  fcircle 100,180,5,blue
  fcircle (\a+20)/2,(180+\b)/2,5,blue
  fcircle (\a+180)/2,(180+\b)/2,5,blue
  text blue,100,185,medium,\L[3]'
  text blue,(\a+20)/2-15,(180+\b)/2-10,medium,\L[2]'
  text blue,(\a+180)/2+10,(180+\b)/2-10,medium,\L[1]'
}

\text{droite=randitem(\name_prop[1;])}
\if{\droite issametext \name_prop[1;1]}{
 \text{de=\name_prop[3;] \m[1]}
 \text{rep1=\m[1],\m[1]',\m[2],\m[3],\m[2]',\m[3]'}
 \text{l1=1,2}
 text{rep2=(\m[2]\m[3])}
 text{rep3=\name_prop[2;]}
 \text{l2=3}
 \text{dessin=draw(\size,\size
    \dess
    )}
 \if{\p=1}{
  \text{dessrep=draw(\size,\size
    \dess
    segment 5,180-15*(\b-180)/(\a+140),\a/2+120,180+(\a/2+100)*(\b-180)/(\a+140),red
    circle (180+(180+\a)/2)/2,(180+(180+\b)/2)/2,10,brown
    circle (\a+(180+\a)/2)/2,(\b+(180+\b)/2)/2,10,brown
    )}
 }{
  \if{\p=2}{
    \text{dessrep=draw(\size,\size
      \dess
      segment \a/2-5,90+\b/2-15*(\b-180)/(\a-340),195,180+15*(\b-180)/(\a-340),red
      circle (\a+(20+\a)/2)/2,(\b+(180+\b)/2)/2,10,brown
      circle (20+(20+\a)/2)/2,(180+(180+\b)/2)/2,10,brown
      )}
  }{
    \text{dessrep=draw(\size,\size
      \dess
      segment (100-\a)*(\b-200)/(180-\b)+100,\b-20,100+15*(100-\a)/(180-\b),195,red
      circle (180+100)/2,180,10,brown
      circle (100+20)/2,180,10,brown
      )}
  }
 }

 }{
  \if{\droite issametext \name_prop[1;2]}{
    \text{de=de [\m[1]\m[2]]}
    \text{rep1=\m[3]',\m[1],\m[1]',\m[2],\m[3],\m[2]'}
    \text{l1=1}
    text{rep2=(\m[1]\m[2])}
    text{rep3=\name_prop[2;]}
    \text{l2=1,4}
    \text{dessin=draw(\size,\size
      \dess
      )}

     \if{\q=1}{
         \text{dessrep=draw(\size,\size
            \dess
            segment 180,-180*(180-\a)/(180-\b)+(180+\b)/2+(180^2-\a^2)/(2*(180-\b)),10,-10*(180-\a)/(180-\b)+(180+\b)/2+(180^2-\a^2)/(2*(180-\b)),red
            circle (180+(180+\a)/2)/2,(180+(180+\b)/2)/2,10,brown
            circle (\a+(180+\a)/2)/2,(\b+(180+\b)/2)/2,10,brown
          )}
    }{
     \if{\q=2}{
        \text{dessrep=draw(\size,\size
           \dess
           segment 180,-180*(20-\a)/(180-\b)+(180+\b)/2+(20^2-\a^2)/(2*(180-\b)),10,-10*(20-\a)/(180-\b)+(180+\b)/2+(20^2-\a^2)/(2*(180-\b)),red
           circle (\a+(20+\a)/2)/2,(\b+(180+\b)/2)/2,10,brown
           circle (20+(20+\a)/2)/2,(180+(180+\b)/2)/2,10,brown
          )}
     }{
       \text{dessrep=draw(\size,\size
          \dess
          segment 100,\b-10,100,195,red
          circle (180+100)/2,180,10,brown
          circle (100+20)/2,180,10,brown
          square 100,175,5,brown
          )}
     }
   }

    }{
    \text{de=\name_prop[3;] \m[1]}
    \text{rep1=\m[1],\m[3]',\m[1]',\m[2],\m[3],\m[2]'}
    \text{l1=1}
    text{rep2=(\m[2]\m[3])}
    text{rep3=\name_prop[2;]}
    \text{l2=6}
    \text{dessin=draw(\size,\size
      \dess
      )}

\if{\p=1}{
 \text{dessrep=draw(\size,\size
   \dess
    segment 180,-180*(180-\a)/(180-\b)+180+20*(180-\a)/(180-\b),10,-10*(180-\a)/(180-\b)+180+20*(180-\a)/(180-\b),red
  )}
}{\if{\p=2}{
 \text{dessrep=draw(\size,\size
    \dess
    segment 180,-180*(20-\a)/(180-\b)+180+180*(20-\a)/(180-\b),10,-10*(20-\a)/(180-\b)+180+180*(20-\a)/(180-\b),red
  )}
}{
 \text{dessrep=draw(\size,\size
    \dess
    segment \a,\b-30,\a,195,red
    square \a,175,5,brown
  )
}
}
}
  }
}

\text{choix=\name_prop[12;] [\m[1]\m[2]] \name_prop[13;],\name_prop[12;] [\m[1]\m[3]] \name_prop[13;],\name_prop[12;] [\m[2]\m[3]] \name_prop[13;],\name_prop[10;] (\m[1]\m[2]) \name_prop[11;],\name_prop[10;] (\m[1]\m[3]) \name_prop[11;],\name_prop[10;] (\m[2]\m[3]) \name_prop[11;]}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\dessin" alt=""></div>
 <div class="medium_size text_col">
\name_prop[4;] \L[1]\L[2]\L[3] \name_prop[5;].
<br>\name_prop[6;] \droite \de \name_prop[7;] \embed{r1}
<br> \name_prop[8;]
<ul>\for{j=1 to 6}{<li>\embed{r2,\j}</li>}</ul>
</div></div>
}

\answer{}{\l1;\rep1}{type=checkbox}{options=shuffle}
choice{}{\rep2}{\choix}{options=shuffle}
\answer{}{\l2;\choix}{type=checkbox}

\solution{
\name_prop[9;] \de :
 <div class="wimscenter"> <img src="\dessrep" alt=""></div>
}
