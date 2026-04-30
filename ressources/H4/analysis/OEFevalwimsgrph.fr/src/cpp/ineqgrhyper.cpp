target=ineqgrhyper1 ineqgrhyper2 ineqgrhyper3 ineqgrhyper4 ineqgrhyper5
#include "lang_titles.inc"
#include "author.inc"

#if defined TARGET_ineqgrhyper2
\text{typeg1=linéaire}
#endif

%%%%choix des coefficients entiers ou fractionnaires
#if defined TARGET_ineqgrhyper5
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

#if defined TARGET_ineqgrhyper2
\text{typeg1=linéaire}
#endif
#if defined TARGET_ineqgrhyper3
\text{typeg1=affine}
#endif

%%%% Choix du nombre de solutions
\integer{nbsol=randint(0..2)}
#if defined TARGET_ineqgrhyper1
\integer{nbsol=randint(0,1,1,1)}
#endif
#if defined TARGET_ineqgrhyper2
\integer{nbsol=randint(0,2)}
#endif
#if (defined TARGET_ineqgrhyper4 || defined TARGET_ineqgrhyper5 )
\integer{nbsol=randint(1,2)}
#endif
%%%%integer{nbsol=2}

#if defined TARGET_ineqgrhyper1
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR) par :
<div class="wimscenter" style="color:red">\(f(x) = \frac{1}{x}),</div>
  ainsi que la droite d'équation:}
\text{tintrocomp=}
#endif
#if (defined TARGET_ineqgrhyper2  || defined TARGET_ineqgrhyper3 )
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR\) par :
<div class="wimscenter" style="color:red">\(f(x) = \frac{1}{x}),</div>
  ainsi que la fonction \typeg1 \(g_1) définie sur \(\ \RR\) par:}
