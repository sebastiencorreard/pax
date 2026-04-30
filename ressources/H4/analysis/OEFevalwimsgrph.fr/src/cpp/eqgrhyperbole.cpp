target=eqgrhyperbole1 eqgrhyperbole2 eqgrhyperbole3 eqgrhyperbole4 eqgrhyperbole5
#include "author.inc"
#include "lang_titles.inc"
%%%choix des coefficients entiers ou fractionnaires
#if defined TARGET_eqgrhyperbole5
\integer{den1=2}
\integer{den2=randitem(1,2)}
#else
\integer{den1=1}
\integer{den2=1}
\integer{num2=1}
#endif

%%%% couleur des grilles
\text{gridcolor=lightblue}

\text{listnbsol=Aucune solution, une solution, deux solutions, une infinité de solutions}

#if defined TARGET_eqgrhyperbole2
\text{typeg1=linéaire}
#endif
#if defined TARGET_eqgrhyperbole3
\text{typeg1=affine}
#endif

%%%% Choix du nombre de solutions
\integer{nbsol=randint(0..2)}
#if defined TARGET_eqgrhyperbole1
\integer{nbsol=randint(0,1,1,1)}
#endif
#if defined TARGET_eqgrhyperbole2
\integer{nbsol=randint(0,2)}
#endif
#if (defined TARGET_eqgrhyperbole4 || defined TARGET_eqgrhyperbole5 )
\integer{nbsol=randint(1,2)}
#endif
%%%%integer{nbsol=2}

#if defined TARGET_eqgrhyperbole1
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR) par :
<div class="wimscenter" style="color:red">\(f(x) = \frac{1}{x}),</div>
  ainsi que la droite d'équation:}
\text{tintrocomp=}
#endif
#if (defined TARGET_eqgrhyperbole2  || defined TARGET_eqgrhyperbole3 )
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR\) par :
<div class="wimscenter" style="color:red">\(f(x) = \frac{1}{x}),</div>
  ainsi que la fonction \typeg1 \(g_1) définie sur \(\ \RR\) par:}
\text{tintrocomp=}
#endif
#if (defined TARGET_eqgrhyperbole4  || defined TARGET_eqgrhyperbole5 )
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR\) par
<div class="wimscenter">\(f(x) = \frac{1}{x}).</div>
  ainsi que les fonctions affines \(g_1) et \(g_2) définies sur \(\ \RR\) par}
\text{tintrocomp=Attention, il faut choisir la fonction affine intéressante parmi les deux présentes.}
#endif

