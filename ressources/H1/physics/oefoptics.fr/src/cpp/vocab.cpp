
\title{AAAA}
Zone éclairée, Pénombre,Ombre portée, Pénombre, Zone éclairée
 dessin avec les 4 tangentes.

\text{S=0}
\text{rS=randint(30..50)}
\text{T=randint(200..300)}
\text{rT=randint(10..2*\rS)}
\text{tangente=slib(tangente \S,0,\rS,\T,0,\rT)}
\text{tangente=wims(declosing \tangente[5])}
\text{tangente=wims(replace internal XXXXXX1 by 1000 in \tangente)}
\text{tangente=wims(replace internal XXXXXX2 by 1000 in \tangente)}
\text{l=3}
\text{range=150}
\text{size=pari([(\l+1)/2*800,800])}

\statement{
\special{expandlines \tangente}
\draw{\size}{
xrange -\range,\l*\range
yrange -\range,\range
circles black, \S,0,\rS,\T,0,\rT
\tangente}
}
