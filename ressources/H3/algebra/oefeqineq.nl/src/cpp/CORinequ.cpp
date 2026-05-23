target= CORinequ3 CORinequ4 CORinequ5

\language{nl}
\author{Guerimand Fabrice}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}
\text{size=45x150x75}
\translator{Reinie Erne}

\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}


#if #TARGET (CORinequ3)
\integer{nombre=4}
\title{Ongelijkheden 4}
#endif

#if #TARGET (CORinequ4)
\integer{nombre=5}
\title{Ongelijkheden 5}
#endif

#if #TARGET (CORinequ5)
\integer{nombre=6}
\title{Ongelijkheden 6}
#endif

\integer{confparm1=\confparm1 /2=0?\confparm1-1}

#include "valeurs.inc"

\text{a=item(1,\valeurs)}
\text{b=item(2,\valeurs)}
\text{x=randitem(x,y,a,b)}

\text{a=2}
\text{b=10}


\text{symb=<,>}
\text{inf=item(1,\symb)}
\text{sup=item(2,\symb)}
\text{dd=simplify((\b)/(\a))}
 
\text{dd2=simplify(\b-\a)}
\text{dd3=simplify(-\dd2)}

\text{donnees=(\x \inf \dd,-\a*\x \sup -\b,\a*\x-\b \inf 0,\a*\x \inf \b),(\x \inf -\dd,-\a*\x \sup \b,\a*\x+\b \inf 0,\a*\x \inf -\b),(\x \sup \dd,-\a*\x \inf -\b,\a*\x-\b \sup 0,\a*\x \sup \b),(\x \sup -\dd,-\a*\x \inf \b,\a*\x+\b \sup 0,\a*\x \sup -\b),(\x \sup \dd2,\x+\a \sup \b),
(\x \sup \dd3,\x-\a \sup -\b)}

\text{donnees=shuffle(\donnees)}
\text{donnees=wims(item 1 to \nombre of \donnees)}

\text{ra=}
\text{nb=}
\for{i=1 to \nombre}{
\text{TMP=item(\i,\donnees)}
\text{TMP=wims(declosing \TMP)}
\text{tmp=item(1,\TMP)}
\if{\confparm1>4}{
\text{tmp=wims(replace internal / by , in \tmp)}
\text{tmp3=items(\tmp)}
\if{\tmp3=2}{
\integer{tmp3=item(1,\tmp)*100}
\integer{tmp4=item(2,\tmp)*100}
\text{tmp=\tmp3/\tmp4}
}}
\text{tmp=simplify(\tmp)}
\text{tmp=texmath(\tmp)}
\text{ra=wims(append item \(\tmp) to \ra)}

\text{tmp=wims(item 2 to -1 of \TMP)}
\text{tmp=randitem(\tmp)}
\text{tmp=texmath(\tmp)}
\text{nb=wims(append item \(\tmp) to \nb)}  
}

\integer{ch=random(1..2)}
\if{\ch=2}{
\text{nb=wims(replace internal < by \leq in \nb)}
\text{ra=wims(replace internal < by \leq in \ra)}
\text{nb=wims(replace internal > by \geq in \nb)}
\text{ra=wims(replace internal > by \geq in \ra)}
}

\statement{<br>
Geef aan welke ongelijkheden overeenkomen.
<p><center>
\embed{reply 1,\size}
</center>
}

\reply{Overeenkomst}{\nb;\ra}{type=correspond}
