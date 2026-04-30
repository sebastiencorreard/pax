\title{E pour calculer une circonférence une aire ou un volume.}

\integer{R=randint(1..100)}
\text{alea=randint(1..3)}
\text{nff=circonference,aire,volume}
\text{dsde=d'une sphère de rayon \(R\)}
\text{gghh=la circonférence \dsde,l'aire \dsde,le volume \dsde}
\text{unite=km,km^2,km^3}

\text{prob=E afin de s'approprier son fonctionnement.}
\text{enonce=La circonférence d'une sphère est donnée par la relation : \(P=2  \pi  R \).
<br>
L'aire d'une sphère est donnée par la relation : \(A= 4\pi  R^2 \).
<br>
Le volume d'une sphère est donnée par la relation : \(V= \frac{4}{3}\pi  R^3 \)}
\text{inst=print(\nff[\alea](5))}
 
\real{xO=(\alea==1)?2*pi*\R}
\real{xO=(\alea==2)?4*pi*R^2}
\real{xO=(\alea==3)?4/3*pi*\R^3}

\text{ale=randint(1..8)}
\matrix{plan=de Mercure,2400,Mercure.jpg
de Vénus,6100,Venus.jpg
de la Terre,6400,Terre.jpg
de Mars,3400,Mars.jpg
de Jupiter,71500,Jupiter.jpg
de Saturne,60300,Saturne.jpg
d'Uranus,25600,Uranus.png
de Neptune,26800,Neptune.jpg}
\integer{RP=(\alea==1)?2*pi*\plan[\ale;2]}
\integer{RP=(\alea==2)?4*pi*(\plan[\ale;2])^2}
\integer{RP=(\alea==3)?4/3*pi*(\plan[\ale;2])^3}

\text{question=Pour effectuer des calculs avec le nombre \(\Pi\) en Python,
 il faut importer le module math <code>from math import *</code> et écrire <code>pi</code> dans le code.
<br> 
E Python intitulée "\nff[\alea]" ayant pour paramètre
 la valeur de \(R\).
 Cette fonction "\nff[\alea]" doit retourner \gghh[\alea].}

\text{code=
\#importation de la librairie mathématiques#
from math import *
def ...
...
\#Test#
...
}

\text{post='@@@@'+'\eva1'+'=\nff[\alea](\R)'}
\text{rtest=[\eva1,[\xO]]}
