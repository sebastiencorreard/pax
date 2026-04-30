target=ineqvalabs1 ineqvalabs2 ineqvalabs3 ineqvalabs4 ineqvalabs5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Inéquation avec valeur absolue
\integer{ord=randint(1,2)}
%%%% les deux racines de f1 et f2 ######
%%%% borne pour la valeur absolue d'une des racines ##
\integer{singmax=20}

%%%% écart maximale entre les racines ##
\integer{singdif=30}

%%%% Choix des bornes ##
\integer{sing1=random(-\singmax..\singmax)}
\integer{sing2=random(1..\singdif)+\sing1}
\rational{centre=(\sing1+(\sing2))/2}
\rational{rayon=abs(\sing2-(\sing1))/2}

\integer{a=random(1..10)*random(1,-1)}
\integer{b=\a+random(1..3)*random(1,-1)}
\integer{c=random(1..10)*random(1,-1)}
\integer{d=random(1..10)*random(1,1,1,1,-1)}
\integer{e=random(1..10)*random(1,-1)}
\integer{f=random(1..10)*random(1,-1)}


%%%% la liste des objets que l'on peut cliquer pour résoudre l'exercice ###
\integer{v1=\sing1}
\integer{v2=\sing2}
\integer{v3=\sing1-random(1,5)}
\integer{v4=\sing2+random(1,5)}

\text{x1=\(\v1)}
\text{x2=\(\v2)}

