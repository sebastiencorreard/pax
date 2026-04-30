target=solineq1 solineq2 solineq3 solineq4 solineq5
#define TITRE Solution d'une inéquation
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
%%%% la liste des objets que l'on peut cliquer pour résoudre l'exercice ###
\css{<style>.border {border:solid black 1px}</style>}
\text{crocg=&#91;}
\text{crocd=&#93;}
\text{union=\(\cup\)}
\text{inter=\(\cap\)}
\text{infg=\(-\infty\)}
\text{infd=\(+\infty\)}
\text{empt=\(\emptyset\)}
\text{bracg=&#123;}
\text{bracd=&#125;}
\text{ptvirg=&#59;}
\text{sou=OU}
\text{sle=\(\le\)}
\text{slt=\(<\)}
\text{solR=\(x \in \RR\)}

\integer{a=randint(2..9)*randint(1,-1)}
\integer{b=randint(2..9)*randint(1,-1)}
\text{lstsymb=<,>,<=,>=}
\text{swapsymb=>,<,>=,<=}

#if defined TARGET_solineq1
\title{TITRE 1}
\text{typeeq=l'inéquation}
\integer{k=randint(1..4)}
\text{symb=\lstsymb[\k]}
\text{equat=\(texmath(\a*x+\b \symb 0)\)}
\rational{x1=simplify(-\b / \a)}
\rational{x2=simplify(\b / \a)}
\rational{x3=simplify(\a / \b)}
\rational{x4=simplify(-\a / \b)}
\rational{x5=\a}
\rational{x6=\b}
#endif

#if (defined TARGET_solineq2 || defined TARGET_solineq3 )
\integer{c=randint(-9..-1)}
\integer{d=randint(1..9)}
\text{typeeq=la double inéquation}
#if defined TARGET_solineq2
\title{TITRE 2}
\integer{kg=randint(1,3)}
\integer{kd=randint(1,3)}
\text{symbg=\lstsymb[\kg]}
\text{symbd=\lstsymb[\kd]}
\text{equat=\(texmath(\c \symbg \a*x+\b \symbd \d)\)}
#endif
#if defined TARGET_solineq3
\title{TITRE 3}
\integer{kg=randint(1..4)}
\integer{kd=randint(1..4)}
\text{symbg=\lstsymb[\kg]}
\text{symbd=\lstsymb[\kd]}
\text{equat=\(texmath(\a*x+\b \symbg \c)\) ou \(texmath(\a*x+\b \symbd \d)\)}
#endif
\rational{x1=simplify((\c-\b) / \a)}
\rational{x2=simplify((\d -\b) / \a)}
\rational{x3=-\x1}
\rational{x4=-\x2}
\rational{x5=1/\x1}
\rational{x6=1/\x2}
#endif
#if (defined TARGET_solineq4 || defined TARGET_solineq5 )
\integer{c=randint(2..9)*randint(1,-1)}
\integer{d=randint(2..9)*randint(1,-1)}
\integer{k=randint(1..4)}
\text{symb=\lstsymb[\k]}
\if{\k<3}{
  %% inégalité stricte
 \text{crochg=\crocd}
 \text{crochd=\crocg}
 }{
%%%% inégalité large
 \text{crochg=\crocg}
 \text{crochd=\crocd}
 }
\rational{x1=simplify(-\b / \a)}
\rational{x2=simplify(-\d / \c)}
\if{\x2=\x1}{
  \integer{d=-\d}
  \rational{x2=simplify(-\d / \c)}
}
\rational{x3=simplify(\a / \b)}
\rational{x4=simplify(-\a / \b)}
\rational{x5=\b}
\rational{x6=\d}
#endif
\text{tx1=\(\x1)}
\text{tx2=\(\x2)}
\text{tx3=\(\x3)}
\text{tx4=\(\x4)}
\text{tx5=\(\x5)}
\text{tx6=\(\x6)}

\text{permut=shuffle(\tx1,\tx2,\tx3,\tx4,\tx5,\tx6)}
\text{permut=wims(listuniq \permut)}

\text{clicList=
\crocg,\ptvirg,\crocd,\union,\inter,\infg,\infd,\permut[1],\permut[2],\permut[3],\permut[4],\permut[5],\permut[6],\empt,\bracg,\bracd,\sle,\slt,\sou,x,\solR
}
## taille des symboles et des champs à remplir par clic LxHxnb ##
\text{size=60x55x12}

#if defined TARGET_solineq1
## calcul de la réponse
\if{\k<3}
 {
%%%% inégalité stricte
 \text{crochg=\crocd}
 \text{crochd=\crocg}
 \text{solsymb=\slt}
 }
 {
%%%% inégalité large
 \text{crochg=\crocg}
 \text{crochd=\crocd}
 \text{solsymb=\sle}
 }
\text{consigne=Construisez une inégalité de la forme \(x\) \solsymb \(....\) ou bien \(....\) \solsymb \(x\)}

\if{(\a>0 and (\k=1 or \k=3)) or (\a<0 and (\k=2 or \k=4))}
 {
 \text{grep=\crocd,\infg,\ptvirg,\tx1,\crochd}
 \text{srep=x,\solsymb,\tx1}
 }
 {
 \text{grep=\crochg,\tx1,\ptvirg,\infd,\crocg}
 \text{srep=\tx1,\solsymb,x}
 }
#endif
#if defined TARGET_solineq2
\text{consigne=Construisez un encadrement de \(x\) ou bien deux inégalités de la forme
\(x < ... OU ... < x\) reliées par le mot "OU".}
\if{\kg=1}
 {
%%%% inégalité stricte
 \text{croch1g=\crocd}
 \text{croch1d=\crocg}
 \text{solsymb1=\slt}
 }
 {
%%%% inégalité large
 \text{croch1g=\crocg}
 \text{croch1d=\crocd}
 \text{solsymb1=\sle}
 }
\if{\kd=1}
 {
%%%% inégalité stricte
 \text{croch2g=\crocd}
 \text{croch2d=\crocg}
 \text{solsymb2=\slt}
 }
 {
%%%% inégalité large
 \text{croch2g=\crocg}
 \text{croch2d=\crocd}
 \text{solsymb2=\sle}
 }

\if{\a>0 }
 {
 \text{grep=\croch1g,\tx1,\ptvirg,\tx2,\croch2d}
 \text{srep=\tx1,\solsymb1,x,\solsymb2,\tx2}
 }
 {
 \text{grep=\croch2g,\tx2,\ptvirg,\tx1,\croch1d}
 \text{srep=\tx2,\solsymb2,x,\solsymb1,\tx1}
 }
#endif
#if defined TARGET_solineq3
\text{consigne=Construisez <ul>
<li>soit un encadrement de \(x\),</li>
<li> soit une inégalité de la forme \(x < ...\) ou de la forme \( ... < x\),</li>
<li> soit deux inégalités de la forme
\(x < ... OU ... < x\) reliées par le mot "OU",</li></ul>
  ou bien choisissez \solR.
}
\rational{valmin=\x1<\x2?\x1:\x2}
\rational{valmax=\x1<\x2?\x2:\x1}
\text{tmin=\x1<\x2?\tx1:\tx2}
\text{tmax=\x1<\x2?\tx2:\tx1}
\if{\kg<3}
 {
%%%% inégalité stricte
 \text{croch1g=\crocd}
 \text{croch1d=\crocg}
 \text{solsymb1=\slt}
 }
 {
%%%% inégalité large
 \text{croch1g=\crocg}
 \text{croch1d=\crocd}
 \text{solsymb1=\sle}
 }
\if{\kd<3}
 {
%%%% inégalité stricte
 \text{croch2g=\crocd}
 \text{croch2d=\crocg}
 \text{solsymb2=\slt}
 }
 {
%%%% inégalité large
 \text{croch2g=\crocg}
 \text{croch2d=\crocd}
 \text{solsymb2=\sle}
 }
\if{((\kg=1 or \kg=3) and (\kd=1 or \kd=3)) or ((\kg=2 or \kg=4) and (\kd=2 or \kd=4))}{
  \if{(\a>0 and (\kg=1 or \kg=3)) or (\a<0 and (\kg=2 or \kg=4))}{
    \text{grep=\x1<\x2?\crocd,\infg,\ptvirg,\tmax,\croch2d:\crocd,\infg,\ptvirg,\tmax,\croch1d}
    \text{srep=\x1<\x2?x,\solsymb2,\tmax:x,\solsymb1,\tmax}
  }{
    \text{grep=\x1<\x2?\croch1g,\tmin,\ptvirg,\infd,\crocg:\croch2g,\tmin,\ptvirg,\infd,\crocg}
    \text{srep=\x1<\x2?\tmin,\solsymb1,x:\tmin,\solsymb2,x}
  }
}{
  \if{(\a>0 and (\kg=1 or \kg=3)) or (\a<0 and (\kg=2 or \kg=4))}{
    \if{\x1<\x2}{
      \text{grep=\crocd,\infg,\ptvirg,\tx1,\croch1d,\union,\croch2g,\tx2,\ptvirg,\infd,\crocg}
      \text{srep=x,\solsymb1,\tx1,\sou,\tx2,\solsymb2,x}
    }{
      \if{\x1=\x2}{
        \if{(\kg=1 and \kd=2) or (\kg=2 and \kd=1)}{
           \text{grep=\crocd,\infg,\ptvirg,\tx1,\croch1d,\union,\croch2g,\tx2,\ptvirg,\infd,\crocg}
           \text{srep=x,\solsymb1,\tx1,\sou,\tx2,\solsymb2,x}
        }{
          \text{grep=\crocd,\infg,\ptvirg,\infd,\crocg}
          \text{srep=\solR}
        }
      }{
        \text{grep=\crocd,\infg,\ptvirg,\infd,\crocg}
        \text{srep=\solR}
      }
    }
  }{
    \if{\x2<\x1}{
      \text{grep=\crocd,\infg,\ptvirg,\tx2,\croch2d,\union,\croch1g,\tx1,\ptvirg,\infd,\crocg}
      \text{srep=x,\solsymb2,\tx2,\sou,\tx1,\solsymb1,x}
     }{
      \if{\x1=\x2}{
        \if{(\kg=1 and \kd=2) or (\kg=2 and \kd=1)}{
          \text{grep=\crocd,\infg,\ptvirg,\tx2,\croch2d,\union,\croch1g,\tx1,\ptvirg,\infd,\crocg}
          \text{srep=x,\solsymb2,\tx2,\sou,\tx1,\solsymb1,x}
        }{
          \text{grep=\crocd,\infg,\ptvirg,\infd,\crocg}
          \text{srep=\solR}
        }
      }{
        \text{grep=\crocd,\infg,\ptvirg,\infd,\crocg}
        \text{srep=\solR}
      }
    }
  }
}
#endif
#if (defined TARGET_solineq4  || defined TARGET_solineq5 )
\rational{valmin=\x1<\x2?\x1:\x2}
\rational{valmax=\x1<\x2?\x2:\x1}
\text{tmin=\x1<\x2?\tx1:\tx2}
\text{tmax=\x1<\x2?\tx2:\tx1}
\text{tableau=<table class="wimscenter wimsnoborder border">
<tr class="border"><th class="border" style="width:20%">\(x)</th><td style="width:10%">\infg</td><td style="width:20%">&nbsp;</td><td style="width:10%">\(\valmin\)</td><td style="width:20%">&nbsp;</td><td style="width:10%">\(\valmax\)</td><td style="width:20%">&nbsp;</td><td style="width:10%"> \infd </td></tr>
}
\if{\a>0}
  {
  \text{ligne=\x1 < \x2?<tr class="border"><th class="border">\(texmath(\a*x+\b)\)</th><td>&nbsp;</td><td>-</td><td>0</td><td>+</td><td>&nbsp;</td><td>+</td><td>&nbsp;</td></tr>:<tr class="border"><th class="border">\(texmath(\a*x+\b)\)</th><td>&nbsp;</td><td>-</td><td>&nbsp;</td><td>-</td><td>0</td><td>+</td><td>&nbsp;</td></tr>}
  }
  {
  \text{ligne=\x1 < \x2?<tr class="border"><th class="border">\(texmath(\a*x+\b)\)</th><td>&nbsp;</td><td>+</td><td>0</td><td>-</td><td>&nbsp;</td><td>-</td><td>&nbsp;</td></tr>:<tr class="border"><th class="border">\(texmath(\a*x+\b)\)</th><td>&nbsp;</td><td>+</td><td>&nbsp;</td><td>+</td><td>0</td><td>-</td><td>&nbsp;</td></tr>}
  }
  \text{tableau=\tableau \ligne}
\if{\c>0}
  {
  \text{ligne=\x1 > \x2?<tr class="border"><th class="border">\(texmath(\c*x+\d)\)</th><td>&nbsp;</td><td>-</td><td>0</td><td>+</td><td>&nbsp;</td><td>+</td><td>&nbsp;</td></tr>:<tr class="border"><th class="border">\(texmath(\c*x+\d)\)</th><td>&nbsp;</td><td>-</td><td>&nbsp;</td><td>-</td><td>0</td><td>+</td><td>&nbsp;</td></tr>}
  }
  {
  \text{ligne=\x1 > \x2?<tr class="border"><th class="border">\(texmath(\c*x+\d)\)</th><td>&nbsp;</td><td>+</td><td>0</td><td>-</td><td>&nbsp;</td><td>-</td><td>&nbsp;</td></tr>:<tr class="border"><th class="border">\(texmath(\c*x+\d)\)</th><td>&nbsp;</td><td>+</td><td>&nbsp;</td><td>+</td><td>0</td><td>-</td><td>&nbsp;</td></tr>}
  }
  \text{tableau=\tableau \ligne}
\integer{\ac=\a*\c}
\text{signe1=\ac>0?+:-}
\text{signe2=\ac>0?-:+}
#if defined TARGET_solineq4
\title{TITRE 4}
\text{typeeq=l'inéquation produit}
\text{equat=\(texmath((\a*x+\b)*(\c*x+\d) \symb 0)\)}
\text{tableau=\tableau
<tr class="border"><th class="border">Produit</th><td>&nbsp;</td><td>\signe1</td><td>0</td><td>\signe2</td><td>0</td><td>\signe1</td><td>&nbsp;</td></tr></table>}
\if{(\ac>0 and (\k=1 or \k=3)) or (\ac<0 and (\k=2 or \k=4))}{
  \text{grep=\crochg,\tmin,\ptvirg,\tmax,\crochd}
  \text{srep=\tmin,\symbg,x,\symbd,\tmax}
}{
  \text{grep=\crocd,\infg,\ptvirg,\tmin,\crochd,\union,\crochg,\tmax,\ptvirg,\infd,\crocg}
  \text{srep=x,\symbg,\tmin,\sou,x,\symbd,\tmax}
}
#endif
#if defined TARGET_solineq5
\title{TITRE 5}
\text{typeeq=l'inéquation quotient}
\text{equat=\(texmath((\a*x+\b)/(\c*x+\d) \symb 0)\)}
\if{\x1<\x2}{
  \text{ligne=<tr class="border"><th class="border">Quotient</th><td>&nbsp;</td><td>\signe1</td><td>0</td><td>\signe2</td><td><span style="color:red">&#124;&#124;</span></td><td>\signe1</td><td>&nbsp;</td></tr></table>}
}{
  \text{ligne=<tr class="border"><th class="border">Quotient</th><td>&nbsp;</td><td>\signe1</td><td><span style="color:red">&#124;&#124;</span></td><td>\signe2</td><td>0</td><td>\signe1</td><td>&nbsp;</td></tr></table>}
}
\text{tableau=\tableau \ligne}
\if{(\ac>0 and (\k=1 or \k=3)) or (\ac<0 and (\k=2 or \k=4))}{
  \text{grep=\x1<\x2?\crochg,\tmin,\ptvirg,\tmax,\crocg:\crocd,\tmin,\ptvirg,\tmax,\crochd}
}{
  \text{grep=\x1<\x2?\crocd,\infg,\ptvirg,\tmin,\crochd,\union,\crocd,\tmax,\ptvirg,\infd,\crocg:\crocd,\infg,\ptvirg,\tmin,\crocg,\union,\crochg,\tmax,\ptvirg,\infd,\crocg}
}
#endif
\statement{
  Pour résoudre \typeeq,
<div class="wimscenter">\equat </div>
 on a construit le tableau des signes suivant&nbsp;:
  \tableau
  Donner l'ensemble solution sous forme d'intervalles.
<div class="spacer"> \(S\) =\embed{reply1,\size}</div>
}
\answer{Solution}{\grep;\clicList}{type=clickfill}
#else
\statement{
  Résoudre \typeeq&nbsp;:
<div class="wimscenter"> \equat </div>
<ol>
<li> \typeeq est équivalente à&nbsp;:
<br>\consigne
<div class="spacer">\embed{reply2,\size} </div>
</li>
<li>
  Donner l'ensemble solution sous forme d'intervalles.
<div class="spacer"> S=\embed{reply1,\size}</div>
</li>
</ol>
}
\answer{Solution}{\grep;\clicList}{type=clickfill}
\answer{Symbole}{\srep;\clicList}{type=clickfill}
#endif
