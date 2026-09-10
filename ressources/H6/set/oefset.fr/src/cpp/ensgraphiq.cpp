target=ensgraphiq
#define GGG B3 -
\title{GGG Points à coordonnées entières}
\description{certains ensembles peuvent être identifiés à des sous-ensembles du plan. Il s'agit de trouver la représentation graphique correspondante à un tel ensemble.}
\keywords{set_theory}
\language{fr}
\range{-5..5}
\author{Thomas, Guillon}
\email{bpr@math.u-psud.fr}
\format{html}
#include "css.inc"
#include "common.inc"
#include "lang_ensgraphiq_fr.inc"
\if{\lang=it}{
#include "lang_ensgraphiq_it.inc"
}
\if{\lang=es}{
#include "lang_ensgraphiq_es.inc"
}
\integer{m=randint(7..12)}
\integer{n=randint(7..12)}
\integer{M=max(\m,\n)}
\text{sgn=randitem(-,+)}
\integer{ar=randint(-4..4)}
\integer{br=randint(\M-2..\M+2)}
\integer{choix1=randitem(1,2)}
\integer{choix2=randitem(1,2)}
\text{choix=\leq,<}
\text{s1=\choix[\choix1]}
\text{s2=\choix[\choix2]}
\integer{R=random(1,2)}
\text{i1= \R=1? i: j}
\text{i2= \R=1? j: i}
\integer{a= \choix1=1? \ar: \ar+1}
\integer{b= \choix2=1? \br: \br-1}
\if{\R=1}{
  \if{\sgn issametext +}{
   \integer{rep1= max(1,\a-\n) }
   \integer{rep2= min(\m,\b-1) }
   \function{f3=simplify(\a-i)}\function{f4=simplify(\b-i)}
   \text{rep31= max(1,\f3)}
   \text{rep41= min(\n,\f4)}
    }
   {\integer{rep1= max(1+\a,1)}
   \integer{rep2= min(\b+\n,\m)}
   \function{f3=simplify(i-\b)}\function{f4=simplify(i-(\a))}
   \text{rep31= max(1,\f3)}
   \text{rep41= min(\n,\f4)}
   }
 \real{u31=evalue(\rep31,i=\rep1)}
 \real{v31=evalue(\rep31,i=\rep2)}
 \if{\u31=\v31}
   {\integer{rep3=1}}
   {\real{u31=evalue(\f3,i=\rep1)}
    \real{v31=evalue(\f3,i=\rep2)}
    \if{\u31>=1 and \v31>=1}{\text{rep3=\f3}}
       {\text{rep3=\rep31}}
   }
\real{u41=evalue(\rep41,i=\rep1)}
\real{v41=evalue(\rep41,i=\rep2)}
\if{\u41=\v41}
   {\integer{rep4=\n}}
   {\real{u41=evalue(\f4,i=\rep1)}
    \real{v41=evalue(\f4,i=\rep2)}
    \if{\u41<=\n and \v41<=\n}{\text{rep4=\f4}}
       {\text{rep4=\rep41}}
   }
}{
 \if{\sgn issametext +}{
    \integer{rep1= max(1,\a-\m) }
    \integer{rep2= min(\n,\b-1) }
    \function{f3=simplify(\a-j)}
    \function{f4=simplify(\b-j)}
    \text{rep31= max(1,\f3)}
    \text{rep41= min(\m,\f4)}
    }
   {\integer{rep1= max(1-\b,1)}
    \integer{rep2= min(\m-\a,\n)}
    \function{f3=simplify(\a+j)}
    \function{f4=simplify(\b+j)}
    \text{rep31= max(1,\f3)}
    \text{rep41= min(\m,\f4)}
    }
\real{u31=evalue(\rep31,j=\rep1)}
\real{v31=evalue(\rep31,j=\rep2)}
\if{\u31=\v31}
   {\integer{rep3=1}}{
     \real{u31=evalue(\f3,j=\rep1)}
     \real{v31=evalue(\f3,j=\rep2)}
     \if{\u31>=1 and \v31 >=1}{\text{rep3=\f3}}
       {\text{rep3=\rep31}}}
\real{u41=evalue(\rep41,j=\rep1)}
\real{v41=evalue(\rep41,j=\rep2)}
\if{\u41=\v41}
   {\integer{rep4=\m}}
   {\real{u41=evalue(\f4,j=\rep1)}
    \real{v41=evalue(\f4,j=\rep2)}
    \if{\u41<=\m and \v41<=\m}{\text{rep4=\f4}}
     {\text{rep4=\rep41}}}
}
\integer{A=2}
\text{condition= \sgn issametext +? i+j: i-j}
\text{ncondition= \sgn issametext +? i-j: i+j}
\integer{da=randint(1..2)*random(-1,1)}
\integer{db=randint(1..2)}
\text{dessin1=xrange -1,\M+1
yrange -1,\M+1
parallel 0,0,0,\M, 1,0,\M,grey
parallel 0,0,\M, 0,0,1,\M,grey
text black,0,\M,medium,j
text black,\M,0, medium,i
hline 0,0,black
vline 0,0,black}
\text{dessin2=\dessin1}
\text{dessin3=\dessin1}
\text{dessin4=\dessin1}
\for{i=1 to \m}{
  \for{j=1 to \n}{
                \real{r=evalue(\condition, i=\i,j=\j)}
      \real{nr=evalue(\ncondition, i=\i,j=\j)}
                \if{\r >=\a and \r<=\b}{
        \text{dessin1= \dessin1
          disk \i,\j, 8,red}
      }
      \if{\r >=\a+\da and \r<=\b+\db }{
        \text{dessin2= \dessin2
        disk \i,\j, 8,red}
      }
      \if{\nr >=\a and \nr <=\b}{
         \text{dessin3= \dessin3
          disk \i,\j, 8,red}
      }
      \if{\nr >=\a+\da and \nr <=\b+\db}{
         \text{dessin4= \dessin4
          disk \i,\j, 8,red}
      }
  }
}
\text{des1=draw(200,200
 \dessin1)}

\integer{X=random(1,2)}
\integer{Y=random(1,2)}
\text{des2= \X=1? draw(200,200
 \dessin4)}
\text{des3= \X=1? draw(200,200
 \dessin3)}
\if{\X=2 and \Y=1}{
\text{des2=draw(200,200
 \dessin2)}
\text{des3=draw(200,200
 \dessin3)}}
\if{\X=2 and \Y=2}{
\text{des2=draw(200,200
 \dessin2)}
\text{des3=draw(200,200
 \dessin4)}}
 \text{a=shuffle(1,2,3)}
 \text{reponse=<img src="\des1" alt="">,<img src="\des2" alt="">,
 <img src="\des3" alt="">}
 \text{reponse=\reponse[\a]}
 \text{rep=position(1,\a)}
\statement{<div class="color1">
\instruction[1;]
\(1 \leq i \leq \m \) \name_et \(1 \leq j \leq \n\)
\instruction[2;]
<div class="center">\(\ar \:\s1 i \sgn j \s2\: \br\) . </div>
</div>
<div class="wims_question">
\instruction[3;]:
<div class="wimscenter">\embed{reply1,1},\embed{reply1,2},\embed{reply1,3}</div>
</div>}
\answer{}{\rep;\reponse}{type=click}
