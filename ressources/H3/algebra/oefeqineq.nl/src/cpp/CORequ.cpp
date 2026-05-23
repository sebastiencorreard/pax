target=CORequ3 CORequ4 CORequ5

\language{nl}
\author{Guerimand Fabrice}
\email{wguerima@free.fr}
\translator{Reinie Erne}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}

\if{\confparm1>2}
{\text{size=50x120x75}}
{\text{size=50x75x75}}

#if #TARGET(CORequ3)
\integer{nombre=4}
\title{Gelijkheden 4}
#endif

#if #TARGET(CORequ4)
\integer{nombre=5}
\title{Gelijkheden 5}
#endif

#if #TARGET(CORequ5)
\integer{nombre=6}
\title{Gelijkheden 6}
#endif

#include "valeurs.inc"

\text{a=item(1,\valeurs)}
\text{b=item(2,\valeurs)}
\text{x=randitem(x,y,a,b)}

\text{donnees=\a*\x+\b=0;#;-(\b)/(\a),\a*\x-\b=0;#;(\b)/(\a),\b*\x+\a=0;#;-(\a)/(\b),\b*\x-\a=0;#;(\a)/(\b),\x+\b=\a;#;(\a)-(\b),\x-\b=\a;#;(\a)+(\b)}

\text{donnees=shuffle(\donnees)}
\text{donnees=wims(item 1 to \nombre of \donnees)}
\matrix{donnees=wims(items2lines \donnees)}
\matrix{donnees=wims(replace internal ;#; by , in \donnees)}
\text{nb=column(1,\donnees)}
\text{ra=column(2,\donnees)}

\text{tmp1=}
\text{tmp2=}
\for{i=1 to \nombre}{
\text{tmp=item(\i,\ra)}
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
\text{tmp1=wims(append item \(\tmp) to \tmp1)}
\text{tmp=item(\i,\nb)}
\text{tmp=texmath(\tmp)}
\text{tmp2=wims(append item \(\tmp) to \tmp2)}  
}
\text{ra=\tmp1}
\text{nb=\tmp2}

\statement{Geef aan welke oplossing bij welke vergelijking met onbekende \(\x) hoort. 
<p><center>
\embed{reply 1,\size}
</center>
}

\reply{Overeenkomst}{\nb;\ra}{type=correspond}
