target=eqgrparabole1 eqgrparabole2 eqgrparabole3 eqgrparabole4 eqgrparabole5
#include "author.inc"
#include "lang_titles.inc"
%%%choix des coefficients entiers ou fractionnaires
#if defined TARGET_eqgrparabole5
\integer{den1=2}
\integer{den2=random(1,2)}
#else
\integer{den1=1}
\integer{den2=1}
#endif

%%%% couleur des grilles
\text{gridcolor=lightblue}

\text{listnbsol=Aucune solution, une solution, deux solutions, une infinité de solutions}

%%%% Choix du nombre de solutions
\integer{nbsol=random(0..2)}
#if defined TARGET_eqgrparabole1
\integer{nbsol=random(0,2)}
#endif
#if defined TARGET_eqgrparabole2
\integer{nbsol=2}
#endif
#if (defined TARGET_eqgrparabole4  || defined TARGET_eqgrparabole5 )
\integer{nbsol=randint(1,2)}
#endif
%%%%integer{nbsol=2}

%%%% choix du type de représentation
#if defined TARGET_eqgrparabole1
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR) par :
<div class="wimscenter" style="color:red">\(f(x) = x^2),</div>
  ainsi que la droite d'équation:}
\text{tintrocomp=}
#endif
#if defined TARGET_eqgrparabole2
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR) par :
<div class="wimscenter">\(f(x) = x^2),</div>
  ainsi que la fonction linéaire \(g_1) définie sur \(RR) par}
\text{tintrocomp=}
#endif
#if defined TARGET_eqgrparabole3
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR) par :
<div class="wimscenter">\(f(x) = x^2),</div>
  ainsi que la fonction affine \(g_1) définie sur \(\ \RR) par}
\text{tintrocomp=}
#endif
#if (defined TARGET_eqgrparabole4  || defined TARGET_eqgrparabole5 )
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR) par :
<div class="wimscenter">\(f(x) = x^2),</div>
  ainsi que les fonctions affines \(g_1) et \(g_2) définies sur \(\ \RR) par:}
\text{tintrocomp=Attention, il faut choisir la fonction affine intéressante parmi
  les deux présentes.}
#endif

\if{\nbsol=0}{
  \text{goodrep=vide}
#if defined TARGET_eqgrparabole1
  \rational{y0=randitem(-0.2,-0.5,-0.8,-1)}
  \text{g1=\y0}
  \text{equat=simplify(x^2 -\y0)}
  text{equat2=simplify(x^2 - \y0)}
#else
\integer{c=randint(1..5)}
\integer{d=randint(1..5)}
\integer{a=\c*(\c+\d)}
\integer{b=\c}
\integer{bb=\b}
\integer{c=\c+\d}
\integer{cc=\c}
\rational{br=simplify(\b/(\a))}
\rational{cr=simplify(\c/(\a))}
\integer{ix=random(1,2)}
%%%%integer{ix=2}
\text{sx=\ix=1?+:-}
\text{sc=+}
\text{smx=\ix=1?-:+}
\text{smc=-}
\function{f=x^2 \sx (\br)*x \sc (\cr)}
\text{equat=x^2}
text{equat2=x^2}
\text{s1=\b>0?+:-}
\integer{b=\b<0?\b*(-1)}
\text{s2=\c>0?+:-}
\integer{c=\c<0?\c*(-1)}
\if{\b !=0}{
   \rational{mbr=\br*(-1)}
   \text{equat=\equat \sx \br * x}
   text{equat2=\equat2 \sx \br  x}
   \text{g1=\smx (\br) * x}
   \text{g2=\sx (\br) * x}
  }{
   \text{g1=}
   \text{g2=}
  }
\if{\c !=0}{
   \text{equat=\equat \sc \cr}
   text{equat2=\equat2 \sc \cr}
   \text{g1=\g1 \smc \cr}
   \text{g2=\g2 \smc \cr}
  }
\integer{indsol=1}
#endif
 }{
%%%% Choix de l'équation à résoudre
\text{lstsing=wims(values x for x = -4 to 4)}
\text{lstsing=shuffle(\lstsing)}
\rational{sing1=\lstsing[1]}
\rational{sing1=\sing1=0?\lstsing[3]}
\integer{num1=\sing1}
\rational{sing1=\sing1/\den1}

\if{\nbsol=1}{
  \rational{sing2=\sing1}
  \integer{den2=\den1}
  \integer{num2=\num1}
  \integer{indsol=2}
  \text{goodrep=\sing1}
  }{
#if defined TARGET_eqgrparabole2
  \rational{sing2=0}
#else
  \rational{sing2=\lstsing[2]}
  \rational{sing2=\sing2=0?\lstsing[4]}
#endif
  \integer{num2=\sing2}
  \rational{sing2=\sing2/\den2}
  \rational{bs=\sing1+(\sing2)}
  \if{\bs=0}{
    \rational{sing2=\lstsing[3]}
    \integer{num2=\sing2}
    \rational{sing2=\sing2/\den2}
  }
  \integer{indsol=3}
  \if{\sing1=\sing2}{
    \integer{nbsol=1}
    \integer{indsol=2}
    \text{goodrep=\sing1}
  }{
    \text{goodrep=\sing1,\sing2}
  }
}
#if defined TARGET_eqgrparabole1
\integer{iY=randint(1..4)}
\text{yl=1,4,9,16}
\text{xl=1,-1,2,-2,3,-3,4,-4}
\rational{y0=\yl[\iY]}
\text{goodrep=\xl[\iY*2-1],\xl[\iY*2]}
\text{g1=\y0}
\text{equat=simplify(x^2 -\y0)}
text{equat2=texmath(x^2 - \y0)}
#else
\function{f=\den1*\den2*(x- (\sing1))*(x-(\sing2))}
\integer{a=\den1*\den2}
\integer{b=-\a*((\sing1)+(\sing2))}
\text{s1=\b>0?+:-}
\integer{b=\b<0?\b*(-1)}
\integer{c=\a*(\sing1)*(\sing2)}
\text{s2=\c>0?+:-}
\integer{c=\c<0?\c*(-1)}
\text{equat= \a*x^2}
text{equat2= \a x^2}
\if{\b !=0}{
  \text{equat=\equat \s1\b*x}
  text{equat2=\equat2 \s1 \b x}
}
\if{\c !=0}{
  \text{equat=\equat \s2 \c}
  text{equat2=\equat2 \s2 \c}
}
\function{g1=simplify(((\sing1)+(\sing2))*x -(\sing1)*(\sing2))}
\function{g2=simplify(-((\sing1)+(\sing2))*x +(\sing1)*(\sing2))}
#if defined TARGET_eqgrparabole5
\function{g2=simplify(\a*((\sing1)+(\sing2))*x -\a*(\sing1)*(\sing2))}
#endif
\text{eqaff=\g1}
#endif
}
\text{color=shuffle(green,blue,orange,purple)}