\text{crocg=&#91;}
\text{crocd=&#93;}
\text{union=\(\cup\)}
\text{inter=\(\cap\)}
\text{infg=\(-\infty\)}
\text{infd=\(+\infty\)}
\text{ptvirg=&#59;}
\text{empt=\(\emptyset\)}
\text{bracg=&#123;}
\text{bracd=&#125;}


%%%% Choix du type d'encadrement
\integer{k=randint(1..3)}
%%%% k= 1 encadrement, k= 2 x symb val , k=3 val symb x
%%%% la liste des symboles d'inégalité ###
\text{sgt=>}
\text{sge=\(\ge \)}
\text{slt=<}
\text{sle=\(\le \)}

\text{symboles=\slt,\sle,\sgt,\sge}
\text{swapsymboles=\sgt,\sge,\slt,\sle}

#if (defined TARGET_ineqvalabs1 || defined TARGET_ineqvalabs3 )
\integer{symbx2=1}
#else
\integer{symbx2=randint(1..2)}
#endif

\integer{symbx1=randint(1..2)}
\integer{symbx=\symbx1+2*(\symbx2-1)}



#if (defined TARGET_ineqvalabs1 || defined TARGET_ineqvalabs2 )

#if defined TARGET_ineqvalabs1
 \title{ TITRE I}
#endif
#if defined TARGET_ineqvalabs2
 \title{ TITRE II}
#endif
%%%% Choix de l'hypothèse
\if{\k=1}{
    \text{eqx=\(abs(x-\centre)\) \symboles[\symbx2] \(texmath(\rayon)\) }
  }{
    \text{eqx=\k=2? \(abs(x-\centre)\) \symboles[\symbx] \(texmath(\rayon)\): \(texmath(\rayon)\) \swapsymboles[\symbx] \(abs(x-\centre)\) }
  }

%%%% calcul de la bonne réponse ###

\if{\k=1}{
    \text{croc1=\symbx2=1?\crocd:\crocg}
    \text{croc2=\symbx2=1?\crocg:\crocd}
    \text{brep=\croc1,\x1,\ptvirg,\x2,\croc2}
    \text{typeeq=l'encadrement}
    }{
     \text{typeeq=l'inégalité}
     \if{\symbx2=1 }{
%%%% x < ou <= sing2
       \text{croc2=\symbx1=1?\crocg:\crocd}
       \text{croc1=\symbx1=1?\crocd:\crocg}
       \text{brep=\croc1,\x1,\ptvirg,\x2,\croc2}
       }{
%%%% x > ou >= sing2
       \text{croc2=\symbx1=1?\crocg:\crocd}
       \text{croc1=\symbx1=1?\crocd:\crocg}
       \text{brep=\crocd,\infg,\ptvirg,\x1,\croc2,\union,\croc1,\x2,\ptvirg,\infd,\crocg}
       }
}

#endif

#if (defined TARGET_ineqvalabs3 || defined TARGET_ineqvalabs4 )

#if defined TARGET_ineqvalabs3
 \title{ TITRE III}
#endif
#if defined TARGET_ineqvalabs4
 \title{ TITRE IV}
#endif

\integer{a=randint(1,-1)}
%%%% Choix de l'hypothèse
\text{eqx=\ord=1?\(abs(texmath(\a*x-(\c)))\) \symboles[\symbx] \d :\(abs(texmath(-(\c)+\a*x))\) \symboles[\symbx] \d }
\text{eqs1=texmath(\a*x-(\c))}

%%%% calcul de la bonne réponse ###
\if{\d<0}{
  \if{\symbx2=1}{
    \text{brep=\empt}
  }{
    \text{brep=\crocd,\infg,\ptvirg,\infd,\crocg}
  }
}
{
\if{\d=0}{
  \rational{v1=\c / (\a)}
  \rational{v2=0}
  \text{x1=\(\v1)}
  \text{x2=\(\v2)}
  \if{\symbx2=1}{
    \if{\symbx1=1}{
      \text{brep=\empt}
     }{
      \text{brep=\bracg,\x1,\bracd}
     }
  }{
    \if{\symbx1=1}{
      \text{brep=\crocd,\infg,\ptvirg,\x1,\crocg,\union,\crocd,\x1,\ptvirg,\infd,\crocg}
    }{
      \text{brep=\crocd,\infg,\ptvirg,\infd,\crocg}
    }
  }
}{
\integer{n1=\d + (\c)}
\integer{d1=\a}
\rational{v1= \n1 /(\d1)}

\integer{n2=\c - (\d)}
\integer{d2=\a }
\rational{v2= \n2 /(\d2)}
\text{x1=\(\v1)}
\text{x2=\(\v2)}
\text{rep1=\v1<\v2?\x1:\x2}
\text{rep2=\v1<\v2?\x2:\x1}
       \text{croc2=\symbx1=1?\crocg:\crocd}
       \text{croc1=\symbx1=1?\crocd:\crocg}
    \if{\symbx2=1}
     {
      \text{brep=\croc1,\rep1,\ptvirg,\rep2,\croc2}
     }
     {
      \text{brep=\crocd,\infg,\ptvirg,\rep1,\croc2,\union,\croc1,\rep2,\ptvirg,\infd,\crocg}
     }
 }
}
\integer{x3=\c}
\integer{x4=\d}
\integer{x3=(\x3=\v1 or \x3=\v2)?\x3+0.5}
\integer{x4=(\x4=\v1 or \x4=\v2)?\x4-0.5}
\text{x3=\(\x3)}
\text{x4=\(\x4)}
#endif

#if defined TARGET_ineqvalabs5
 \title{ TITRE V}

%%%% Choix de l'hypothèse
    \text{eqx=\(abs(texmath(x-(\c)))\) \symboles[\symbx] \(abs(texmath(x-(\d)))\) }
    \text{eqs1=texmath(x-(\c))}
    \text{eqs2=texmath(x-(\d))}
    \text{eqs3=texmath(-x+(\d))}

%%%% calcul de la bonne réponse ###
\integer{v1=\c<\d?\c:\d}
\integer{v2=\c<\d?\d:\c}
\rational{v3=(\v1+(\v2))/2}
\rational{v4=(\v1-(\v2))/2}
\text{x1=\(\v1)}
\text{x2=\(\v2)}
\text{x3=\(\v3)}
       \text{croc2=\symbx1=1?\crocg:\crocd}
       \text{croc1=\symbx1=1?\crocd:\crocg}
\if{(\c<\d and \symbx2=1) or (\c>\d and \symbx2=2)}
  {
   \text{brep=\crocd,\infg,\ptvirg,\x3,\croc2}
  }
  {
   \text{brep=\croc1,\x3,\ptvirg,\infd,\crocg}
  }
#endif

\integer{v5=-\v1}
\integer{v6=-\v2}
\integer{v7=-\v3}
\integer{v8=-\v4}
\text{x3=\(\v3)}
\text{x4=\(\v4)}
\text{x5=\(\v5)}
\text{x6=\(\v6)}
\text{x7=\(\v7)}
\text{x8=\(\v8)}
\text{permut=shuffle(\x1,\x2,\x3,\x4,\x5,\x6,\x7,\x8)}
\text{permut=wims(listuniq \permut)}

\text{clicList=
\crocg,\ptvirg,\crocd,\union,\inter,\infg,\infd,\permut[1],\permut[2],\permut[3],\permut[4],\permut[5],\permut[6],\permut[7],\permut[8],\empt,\bracg,\bracd
}
%%%% taille des symboles et des champs à remplir par clic LxHxnb ##
\text{size=60x55x12}

%%%% Maintenant, rédigeons l'énoncé ###
\statement{
      Lorsque \(x\) vérifie \typeeq
      <div class="wimscenter">
        <p>\eqx </p>
      </div>
      à quel intervalle appartient-il&nbsp;?
<div class="spacer">
     \(x \in) \embed{reply1,\size}
</div>
}

%%%% Récupération des réponses ###
\answer{}{\brep;\clicList}{type=clickfill}
