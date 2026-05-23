target= reduitsom2,reduitsom3,reduitsom4

\language{nl}
\author{Guerimand Fabrice}
\email{fguerima@tele2.fr}
\translator{Reinie ERNE}
\computeanswer{no}
\format{html}
\precision{10000}
\text{size=50x50x50}

#if #TARGET (reduitsom2)
\integer{nombre=2}
\title{Som herschrijven 2.}
#endif

#if #TARGET (reduitsom3)
\integer{nombre=3}
\title{Som herschrijven 3.}
#endif

#if #TARGET (reduitsom4)
\integer{nombre=4}
\title{Som herschrijven 4.}
#endif

\integer{c=random(2,3,5,6,7,10)}
\text{b=randint(2..15),randint(2..15),randint(2..15),randint(2..15)}
\text{a=randint(-1,1)*randint(2..15),randint(-1,1)*randint(2..15),randint(-1,1)*randint(2..15),randint(-1,1)*randint(2..15)}

\text{enonce=}
\integer{res=0}
\for{i=1 to \nombre}{
\integer{tmp=(\b[\i])^2*\c}
\integer{tmp2=\a[\i]}
\text{sg=\tmp2>0 and \i>1?+:}
\text{enonce=\enonce \sg \tmp2\sqrt{\tmp}}
\integer{res=\res+(\tmp2)*(\b[\i])}
}

\text{rep=\res*sqrt(\c)}

\statement{Schrijf het getal \(\enonce) als \(a\sqrt{b}) waar \(b) een 
zo klein mogelijk geheel getal is. <br>
(schrijf sqrt(2) voor \(\sqrt{2}) ) }

\hint{Laat \(\sqrt{\c}) in beide termen van de som voorkomen.}

\reply{Antwoord}{\rep}{type=algexp}
