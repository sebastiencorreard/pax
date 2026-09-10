target=rootinterv

\title{Racines contenues dans un intervalle}
\language{fr}
\range{-5..5}
\author{Marie-Claude, David;Gérard, Lauton}
\email{lauton@u-pec.fr}
\computeanswer{no}
\format{html}
\precision{10000}
\description{Compter des racines dans un intervalle sans les calculer}
\keywords{trinomial, roots, interval, order}

%% Matrice : ligne 1 = dénominateurs lignes 2 à 8 numérateurs %%
\matrix{M=2,3,5;1,1,1;3,2,2;5,4,3;7,5,4;9,7,6;11,8,7;13,10,8}

% Tirages aléatoires de deux N° de lignes et de deux N° de colonnes %
\integer{j1=randint(1..3)}
\integer{j2=randint(1..3)}
\integer{i1=randint(2..8)}
\integer{i2=randint(2..8)}

% TIrage aléatoires de deux signes des racines %
\integer{s1=randitem(-1,1)}
\integer{s2=randitem(-1,1)}

% Numérateurs et dénominateurs des deux racines %
\integer{n1=\M[\i1;\j1]}
\integer{n2=\M[\i2;\j2]}
\integer{d1=\M[1;\j1]}
\integer{d2=\M[1;\j2]}

% Les deux racines r et s %
\rational{r=\s1*\n1/\d1}
\rational{s=\s2*\n2/\d2}

\rational{P=\r*\s}
\rational{S=\r+\s}
\rational{DS=\S/2}
\rational{D=\s-\r}
\rational{Q=\S*\P}

% Écarter des racines opposées, nulles ou trop proches %
\while{\Q=0 or \D<3}
{
\integer{j1=randint(1..3)}
\integer{j2=randint(1..3)}
\integer{i1=randint(2..8)}
\integer{i2=randint(2..8)}

\integer{s1=randitem(-1,1)}
\integer{s2=randitem(-1,1)}

\integer{n1=\M[\i1;\j1]}
\integer{n2=\M[\i2;\j2]}
\integer{d1=\M[1;\j1]}
\integer{d2=\M[1;\j2]}

\rational{r=\s1*\n1/\d1}
\rational{s=\s2*\n2/\d2}

\rational{P=\r*\s}
\rational{S=\r+\s}
\rational{DS=\S/2}
\rational{D=\s-\r}
\rational{Q=\S*\P}
}

\integer{signPS=\P<0 and \S<0?-1:1}

%% racines r et s par ordre croissant %%

\rational{t=\r}
\rational{r=min(\r,\s)}
\rational{s=max(\t,\s)}

%% Valeurs approchées entières et signes de r et s  %%
\integer{dr=floor(\r)}
\integer{ds=floor(\s)}
\integer{er=ceil(\r)}
\integer{es=ceil(\s)}
\text{Sr=\r<0?-:+}
\text{Ss=\s<0?-:+}

%% Affichage des racines comme fractions %%
\text{rF=texmath(simplify(\r))}
\text{sF=texmath(simplify(\s))}

Coefficients a, b et c et calcul du trinôme
\integer{a=\d1*\d2}
\integer{a=\signPS * \a}
\rational{b=-\a*\S}
\rational{c=\a*\P}
\function{F=\a*x^2+\b*x+\c}
\text{TR=pari(\a*(x-(\r))*(x-(\s)))}

%% Valeurs candidates des bornes c et d %%
% Tirages de valeurs possibles : y1 < r, r < y2 < s, y2 < y3 < s et y4 > s  %
\integer{y1=randint(\dr -5 .. \dr)}
\integer{y2=randint(\er .. \ds -1)}
\integer{y3=randint(\y2 +1 .. \ds)}
\integer{y4=randint(\es .. \es + 5)}

% Choix aléatoire de 2 valeurs parmi 4 = bornes c et d %
\matrix{Y=\y1,\y2,\y3,\y4}
\integer{p=randint(1..3)}
\integer{q=randint(\p+1 ..4)}
\integer{c=\Y[\p]}
\integer{d=\Y[\q]}

