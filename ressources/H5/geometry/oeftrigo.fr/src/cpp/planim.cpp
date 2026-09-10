target=planim
#include "lang_titles.inc"

\author{Bernadette, Perrin-Riou}
\email{bpr@math.u-psud.fr}
\precision{1000}
#include "lang.inc"
\real{x=random(1,-1)*randint(3..20)/10}
\real{xx=sqrt(4-(\x)^2)}
\real{y=randint(-10*\xx..10*\xx)/10}
\real{ ab=sqrt((4-(\x)^2-(\y)^2)/((\x)^2+(\y)^2))/2}
\real{ a=(\x)/2+(\y)*(\ab)}
\real{ b=(\y)/2-(\x)*(\ab)}
\real{norme=(\a)^2 + (\b)^2}
\real{angle2=acos(sqrt((\x)^2+(\y)^2)/2)/2}
\real{angle1= pari(print(arg(\x+I*(\y))-2*(\angle2)))
}
\real{angle1= \angle1-(floor(\angle1/(2*pi))*2*pi)}

\statement{ \name_instruction:
<div class="wimscenter">\draw{200,200}
{xrange -2,2
yrange -2,2
hline 0,0,black
arrow 0,0,2,0,7,black
vline 0,0,black
segment 0,0, 2*\a,2*\b, black
linewidth 3
disk 0,0,8, orange
disk \a,\b,8, blue
disk \x,\y,8, red
text black, \x,\y,medium, M
text black, \0,0,medium, O
text black, \a,\b,medium, N
polyline green, 0,0,\a,\b,\x,\y
}
</div>
\name_question1 \((\x , \y)), \name_question2
<div class="wims_instruction"> \name_inst
</div>
}

\answer{\(x_N)}{\a}{type=numeric}
\answer{\(y_N)}{\b}{type=numeric}
\answer{\(\theta_1)}{\angle1}{type=numeric}
\answer{\(\theta_2)}{\angle2}{type=numeric}
\hint{\name_hint}
