target=centercircle
#include "lang_titles.inc"

\language{fr}
\range{-5..5}
\author{XIAO, Gang}
\email{xiao@unice.fr}
\computeanswer{yes}
\format{html}
\precision{10000}

#include "lang.inc"
\integer{x1=random(10..50)}
\integer{y1=random(10..30)}
\integer{x2=random(-50..-10)}
\integer{y2=random(10..30)}
\integer{x3=random(-20..20)}
\integer{y3=random(-50..-10)}

\statement{\name_question[1] \(p_0 =(x_0,y_0)\) \name_question[2]
<div class="wimscenter">
\(p_1=(\x1,\y1)\),
\(p_2=(\x2,\y2)\),
\(p_3=(\x3,\y3)\).
</div>}

\hint{\name_hint1
<p>
\name_hint2
</p>
}
\answer{\(x_0\)}{\x0}
\answer{\(y_0\)}{\y0}
\condition{\(p_0\) \name_condition}
  {(\x0-(\x1))^2+(\y0-(\y1))^2=(\x0-(\x2))^2+(\y0-(\y2))^2 and
    (\x0-(\x1))^2+(\y0-(\y1))^2=(\x0-(\x3))^2+(\y0-(\y3))^2}
