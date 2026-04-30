target=ineqgrpara1 ineqgrpara2 ineqgrpara3 ineqgrpara4 ineqgrpara5

#if defined TARGET_ineqgrpara2
\text{typeg1=linéaire}
#endif
#if defined TARGET_ineqgrpara3
\text{typeg1=affine}
#endif
#include "lang_titles.inc"
#include "author.inc"

#if defined TARGET_ineqgrpara5
\integer{den1=2}
\integer{den2=randitem(1,2)}
#else
\integer{den1=1}
\integer{den2=1}
#endif

%%%% couleur des grilles
\text{gridcolor=lightblue}

\text{listnbsol=Aucune solution, une solution, deux solutions, une infinité de solutions}

#if defined TARGET_ineqgrpara2
\text{typeg1=linéaire}
#endif
#if defined TARGET_ineqgrpara3
\text{typeg1=affine}
#endif

%%%% Choix du nombre de solutions
\integer{nbsol=randint(0..2)}
#if defined TARGET_ineqgrpara1
\integer{nbsol=random(0,2)}
#endif
#if defined TARGET_ineqgrpara2
\integer{nbsol=2}
#endif
#if (defined TARGET_ineqgrpara4 || defined TARGET_ineqgrpara5 )
\integer{nbsol=randint(1,2)}
#endif
%%%%integer{nbsol=2}

%%%% choix du type de représentation
#if defined TARGET_ineqgrpara1
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR) par
<div class="wimscenter" style="color:red">\(f(x) = x^2),</div>
  ainsi que la droite d'équation:}
\text{tintrocomp=}
#endif
#if (defined TARGET_ineqgrpara2  || defined TARGET_ineqgrpara3 )
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR) par
<div class="wimscenter" style="color:red">\(f(x) = x^2),</div>
  ainsi que la fonction \typeg1 \(g_1) définie sur \(\ \RR) par}
\text{tintrocomp=}
#endif
#if (defined TARGET_ineqgrpara4 || defined TARGET_ineqgrpara5 )
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR) par
<div class="wimscenter">\(f(x) = x^2),</div>
  ainsi que les fonctions affines \(g_1) et \(g_2) définies sur \(\ \RR\) par}