%% Paramètres et affichages fractions %%
\text{DSF=texmath(simplify(\DS))}
\rational{DSc=\DS-\c}
\rational{DSd=\DS-\d}
\rational{DScd=\DSc*\DSd}
\text{DScF=texmath(simplify(\DSc))}
\text{DSdF=texmath(simplify(\DSd))}

%% Valeurs du trinôme pour x = c et d %%
\rational{Tc=evalue(\TR,x=\c)}
\rational{Td=evalue(\TR,x=\d)}
\rational{Tcd=\Tc*\Td}

\rational{aTc=\a*\Tc}
\rational{aTd=\a*\Td}

\text{TcF=texmath(simplify(\Tc))}
\text{TdF=texmath(simplify(\Td))}
\text{aTcF=texmath(\aTc)}
\text{aTdF=texmath(\aTd)}

%% Six cas de figure de disposition de [r,s] par rapport à [c,d]
% n° T = 1,2,3,4,5,6  %%

\rational{crs=(\c-\r)*(\c-\s)}
\rational{drs=(\d-\r)*(\d-\s)}

\text{liste=
\({r < s < \c < \d}\),\({\c < \d < r < s}\),\({r < \c < s < \d}\),\({\c < r < \d < s}\),\({r < \c < \d < s}\),\({\c < r < s < \d}\)}

\if{\s < \c}{\text{T = 1}}
\if{\d < \r}{\text{T = 2}}
\if{\crs < 0 and \s < \d}{\text{T = 3}}
\if{\c < \r and \drs < 0}{\text{T = 4}}
\if{\crs < 0 and \drs < 0}{\text{T = 5}}
\if{\c < \r and \s < \d}{\text{T = 6}}

%% Textes de la solution selon le cas de figure %%
\if{\T=1 or \T=2}{
\integer{C=0}
\text{signDSmoinsalpha=\T=1? négatif:positif}
\text{sol=Elles sont de mêmes signes et les produits
\(a \times T(\alpha)=(\a) \times T(\c) = \aTc\) et
\(a \times T(\beta)=\a \times T(\d) = \aTd\) sont tous deux positifs.
Pour en savoir plus, il faut situer l'intervalle \(\lbrack \c,\d\rbrack\)
par rapport à la demi-somme des racines \(-\frac{b}{2a} = \DSF\).
<p>Pour cela, on observe les différences
\(\left(-\frac{b}{2a}-(\alpha)\right)=\DSF-(\c)=\DScF\)
et \(\left(-\frac{b}{2a}-\beta\right)=\DSF-(\d)=\DSdF\).
Elles sont de mêmes signes \signDSmoinsalpha. Donc les bornes \(\alpha=\c\)
et \(\beta=\d\) sont situées d'un même côté de l'intervalle des racines.
Avec ces données :</p>
<ul><li>Le trinôme \(T\) a \(0\) racine dans
\(\lbrack \c,\d\rbrack\).</li>
<li>Le bon ordre des termes est \liste[\T].</li></ul>
}}