%%%%text{equat=maxima(\f)}

\text{indcol=shuffle(4)}
%%%%text{indcol=1,2,3,4}

\text{gt1=maxima(\g1)}
text{gt1=\(texmath(\gt1))}
\text{gt2=maxima(\g2)}
text{gt2=\(texmath(\gt2))}
\text{gt3=maxima(\g3)}
text{gt3=\(texmath(\gt3))}
\text{gt4=maxima(\g4)}
text{gt4=\(texmath(\gt4))}

\text{eqaff=\gt1}
text{eqaff=wims(replace * by in \eqaff)}
\text{lstaff=}
\text{lstaff=wims(append item \eqaff to \lstaff)}
\text{eqaff=\gt2}
text{eqaff=wims(replace * by in \eqaff)}
\text{lstaff=wims(append item \eqaff to \lstaff)}
\text{eqaff=\gt3}
text{eqaff=wims(replace * by in \eqaff)}
\text{lstaff=wims(append item \eqaff to \lstaff)}
\text{eqaff=\gt4}
text{eqaff=wims(replace * by in \eqaff)}
\text{lstaff=wims(append item \eqaff to \lstaff)}

\text{lstdraw=\g1,\g2,\g3,\g4}

#if defined TARGET_eqgrparabole1
\text{dessindte=plot \color[\indcol[1]],\g1}
\text{listeaff=<span style="color:\color[\indcol[1]]">\(y =\gt1\)</span>}
#endif
\text{indaff=shuffle(2)}
#if (defined TARGET_eqgrparabole2  || defined TARGET_eqgrparabole3 )
\text{dessindte=plot \color[\indcol[\indaff[1]]],\g1}
\text{listeaff=<span style="color:\color[\indcol[\indaff[1]]]">
  \(g_1(x)\) = \(\gt1\)</span>}
#endif
#if (defined TARGET_eqgrparabole4  || defined TARGET_eqgrparabole5 )
\text{dessindte=plot \color[\indcol[\indaff[1]]],\lstdraw[\indaff[1]]
  plot \color[\indcol[\indaff[2]]],\lstdraw[\indaff[2]]}
\text{listeaff=<span style="color:\color[\indcol[\indaff[1]]]">
    \(g_1(x)\) = \(\lstaff[\indaff[1]]\)</span><br>
  <span style="color:\color[\indcol[\indaff[2]]]">
    \(g_2(x)\) = \(\lstaff[\indaff[2]]\)</span>}
#endif

%%%% cadre générique %%%%
\text{cadre=
xrange -5,5
yrange -1.2,17
gridfill 0,0,5,5,\gridcolor
linewidth 1
linewidth 2
parallel -5,-1,-5,17,1,0,12,gray
parallel -5,-1,5,-1,0,1,19,gray
linewidth 2
vline 0,0,black
hline 0,0,black
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
linewidth 2
plot red,x^2
\dessindte
}
%%%% fin du cadre générique %%%%
\if{\nbsol>1}
 {\text{tindiquer=les solutions de l'équation (séparées par une virgule)}}
 {\text{tindiquer=la solution de l'équation}}

%%%% enoncé de l'exo %%%%
\statement{
  <div class="wims_columns">
 <div class="medium_size img_col">
\draw{400,400}{\cadre}</div>
 <div class="medium_size text_col">
  <div>\tintro</div>
  <div class="wimscenter">\listeaff.</div>
    Utiliser ce dessin pour résoudre graphiquement dans \(\ \RR\) l'équation:
    <div class="wimscenter">\(\equat =0\).</div>
  \if{\tintrocomp!=}{
    <div class="wims_instruction">\tintrocomp</div>}
  <p>
    Indiquer la ou les solutions de l'équation :
  </p>
    <div class="wimscenter"> <label for="reply1">\(S=)</label>\embed{reply1,5}</div>
  <div class="wims_instruction">
  Les solutions sont entières ou de la forme un entier +0.5.
  S'il n'y a pas de solution taper <span class="tt">vide</span>.
  S'il y a plusieurs solutions, les séparer par une virgule.
  </div>
  </div></div>
}

%%%% soumission de réponse %%%%
\answer{solution}{\goodrep}{type=fset}
