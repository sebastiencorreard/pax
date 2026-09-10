target=rulefrac rulefracirr rulefracrel rulefracrelirr 

\integer{m=6}
#if #TARGET (rulefrac)
 \title{Regla y fracciones}
 \integer{m1=0}
 \integer{signe=1}
 \text{consigne=}
#endif

#if #TARGET (rulefracirr)
 \title{Regla y fracciones irreductibles}
 \integer{m1=0}
 \integer{signe=1}
 \text{consigne=<b>Instrucciones</b>. Debe presentarse la fracción en forma irreductible. }
#endif

#if #TARGET (rulefracrel)
 \title{Regla y fracciones relativas}
 \integer{m1=-\m}
 \integer{signe=randitem(-1,1)}
#endif
 
#if #TARGET (rulefracrelirr)
 \title{Regla, fracciones irreductibles (relativas)}
 \integer{m1=-\m}
 \integer{signe=randitem(-1,1)}
\text{consigne=<b>Instrucciones</b>. Debe presentarse la fracción en forma irreductible. }
#endif

\language{es}
\range{-5..5}
\author{Bernadette Perrin-Riou}
\email{bpr@math.u-psud.fr}
\computeanswer{no}
\format{html}
\precision{1000}

\text{a=0}
\text{dessin=}
\for{i=\m1 to \m}{
\integer{a=\i*1}
\integer{s=\i}
\text{dessin=\dessin
text blue, \s,-1, medium,\a}}
\text{den=randitem(2,4,5,3)}
\text{num=randint( 1..10)}
\text{reste=pari(divrem(\num,\den)~[2])}
\integer{den = \reste=0 ? \den*\den}
\rational{a=\signe*\num/\den}
\text{nd=pari([numerator(\a),denominator(\a)])}


\statement{Aquí tiene una recta graduada. El punto indicado por la flecha sobre la recta graduada 
tiene como abscisa al cociente de dos enteros. Se trata de 
<table align="center">
<tr align="center"><td>\embed{reply 1,6}</td></tr>
<tr align="center"><td><hr></td></tr>
<tr align="center"><td>\embed{reply 2,6}</td></tr>
</table>
<p align="center">\draw{600,50}
{xrange \m1-0.1,\m+0.1
yrange -2,2.2
hline black,0,0
arrow 2.5,0,\m,0,10,black
parallel \m1,-0.8,\m1,0.4,1/2,0, 40, blue
parallel \m1,-0.3,\m1,0.3,1/10,0, 200, blue
parallel \m1,-0.8,\m1,0.6,1,0, 40, red
\dessin
arrow \a,2,\a,0, 8, black
}
</p>
<p>
\consigne
</p>
}


#if #TARGET (rulefrac)
\answer{numerador}{\nd1}{type=numeric}
\answer{denominador}{\nd2}{type=numeric}
\text{test1=round(\reply1)=\reply1 ? 1:0}
\condition{}{\test1=1 and \reply1/\reply2=\a}
#endif 

#if #TARGET (rulefracrel)
\answer{numerador}{\nd1}{type=numeric}
\answer{denominador}{\nd2}{type=numeric}
\text{test1=round(\reply1)=\reply1 ? 1:0}
\condition{}{\test1=1 and \reply1/\reply2=\a}
#endif 

#if #TARGET (rulefracirr)
\answer{numerador}{\nd[1]}{type=numeric}
\answer{denominador}{\nd[2]}{type=numeric}
\real{test1=\reply1/\reply2-\a}
\feedback{\test1=0 and \reply1<>\nd[1]}{No ha simplificado la fracción.}
#endif 

#if #TARGET (rulefracrelirr)
\answer{numerador}{\nd[1]}{type=numeric}
\answer{denominador}{\nd[2]}{type=numeric}
\real{test1=\reply1/\reply2-\a}
\feedback{\test1=0 and \reply1<>\nd[1]}{No ha simplificado la fracción. }
#endif 