\if{\T=3 or \T=4}{
\integer{C=1}
\if{\aTc >0}
{\text{SolSignaTc=positif, donc la borne \(\alpha=\c\) est hors de l'intervalle
  des racines et la borne \(\beta=\d\) est dedans}}
{\text{SolSignaTc=négatif, donc la borne \(\alpha=\c\) est dans l'intervalle
  des racines et la borne \(\beta=\d\) est en dehors}}
\text{sol=Elles sont de signes contraires. On en déduit que l'une des bornes
  \(\alpha=\c\) ou \(\beta=\d\) est entre les deux racines et l'autre à l'extérieur.
  Le nombre de racines dans l'intervalle donné est donc égal à \(1\).
<p>Comme l'image \(T(\c) = \Tc\) est du signe opposé de celui de \(a\),
  la borne \(\alpha=\c\) est entre les racines et la borne \(\beta=\d\) en
  dehors de l'intervalle des racines. On en déduit l'ordre ci-dessous des bornes
  de l'intervalle et des deux racines.
Avec ces données :</p>
<ul><li>Le trinôme \(T\) a \(1\) racine dans
\(\lbrack \c,\d\rbrack\).</li>
<li>Le bon ordre des termes est \liste[\T].</li></ul>}}
\if{\T=5}{
\integer{C=0}
\text{sol=Elles sont de mêmes signes et les produits
\(a \times T(\alpha)=(\a) \times T(\c) = \aTc\) et
\(a \times T(\beta)=\a \times T(\d) = \aTd\) sont tous deux négatifs.
<p>On en déduit que l'intervalle donné \(\lbrack \c,\d\rbrack\)
est strictement contenu dans celui des racines \(\lbrack r,s\rbrack\).
Avec ces données :</p>
<ul><li>Le trinôme \(T\) a \(0\) racines dans
\(\lbrack \c,\d\rbrack\).</li>
<li>Le bon ordre des termes est \liste[\T].</li></ul>}}
\if{\T = 6}{
\integer{C=2}
\if{\aTc > 0 and \aTd > 0}{\text{SignaTcaTd=positifs}}
\if{\aTc < 0 and \aTd < 0}{\text{SignaTcaTd=négatifs}}
\text{sol=Elles sont de mêmes signes. De plus, les produits
\(a \times T(\alpha)=(\a) \times \Tc = \aTc\) et
\(a \times T(\beta)=(\a) \times \Td = \aTd\) sont tous deux \SignaTcaTd.
<p>On en déduit que l'intervalle donné
\(\lbrack \alpha , \beta\rbrack = \lbrack \c , \d\rbrack\)
contient les deux racines \(r\) et \(s\).
Avec ces données :</p>
<ul><li>Le trinôme \(T\) a \(2\) racines dans
\(\lbrack \c,\d\rbrack\).</li>
<li>Le bon ordre des termes est \liste[\T].</li></ul>}}

%% Dessin %%
\rational{Tm=evalue(\TR,x=\DS)}
\text{TmF=texmath(simplify(\Tm))}
\real{d2Tm=rint(100*\Tm)/100}

% dimensions et réglages du cadre %
\rational{Xmini=min(\r,\s)}
\rational{Xmini=min(\Xmini,\c)}
\rational{Xmini=min(\Xmini,\d)}
\rational{Xmini=min(\Xmini,-2)-2}
\rational{Xmini=ceil(\Xmini)}
\rational{Xmaxi=max(\r,\s)}
\rational{Xmaxi=max(\Xmaxi,\c)}
\rational{Xmaxi=max(\Xmaxi,\d)}
\rational{Xmaxi=max(\Xmaxi,2)+2}
\rational{Xmaxi=floor(\Xmaxi)}

\rational{Tmini=min(\Tc,\Td)}
\rational{Tmini=min(\Tmini,\Tm)}
\rational{Tmaxi=max(\Tc,\Td)}
\rational{Tmaxi=max(\Tmaxi,\Tm)}

\integer{RTmini=floor(\Tmini)-5}
\integer{RTmaxi=ceil(\Tmaxi)+5}

\if{\Tcd<0}{}{
\rational{ATmini=abs(\Tmini)}
\rational{ATmaxi=abs(\Tmaxi)}
\rational{RTmini=-max(\ATmini,\ATmaxi)}
\rational{RTmaxi=-\RTmini}
}

% Amplitudes du cadre %
\integer{RTmini=floor(\RTmini)-5}
\integer{RTmaxi=ceil(\RTmaxi)+5}
\integer{Xcad=\Xmaxi-\Xmini}
\integer{Tcad=\RTmaxi-\RTmini}

% Paramètre de position d'une légende du dessin %
\integer{tt=\a>0?-1:1}

% Paramètres de points du dessin %
\rational{uu=\Tcad/25}
\rational{vv=\tt*\uu}
\rational{xFF=\DS}
\real{d2Tm=rint(100*\Tm)/100}
\real{DS2=rint(100*\DS)/100}

\rational{yFF=\a<0?\RTmini+2*\uu:\RTmaxi-2*\uu}
\rational{yS=\yFF-\uu}
\rational{ymc=\Tc<0?\uu:-\uu}
\rational{ypd=\Td<0?\uu:-\uu}

