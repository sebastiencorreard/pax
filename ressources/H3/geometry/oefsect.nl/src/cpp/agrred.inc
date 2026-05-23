\language{nl}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fguerima@tele2.fr}
\translator{Reinie ERNE}
\computeanswer{no}
\format{html}
\precision{1000}

\text{unit=randitem(cm,dm,m,mm,dam)}
\text{nom=een piramide, een kegel, een cylinder}
\text{pnom=twee piramides, twee kegels, twee cylinders}
\text{verbe=verkregen,verkregen,verkregen}
\integer{ch=random(1..3)}
\text{nom=item(\ch,\nom)}
\text{verbe=item(\ch,\verbe)}
\text{pnom=item(\ch,\pnom)}

\integer{num1=random(120..1000)}
\real{num1=\num1/10}
\integer{coef=random(1..50)}
\real{coef=\coef/10}
