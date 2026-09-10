%% Nb de filles, taux de filles dans A, total candidats de A
\matrix{M=75,60,125
80,40,200
125,50,250
64,50,128
50,40,125
128,50,256
128,40,320}
\integer{n=randint(1..7)}

\integer{f=\M[\n;1]}
\integer{tfA=\M[\n;2]}
\integer{A=\M[\n;3]}
\integer{g=\A-\f}
\integer{tgA=100-\tfA}
%% Taux de réussite sur le collège A pour que le nombre d'élèves soit entier.
\text{ListR=}
\for{ i = 72 to 96}{
  \real{r=\A*\i/100-floor(\i*\A/100)}
  \if{\r=0}{\text{ListR=wims(append item \i to \ListR)}}
}
\integer{tAr=randitem(\ListR)}
\integer{Ar=\A*\tAr/100}

\integer{mfr=\Ar-\g}
\integer{fr=\mfr}

\text{ListF=}
\for{ j = \mfr to \f}{
  \integer{r=100*\j-\f*floor(100*\j/\f)}
  \if{\r=0}{\text{ListF=wims(append item \j to \ListF)}}
}
\integer{\fr=randitem(\ListF)}

\integer{gr=\Ar-\fr}
\real{tfr=100*\fr/\f}
\real{tgr=0.1*round(1000*\gr/\g)}
\integer{tgra=100*\tgr}
\real{tgra=\tgra/100}
\matrix{name_header=Filles,Garçons,Nombre
  Reçues,Reçus,Reçu(e)s
  Candidates,Candidats,Candidat(e)s
  Collège A
}

%% Tableau à remplir
\text{tabF=<table class="wimscenter wimsborder myred">
<tr><td>\name_header[1;1]</td><td>\name_header[1;3]</td><td>%</td></tr>
<tr><td>\name_header[2;1]</td><td>\fr</td><td>.... %</td></tr>
<tr><td>\name_header[3;1]</td><td>....</td><td>100 %</td></tr>
</table>
}
\text{tabG=<table class="wimscenter wimsborder myblue">
<tr><td>\name_header[1;2]</td><td>\name_header[1;3]</td><td>%</td></tr>
<tr><td>\name_header[2;2]</td><td>....</td><td>.... %</td></tr>
<tr><td>\name_header[3;2]</td><td>....</td><td>100 %</td></tr>
</table>
}
\text{tabT=<table class="wimscenter wimsborder mygreen">
<tr><td>\name_header[4;1]</td><td>\name_header[1;3]</td><td>%</td></tr>
<tr><td>\name_header[2;3]</td><td>....</td><td>\tAr %</td></tr>
<tr><td>\name_header[3;3]</td><td>\A</td><td>100 %</td></tr>
</table>
}
\text{tabA=<table class="wimscenter wimsborder mygreen">
<tr><td>\name_header[4;1]</td><td>\name_header[1;1] \tfA %</td><td>\name_header[1;2] .... %</td></tr>
<tr><td>\tabT</td><td>\tabF</td><td>\tabG</td></tr>
</table>
}

%% Tableau complet pour la solution
\text{tableauF=<table class="wimscenter wimsborder myred">
<tr><td>\name_header[1;1]</td><td>\name_header[1;3]</td><td>%</td></tr>
<tr><td>\name_header[2;1]</td><td>\fr</td><td>\tfr %</td></tr>
<tr><td>\name_header[3;1]</td><td>\f</td><td>100 %</td></tr>
</table>
}
\text{tableauG=<table class="wimscenter wimsborder myblue">
<tr><td>\name_header[1;2]</td><td>\name_header[1;3]</td><td>%</td></tr>
<tr><td>\name_header[2;2]</td><td>\gr</td><td>\tgra %</td></tr>
<tr><td>\name_header[3;2]</td><td>\g</td><td>100 %</td></tr>
</table>
}
\text{tableauT=<table class="wimscenter wimsborder mygreen">
<tr><td>\name_header[4;1]</td><td>\name_header[1;3]</td><td>%</td></tr>
<tr><td>\name_header[2;3]</td><td>\Ar</td><td>\tAr %</td></tr>
<tr><td>\name_header[3;3]</td><td>\A</td><td>100 %</td></tr>
</table>
}
\text{tableauS=<table class="wimscenter wimsborder mygreen">
<tr><td>\name_header[4;1]</td><td>\name_header[1;1] \tfA %</td><td>\name_header[1;2] \tgA %</td></tr>
<tr><td>\tableauT</td><td>\tableauF</td><td>\tableauG</td></tr>
</table>
}

%% Dessin à compléter
\integer{hF=floor(\tfA*0.4)+80}
\integer{hG=floor(\tgA*0.4)+40}

