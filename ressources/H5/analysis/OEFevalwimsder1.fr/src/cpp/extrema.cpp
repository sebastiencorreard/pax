target=extrema1 extrema2 extrema3 extrema4 extrema5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}

#define TITRE Recherche d'extremum
#if defined TARGET_extrema1
\title{TITRE 1}
\integer{k=randint(1..3)}
integer{k=3}
\if{\k<3}{
  \text{dessin=
   xrange -5,5
   yrange -5,5
   circle 0,0,150,black
   polyline red,2.5*cos(-pi/6),2.5*sin(-pi/6),0,0,0,2.5
   polyline blue,0,0,0,2.5*sin(-pi/6),2.5*cos(-pi/6),2.5*sin(-pi/6)
   polyline green,-2.5*cos(-pi/6),2.5*sin(-pi/6),0,2.5,2.5*cos(-pi/6),2.5*sin(-pi/6)
   ellipse 0,2.5*sin(-pi/6),2.5*sqrt(3),1,green
   text black,-0.2,0,medium,O
   text black,-0.2,-1.25,medium,O'
   text black,-0.2,2.9,medium,S
   }
  \text{mstep=r1,r2}
}
\if{\k=1}{
  \function{r=sqrt(R^2-(h-R)^2)}
  \function{base = pi* (\r)^2}
  \function{V=(\base)*h/3}
  \function{h0=4*R/3}
  \text{th=SO'}
}
\if{\k=2}{
  \function{r=sqrt(R^2-h^2)}
  \function{base = pi* (\r)^2}
  \function{V=(\base)*(R+h)/3}
  \function{h0=R/3}
  \text{th=OO'}
}
\if{\k=3}{
  \text{dessin=
   xrange -5,5
   yrange -5,5
   arc -2.5,0,5,5,30,-20,green
   polyline green,-2.5+2.5*cos(pi/6),2.5*sin(pi/6),-2.5,0,-2.5+2.5*cos(-pi/9),2.5*sin(-pi/9)
   polyline blue,2.5,4,2.5,2.5*sin(-pi/6),2.5+2.5*cos(-pi/6),2.5*sin(-pi/6)
   polyline green,2.5-2.5*cos(-pi/6),2.5*sin(-pi/6),2.5,4,2.5+2.5*cos(-pi/6),2.5*sin(-pi/6)
   ellipse 2.5,2.5*sin(-pi/6),2.5*sqrt(3),1,green
   text black,-1.8,1,medium,R
   text black,4,1.8,medium,R
   text black,2.3,1.5,medium,h
   text black,3,-0.7,medium,r
   fill -3,0,yellow
  }
  \text{mstep=r1,r2,r3,r4}
  \function{r=sqrt(R^2-h^2)}
  \function{base = pi* (\r)^2}
  \function{V=(\base)*h/3}
  \function{h0=sqrt(3)*R/3}
  \function{r0=sqrt(2/3)*R}
  \function{a=2*pi*(1-sqrt(2/3))}
}
\steps{\mstep}
\statement{
<div class="wimscenter"><b> Le plus grand cône</b></div>
\draw{300,300}{\dessin}
\if{\k<3}
 {
   On construit un cône dans une sphère de centre O et de rayon R comme indiqué sur la figure.<p>
   On veut déterminer la distance \(\th) pour que ce cône ait un volume maximal.</p>
<ol>
<li> On note \(\th=h).<br>
   Donner l'expression algébrique de \(V(h)) représentant le volume du cône en fonction de \(h) et de \(R\)&nbsp;:
<div class="wimscenter"><label for="reply1">\(V(h))=</label>\embed{reply1} </div></li>
<li> Déterminer la hauteur \(h_0) en fonction de R pour laquelle le volume du cône est maximal&nbsp;:
<div class="wimscenter"><label for="reply2">\(h_0)=</label>\embed{reply2}</div></li>
 </ol>
}{
   Dans un disque de rayon R, on découpe un secteur circulaire de \(\alpha) radian.<br>
  En joignant les deux bords droits du secteur angulaire restant,
   on fabrique un cône.<p>
   On veut déterminer pour quelle valeur de \(\alpha) le volume du cône est maximal.
  </p>
<ol>
<li> On note \(h) la hauteur du cône.<br>
   Donner l'expression algébrique de \(V(h)) représentant le volume du cône en fonction de \(h) et de \(R\)&nbsp;:
<div class="wimscenter"> <label for="reply1">\(V(h))=</label>\embed{reply1} </div></li>
<li> Calculer la hauteur \(h_0) pour laquelle le volume du cône est maximal&nbsp;:
<div class="wimscenter"> <label for="reply2">\(h_0)=</label>\embed{reply2}</div></li>
<li> Exprimer \(r_0), rayon de la base du cône correspondant à cette hauteur \(h_0)&nbsp;:
<div class="wimscenter"> <label for="reply3">\(r_0)=</label>\embed{reply3}</div></li>
<li> En exprimant que la circonférence du secteur angulaire de départ correspond
 à la circonférence de la base du cône, donner une valeur exacte de \(\alpha)&nbsp;:
<div class="wimscenter"> <label for="reply4">\(alpha)=</label>\embed{reply4}</div></li>
</ol>
 }
<div class="wims_instruction"> Taper <span class="tt">pi</span> pour \(\pi) et
<span class="tt">sqrt(a)</span> pour \(\sqrt{a}).</div>
}
\answer{V(h)}{\V}{type=formal}
\answer{\(h_0)}{\h0}{type=formal}
\answer{\(r_0)}{\r0}{type=formal}
\answer{\(\alpha)}{\a}{type=formal}
#endif

#if defined TARGET_extrema2
\title{TITRE 2}
\integer{a=randint(1..4)}
\integer{p1=randint(2..8)*100}
\integer{p2=randint(1,2,4,5)*100}
\real{V=round(100*\p1*\a^3/\p2)/100}
\rational{h=\p1*\a/\p2}
\function{P=maxima(2*\p1*a^2/100+4*\p2*\V/(100*a))}
\statement{<p>
   Un coffre à bijoux a la forme d'un parallélépipède
   rectangle à base carrée et a un volume imposé de \V L (\V dm<sup>3</sup>).</p><p>
   Le matériau utilisé pour construire les bases coûte \p1 euros le mètre carré
   et celui utilisé pour construire la surface latérale coûte \p2 euros le mètre carré.</p>
<ol><li>
 Exprimer le prix de revient \(P(a)) en fonction du côté \(a) (en dm) de la base carrée&nbsp;:
<div class="wimscenter"><label for="reply1">\(P(a)=)</label>\embed{reply1}</div> </li>
<li> En déduire les dimensions de la boîte pour que le prix de revient soit minimal.
<ul><li><label for="reply2">Côté de la base&nbsp;:</label> \embed{reply2} dm</li><li>
   <label for="reply3">Hauteur de la boîte &nbsp;:</label> \embed{reply3} dm</li></ul>
</li></ol>
}
\answer{\(P(a))}{\P}{type=formal}
\answer{côté de la base}{\a}{type=numexp}
\answer{hauteur de la boîte}{\h}{type=numexp}
#endif

#if defined TARGET_extrema3
\title{TITRE 3}
\integer{xa=randint(1..5)}
\integer{ya=randint(1..5)}
\rational{a=\ya^2/\xa^2}
\rational{ra=-\ya/\xa}
\rational{b=2*\ya}
\text{eq=\ra*x+\b}
\text{xm=texmath((a*\xa-\ya)/a)}
\text{yn=texmath(\ya-\xa*a)}
\text{eqg=texmath(a*x+\ya-\xa*a)}
\text{eqr=texmath(\eq)}
\text{tsol=Notons \(a) la pente de la droite \(d). Son équation réduite est
\(y=\eqg).<br>
   Les points \(M) et \(N) ont pour coordonnées \(M(\xm,0)) et \(N(0,\yn)).<br>
   L'aire du triangle \(O M N) est donc \(A(a)= \frac{(\xm)\times(\yn)}{2}).<br>
   Cette aire est minimale pour \(a^2=\a), d'où l'équation réduite de \(d)<br>
\(y=\eqr)}
\statement{<p>
   Le plan est rapporté à un repère orthonormal \(O,\vec{i},\vec{j}).</p><p>
   Une droite \(d) non parallèle aux axes et de pente négative passant par le point \(A(\xa,\ya)) coupe
   l'axe des abscisses en \(M) et l'axe des ordonnées en \(N).
</p><p>
  Déterminer l'équation réduite \(d) pour que le triangle \(O M N) ait une aire minimale.
</p><div class="wimscenter"><label for="reply1">\(y=)</label> \embed{reply1} </div>
}
\answer{equation}{\eq}{type=formal}
\solution{\tsol}
#endif

#if defined TARGET_extrema4
\title{TITRE 4}
\integer{a=randint(1..5)}
\function{A=maxima((\a-x)*((\a/2)^2+x^2)/\a)}
\rational{x0=\a/6}
\statement{
   On considère un carré \(A B C D) de côté \a.<br>
   On note \(I) le milieu de [A B] et \(J) celui de [A D].<br>
   Un point \(M) se déplace sur le segment [A I], on note \(x=A M).<br>
 Soit \(N) le point de [B C] tel que le triangle \(J M N) soit rectangle en \(M).

<ol>
<li> Déterminer en fonction de \(x) l'aire du triangle \(J M N)&nbsp;:
<div class="wimscenter"><label for="reply1">Aire = </label>\embed{reply1} </div>
</li>
<li> Quelle est la valeur de \(x) rendant cette aire minimale?
<div class="wimscenter"><label for="reply2">\(x)= </label>\embed{reply2} </div>
</li>
</ol>
<div class="wims_instruction"> Indication&nbsp;: on remarquera que les triangles \(A M J) et
  \(B N M) sont semblables!</div>
}
\answer{Aire}{\A}{type=formal}
\answer{x}{\x0}{type=numexp}
#endif

#if defined TARGET_extrema5
\title{TITRE 5}
\integer{n=randint(3000..4000)}
\integer{o=randint(1..4)}
\text{teuro=\o=1?euro:euros}
\integer{p1=randint(10..15)}
\function{B=maxima(p*\n*(1-(p-\p1)/(\o*10)))}
\rational{p0=(\p1+\o*10)/2}
\statement{<p>
   Le parc d'attraction Totoland a ouvert en 2007 et a reçu \n visiteurs avec un billet d'entrée valant \p1 euros.<br>
   Une étude de marché a montré que si le prix du billet d'entrée augmentait de \o \teuro,
   le nombre de visiteurs baisserait de 10 %, et que si le prix baissait de \o \teuro,
   le nombre de visiteurs augmenterait de 10 %.</p><p>
   On fait l'hypothèse que cette étude de marché se prolonge ainsi à toute hausse ou baisse
   du prix du billet.</p><p>
   On veut déterminer quel prix du billet d'entrée en 2008 permettrait de réaliser une recette maximale.
</p><ol>
<li> Exprimer la recette \(R) réalisée en fonction du prix \(p) du billet d'entrée&nbsp;:
<div class="wimscenter"> <label for="reply1">\(R(p))= </label>\embed{reply1} </div></li>
<li> En déduire le prix \(p_0) correspondant au maximum de cette recette&nbsp;:
<div class="wimscenter"><label for="reply2">\(p_0)=</label> \embed{reply2,3} </div></li>
</ol>
}
\answer{Recette}{\B}{type=formal}
\answer{prix recherché}{\p0}{\type=numexp}
\solution{Soit \(x) l'augmentation par rapport au prix de départ \p1 euros, donc p=\p1+x.<br>
   Le nombre de visiteurs subit une baisse de \(t=\frac{x}{\o}\times 10 \%=\frac{p-\p1}{\o}\times 10 \%).<br>
   Le nombre de visiteurs devient donc \(\n\times(1 -\frac{p-\p1}{\o\times 10}))</p><p>
   La recette s'exprime alors par \(R(p)=p\times \n \times (1 -\frac{p-\p1}{\o\times 10}))</p><p>
   En dérivant on obtient \(R'(p)=\n(1-\frac{2p-\p1}{\o\times 10})) qui s'annule pour \(p_0=\p0).
</p>
}
#endif
