target= corres3,corres4,corres5

\language{nl}
\author{Guerimand Fabrice}
\email{fguerima@tele2.fr}
\translator{Reinie ERNE}
\computeanswer{no}
\format{html}
\precision{10000}
\text{size=50x75x75}

#if #TARGET (corres3)
\integer{nombre=3}
\title{Vierkantswortels 3.}
#endif

#if #TARGET (corres4)
\integer{nombre=4}
\title{Vierkantswortels 4.}
#endif

#if #TARGET (corres5)
\integer{nombre=5}
\title{Vierkantswortels 5.}
#endif

\text{nb=}
\text{ra=}
\for{i=1 to \nombre}{
\integer{a=random(2,3,5,7)}
\integer{b=random(2,3,5,6)}
\integer{c=random(7..15)}
\integer{a2=\a^2}
\integer{a3=\a^3}
\integer{a4=\a^4}
\integer{ab=\a*\b}
\integer{a2b=\a2*\b}
\integer{a3b=\a3*\b}
\integer{a4b=\a4*\b}
\integer{ac=\a*\c}
\integer{a2c=\a^2*\c}

\text{don=\sqrt{\a2b};\a\sqrt{\b},\c\sqrt{\a2b};\ac\sqrt{\b},\sqrt{\a3};\a\sqrt{\a},\sqrt{\a3b};\a\sqrt{\ab},\c\sqrt{\a3};\ac\sqrt{\a},\c\sqrt{\a3b};\ac\sqrt{\ab}}

\text{list=randitem(\don)}
\text{list=wims(replace internal ; by , in \list)}
\text{tmp=item(1,\list)}
\text{nb=\nb,\(\tmp)}
\text{tmp=item(2,\list)}
\text{ra=\ra,\(\tmp)}
}

\text{nb=wims(nonempty item \nb)}
\text{ra=wims(nonempty item \ra)}
\text{nb=wims(listuniq \nb)}
\text{ra=wims(listuniq \ra)}

\statement{Geef voor ieder getal links aan welke getal rechts er mee 
overeenkomt. 
<p><center>
\embed{reply 1,\size}
</center>
}

\reply{Gelijkheid}{\nb;\ra}{type=correspond}