\text{graph = xrange -50,120
yrange 0,300
linewidth 2
comment Le collège A
rectangle 0,200,100,240, black
rectangle 0,200,70,240, green
fill 10,210,green
text black, -49, 230, giant, College A
text black, 30, 280, giant, \A candidats
text black, 20, 260, giant, \tAr % de reçus

comment Flèche
polygon black,20,150,50,120,80,150,60,150,60,180,40,180,40,150,20,150

comment Répartition G/F Filles
rectangle 0,80,100,\hF, red
rectangle 0,80,80, \hF, green
fill 10,82,green
text black, -50, 100, giant, Filles :
text black, -50, 90, giant, \tfA % des candidats
text green, 0, 120, giant,  \fr filles reçues

comment Répartition G/F Garçons
rectangle 0,40,100,\hG, blue
rectangle 0,40,60, \hG, green
fill 10,42,green
text black, -50, 60, giant, Garçons
text blue, 0, 30, giant, Pourcentage de reçus parmi les garçons ?
}

\text{url = draw(600,400
\graph)}

%% Dessin solution
\text{graphS = xrange -50,120
yrange 0,300
linewidth 2
comment Le collège A
rectangle 0,200,100,240, black
rectangle 0,200,\tAr,240, green
fill 10,210,green
text black, -49, 230, giant, College A
text black, 30, 280, giant, \A candidats
text black, 20, 260, giant, \tAr % de reçus soit \Ar reçus

comment Flèche
polygon black,20,150,50,120,80,150,60,150,60,180,40,180,40,150,20,150

comment Répartition G/F Filles
rectangle 0,80,100,\hF, red
rectangle 0,80,\tfr, \hF, green
fill 10,82,green
text black, -50, 100, giant, Filles :
text black, -50, 90, giant, \tfA % des candidats
text red, 0, 120, giant,  \fr filles reçues soit \tfr % des filles.

comment Répartition G/F Garçons
rectangle 0,40,100,\hG, blue
rectangle 0,40,\tgr, \hG, green
fill 10,42,green
text black, -50, 60, giant, Garçons :
text black, -50, 50, giant, \tgA % des candidats
text blue, 0, 30, giant,  \gr garçons sont reçus soit \tgra % des garçons.
}

\text{url1 = draw(600,400
\graphS )}

%%Schéma à compléter
\text{Sch1 = xrange -5,155
yrange -5,155
linewidth 3
rectangle 0,0,150,150,green
text green, 40,140, giant, \A candidats
rectangle 10,20,60,120, red
text red, 30,100,giant, filles
text red, 15,60,giant, \fr reçues
text red, 15,50,medium, soit________%
text red, 15,40,medium,des filles
rectangle 90,20,140,120, blue
text blue, 110,100,giant,garçons
text blue, 110,60,giant,reçus
text blue, 95,50,medium, soit_______%
text blue, 95,40,medium,des garçons
rectangle 5,5,147,70,black
text green, 25,19,medium, \tAr % des candidats sont reçus
text green, 15,90,medium, \tfA %
text green, 15,80,medium, des candidats
text black, 74,14,medium,reçus
}

\text{url2 = draw(320,320
\Sch1)}

\text{Sch1S=\Sch1
text red, 12,100,giant, \f
text blue, 92,100,giant,\g
text blue, 94,60,giant,\gr
text red, 40,50,medium, \tfr
text blue, 110,50,medium, \tgra
text black, 61,14,medium,\Ar
text green, 100,90,medium, \tgA %
text green, 92,80,medium, des candidats
}
\text{url3 = draw(320,320
\Sch1S)}

\text{Sch2 = xrange -10,590
yrange -10,490
linewidth 3
arrow 88,200,168,400,10,black
arrow 88,200,168,0,10,black
arrow 248,400,320,400,10,black
arrow 248,0,320,0,10,black
segment 248,-8,248,8, black
segment 248,392,248,408, black
segment 88,190,88,210, black

text green, 0,220, giant, \A candidats
text green, 108,360,giant, \tfA %
text red, 200,420,giant, filles
text red, 328,420,giant, \fr reçues
text red, 288,480,giant, %
text blue, 200,40,giant, garçons
text blue, 352,40,giant,  reçus
text blue, 288,80,giant, %
arc 390,300,20,200,0,90,black
arc 410,300,20,200,180,270,black
arc 410,100,20,200,90,180,black
arc 390,100,20,200,270,360,black

text black, 448,210,giant,reçus
}
\text{url4 = draw(900,200
\Sch2)}
\text{Sch2S =\Sch2
text green, 108,100,giant, \tgA %
text red, 258,480,giant, \tfr
text red, 170,420,giant, \f
text blue, 328,40,giant, \gr
text blue, 258,80,giant, \tgr
text blue, 170,40,giant, \g
text black, 418,210,giant,\Ar
}
\text{url5 = draw(900,200
\Sch2S)}
