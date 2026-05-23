target=Arbreabattu
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
Corrigé de l'exercice réalisé par Thomas Wareth
#include "lang_titles.inc"
#include "lang.inc"
\matrix{donne=
4,3,8
8,6,16
12,9,24
16,12,32
20,15,40
12,5,18
24,7,32}
\text{ligne=randomrow(\donne)}
\text{s=item(1,\ligne)}
\text{t=item(2,\ligne)}
\text{h=item(3,\ligne)}
\real{Ht=sqrt(\s^2+\t^2)}
\real{H=\Ht+\t}

\statement{<p class="wimscenter">
\draw{250,150}{
xrange -25,25
yrange -15,15
filledrectangle -25,-10,25,-15,20,200,20
polyline black,-22,-10,-22,5,-21,2,-20,4,-19,2,-18,3,-18,-10
fill -20,-5,brown
polyline black,15,-8,-18,3,-15,3,-17,5,-14,5,16,-5
filledcircle 15,-5,50,green
segment -25,-10,25,-10,black
filledcircle 8,-6,40,green
filledcircle 10,-1,40,green
fill -10,3,brown
segment -15,0,-15,-9,black
polyline black,-16,-2,-15,0,-14,-2
polyline black,-16,-7,-15,-9,-14,-7
dpolyline black,-17,-9,-17,1.5,14,-9
segment -16,-11.5,14,-11.5,black
polyline black,-14,-10.5,-16,-11.5,-14,-12.5
polyline black,12,-10.5,14,-11.5,12,-12.5
text black,-3,-12,medium,\s m
text black,-14,-3,medium,\t m
text black,-5,-3,medium,?
}
</p>
\name_enonce[1] (\name_enonce[2] \(m\))?
}
\answer{\name_answer}{\h}
\solution{
<p>\name_sol1<br>
\name_sol2[1]</p><p>
\name_sol2[2]: <br>
\(H_t\) \name_sol2[3] \(H_t = ?\)<br>
\(h\) \name_sol2[4] \(h = \t\)<br>
\(L\) \name_sol2[5]l \(L = \s\)
</p><p>
\name_sol3[1]:<p class="wimscenter">
\(H_t=\sqrt{h^2+L^2}=\sqrt{\t^2+\s^2}=\Ht\)</p>
<p class="wimscenter bold">
\(H_t = \Ht m.\)</p>
<p>\name_sol3[2]:</p>
<p class="wimscenter bold">\(H = \H m.\)</p>
}
