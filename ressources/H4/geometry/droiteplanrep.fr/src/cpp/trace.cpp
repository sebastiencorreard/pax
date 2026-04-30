target = tracpar tracred lectequat

#if defined TARGET_lectequat
\title{Lecture graphique de l'équation réduite}
#endif


#define TITRE Reconnaitre le tracé d'une droite 
#if defined TARGET_tracpar
\title{TITRE (eq. cartésienne) }
#endif
#if defined TARGET_tracred
\title{TITRE (eq. réduite) }
#endif
\author{Cyrille, Douriez;Bruno,Mifsud}
\email{cyrille.douriez@ac-amiens.fr;communaute.mutuwims@laposte.net}
\language{fr}
\keywords{line,equations}
#if defined TARGET_lectequat
%%%%%%%%%%%% cas=0 : x= ; cas=1;y=
\integer{cas=randint(0,1,1,1)}
\integer{q=randint(1..6)*randint(-1,1)}
\integer{m1=randint(1..5)*randint(-1,1)}
\integer{m2=randint(3,5)}
\integer{pgcd=pari(gcd(\m1,\m2))}
\integer{m1=\m1/\pgcd}
\integer{m2=\m2/\pgcd}
\integer{p=randint(-3..3)}
\text{trace=\cas==0? line \q,10,\q,-10,blue : plot blue, (\m1/\m2)*x+\p}
\function{f=\p=0? (\m1/\m2) x:(\m1/\m2) x+\p}

%%%%%%%%%%%%%rep
\text{rep1=\cas==0?1:2}
\text{rep2=\cas==0?\q:\f}
#endif

#if defined TARGET_tracpar || TARGET_tracred
\range{-5..5}
\author{Cyrille,Douriez;Bruno, Mifsud}
\email{cyrille.douriez@ac-amiens.fr;communaute.mutuwims@laposte.net}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{type=randint(1,2)}  1: coef directeur entier, 2: coef directeur rationnel
\integer{a=randint(2..6)*randint(-1,1)}
\integer{aden=randint(3,5,7)}
\integer{anum=randint(1..(\aden-1))*randint(-1,1)}
\if{\type==1}{\integer{b=(\a<0)? randint(2..7):randint(-7..-2)}}{\integer{b=(\anum<0)? randint(2..7):randint(-7..-2)}}
#endif


#if defined TARGET_tracpar
\integer{k=randint(1,2,3)*randint(-1,1)}
\function{fst=(\type=1)? maxima(\a*\k*x-\k*y+\k*\b):maxima(\k*\anum*x-\aden*\k*y+\aden*\k*\b)}
\function{f=(\type=1)? maxima(\a*x+\b):maxima((\anum/\aden)*x+\b)}
\function{g=(\type=1)? maxima(\b*x+\a):maxima(\b*x+\anum)}
\function{h=(\type=1)? -\a*x+\b:maxima((\aden/\anum)*x+\b)}
\function{k=(\type=1)? -\b*x+\a  :maxima((\anum/\aden)*x+\a)}
#endif

#if defined TARGET_tracred
\integer{b=(\b=-\a)? \b-(\a/abs(\a)) :\b}
\function{f=(\type=1)? maxima(\a*x+\b):maxima((\anum/\aden)*x+\b)}
\function{g=(\type=1)? maxima(\b*x+\a):maxima((\aden/\anum)*x+\b)}
\function{h=(\type=1)? maxima((-\b/\a)*x+\a):maxima(((-\b*\aden)/\anum)*x+\b)}
\function{k=(\type=1)? -\b*x+\b  :maxima((\anum/\aden)*x+\a)}
#endif

#if defined TARGET_tracpar || TARGET_tracred
\text{fonc=\f,\g,\h,\k}
\text{liste=shuffle(1,2,3,4)}
\if{\liste[1]=1}{\integer{rep=1}}
{\if{\liste[2]=1}{\integer{rep=2}}
{\if{\liste[3]=1}{\integer{rep=3}}
{\integer{rep=4}}
}}
#endif

\text{imgtemp=xrange -10,10
yrange -10,10
parallel -10,-10,10,-10,0,1,20, grey
parallel -10,-10,-10,10,1,0,20, grey
hline 0,0,black
vline 0,0,black
crosshairs black,1,0,0,1
parallel -5,-0.3,-5,0.3,10,0,2,black
parallel -0.3,-5,0.3,-5,0,10,2,black
text black , 5,-0.5,small , 5
text black , -5,-0.5,small , -5
text black , 0.3,-5,small , -5
text black , -0.5,5,small , 5
text black , -0.5,-0.3,small , O
text black , 0.8,-0.3,small , I
text black , -0.9,1.5,small , J
linewidth 1.5}

#if defined TARGET_lectequat
\text{image0=draw(300,300
\imgtemp
\trace
)}
#endif

#if defined TARGET_tracpar || TARGET_tracred
\text{image1=draw(300,300
\imgtemp
plot blue, \fonc[\liste[1]]
text red , -10,10,big , (1)
)}
\text{image2=draw(300,300
\imgtemp
plot blue, \fonc[\liste[2]]
text red , -10,10,big , (2)
)}
\text{image3=draw(300,300
\imgtemp
plot blue, \fonc[\liste[3]]
text red , -10,10,big , (3)
)}
\text{image4=draw(300,300
\imgtemp
plot blue, \fonc[\liste[4]]
text red , -10,10,big , (4)
)}
#endif
#if defined TARGET_tracpar
\text{eqstat=\fst=0}
#endif
#if defined TARGET_tracred
\text{eqstat=y=\f}
#endif

#if defined TARGET_tracpar || TARGET_tracred
::: sol :::

\integer{yb=(\type==1)?\b+\a:\b+\anum}
\integer{xb=(\type==1)? 1:\aden}
\text{imagecorr=draw(300,300
\imgtemp
plot blue, \fonc[\liste[\rep]]
crosshairs red,0,\b,\xb,\yb
text red , -10,10,big , Graphique \rep
)}
\text{list=<img src="\image1" alt="graphique 1" >,<img src="\image2" alt="graphique 2" >,<img src="\image3" alt="graphique 3" >,<img src="\image4" alt="graphique 4" >}
\text{rep0=\list[\rep]}
#endif

#if defined TARGET_lectequat
%%%sol
\integer{m3=\m1+\p}
\text{tracesol1=\cas==0 ? crosshair \q,2,red:crosshair \m2,\m3,red}
\text{tracesol2=\cas==0 ? crosshair \q,-2,green:crosshair 0,\p,green}
\if{\cas==1}{
\text{tracesol3=\m2>0 ? arrow 0,\p,\m2,\p,8,red:arrow \m2,\p,0,\p,8,red}
\text{tracesol4=arrow \m2,\p,\m2,\m3,8,green}}
\text{imagecorr=draw(300,300
\imgtemp
\tracesol1
\tracesol2
\tracesol3
\tracesol4
\trace)}

%%% fin sol
#endif

\statement{
#if defined TARGET_tracpar || TARGET_tracred
Cliquez sur la représentation graphique de la droite d'équation \(\eqstat).
<div class="wimscenter">\embed{r1}</div>
#endif

#if defined TARGET_lectequat
<p>Lire graphiquement l'équation de la droite tracée :</p>
<div class="wimscenter"><img src="\image0"  alt="graphique"></div>
<div class=wims_question>L'équation de la droite est  \embed{r1,7} \embed{r2,7}</div>
<div class=wims_instruction>Choisir le type d'équation et la compléter</div>
#endif
}


#if defined TARGET_tracpar || TARGET_tracred
\answer{}{\rep;\list}{type=click}{option=shuffle}
#endif
#if defined TARGET_lectequat
\answer{}{\rep1;x=,y=}{type=menu}
\answer{}{\rep2}{type=function}
#endif

\solution{
#if defined TARGET_tracpar || TARGET_tracred
<p>Plusieurs arguments peuvent être utilisés pour faire le choix.</p>

#if defined TARGET_tracpar
<p>Un méthode consiste à rechercher, pour chaque graphique, deux points de la droite qui sont à coordonnées entières. Puis de vérifier si les coordonnées de ces points vérifient l'équation donnée.</p>

<ul><li><p><b>Par exemple :</b> la droite passe par les points \(A(0;\b)) et \(B( \xb;\yb)) tracés en rouge sur le graphique.
</li><li>Les coordonnées de ces deux points vérifient l'équation de la droite \(\eqstat)
</li><li> c'est donc le bon graphique.
</li></ul>

#endif
#if defined TARGET_tracred
<p>L'ordonnée à l'origine est connu : \p . La droite doit donc passer par le point \(A(0;\b))</p>
<p>La droite passe aussi par le point de coordonnées \(B( \xb;\yb)), et puisque les coordonnées de ce point vérifient l'équation de la droite \(\eqstat), Le point \(B) appartient à la droite.</p>
<p><b>Conclusion</b> : La droite passe par les deux points \(A) et \(B) dont les coordonnées vérifient l'équation, c'est le bon graphique</p>
<p><em>Les points \(A) et \(B) sont tracés en rouge sur le graphique ci-dessous.</em></p>

#endif
#endif
#if defined TARGET_lectequat
\if{\cas=0}{<ul>
<li>La droite est parallèle à l'axe des ordonnées. Elle a donc une équation du type \( x = k), il faut déterminer la valeur de \(k).
</li><li>Tous les points de la droite ont la même abscisse.
</li><li>Pour exemple les deux points tracés en rouge et vert ont pour coordonnées \((\q;2)) et \((\q;-2))
</li><li>La droite a donc pour équation \(x=\q)
</li></ul> }{
<ul>
<li>La droite n'est pas parallèle à l'axe des ordonnées. Elle a donc une équation du type \( y = m x +p), il faut déterminer les valeurs de \(m) et de \(p).
</li><li>On repère l'ordonnée à l'origine en lisant l'ordonnée du point d'intersection avec l'axe des ordonnées. 
C'est le point vert d'ordonnée \p. L'<b>ordonnée à l'origine</b> est donc égale à \p. (\(p=\p))
</li><li>Puis on repère un second point sur la droite et sur le quadrillage, par exemple le point tracé en rouge qui a pour coordonnées\((\m2;\m3)).
</li><li>Puis on se déplace sur le quadrillage en comptant les unités et <b>en faisant attention au sens</b> : 
<ul><li>parallèlement à l'axe des abscisses : \(\m2) (<font class="red">flèche rouge </font>sur le graphique)
</li><li>parallèlement à l'axe des ordonnées : \(\m1) (<font class="green">flèche verte</font> sur le graphique)
</li><li>ce qui donne la valeur du <b>coefficient directeur</b> : \(\m1/\m2) (\(m=\m1/\m2))
</li></ul> 
</li><li>La droite a donc pour équation \(y=\f)
</li></ul>}
#endif

</p><center><img src="\imagecorr" alt="graphique" ></center>

}
