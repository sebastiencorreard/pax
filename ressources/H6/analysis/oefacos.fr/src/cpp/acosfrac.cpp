target=acosfrac

\language{fr}
\range{-5..5}
\author{Bernadette, Perrin-Riou}
\email{bernadette.m.riou@orange.fr}
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"

\text{arc=random(Arcsin, Arccos)}
\integer{a=random(4..7)*random(1,-1)}
\integer{b=random(1..7)*random(1,-1)}
\integer{c=random(1..7)*random(1,-1)}
\integer{c= \a=\c? \a +(random(1..3)*random(1,-1))}
\integer{c= \a=-\c? -(\a) +(random(1..3)*random(1,-1))}
\integer{d=random(1..7)*random(1,-1)}
\text{f=simplify(((\a)*x+(\b))/((\c)*x+(\d)))}
\text{f_t=texmath(\f)}
\text{f1=((\a)-(\c))*x+(\b)-(\d)}
\integer{a1=(\a)-(\c)}
\integer{b1=(\b)-(\d)}
\text{f2=((\a)+(\c))*x+(\b)+(\d)}
\integer{a2=(\a)+(\c)}
\integer{b2=(\b)+(\d)}
\real{u1=max(-(\b1)/(\a1), -(\d)/(\c))}
\real{v1=min(-(\b1)/(\a1), -(\d)/(\c))}
\real{u2=max(-(\b2)/(\a2), -(\d)/(\c))}
\real{v2=min(-(\b2)/(\a2), -(\d)/(\c))}
\real{uu= max(\u1,\u2)}
\real{vv=min(\v1,\v2)}
\real{Muv=max(\u1,\v2)}

\real{muv= min(\u2,\v1)}
\text{domaine= (\a1)*(\c)>0 and (\a2)*(\c)<0 ?
\vv, \uu}

\text{domaine= (\a1)*(\c)>0 and (\a2)*(\c)>0 ?
\v1, \v2
\u2,\u1
 }
 \text{domaine= (\a1)*(\c)<0 and (\a2)*(\c)>0 ?
-inf,\vv
 \uu,inf
}
\text{domaine= (\a1)*(\c)<0 and (\a2)*(\c)<0 ?
 \v2,\muv
 \Muv, \u2
}
\integer{n=rows(\domaine)}
\text{sol=}
\for{i=1 to \n}
{\text{z=row(\i,\domaine)}
\matrix{sol=item(1,\z)<item(2,\z) or inf isin item(1,\z) or inf isin item(2,\z) ? \sol
\z}
}
\integer{m=rows(\sol)}
\text{sol1=\sol}
\if{\m=2}
{\text{sol1=item(2,row(1,\sol) )>= item(1,row(2,\sol) )?
 min(item(1,row(1,\sol)), item(1,row(2,\sol))),max(item(2,row(1,\sol)), item(2,row(2,\sol)))}}
\integer{m=rows(\sol)}
\text{sol2=}
\for{i=1 to \m}
{\text{sol2 = item(1,row(\i,\sol1))<-(\d)/(\c) and
-(\d)/(\c)< item(1,row(\i,\sol1)) ? \sol2
item(1,row(\i,\sol1)), -(\d)/(\c)
-(\d)/(\c), item(1,row(\i,\sol1)):
\sol1}}


\text{sol21=\m=2 ? row(1,\sol2):\sol2}
\text{sol22=\m=2? row(2,\sol2)}
\text{Sol11= item(1,\sol21)}
\text{Sol12= item(2,\sol21)}
\text{Sol21= item(1,\sol22)}
\text{Sol22= item(2,\sol22)}


\matrix{STEP=\m=1? reply 1
reply 2, reply 3
:reply 1
reply 2, reply 3, reply 4 ,reply 5}
\steps{\STEP}

\text{born1= \m=2 ? \(\rbrack):\(\lbrack)}
\statement{\name_enonce \(f(x) = \arc(\f)).
 \if{\step<=1}{\name_question[1;1] \(f\) <label for="reply1">\name_question[1;2]</label>
  \embed{reply 1, 4} \name_question[1;3]}

\if{\step=2}{\name_question[2;1] \m \if{\m=1}{\name_question[2;2]}{\name_question[2;3]}:
\name_question[3;]
<div class="wimscenter"> <label for="reply2">\born1</label> \embed{reply 2,5}, \embed{reply 3,5}\(\rbrack)
 \if{\m=2}{&nbsp;\(\lbrack ) \embed{reply 4,5}, \embed{reply 5,5}\(\lbrack)}. </div>
<div class="wims_instruction">\name_instruction</div>
}}

\answer{\name_answer}{ \m}{type=numeric}
\answer{}{\Sol11,inf}{type=function}
\answer{}{\Sol12,inf}{type=function}
\answer{}{\Sol21,inf}{type=function}
\answer{}{\Sol22,inf}{type=function}
\text{reponse=inf notin \reply1 ? vline \reply2, 0,red:}
\text{reponse= \reponse
vline \reply3,0,red
}
\text{reponse=\m=2 ?\reponse
vline reply4,0,red}
\text{reponse=\m=2 and inf notin \reply5 ?\reponse
vline reply5,0,red}
\real{mx=min(\v1,\v2)-5}
\real{Mx= max(\u1,\u2)+5}

\hint{\name_hint[1;] \(\arc) ? \name_hint[2;1] \(x\rightarrow \f_t\) \name_hint[2;2]}

feedback{1=1}{
	\draw{150,150}
	{xrange \mx,\Mx
	yrange -1.5, 1.5
	hline 0,0, black
	vline 0,0,black
	hline 0,-1, green
	hline 0,1, green
	text black, 0,1.2,medium,y=1
	text black, 0,-1.2,medium,y=-1
	\reponse
	plot blue, \f
	}
}


