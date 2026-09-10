target=compose
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{x=randitem(x,y,a,b,c,r,s,t)}
\text{n=randint(2..9)}
\function{arg=\n*\x}
\real{a=randint(5..1000)*random(0.01,-0.01)}
\real{b=randint(5..1000)*random(0.01,-0.01)}
\text{sincos=random(sin,cos)}
\function{f1=random(\a*cos(\arg) + \b*sin(\arg),\b*sin(\arg) + \a*cos(\arg))}

\statement{\name_instruction
<div class="wimscenter">
  \(f(\x) = \f1) ,
</div>
  \name_instruction2
<div class="wimscenter">
  \(f(\x) = A*\sincos(\arg - p)).
</div>
}
\matrix{name_feed=Vous avez donné une amplitude négative&nbsp;
  Un calcul rapide donne
  ce qui ne correspond pas à la fonction \(f) donnée.}

\answer{\name_answer[1] \(A)}{\A}{type=number}
\answer{\name_answer[2]}{\p}{type=number}

\real{aa=rint(1000*\A*\sincos(-(\p)))/1000}
\real{bb=rint(1000*\A*\sincos(pi/2-(\p)))/1000}
\real{diff=sqrt((\a-(\aa))^2+(\b-(\bb))^2)}

\condition{\name_condition}{\A > 0 and \diff <0.01}

\feedback{\A < 0}{\name_feed[1;];!}

\feedback{\diff >= 0.01}{
 \name_feed[2;]
 <div class="wimscenter">
  \(\A*\sincos(\arg - \p) = \aa*cos(\arg) + \bb*sin(\arg)) ,
 </div>
 \name_feed[3;]
}
