target=circleeq
\language{fr}
\range{-5..5}
\author{XIAO, Gang}
\email{xiao@unice.fr}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\real{tolerance=0.0005}
\integer{x1=random(10..50)}
\integer{y1=random(10..30)}
\integer{x2=random(-50..-10)}
\integer{y2=random(10..30)}
\integer{x3=random(-20..20)}
\integer{y3=random(-50..-10)}

\statement{\name_instruction
<div class="wimscenter">\(x^2+y^2 =a x+ b y+c\),</div>
\name_instruction1
<div class="wimscenter">
\(p_1 = (\x1,\y1)\),
\(p_2 = (\x2,\y2)\),
\(p_3 =(\x3,\y3)\),
</div>
\name_instruction2 \(a\), \(\b\), \(\c\).}
\answer{\(a\)}{\aa}
\answer{\(b\)}{\ab}
\answer{\(\c\)}{\ac}
\condition{\(C\) \name_condition \(p_1\)}
  {abs((\x1)^2+(\y1)^2-(\aa)*(\x1)-(\ab)*(\y1)-(\ac))<\tolerance}
\condition{\(C\) \name_condition \(\p_2\)}
  {abs((\x2)^2+(\y2)^2-(\aa)*(\x2)-(\ab)*(\y2)-(\ac))<\tolerance}
\condition{\(C\) \name_condition \(p_3\)}
  {abs((\x3)^2+(\y3)^2-(\aa)*(\x3)-(\ab)*(\y3)-(\ac))<\tolerance}
