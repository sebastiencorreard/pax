target=Cerfvolant
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
Corrigé programmé par Thomas Wareth
#include "lang_titles.inc"
#include "lang.inc"
\matrix{donne=
10,8,7.5
15,12,10.5
20,16,13.5
25,20,16.5
30,24,19.5
35,28,22.5
40,32,25.5
45,36,28.5
50,40,31.5
13,12,6.5
25,24,8.5
41,40,10.5
}
\text{ligne=randomrow(\donne)}
\text{h=item(1,\ligne)}
\text{ao=item(2,\ligne)}
\text{r=item(3,\ligne)}

\statement{<div class="wimscenter">
\draw{300,250}{
xrange -25,25
yrange -25,25
segment -25,-24,25,-24,green
fill 0,-25,green
rectangle -22,-16,-20,-24,black
rectangle -20,-16,-19,-24,black
polyline black,-15,-9,-21,-10,-20.5,-11.5,-14.5,-10.3
polyline black,-20,-9.8,-22,-9.8,-22,-16
segment -19,-11,-19,-24,black
circle -14,-9,10,black
segment -15,-8.5,-20,-9.5,black
circle -20.5,-8,17,black
segment -13.3,-8.2,14.5,8.5,black
poly black,14.5,8.5,20.5,9,24,15,17.3,14.3
segments red,14.5,8.5,24,15,20.5,9,17.3,14.3
dsegment 24,15,24,-24,black
segments black,-13,-10,23,-10,23,-11,23,-23
polyline black,-12,-9.5,-13,-10,-12,-10.5
polyline black,22,-9.5,23,-10,22,-10.5
polyline black,22.5,-12,23,-11,23.5,-12
polyline black,22.5,-22,23,-23,23.5,-22
text black,22.5,-2,medium,?
text black,15,-15,giant,1.5 m
text black,6,-7,giant,\ao m
text black,-2,5,giant,\h m
}
</div>
\name_enonce[1] (\name_enonce[2] \(m\)) ?
}

\answer{\name_answer}{\r}

\solution{<p>
\name_sol1<br>
\name_sol2[1]</p>
<p>\name_sol2[2]:</p>
<div class="wimscenter">
\draw{130,100}{triangle 10,60,90,60,90,10,black
text black,2,56,medium,A
text black,95,53,medium,B
text black,95,6,medium,C
arrow 90,75,90,63,7,black
arrow 90,75,90,99,7,black
text black,92,73,medium,1.5 m}</div>
<p>
\name_sol3[1]:<br>
\(AC\) \name_sol3[2], \(AC=\h m.\)<br>
\(AB\) \name_sol3[3] \(AB=\ao m.\)<br>
\(H\) \name_sol3[4]
</p><p>
\name_sol4[1]:</p>
<p class="wimscenter">\(AB^2+BC^2 = AC^2\)</p>
\name_sol4[2] <p class="wimscenter">\(BC^2 = AC^2-AB^2\)</p>
<p class="wimscenter">\(BC=\sqrt{AC^2-AB^2}\)</p>
\name_sol4[3] <p class="wimscenter">\(H=BC+1,5 = \sqrt{AC^2-AB^2}+1.5=\sqrt{\h^2-\ao^2}+1.5=\r\).</p>
<strong>\name_sol4[4] \(\r\ m\).</strong>
}
