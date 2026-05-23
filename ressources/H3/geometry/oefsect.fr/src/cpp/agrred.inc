\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{1000}

\text{unit=randitem(cm,dm,m,mm,dam)}
\text{nom=une pyramide, un cône, un cylindre}
\text{pnom=deux pyramides, deux cônes, deux cylindres}
\text{verbe=obtenue,obtenu,obtenu}
\integer{ch=random(1..3)}
\text{nom=item(\ch,\nom)}
\text{verbe=item(\ch,\verbe)}
\text{pnom=item(\ch,\pnom)}

\integer{num1=random(120..1000)}
\real{num1=\num1/10}
\integer{coef=random(1..50)}
\real{coef=\coef/10}