\text{tintrocomp=}
#endif
#if (defined TARGET_ineqgrhyper4 || defined TARGET_ineqgrhyper5 )
\text{tintro=Sur le dessin ci-contre, on a représenté la fonction \(f) définie sur \(\ \RR) par
<div class="wimscenter">\(f(x) = \frac{1}{x}),</div>
  ainsi que les fonctions affines \(g_1) et \(g_2) définies sur \(\ \RR \) par}
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
\text{v1=\(1)}
\text{v2=\(2)}
\text{v3=3}
\text{v4=4}
\text{v5=5}
\text{vm1=-1}
\text{vm2=-2}
\text{vm3=-3}
\text{vm4=-4}
\text{vm5=\( -5 )}
\text{v15=\(1.5)}
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
#include "ineqgrhyp0sol.inc"
 }{
%%%%
%%%% nbsol > 0
%%%%
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
#if defined TARGET_ineqgrhyper1
  \text{xl=-2,-1,-0.5,0.5,1,2}
  \text{yl=-\frac{1}{2},-1,-2,2,1,\frac{1}{2}}
  \text{ylv=-0.5,-1,-2,2,2,0.5}
  \text{ylm=+\frac{1}{2},+1,+2,-2,-1,-\frac{1}{2}}
  \integer{iY=randint(1..6)}
  \text{y0=\yl[\iY]}
  \text{y0v=\ylv[\iY]}
  \text{y0m=\ylm[\iY]}
  \rational{sing1=\xl[\iY]}
#endif
%%%% préparation de la réponse
        \real{tsing1=\sing1}
        \text{tsing1=\tsing1}
#include "ineqgrhyp1sol.inc"
  }{
%%%%
%%%% nbsol =2
%%%%
#if defined TARGET_ineqgrhyper2
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
%%%% attention faux nbsol=2 car les 2 singularités sont confondues
    \integer{nbsol=1}
    \integer{indsol=2}
    \text{goodrep=\sing1}
%%%% préparation de la réponse
    \real{tsing1=\sing1}
    \text{tsing1=\tsing1}
    \if{\sing1>0}{
      \if{\sensineq=1}{
        \text{grep=\strictineq=0?\crocd,\infg,\ptvirg,\v0,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg,\union,\bracg,\tsing1,\bracd}
#if defined TARGET_ineqgrhyper5
        \text{grepp=\strictineq=0?\crocd,\infg,\ptvirg,\v0,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg,\union,\bracg,\tsing1,\bracd}
        \text{grepm=\strictineq=0?\crocd,\v0,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\infd,\crocg:\crocd,\v0,\ptvirg,\infd,\crocg}
#endif
      }{
        \text{grep=\strictineq=0?\crocd,\v0,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\infd,\crocg:\crocd,\v0,\ptvirg,\infd,\crocg}
#if defined TARGET_ineqgrhyper5
        \text{grepp=\strictineq=0?\crocd,\v0,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\infd,\crocg:\crocd,\v0,\ptvirg,\infd,\crocg}
        \text{grepm=\strictineq=0?\crocd,\infg,\ptvirg,\v0,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg,\union,\bracg,\tsing1,\bracd}
#endif
      }
    }{
      \if{\sensineq=2}{
        \text{grep=\strictineq=0?\crocd,\v0,\ptvirg,\infd,\crocg:\bracg,\tsing1,\bracd,\union,\crocd,\v0,\ptvirg,\infd,\crocg}
#if defined TARGET_ineqgrhyper5
        \text{grepp=\strictineq=0?\crocd,\v0,\ptvirg,\infd,\crocg:\bracg,\tsing1,\bracd,\union,\crocd,\v0,\ptvirg,\infd,\crocg}
        \text{grepm=\strictineq=0?\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\v0,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg}
#endif
     }{
      \text{grep=\strictineq=0?\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\v0,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg}
#if defined TARGET_ineqgrhyper5
      \text{grepp=\strictineq=0?\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crocd,\tsing1,\ptvirg,\v0,\crocg:\crocd,\infg,\ptvirg,\v0,\crocg}
      \text{grepm=\strictineq=0?\crocd,\v0,\ptvirg,\infd,\crocg:\bracg,\tsing1,\bracd,\union,\crocd,\v0,\ptvirg,\infd,\crocg}
#endif
    }
  }
}{
%%%% vrai nbsol=2
  \text{goodrep=\sing1,\sing2}
%%%% préparation de la réponse
  \rational{sing=\sing1}
  \rational{sing1=\sing1<\sing2?\sing:\sing2}
  \rational{sing2=\sing1<\sing2?\sing2:\sing}
  \real{tsing=\sing1}
  \text{tsing1=\tsing}
  \real{tsing=\sing2}
  \text{tsing2=\tsing}
  \if{\sing2<0}{
    \text{grep=\sensineq=2?\crochg,\tsing1,\ptvirg,\tsing2,\crochd,\union,\crocd,\v0,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crochg,\tsing2,\ptvirg,\v0,\crocg}
#if defined TARGET_ineqgrhyper5
    \text{grepp=\sensineq=2?\crochg,\tsing1,\ptvirg,\tsing2,\crochd,\union,\crocd,\v0,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crochg,\tsing2,\ptvirg,\v0,\crocg}
    \text{grepm=\sensineq=1?\crochg,\tsing1,\ptvirg,\tsing2,\crochd,\union,\crocd,\v0,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crochg,\tsing2,\ptvirg,\v0,\crocg}
#endif
  }
  \if{\sing1>0}{
    \text{grep=\sensineq=1?\crocd,\infg,\ptvirg,\v0,\crocg,\union,\crochg,\tsing1,\ptvirg,\tsing2,\crochd:\crocd,\v0,\ptvirg,\tsing1,\crochd,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
#if defined TARGET_ineqgrhyper5
    \text{grepp=\sensineq=1?\crocd,\infg,\ptvirg,\v0,\crocg,\union,\crochg,\tsing1,\ptvirg,\tsing2,\crochd:\crocd,\v0,\ptvirg,\tsing1,\crochd,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
    \text{grepm=\sensineq=2?\crocd,\infg,\ptvirg,\v0,\crocg,\union,\crochg,\tsing1,\ptvirg,\tsing2,\crochd:\crocd,\v0,\ptvirg,\tsing1,\crochd,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
#endif
  }
  \if{(\sing2>0) and (\sing1<0)}{
    \text{grep=\sensineq=2?\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crocd,\v0,\ptvirg,\tsing2,\crochd:\crochg,\tsing1,\ptvirg,\v0,\crocg,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
#if defined TARGET_ineqgrhyper5
    \text{grepp=\sensineq=2?\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crocd,\v0,\ptvirg,\tsing2,\crochd:\crochg,\tsing1,\ptvirg,\v0,\crocg,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
    \text{grepm=\sensineq=1?\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crocd,\v0,\ptvirg,\tsing2,\crochd:\crochg,\tsing1,\ptvirg,\v0,\crocg,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
#endif
    }
  }
}
%%%% fin nb sol =2
%%%% ce qui suit est donc valable pour nbsol > 0
%%%%

#if defined TARGET_ineqgrhyper1
\text{g1=\y0v}
\text{equat= \frac{1}{x} \y0m }
text{equat2= \frac{1}{x} \y0m }
#else
\function{f=\den1*\den2*(x- (\sing1))*(x-(\sing2))}
\integer{a=\den1*\den2}
\integer{b=-\a*((\sing1)+(\sing2))}
\text{sb=\b>0?+:-}
\text{smb=\b<0?+:-}
\integer{c=\a*(\sing1)*(\sing2)}
# if defined TARGET_ineqgrhyper5
\text{grep=\c>0?\grepp:\grepm}
# endif
\text{sc=\c>0?+:-}
\text{smc=\c<0?+:-}
\integer{bc=\b*\c}
\text{sbc=\bc>0?+:-}
\text{smbc=\bc<0?+:-}

\integer{b=\b<0?\b*(-1)}
\integer{c=\c<0?\c*(-1)}
\rational{ar=simplify(\a/(\c))}
\rational{br=simplify(\b/(\c))}
# if defined TARGET_ineqgrhyper5
\text{equat=\a=1?x: \a*x }
text{equat2=\a=1?x: \a x }
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
# if defined TARGET_ineqgrhyper5
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
# if defined TARGET_ineqgrhyper5
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

#if defined TARGET_ineqgrhyper1
\text{dessindte=plot \color[\indcol[1]],\g1}
\text{listeaff=<span style="color:\color[\indcol[1]]">\(y = \lstaff[1]\)</span>}
#endif
#if (defined TARGET_ineqgrhyper2 || defined TARGET_ineqgrhyper3 )
\text{indaff=shuffle(2)}
\text{dessindte=plot \color[\indcol[\indaff[1]]],\g1}
\text{listeaff=<span style="color:\color[\indcol[\indaff[1]]]">
  \(g_1(x)\) = \(\gt1\)</span>}
#endif
#if defined TARGET_ineqgrhyper4 || defined TARGET_ineqgrhyper5
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
%%%% enoncé de l'exo %%%%
\statement{
  <div class="wims_columns">
 <div class="medium_size img_col">
\draw{400,400}{\cadre}</div>
 <div class="medium_size text_col">
  <div>\tintro</div>
  <div class="wimscenter">\listeaff</div>
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