\text{tintrocomp=Attention, il faut choisir la fonction affine intéressante parmi les deux présentes.}
#endif
%%%% choix de la question
\integer{sensineq=randint(1..2)}
\integer{strictineq=randint(0..1)}
\text{sgt=>}
\text{sge=\ge}
\text{slt=<}
\text{sle=\le }
%%%% la liste des objets que l'on peut cliquer pour résoudre l'exercice %%%%
\text{v1=1}
\text{v2=2}
\text{v3=3}
\text{v4=4}
\text{v5=5}
\text{vm1=-1}
\text{vm2=-2}
\text{vm3=-3}
\text{vm4=-4}
\text{vm5=-5}
\text{v15=1.5}
\text{v25=2.5}
\text{v35=3.5}
\text{v45=4.5}
\text{v05=0.5}
\text{v0=0}
\text{vm15=-1.5}
\text{vm25=-2.5}
\text{vm35=-3.5}
\text{vm45=-4.5}
\text{vm05=-0.5}
\text{crocg=&#91;}
\text{crocd=&#93;}
\text{bracg=&#123;}
\text{bracd=&#125;}
\text{union=\(\cup)}
\text{inter=\(\cap)}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{empt=\(\emptyset)}
\text{ptvirg=&#59;}

\text{clicList=
\crocg,\ptvirg,\crocd,\union,\inter,\infg,\infd,\empt,\bracg,\bracd,\vm5,\vm45,\vm4,\vm35,\vm3,\vm25,\vm2,\vm15,\vm1,\vm05,\v0,\v05,\v1,\v15,\v2,\v25,\v3,\v35,\v4,\v45,\v5
}
%%%% taille des symboles et des champs à remplir par clic LxHxnb %%%%
\text{size=30x40x12}

\text{crochg=\strictineq=0?\crocd:\crocg}
\text{crochd=\strictineq=0?\crocg:\crocd}

%%%% préparation de la question
\text{symb=\slt,\sgt,\sle,\sge}
\integer{indsymb=\sensineq+2*\strictineq}

%%%% nbsol=0
\if{\nbsol=0}{
\text{goodrep=vide}
#if defined TARGET_ineqgrpara1
\rational{y0=random(-0.2,-0.5,-0.8,-1)}
\text{g1=\y0}
\text{equat= texmath(x^2 -\y0) }
\text{equat2= texmath(x^2 - \y0) }

#else
\integer{c=random(1..5)}
\integer{d=random(1..5)}
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
\text{equat= x^2 }
\text{equat2= x^2 }
#if defined TARGET_ineqgrpara5
\function{f=\a*x^2 \sx (\b)*x \sc (\c)}
\text{equat= \a*x^2 }
\text{equat2= \a x^2 }
#endif
\text{s1=\b>0?+:-}
\integer{b=\b<0?\b*(-1)}
\text{s2=\c>0?+:-}
\integer{c=\c<0?\c*(-1)}
\if{\b !=0}{
   \rational{mbr=\br*(-1)}
   \text{equat=\equat \sx \br * x }
   \text{equat2=\equat2 \sx \br  x }
#if defined TARGET_ineqgrpara5
   \text{equat=\equat \sx \b  * x }
   \text{equat2=\equat2 \sx \b x }
#endif
   \text{g1=\smx (\br) * x}
   \text{g2=\sx (\br) * x}
   \text{g3=\smx (\br) * x}
   \text{g4=\sx (\br) * x }
  }{
   \text{g1=}
   \text{g2=}
   \text{g3=}
   \text{g4=}
  }
\if{\c !=0}{
   \text{equat=\equat \sc \cr }
   \text{equat2=\equat2 \sc \cr }
#if defined TARGET_ineqgrpara5
   \text{equat=\equat \sc \c }
   \text{equat2=\equat2 \sc \c }
#endif
   \text{g1=\g1 \smc \cr}
   \text{g2=\g2 \smc \cr}
  }
#endif
%%%% préparation de la réponse
\text{grep=\sensineq=1?\empt:\crocd,\infg,\ptvirg,\infd,\crocg}

\integer{indsol=1}
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
  \real{tsing1=\sing1}
  \text{tsing1=\tsing1}
  \if{\sensineq=1}{
    \text{grep=\strictineq=0?\empt:\bracg,\tsing1,\bracd}
    }{
    \text{grep=\strictineq=0?\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\infd,\crocg}
    }
  }{
#if defined TARGET_ineqgrpara2
    \rational{sing2=0}
#else
#if defined TARGET_ineqgrpara1
  \rational{sing2=-\sing1}
  \integer{num2=\sing2}
  \rational{sing2=\sing2/\den2}
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
# endif
#endif
  \integer{indsol=3}
  \if{\sing1=\sing2}{
    \integer{nbsol=1}
    \integer{indsol=2}
    \text{goodrep=\sing1}
    \real{tsing1=\sing1}
    \text{tsing1=\tsing1}
    \if{\sensineq=1}{
      \text{grep=\strictineq=0?\empt:\bracg,\tsing1,\bracd}
     }{
      \text{grep=\strictineq=0?\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\infd,\crocg}
     }
  }{
    \text{goodrep=\sing1,\sing2}
    \real{tsing1=\sing1<\sing2?\sing1:\sing2}
    \text{tsing1=\tsing1}
    \real{tsing2=\sing1<\sing2?\sing2:\sing1}
    \text{tsing2=\tsing2}
    \if{\sensineq=1}{
      \text{grep=\crochg,\tsing1,\ptvirg,\tsing2,\crochd}
    }{
      \text{grep=\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
    }
  }
}
  \function{f=\den1*\den2*(x- (\sing1))*(x-(\sing2))}
  \integer{a=\den1*\den2}
  \integer{b=-\a*((\sing1)+(\sing2))}
  \text{s1=\b>0?+:-}
  \integer{b=\b<0?\b*(-1)}
  \integer{c=\a*(\sing1)*(\sing2)}
  \text{s2=\c>0?+:-}
  \integer{c=\c<0?\c*(-1)}
  \text{equat= \a * x^2 }
  \text{equat2= \a x^2 }
  \if{\b !=0}{
    \text{equat=\equat \s1 \b  * x }
    \text{equat2=\equat2 \s1 \b x }
  }
  \if{\c !=0}{
    \text{equat=\equat \s2 \c }
    \text{equat2=\equat2 \s2 \c }
  }
  \function{g1=simplify(((\sing1)+(\sing2))*x -(\sing1)*(\sing2))}
  \function{g2=simplify(-((\sing1)+(\sing2))*x -(\sing1)*(\sing2))}
#if defined TARGET_ineqgrpara5
  \function{g2=simplify(\a*((\sing1)+(\sing2))*x -\a*(\sing1)*(\sing2))}
#endif
  \text{eqaff=\g1}
}
\text{color=shuffle(green,blue,orange,purple)}

%%%text{equat=\f}
\text{equat=texmath(\equat) \symb[\indsymb] 0}
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

#if defined TARGET_ineqgrpara1
\text{dessindte=plot \color[\indcol[1]],\g1}
\text{listeaff=<span style="color:\color[\indcol[1]]">\(y = \lstaff[1]\)</span>}
#endif
#if (defined TARGET_ineqgrpara2 || defined TARGET_ineqgrpara3 )
\text{indaff=shuffle(2)}
\text{dessindte=plot \color[\indcol[\indaff[1]]],\g1}
\text{listeaff=<span style="color:\color[\indcol[\indaff[1]]]">
  \(g_1(x)\) = \(\gt1\)</span>}
#endif
#if defined TARGET_ineqgrpara4 || defined TARGET_ineqgrpara5
\text{indaff=shuffle(2)}
\text{dessindte=plot \color[\indcol[\indaff[1]]],\lstdraw[\indaff[1]]
  plot \color[\indcol[\indaff[2]]],\lstdraw[\indaff[2]]}
\text{listeaff=<span style="color:\color[\indcol[\indaff[1]]]">\(g_1(x)\)=\(\lstaff[\indaff[1]]\)</span><br>
<span style="color:\color[\indcol[\indaff[2]]]">\(g_2(x)\) =\(\lstaff[\indaff[2]]\)</span>}
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
%%%% enoncé de l'exo %%%%
\statement{
  <div class="wims_columns">
 <div class="medium_size img_col">\draw{400,400}{\cadre}</div>
  <div class="medium_size text_col"><div>\tintro</div>
  <div class="wimscenter">\listeaff.</div>
  Utiliser ce dessin pour résoudre graphiquement dans \(\ \RR\) l'inéquation:
  <div class="wimscenter">\(\equat\).</div>
  \if{\tintrocomp!=}{<div class="wims_instruction">\tintrocomp</div>}
  <p>
    Indiquer l'ensemble solution de l'inéquation :
  </p>
  <div class="wimscenter"> \(S=)\embed{reply1,\size}</div>
  <div class="wims_instruction">
    Les abscisses des points d'intersection sont entières ou de la forme un entier +0.5.
  </div>
  </div></div>
}

%%%% soumission de réponse %%%%
\answer{}{\grep;\clicList}{type=clickfill}