%% Composition du dessin %%
\text{repere =
xrange \Xmini,\Xmaxi
yrange \RTmini,\RTmaxi
parallel \Xmini,\RTmini,\Xmini,\RTmaxi,1,0,\Xcad,grey
parallel \Xmini,\RTmini,\Xmaxi,\RTmini,0,1,\Tcad,grey
hline 0,0,black
arrow 0,0,1,0,10, black
arrow 0,0,0,1,10, black
vline 0,0,black}

\text{parabole =
\repere
text green,\xFF,\yFF,medium,F(x)=\TR
text blue,\xFF,\yFF-\uu,medium,S(\DS2,\d2Tm)
plot green,\F
fcircle \DS,0,10,blue
fcircle \DS,\Tm,10,blue
fcircle \r,0,10,black
fcircle \s,0,10,black
text blue,\DS,\Tm+\vv,medium,S
dsegment \DS,0,\DS,\Tm,blue
dsegment 0,\Tm,\DS,\Tm,blue
text red,\c,\ymc,medium,\c
text red,\d,\ypd,medium,\d
linewidth 3
dsegment \c,0,\c,\Tc,red
dsegment \d,0,\d,\Td,red
fcircle \c,0,10,red
fcircle \d,0,10,red
fcircle \c,\Tc,10,red
fcircle \d,\Td,10,red
linewidth=4
dsegment \c,0,\d,0,red}

\if{\DS=\DS2 and \Tm=\d2Tm}{\text{sommet=\(S \left(\DSF\; ;\;\TmF\right)\)}}
{\text{sommet=\(S \left(\DSF\; ;\;\TmF\right)\) c'est-à-dire \(S\; (\DS2\; ;\d2Tm)\) avec 2 décimales.}}

\text{name_hint1=On rappelle qu'un trinôme \(a\; x^2+b\; x+c\) est du signe de \(-a\)
  entre les racines et du signe de \(a\) à l'extérieur des racines.}
\text{name_hint2=La valeur de la demi-somme des racines \(-\frac{b}{2a}\)
  peut être utile pour placer les bornes \({\alpha}\) et \({\beta}\)
  de l'intervalle donné par rapport aux racines.}

\statement{
<div class="wims_instruction">
  Pour résoudre cet exercice, on ne calculera pas les racines. On raisonnera
  à partir des valeurs du trinôme en certains points.</div>
  Soit le trinôme \(T\) défini par \(T(x) =\TR\).
      <div class="wims_question">
  <ol><li><label for="reply1">Le nombre de racines du trinôme appartenant
  à l'intervalle
  \(\lbrack \alpha , \beta \rbrack = \lbrack \c , \d \rbrack\)
  vaut </label> \embed{reply1,3}.</li>
  <li>La disposition des racines \(r\) et \(s\) \({(r < s)}\)
  par rapport à cet intervalle est :
  <fieldset>
<legend><em>Cliquer sur la bonne disposition :</em></legend>
<ul style="list-style-type:none;">
  <li>\embed{reply2,1}</li>
  <li>\embed{reply2,2}</li>
  <li>\embed{reply2,3}</li>
  <li>\embed{reply2,4}</li>
  <li>\embed{reply2,5}</li>
  <li>\embed{reply2,6}</li>
</ul>
</fieldset>
</li>
</ol>
</div>
}
\answer{Nombre de racines}{\C}{type=numeric}
\answer{Disposition}{\T;\liste}{type=radio}{option=shuffle}

\hint{\name_hint1 \name_hint2}

\solution{<p> \name_hint1
  On calcule tout d'abord les images \(T(\alpha) = \TcF\) et
  \(T(\beta) = \TdF\) des bornes de l'intervalle donné
  \(\lbrack \alpha , \beta\rbrack = \lbrack \c , \d\rbrack\)
  (traits en pointillé <span style="color:red">rouge</span>
  sur la parabole représentant le trinôme).</p>
<p>\sol</p>
<p class="wimscenter">La demi-somme des racines est l'abscisse du
sommet de la parabole, soit :</p>
<p class="wimscenter">\sommet.</em></p>
<p class="wimscenter">\draw{500,500}{\parabole}</p>
<p class="wimscenter"><em>On a résolu l'exercice sans calculer les racines
de ce trinôme. Elles sont ici égales à \(r = \rF\) et \(s = \sF\).</em></p>
}
