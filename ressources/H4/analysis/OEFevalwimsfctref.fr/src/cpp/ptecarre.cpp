target=ptecarre1 ptecarre2 ptecarre4 ptecarre5 pteinverse5
#if defined TARGET_ptecarre1
# define NUM 1
#endif
#if defined TARGET_ptecarre2
# define NUM 2
#endif
#if defined TARGET_ptecarre4
# define NUM 4
#endif
#if defined TARGET_ptecarre5
# define NUM 5
#endif
#if defined TARGET_pteinverse5
# define NUM 5
#endif
#include "lang_titles.inc"
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{1000}
\computeanswer{no}

#if defined TARGET_ptecarre1
\text{lstrep=\(x),\(-x),\(x^2),\(-x^2)}
\text{lbrack=&#91;}
\text{rbrack=&#93;}
\text{ptvirg=&#59;}
\text{interlst=\rbrack 0\ptvirg 1 \lbrack, \rbrack 1\ptvirg \(+\infty) \lbrack, \rbrack -1\ptvirg 0 \lbrack, \rbrack \(-\infty)\ptvirg -1 \lbrack}
\integer{k=randint(1..4)}
\text{inter=\interlst[\k]}
\text{greplst=\(-x),\(-x^2),\(x^2),\(x)
\(-x^2),\(-x),\(x),\(x^2)
\(x),\(-x^2),\(x^2),\(-x)
\(-x^2),\(x),\(-x),\(x^2)
}
\text{rep=row(\k,\greplst)}
\text{size=40x40x4}
\statement{
Ranger dans l'ordre croissant les réels suivants,
<div class="wimscenter"> sachant que \(x \in ) \inter</div>
<div class="wimscenter">\embed{reply1,\size}</div>
}
\answer{rangement}{\rep;\lstrep}{type=clickfill}
#endif


#if defined TARGET_ptecarre2
\text{data=les carrés,\(0 \le a < b),\(a^2),\(b^2)
les carrés,\(a< b  \le 0),\(b^2),\(a^2)
}
%%%% Supprimer!!!les racines carrées,\(0 \le a < b),\(\sqrt{a}),\(\sqrt{b})

\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\text{cond=\cedata[2]}
\text{rep1=\cedata[3]}
\text{rep2=\cedata[4]}
\text{lstrep=\rep1,\rep2}
\text{size=40x40x1}
\statement{
  Classer dans l'ordre croissant \quest des réels \(a) et \(b),
<div class="wimscenter">sachant que \cond</div>
<div class="wimscenter">\embed{reply1,\size} \(<\) \embed{reply2,\size}</div>
}
\answer{}{\rep1;\lstrep}{type=clickfill}
\answer{}{\rep2;\lstrep}{type=clickfill}
#endif

#if (defined TARGET_ptecarre5 || defined TARGET_ptecarre4 || defined TARGET_pteinverse5 )

%%%% la liste des objets que l'on peut cliquer pour résoudre l'exercice ###
\text{sgt=>}
\text{sge=\(\ge )}
\text{slt=<}
\text{sle=\(\le )}

\text{symboles=\slt,\sle,\sgt,\sge}
\text{swapsymb=2,1}
\integer{symbx1=randint(1..2)}
\integer{symbx2=randint(1..2)}
\integer{aa=random(1..10)*random(1,-1)}
\integer{bb=random(1..10)*random(1,-1)}
\integer{bb=\aa=\bb?\bb+5:\bb}
\integer{mbb=\bb*(-1)}
\integer{aa=\aa=\mbb?\aa-1:\aa}
\integer{a=\aa<\bb?\aa:\bb}
\integer{b=\aa<\bb?\bb:\aa}

\integer{kt=random(1,2)}
#if defined TARGET_ptecarre4
\integer{kt=2}
#endif
#if defined TARGET_ptecarre5
\integer{kt=2}
\integer{ma=-\a}
\integer{b=\b=\ma?\b+1}
#endif
\integer{symbx=\symbx1+2*(\symbx2-1)}
\if{\kt=2}{
  \text{eqx=\a \symboles[\symbx1] \(x) \symboles[\symbx2] \b }
}{
  \if{\symbx2=1 and \b>0}{\text{eqx= 0 \slt \(x) \symboles[\symbx] \b}}
  \if{\symbx2=2 and \b>0}{\text{eqx= \(x) \symboles[\symbx] \b} }
  \if{\symbx2=2 and \b<0}{\text{eqx= 0 \sgt \(x) \symboles[\symbx] \b }}
  \if{\symbx2=1 and \b<0}{\text{eqx= \(x) \symboles[\symbx] \b} }
}

\text{clicList=
\slt,\sle
}
#if defined TARGET_ptecarre4
 \function{fref=texmath(x^2)}
\text{eqfx=\(texmath(maxima((x)^2;)))}
%% valeurs des constantes intervenant dans les réponses possibles
\integer{bb2=(\b)^2}
\integer{aa2=(\a)^2}
\integer{a2=\aa2<\bb2?\aa2:\bb2}
\integer{b2=\aa2<\bb2?\bb2:\aa2}
\text{symb1=\aa2<\bb2?\symbx1:\symbx2}
\text{symb2=\aa2<\bb2?\symbx2:\symbx1}
\integer{ma2=-\a2}
\integer{mb2=-\b2}
\integer{s=\a*(\b)}
\if{\s>0}{
  \integer{rep1=\a2}
  \integer{rep4=\b2}
  \text{rep2=\symboles[\symb1]}
  \text{rep3=\symboles[\symb2]}
  }{
  \integer{rep1=0}
  \integer{rep4=\b2}
  \text{rep2=\sle}
  \text{rep3=\symboles[\symb2]}
}

#endif
#if defined TARGET_ptecarre5
\integer{c=randint(1..5)*randint(1,-1)}
\integer{d=randint(1..5)*randint(1,-1)}
\integer{e=\a-randint(1..3)}
\function{fref=texmath(\c*(x-\e)^2+\d)}
\text{eqfx=\(texmath(maxima(\c*(x-\e)^2+\d;)))}
%%%% valeurs des constantes intervenant dans les réponses possibles
\integer{bb2=\c*(\b-\e)^2+\d}
\integer{aa2=\c*(\a-\e)^2+\d}
\integer{a2=\aa2<\bb2?\aa2:\bb2}
\integer{b2=\aa2<\bb2?\bb2:\aa2}
\text{symb1=\aa2<\bb2?\symbx1:\symbx2}
\text{symb2=\aa2<\bb2?\symbx2:\symbx1}

\integer{ma2=-\a2}
\integer{mb2=-\b2}
\integer{s=\a*(\b)}
%%%% on s'arrange pour éviter le cas difficile, plus besoin de tester le signe de s
if{\s>0}
%%%%
  \if{0=0}{
    \text{bonchoix=\a2 \symboles[\symb1] \eqfx \symboles[\symb2] \b2}
    \text{badchoix1=\a2=0?0 \slt \eqfx \symboles[\symb2] \b2:0 \sle \eqfx \symboles[\symb2] \b2}
    \text{badchoix2=0 \sle \eqfx \symboles[\symb1] \a2}
    \text{badchoix3=\b2 \symboles[\symb2] \eqfx \symboles[\symb1] \a2}
  }{
    \integer{rep1=0}
    \integer{rep4=\b2}
    \text{rep2=\sle}
    \text{rep3=\symboles[\symb2]}
    \text{bonchoix=0 \sle \eqfx \symboles[\symb2] \b2}
    \text{badchoix1=\a2 \symboles[\symb1] \eqfx \symboles[\symb2] \b2}
    \text{badchoix2=0 \sle \eqfx \symboles[\symb1] \a2}
    \text{badchoix3=\b2 \symboles[\symb2] \eqfx \symboles[\symb1] \a2}
  }
  \text{repList=\bonchoix,\badchoix1,\badchoix2,\badchoix3}
  \integer{greplist=1}
#endif
#if defined TARGET_pteinverse5
\function{fref=texmath(1/x)}
\text{eqfx=\(texmath(maxima(1/x;)))}
\rational{ib=1/(\b)}
\rational{mib=-1/(\b)}
\integer{mb=-1*(\b)}
\rational{ia=1/(\a)}
\rational{mia=-1/(\a)}
\integer{ma=-1*(\a)}
\integer{ab=\a*(\b)}
\if{\kt=1}{
  \if{\b>0 }{
    \text{x1=0 \slt \(texmath(maxima(1/x;))) \slt \ib}
    \text{x2=0 \slt \(texmath(maxima(1/x;))) \sle \ib}
    \text{x3= \ib \slt \(texmath(maxima(1/x;)))}
    \text{x4= \ib \sle \(texmath(maxima(1/x;)))}
    \text{x5= \mb \slt \(texmath(maxima(1/x;))) \slt 0}
    \text{x6= \mb \sle \(texmath(maxima(1/x;))) \slt 0}
    \text{x7= \(texmath(maxima(1/x;))) \slt \mb}
    \text{x8= \(texmath(maxima(1/x;))) \sle \mb}
    \text{x9= \mib \slt \(texmath(maxima(1/x;))) \slt 0}
    \text{x10= \mib \sle \(texmath(maxima(1/x;))) \slt 0}
    \text{x11= \(texmath(maxima(1/x;))) \slt \mib}
    \text{x12= \(texmath(maxima(1/x;))) \sle \mib}
    \if{\symbx2=1}{
      \integer{gind=2+\symbx1}
    }{
      \integer{gind=\symbx1}
    }
    \text{greplist=\gind}
  }{
    \text{x1=\ib \slt \(texmath(maxima(1/x;))) \slt 0}
    \text{x2=\ib \sle \(texmath(maxima(1/x;))) \slt 0}
    \text{x3= \(texmath(maxima(1/x;))) \slt \ib}
    \text{x4= \(texmath(maxima(1/x;))) \sle \ib}
    \text{x5= \mb \slt \(texmath(maxima(1/x;))) }
    \text{x6= \mb \sle \(texmath(maxima(1/x;))) }
    \text{x7= 0 \slt \(texmath(maxima(1/x;))) \slt \mb}
    \text{x8= 0 \slt \(texmath(maxima(1/x;))) \sle \mb}
    \text{x9= \mib \slt \(texmath(maxima(1/x;))) }
    \text{x10= \mib \sle \(texmath(maxima(1/x;)))}
    \text{x11= 0 \slt \(texmath(maxima(1/x;))) \slt \mib}
    \text{x12= 0 \slt \(texmath(maxima(1/x;))) \sle \mib}
    \if{\symbx2=2}{
      \integer{gind=2+\symbx1}
    }{
      \integer{gind=\symbx1}
    }
    \text{greplist=\gind}
  }
  \text{repList=\x1,\x2,\x3,\x4,\x5,\x6,\x7,\x8,\x9,\x10,\x11,\x12}
%%%% fin kt=1
}{
%%%% debut kt=2
  \if{\ab>0}{
%%%% a et b de meme signe
    \text{eqx0=}

    \text{x1=\ia \slt \(texmath(maxima(1/x;))) ou \(texmath(maxima(1/x;))) \slt \ib}
    \text{x2=\ia \slt \(texmath(maxima(1/x;))) ou \(texmath(maxima(1/x;))) \sle \ib}
    \text{x3=\ia \sle \(texmath(maxima(1/x;))) ou \(texmath(maxima(1/x;))) \slt \ib}
    \text{x4=\ia \sle \(texmath(maxima(1/x;))) ou \(texmath(maxima(1/x;))) \sle \ib}
    \text{x5=\ib \slt \(texmath(maxima(1/x;))) \slt \ia}
    \text{x6=\ib \slt \(texmath(maxima(1/x;))) \sle \ia}
    \text{x7=\ib \sle \(texmath(maxima(1/x;))) \slt \ia}
    \text{x8=\ib \sle \(texmath(maxima(1/x;))) \sle \ia}
    \integer{gind=4+\symbx1+2*(\symbx2-1)}
    \text{greplist=\gind}
  }{
%%%% a négatif et b positif
    \text{eqx0= et x \(\not =) 0}
    \text{eqx=\eqx \eqx0}
    \text{x1=\ia \slt \(texmath(maxima(1/x;))) \slt \ib \eqx0}
    \text{x2=\ia \slt \(texmath(maxima(1/x;))) \sle \ib \eqx0}
    \text{x3=\ia \sle \(texmath(maxima(1/x;))) \slt \ib \eqx0}
    \text{x4=\ia \sle \(texmath(maxima(1/x;))) \sle \ib \eqx0}
    \text{x5=\ib \slt \(texmath(maxima(1/x;))) ou \(texmath(maxima(1/x;))) \slt \ia}
    \text{x6=\ib \slt \(texmath(maxima(1/x;))) ou \(texmath(maxima(1/x;))) \sle \ia}
    \text{x7=\ib \sle \(texmath(maxima(1/x;))) ou \(texmath(maxima(1/x;))) \slt \ia}
    \text{x8=\ib \sle \(texmath(maxima(1/x;))) ou \(texmath(maxima(1/x;))) \sle \ia}
    \integer{gind=4+\symbx1+2*(\symbx2-1)}
    \text{greplist=\gind}
  }
  \text{x9=\mb \slt \(texmath(maxima(1/x;))) \slt \ma \eqx0}
  \text{x10=\mb \slt \(texmath(maxima(1/x;))) \sle \ma \eqx0}
  \text{x11=\mb \sle \(texmath(maxima(1/x;))) \slt \ma \eqx0}
  \text{x12=\mb \sle \(texmath(maxima(1/x;))) \sle \ma \eqx0}
  \text{x13=\mia \slt \(texmath(maxima(1/x;))) \slt \mib \eqx0}
  \text{x14=\mia \slt \(texmath(maxima(1/x;))) \sle \mib \eqx0}
  \text{x15=\mia \sle \(texmath(maxima(1/x;))) \slt \mib \eqx0}
  \text{x16=\mia \sle \(texmath(maxima(1/x;))) \sle \mib \eqx0}
  \text{repList=\x1,\x2,\x3,\x4,\x5,\x6,\x7,\x8,\x9,\x10,\x11,\x12}
}
#endif

 \text{ench1=\(\begin{array}{ccccccc}& \aff1 &&\fref && \aff2 &\\ x & \longmapsto &\cdots &\longmapsto & \cdots & \longmapsto & \cdots\end{array})}


#if defined TARGET_pteinverse5
%%%% preparation de la présentation des cases à cocher
\integer{nbrep=items(\repList)}
\integer{nbrows=floor((\nbrep+1)/2)}
\text{col1=wims ( values i for i=1 to \nbrows)}
\text{col2=wims ( values i+\nbrows for i=1 to \nbrows)}
#endif

#if defined TARGET_ptecarre5
\statement{
  On considère une fonction \(f) définie sur \(\,\RR) par \(f(x)=)\eqfx.
  Cocher l'encadrement de \(f(x)) correspondant à \eqx.
      <table>
      <tr><td>\embed{r1,1}</td><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>\embed{r1,2}</td></tr>
      <tr><td>\embed{r1,3}</td><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>\embed{r1,4}</td></tr>
      </table>
}
\answer{Encadrement}{\greplist;\repList}{type=checkbox}{option=shuffle}
#else
\statement{
#if defined TARGET_ptecarre4
  On considère la fonction carré de référence \(f) définie par \(f(x)=\fref).
#else
  On considère la fonction inverse de référence \(f) définie par \(f(x)=\fref).
#endif
#if defined TARGET_pteinverse5
  Cocher l'encadrement de \(f(x)) correspondant à \eqx.
    <table>
    \for{k=1 to \nbrows}{
      <tr><td>\embed{r1,\col1[\k]}</td><td>&nbsp;&nbsp;&nbsp;&nbsp;</td>
        <td>\embed{r1,\col2[\k]}</td></tr>
    }
    </table>}
\answer{Encadrement}{\greplist;\repList}{type=checkbox}{option=shuffle}
#else
  Donner l'encadrement de \(f(x)) correspondant à \eqx.
<div class="wimscenter">\embed{reply1,5} \embed{reply2} \(f(x)) \embed{reply3} \embed{reply4,5} </div>
}
\answer{borne gauche}{\rep1}{type=numeric}
\answer{symbole gauche}{\rep2;\clicList}{type=clickfill}
\answer{symbole droite}{\rep3;\clicList}{type=clickfill}
\answer{borne droite}{\rep4}{type=numeric}
#endif
#endif
#endif