\if{\nbsol=0}{
  \text{goodrep=vide}
#if defined TARGET_eqgrhyperbole1
\rational{y0=0}
\text{g1=\y0}
\text{equat= 1/x}
text{equat2= texmath(1/x) }
#else
\integer{c=randint(1..5)}
\integer{d=randint(1..5)}
\integer{a=\c*(\c+\d)}
# if defined TARGET_eqgrhyperbole2
\integer{b=0}
# else
\integer{b=\c}
# endif
\integer{bb=\b}
\integer{c=\c+\d}
\integer{cc=\c}
\rational{ar=simplify(\a/(\c))}
\rational{br=simplify(\b/(\c))}
\integer{ix=randitem(1,2)}
%%%%integer{ix=2}
\text{sx=\ix=1?+:-}
\text{sc=+}
\text{smx=\ix=1?-:+}
\text{smc=-}
\function{f=\ar*x \sx (\br) \sc (\c)/x}
\text{equat= \ar*x }
text{equat2= \ar x }
# if defined TARGET_eqgrhyperbole5
\function{f=\a*x \sx (\b) \sc (\c)/x}
\text{equat= \a*x }
text{equat2= \a x }
# endif
\text{s1=\b>0?+:-}
\integer{b=\b<0?\b*(-1)}
\text{s2=\c>0?+:-}
\integer{c=\c<0?\c*(-1)}
# if defined TARGET_eqgrhyperbole5
   \text{g1=-(\ar) * x}
   \text{g2=-(\a) * x}
   \text{g3= (\ar) * x}
   \text{g4= (\a) * x }
# else
   \text{g1=-(\ar) * x}
   \text{g2= (\ar) * x}
   \text{g3=- (\ar) * x}
   \text{g4= (\ar) * x }
# endif
\if{\b !=0}{
   \rational{mbr=\br*(-1)}
# if defined TARGET_eqgrhyperbole5
   \text{equat=\equat \sx \b }
   text{equat2=\equat2 \sx \b  }
   \text{g1=\g1 \smx (\br)}
   \text{g2=\g2 \smx (\b) }
   \text{g3=\g3 \sx (\br)}
   \text{g4=\g4 \sx (\b) }
# else
   \text{equat=\equat \sx \br  }
   text{equat2=\equat2 \sx \br  }
   \text{g1=\g1 \smx (\br)}
   \text{g2=\g2 \sx (\br) }
   \text{g3=\g3 \sx (\br)}
   \text{g4=\g4 \smx (\br) }
# endif
  }
# if defined TARGET_eqgrhyperbole5
   \text{equat=\equat \s2 \c/x }
   text{equat2=\equat2 \sc \frac{\c}{x} }
# else
   \text{equat=\equat \s2 1/x }
   text{equat2=\equat2 \sc \frac{1}{x} }
# endif
#endif
\integer{indsol=1}
 }{
%%%% Choix de l'équation à résoudre
\text{lstsing=wims(values x for x = 1 to 4),wims(values -x for x=1 to 4)}
\text{lstsing=shuffle(\lstsing)}
\rational{sing1=\lstsing[1]}
\integer{num1=\sing1}
\rational{sing1=\sing1/\den1}

\if{\nbsol=1}{
  \rational{num1=\sing1=1?2*\num1}
  \rational{sing1=\sing1=1?\num1/\den1}
  \rational{sing2=\sing1}
  \integer{den2=\den1}
  \integer{num2=\num1}
  \rational{cs=(\num1)*(\num2)}
  \if{\cs=1}{
    \rational{sing1=2*\sing1}
    \rational{sing2=2*\sing2}
    \rational{num1=2*\num1}
    \rational{num2=2*\num2}
  }
   \integer{indsol=2}
   \text{goodrep=\sing1}
  }{
#if defined TARGET_eqgrhyperbole2
  \rational{sing2=-1*\sing1}
#else
  \rational{sing2=\lstsing[2]}
  \integer{num2=\sing2}
  \rational{sing2=\sing2/\den2}
  \rational{bs=\sing1+(\sing2)}
  \if{\bs=0}{
    \rational{sing2=\lstsing[3]}
    \integer{num2=\sing2}
    \rational{sing2=\sing2/\den2}
  }
#endif
  \rational{cs=(\num1)*(\num2)}
  \if{\cs=1}{
     \rational{sing1=2*\sing1}
     \rational{sing2=2*\sing2}
     \rational{num1=2*\num1}
     \rational{num2=2*\num2}
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
#if defined TARGET_eqgrhyperbole1
\text{xl=-2,-1,-0.5,0.5,1,2}
\text{yl=-\frac{1}{2},-1,-2,2,1,\frac{1}{2}}
\text{ylv=-0.5,-1,-2,2,2,0.5}
\text{ylm=+\frac{1}{2},+1,+2,-2,-1,-\frac{1}{2}}
\integer{iY=randint(1..6)}
\text{y0=\yl[\iY]}
\text{y0v=\ylv[\iY]}
\text{y0m=\ylm[\iY]}
\text{g1=\y0v}
\text{equat= \frac{1}{x} \y0m }
\text{equat2= \frac{1}{x} \y0m }
\text{goodrep=\xl[\iY]}
#else
\function{f=\den1*\den2*(x- (\sing1))*(x-(\sing2))}
\integer{a=\den1*\den2}
\integer{b=-\a*((\sing1)+(\sing2))}
\text{sb=\b>0?+:-}
\text{smb=\b<0?+:-}
\integer{c=\a*(\sing1)*(\sing2)}
\text{sc=\c>0?+:-}
\text{smc=\c<0?+:-}
\integer{bc=\b*\c}
\text{sbc=\bc>0?+:-}
\text{smbc=\bc<0?+:-}

\integer{b=\b<0?\b*(-1)}
\integer{c=\c<0?\c*(-1)}
\rational{ar=simplify(\a/(\c))}
\rational{br=simplify(\b/(\c))}
# if defined TARGET_eqgrhyperbole5
\text{equat=\a=1?x: \a*x }
\text{equat2=\a=1?x: \a x }
\text{g1=\smc(\ar) * x}
\text{g2=\smc(\a) * x}
\text{g3=\sc (\ar) * x}
\text{g4=\sc (\a) * x }
# else
\text{equat=\ar=1?\sc x: \sc \ar*x }
text{equat2=\ar=1? \sc x: \sc \ar x }
\text{g1=\smc(\ar) * x}
\text{g2=\sc (\ar) * x}
\text{g3=\smc (\ar) * x}
\text{g4=\sc (\ar) * x }
# endif
\if{\b !=0}{
# if defined TARGET_eqgrhyperbole5
  \text{equat=\equat \sb \b }
  text{equat2=\equat2 \sb \b }
  \text{g1=\g1 \smbc (\br)}
  \text{g2=\g2 \smb (\b) }
  \text{g3=\g3 \sbc (\br)}
  \text{g4=\g4 \sb (\b) }
# else
  \text{equat=\equat \sbc \br }
  text{equat2=\equat2 \sbc \br}
  \text{g1=\g1 \smbc (\br)}
  \text{g2=\g2 \sbc (\br) }
  \text{g3=\g3 \sbc (\br)}
  \text{g4=\g4 \smbc (\br) }
# endif
  }
# if defined TARGET_eqgrhyperbole5
  \text{equat=\equat \sc \c/ x }
  text{equat2=\equat2 \sc \frac{\c}{x} }
# else
  \text{equat=\equat + 1/ x }
  text{equat2=\equat2 + \frac{1}{x} }
# endif
#endif
  \text{eqaff=\g1}
}
\text{color=shuffle(green,blue,orange,purple)}

%%%%text{equat=maxima(\f)}
\text{equat=\equat =0}
\text{indcol=shuffle(4)}

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

#if defined TARGET_eqgrhyperbole1
\text{dessindte=plot \color[\indcol[1]],\g1}
\text{listeaff=<span style="color:\color[\indcol[1]]">\(y = \y0\)</span><br>}
#endif
#if (defined TARGET_eqgrhyperbole2  || defined TARGET_eqgrhyperbole3 )
\text{indaff=shuffle(2)}
\text{dessindte=plot \color[\indcol[\indaff[1]]],\g1}
\text{listeaff=<span style="color:\color[\indcol[\indaff[1]]]">
  \(g_1(x)\) = \(\gt1\)</span>}
#endif
#if defined TARGET_eqgrhyperbole4  || defined TARGET_eqgrhyperbole5
\text{indaff=shuffle(2)}
\text{dessindte=plot \color[\indcol[\indaff[1]]],\lstdraw[\indaff[1]]
  plot \color[\indcol[\indaff[2]]],\lstdraw[\indaff[2]]}
\text{listeaff=<span style="color:\color[\indcol[\indaff[1]]]">\(g_1(x)\)=\(\lstaff[\indaff[1]]\)</span><br>
<span style="color:\color[\indcol[\indaff[2]]]">\(g_2(x)\) =\(\lstaff[\indaff[2]]\)</span>}
#endif

%%%% cadre générique %%%%
\text{cadre=
xrange -5,5
yrange -5,5
gridfill 0,0,5,5,\gridcolor
linewidth 1
linewidth 2
parallel -5,-5,-5,5,1,0,11,gray
parallel -5,-5,5,-5,0,1,11,gray
linewidth 2
vline 0,0,black
hline 0,0,black
arrow 0,0,1,0,10,magenta
arrow 0,0,0,1,10,magenta
text red,0.7,-0.1,medium,i
text red,-0.2,0.7,medium,j
text black,-0.2,-0.1,medium,O
linewidth 2
plot red,1/x
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
  <div class="wimscenter">\(\equat\).</div>
  \if{\tintrocomp!=}{<div class="wims_instruction">\tintrocomp</div>}
  <p>
    Indiquer la ou les solutions de l'équation :
  </p>
  <div class="wimscenter"><label for="reply1">\(S=)</label>\embed{reply1,5}</div>
  <div class="wims_instruction">
  Les solutions sont entières ou de la forme un entier +0.5.
  <br>
  S'il n'y a pas de solution taper <span class="tt">vide</span>.
  <br>
  S'il y a plusieurs solutions, les séparer par une virgule.
  </div>
  </div></div>
}

%%%% soumission de réponse %%%%
\answer{solution}{\goodrep}{type=fset}
