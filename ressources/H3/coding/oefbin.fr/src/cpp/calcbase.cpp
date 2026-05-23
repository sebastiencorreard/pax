target=calcbase
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{b=randint(2..5)}
\text{signe=random(+,-)}
\integer{u=\signe issametext +? random(\b-1,randint(0..\b-1)):random(\b-1,randint(1..\b-1) )}
\integer{v=\signe issametext +? randint(0..\b-2): randint(1..\b-1)}
\integer{choix=random(1,2)}
\integer{w=item(\choix,100,1000)}
\if{\signe issametext + }{
  \integer{u1=\choix=1? \u+1:\u}
  \integer{v1=\choix=1?\v:\v+1}
  \integer{v1=\u1=\b ? \v1+1}
  \integer{u1= \u1=\b ? 0}
  }
  {
  \integer{u1=\choix=1? \u-1:\u}
  \integer{v1=\choix=1?\v:\v-1}
  \integer{u1= \v1=-1 ? \u1-1}
  \integer{v1=\v1=-1 ? \b-1}
}
 \text{e=random(e,e,randint(0..\b-1))}

\text{n=wims(nospace abc\v\u d\e)}
\text{rep=wims(nospace abc\v1\u1 d\e)}
\statement{\name_enonce[1] \b. \name_enonce[2] \n.
  \name_enonce[3] \(n \signe \w\)?
}

\answer{\(n) \signe \w}{\rep}{type=nocase}
