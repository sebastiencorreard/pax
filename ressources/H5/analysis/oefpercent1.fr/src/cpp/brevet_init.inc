\matrix{name_header=Collège A,Collège B,Collège C,Tous les collèges,Élèves,Total
Nombre de candidats,Nombre de reçus,Pourcentage de reçus}

\integer{a=110+20*randint(0..4)}
\integer{b=220+50*randint(0..4)}
\integer{c=40+10*randint(0..4)}
\integer{t1=80}
\integer{t2=70}
\integer{t3=90}
\integer{ar=\a*\t1/100}
\integer{br=\b*\t2/100}
\integer{cr=\c*\t3/100}
\integer{g=\a+\b+\c}
\integer{gr=\ar+\br+\cr}
\real{tgd=\gr/\g}
\real{tg=100*\tgd}
\integer{tga=round(\tg)}
\real{tg1=\tg-1}
\real{tg2=\tg+1}

\integer{xM=\b+20}

%% Fond du dessin
\text{graph = xrange -5,\xM
yrange 0,120
linewidth 2
comment Le collège A
rectangle 0,90,\a,100, black
rectangle 0,90,\ar, 100, green
fill 10,95,green
text black, 20, 115, giant, College A
text black, 30, 110, giant, \a candidats
text black, 20, 88, giant, \t1 %
comment Le collège B
rectangle 0,50,\b,60, black
rectangle 0,50,\br, 60, green
fill 10,55,green
text black, 20, 75, giant, College B
text green, 10, 65, giant, \br reçus
text black, 80, 70, giant, \b candidats
comment Le collège C
rectangle 0,10,\c,20, black
rectangle 0,10,\cr, 20, green
fill 10,15,green
text black, 20, 35, giant, College C
text green, 0, 25, giant, \cr reçus
text black, 10, 8, giant, \t3 %
}

\text{url = draw(600,400
\graph)}
\text{urlt = Trois rectangles de longueurs différentes représentent les trois collèges avec une partie verte à l'intérieur pour représenter les reçus.}


%% Tableau vide
\text{tableau1=<table class="wimscenter wimsborder">
<tr><td></td><th>\name_header[1]</th><th>\name_header[2]</th><th>\name_header[1;3]</th></tr>
<tr><th>\name_header[2;1]</th><td>\a</td><td>\b</td><td></td></tr>
<tr><th>\name_header[2;2]</th><td></td><td>\br</td><td>\cr</td></tr>
<tr><th>\name_header[2;3]</th><td>\t1 %</td><td></td><td>\t3 %</td></tr>
</table>
}


%% Tableaux de proportionnalité
\text{tableauA=<table class="wimscenter wimsborder">
<tr><th>\name_header[1;1]</th><th>\name_header[1;5]</th><th>%</th></tr>
<tr><th>\name_header[2;1]</th><td>\a</td><td>100</td></tr>
<tr><th>\name_header[2;2]</th><td></td><td>\t1</td></tr>
</table>
}
\text{tableauB=<table class="wimscenter wimsborder">
<tr><th>\name_header[1;2]</th><th>\name_header[1;5]</th><th>%</th></tr>
<tr><th>\name_header[2;1]</th><td>\b</td><td>100</td></tr>
<tr><th>\name_header[2;2]</th><td>\br</td><td></td></tr>
</table>
}
\text{tableauC=<table class="wimscenter wimsborder">
<tr><th>\name_header[1;3]</th><th>\name_header[1;5]</th><th>%</th></tr>
<tr><th>\name_header[2;1]</th><td></td><td>100</td></tr>
<tr><th>\name_header[2;2]</th><td>\cr</td><td>\t3</td></tr>
</table>
}

\text{tableauG=<table class="wimscenter wimsborder">
<tr><th>\name_header[1;4]</th><th>\name_header[1;5]</th><th>%</th></tr>
<tr><th>\name_header[2;1]</th><td></td><td>100</td></tr>
<tr><th>\name_header[2;2]</th><td></td><td></td></tr>
</table>
}

\text{fa=\(\frac{...}{\a}=\frac{\t1}{100})}
\text{fb=\(\frac{\br}{\b}=\frac{...}{100})}
\text{fc=\(\frac{\cr}{...}=\frac{\t3}{100})}
\text{fg=\(\frac{... + \br + \cr}{\a + \b + ...}=\frac{...}{100})}

\text{fgs=\(\frac{\ar + \br + \cr}{\a + \b + \c} = \frac{\gr}{\g} \approx \tgd = \frac{\tg}{100})}

\text{opa=Pour calculer \t1 % de \a, on multiplie \a par \t1/100. }
\text{opb=Pour obtenir \br à partir de \b, on a multiplié \b par \(\frac{\br}{\b}) donc \(\frac{p}{100}=\frac{\br}{\b}).}
\text{opc=On a obtenu \cr en multipliant un nombre inconnu \(x) par \(\frac{\t3}{100}) donc \(\frac{\t3}{100} x = \cr).}
