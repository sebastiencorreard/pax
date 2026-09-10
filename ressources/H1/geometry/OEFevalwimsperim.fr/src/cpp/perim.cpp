target=oefperim1 oefperim2 oefperim3 oefperim4 oefperim5
\keywords{perimeter}
#include "author.inc"
#include "lang_titles.inc"
\precision{10000}
#include "lang.inc"

#if defined TARGET_oefperim1
\integer{a=randint(80..250)}
\integer{b=randint(40..\a-20)}
\integer{x=(300-\a)/2}
\integer{y=(300-\b)/2}
\real{rep=(\b*2+\a*2)/10}

\text{fig=draw(300,300
rect \x,\y,\x+\a,\y+\b,black
)}
\real{a=\a/10}
\real{b=\b/10}
\text{dim=\name_dim[1] \a cm \name_dim[2] \b cm.}
#endif
#if defined TARGET_oefperim2
\integer{a=10*randint(11..25)}
\integer{d=10*randint(11..25)}
\integer{b=10*randint(3..\d/10-5)}
\integer{c=10*randint(3..\a/10-5)}
\integer{x=(300-\a)/2}
\integer{y=300-(300-\d)/2}
\integer{h1=sqrt((\a-\c)^2+(\d-\b)^2)}
\real{rep=(\a+\b+\h1+\c+\d)/10}
\text{fig=draw(300,300
poly black,\x,\y,\x+\a,\y,\x+\a,\y-\b,\x+\c,\y-\d,\x,\y-\d
text red,\x-8,\y,medium,A
text red,\x+\a+2,\y,medium,B
text red,\x+\a+5,\y-\b-8,medium,C
text red,\x+\c+5,\y-\d-10,medium,D
text red,\x-8,\y-\d-8,medium,E
)}
\real{a=\a/10}
\real{b=\b/10}
\real{d=\d/10}
\real{c=\c/10}
\real{e=\e/10}
\real{h1=\h1/10}

\text{dim=\name_dim: <ul><li>\(A B\) = \a cm </li><li>\(B C\) = \b cm </li><li>\(C D\) = \h1 cm</li>
<li>\(D E\) = \c cm</li><li>\(E A\) = \d cm</li></ul> }
#endif
#if defined TARGET_oefperim3
\integer{a=10*randint(10..25)}
\integer{b=10*randint(3..20)}
\integer{d=10*randint(3..25-\b/10)}
\integer{c=10*randint(3..\a/20)}
\integer{e=10*randint(3..\a/10-\c/10-2)}
\integer{f=10*randint(3..\b/10+\d/10-3)}
\integer{x=(300-\a)/2}
\integer{y=300-(300-\b-\d)/2}
\real{rep=((\a+\b+\d)*2)/10}
\text{fig=draw(300,300
poly black,\x,\y,\x+\a,\y,\x+\a,\y-\b,\x+\a-\c,\y-\b,\x+\a-\c,\y-\b-\d,\x+\a-\c-\e,\y-\b-\d,\x+\a-\c-\e,\y-\b-\d+\f,\x,\y-\b-\d+\f
text red,\x-8,\y,medium,A
text red,\x+\a+2,\y,medium,B
text red,\x+\a+2,\y-\b-8,medium,C
text red,\x+\a-\c-8,\y-\b-8,medium,D
text red,\x+\a-\c+5,\y-\b-\d-5,medium,E
text red,\x+\a-\c-\e-8,\y-\b-\d-5,medium,F
text red,\x+\a-\c-\e,\y-\b-\d+\f+5,medium,G
text red,\x-8,\y-\b-\d+\f-8,medium,H)}

\real{a=\a/10}
\real{b=\b/10}
\real{d=\d/10}
\real{c=\c/10}
\real{e=\e/10}
\real{f=\f/10}
\text{dim=\name_dim: <ul><li>\(A B\) = \a cm </li><li>\(B C\) = \b cm </li><li>\(C D\) = \c cm</li>
 <li>\(D E\) = \d cm </li><li>\(E F\) = \e cm </li><li>\(F G\) = \f cm</li></ul>}
#endif
#if defined TARGET_oefperim4
\integer{a=10*randint(2..10)}
\integer{b=10*randint(5..(26-\a/10))/2}
\integer{x=(300-\a)/2}
\integer{y=150+\a/2+\b}
\real{rep=(\b*8+\a*4)/10}

\text{fig=draw(300,300
poly black,\x,\y,\x+\a,\y,\x+\a,\y-\b,\x+\a+\b,\y-\b,\x+\a+\b,\y-\b-\a,\x+\a,\y-\b-\a,\x+\a,\y-\b-\a-\b,\x,\y-\b-\a-\b,\x,\y-\b-\a,\x-\b,\y-\b-\a,\x-\b,\y-\b,\x,\y-\b
text red,\x-8,\y,medium,A
text red,\x+\a+2,\y,medium,B
text red,\x+\a+5,\y-\b+5,medium,C)}

\real{a=\a/10}
\real{b=\b/10}
\text{dim=\name_dim:
  <ul><li>\name_croix</li><li>\(A B\) = \a cm</li><li>\(B C\) = \b cm</li></ul>}
#endif
#if defined TARGET_oefperim5
\integer{a=10*randint(8..25)}
\integer{b=10*randint(4..(\a/10)-2)}
\integer{x=(300-\a)/2}
\integer{y=(300-\b)/2}
\real{rep=\a/10}
\text{name_question=}
\text{fig=draw(300,300
rect \x,\y,\x+\a,\y+\b,black)}

\real{b=\b/10}
\real{p=\a/5+\b*2}
\text{dim=\name_dim[1]: <ul><li>\name_dim[2] \p cm,</li><li>\name_dim[3] \b cm</li></ul>}
#endif
\statement{<div class="wims_columns">
 <div class="medium_size img_col">
   <img src="\fig" alt="">
 </div>
 <div class="medium_size text_col">
 <p>\name_question</p>
  \dim
  <div class="spacer">
  <label for="reply1"> \r \name_is: </label> \embed{r1,6} cm.
  </div>
  </div></div>
}

\answer{}{\rep}{type=numeric}
