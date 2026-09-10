target=droite droite2
#if defined TARGET_droite
# define NUMBER 1
#endif
#if defined TARGET_droite2
# define NUMBER 2
#endif
\author{Bernadette, Perrin-Riou}
#include "lang_title.inc"
\title{TITLE NUMBER}
\title_en{TITLE_en NUMBER}
\title_es{TITLE_es NUMBER}
\title_ca{TITLE_ca NUMBER}

#include "author.inc"

\integer{a=randint(-10..10)}
\integer{b=randint(-10..10)}
\integer{c=randint(-10..10)}
\integer{c= (\a)^2+(\b)^2+(\c)^2=0 ? randint(1..4)}
\integer{x1=randint(-5..5)}
\integer{y1=randint(-5..5)}
\integer{z1=randint(-1..1)}

\text{con=random(1,0)}
\text{t0=random(1,2,3,-1,-2)}
\integer{x2=\con=1 ? randint(-5..5): (\x1)+(\t0)*(\a)}
\integer{y2=\con=1 ? randint(-5..5): (\y1)+(\t0)*(\b)}
\integer{z2=\con=1 ? randint(-5..5): (\z1)+(\t0)*(\c)}
\text{par=random(1,2)}
\integer{r=randint(1..5)*random(1,-1)}
\integer{u=\par=1 ? randint(-10..10): (\r)*(\a)}
\integer{v=\par=1 ? randint(-10..10): (\r)*(\b)}
\integer{w=\par=1 ? randint(-10..10): (\r)*(\c)}
\integer{u= (\u)^2+(\v)^2+(\w)^2=0 ? randint(1..4)}
#if defined TARGET_droite
\text{equa=x = simplify(\x1 + (\a)*t), y = simplify(\y1 + (\b)*t), z = simplify(\z1 + (\c)*t)}
\text{equa1=x = simplify(\x2 + (\u)*t) , y = simplify(\y2 + (\v)*t), z = simplify(\z2 + (\w)*t)}
#endif
#if defined TARGET_droite2
\text{equa= \a<>0 or \b<>0 ? simplify(((\b)*x - (\x1)*(\b) - (\a)*y + (\a)*\y1)) = 0 ,
simplify((\c)*x - (\c)*(\x1) - (\a)*z + (\a)*(\z1)) = 0: x = \x1 , y = \y1}
\text{equa1= \u<>0 or \v<>0 ? simplify((\v)*x - (\v)*(\x2) - (\u)*y + (\u)*\y2) = 0 ,
 simplify((\w)*x - (\w)*(\x2) - (\u)*z + (\u)*(\z2)) = 0: x = \x2 , y = \y2}
#endif
\real{cond=((\u)*(\b)-(\v)*(\a))^2+((\w)*(\b)-(\v)*(\c))^2+((\u)*(\c)-(\w)*(\a))^2}
\matrix{M= \x1-(\x2),\y1-(\y2), \z1-(\z2)
\a,\b,\c
\u,\v,\w
}
\real{condcon=det(\M)}
\text{para= \cond=0 ? 1:3}

#include "lang.inc"

\text{para= \condcon=0 and \cond <>0 ? 2}
\text{sol= item(\para,\choix)}

\if{\para=2}{
\real{sol1= ((\a)*(\u)+(\b)*(\v)+(\c)*(\w))/
(((\a)^2+(\b)^2+(\c)^2)*((\u)^2+(\v)^2+(\w)^2))^(1/2)}
  }
  {
  \text{QR= \a , \b , \c}
  \text{QP= \x2 - (\x1) , \y2 - (\y1) , \z2 - (\z1)}
  \text{QS = \para=3 ? \u , \v , \w}
  \text{QS= \para=1 ? \QP}
  \real{num= ((item(2,\QR))*(item(3,\QS))-(item(3,\QR))*(item(2,\QS)))^2
+((item(3,\QR))*(item(1,\QS))-(item(1,\QR))*(item(3,\QS)))^2
+((item(1,\QR))*(item(2,\QS))-(item(2,\QR))*(item(1,\QS)))^2}
  \real{sol1= \para=1 ? ((\num)/((item(1,\QR))^2+(item(2,\QR))^2+(item(3,\QR))^2))^(1/2)}
 \if{\para=3}{
 	 \matrix{M=\QR
  \QS
  \QP
  }
  \real{sol1=abs(det(\M))/(\num)^(1/2)}}
}

\steps{choice 1
reply 1}

\statement{\name_instruction1 :
<div class="wimscenter"> \(\equa) </div>
\name_instruction2[1;]
<div class="wimscenter">\(\equa1 )</div>
 \if{\step <=1}{\name_instruction2[2;] \embed{choice 1}
}
\if{\step=2}{
\if{ \para= 1}{\name_instruction2[3;]}
\if{ \para= 2}{\name_instruction2[4;]}
\if{ \para= 3}{\name_instruction2[5;]}
}
}
\choice{\name_instruction2[6;]}{\sol}{\choix}
\answer{\texte}{\sol1}{type=numeric}
\hint{
  \if{\step <=1}{\name_hint1}
  \if{\step =2 and \para=2}{name_hint2}
  \if{\step =2 and \para=3}{
\name_hint3
  }
  \if{\step =2 and \para=3}{
  name_hint4
  }
}
