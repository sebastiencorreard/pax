target=exprcomp1 exprcomp2 exprcomp3 exprcomp4 exprcomp5
#include "author.inc"
#include "lang.inc"
#include "lang_titles.inc"
#if defined TARGET_exprcomp5
\integer{k=randint(1..3)}

\integer{a=randint(1..10)*randint(1,-1)}
\integer{b=randint(1..10)*randint(1,-1)}
\integer{b=\b=\a?-\b}
\text{lstf=texmath(\a*x^2+\b),texmath(sqrt(\b*x-\a)),texmath(1/(2*\a*x+\b))}
\text{f=\lstf[\k]}
\text{data=1,\(texmath(u(x)=\a*x+\b)) \name_and \(texmath(v(x)=x^2)),\(texmath(u(x)=\b)) \name_and \(texmath(v(x)=\a*x^2)),\(texmath(u(x)=\a*x)) \name_and \(texmath(v(x)=x^2+\b)),
2,\(texmath(u(x)=\b*x-\a)) \name_and \(texmath(v(x)=sqrt(x))),\(texmath(u(x)=sqrt(x))) \name_and \(texmath(v(x)=\b*x-\a)),\(texmath(u(x)=\b*x)) \name_and \(texmath(v(x)=sqrt(x-\a))),
3,\(texmath(u(x)=1/(2*\a*x))) \name_and \(texmath(v(x)=x+\b)),\(texmath(u(x)=2*\a*x+\b)) \name_and \(texmath(v(x)=1/x)),\(texmath(u(x)=1/x)) \name_and \(texmath(v(x)=2*\a*x+\b))}
\text{cedata=row(\k,\data)}
\text{lstrep=item(2..-1,\cedata)}
\integer{rep=\cedata[1]}
\statement{
 \name_instruction1 \(f(x)=\f) \name_instruction2
<ul>
 <li>\embed{reply1,1}</li>
 <li>\embed{reply1,2}</li>
 <li>\embed{reply1,3}</li>
</ul>
}
\answer{couple convenable}{\rep;\lstrep}{type=radio}
#else
\integer{a=randint(1..10)*randint(1,-1)}
\integer{c=randint(1..10)}
\integer{c=\a>0?-\c}
\integer{b=randint(1..10)*randint(1,-1)}
\integer{d=randint(1..10)}
\integer{d=\b>0?-\d}
%%%% on ne veut pas ad+b=cb+d
\integer{d=\a*\d+\b-\c*\b-\d=0?2*\d}

\integer{k=randint(1,2)}
\text{rep=randint(1,2),randint(1,2),randint(1,2),randint(1,2)}
# if defined TARGET_exprcomp1
\matrix{ql=\(f \circ g(x)=texmath(maxima(\a*\c*x+\a*\d +\b))),\(f \circ g(x)=texmath(maxima(\a*\c*x+\c*\b +\d)))
\(g \circ f(x)=texmath(maxima(\a*\c*x+\c*\b +\d))),\(g \circ f(x)=texmath(maxima(\a*\c*x+\a*\d +\b)))
\(f \circ f(x)=texmath(maxima((\a)^2*x+\a*\b +\b))),\(f \circ f(x)=texmath((\a*x+\b)^2))
\(g \circ g(x)=texmath(maxima((\c)^2*x+\c*\d +\d))),\(g \circ g(x)=texmath((\c*x+\d)^2))}
# endif

# if defined TARGET_exprcomp2
\matrix{ql=\(u \circ f(x)=texmath((\a*x+\b)^2)),\(u \circ f(x)=texmath(\a*x^2+\b))
\(u \circ g(x)=texmath((\c*x+\d)^2)),\(u \circ g(x)=texmath(\c*x^2+\d))
\(f \circ u(x)=texmath(\a*x^2+\b)),\(f \circ u(x)=texmath((\a*x+\b)^2))
\(g \circ u(x)=texmath(\c*x^2+\d)),\(g \circ u(x)=texmath((\c*x+\d)^2))}
text{q=\k=1?\(u \circ f(x)=texmath((\a*x+\b)^2)),\(u \circ g(x)=texmath(\c*x^2+\d)),\(f \circ u(x)=texmath(\a*x^2+\b)),\(g \circ u(x)=texmath((\c*x+\d)^2)):\(u \circ f(x)=texmath(\a*x^2+\b)),\(u \circ g(x)=texmath((\c*x+\d)^2)),\(f \circ u(x)=texmath((\a*x+\b)^2)),\(g \circ u(x)=texmath(\c*x^2+\d))}
text{rep=\k=1?1,2,1,2:2,1,2,1}
# endif
# if defined TARGET_exprcomp3
\matrix{ql=\(v \circ f(x)=texmath(1/(\a*x+\b))),\(v \circ f(x)=texmath(\a/x+\b))
\(v \circ g(x)=texmath(1/(\c*x+\d))),\(v \circ g(x)=texmath(\c/x+\d))
\(f \circ v(x)=texmath(\a/x+\b)),\(f \circ v(x)=texmath(1/(\a*x+\b)))
\(g \circ v(x)=texmath(\c/x+\d)),\(g \circ v(x)=texmath(1/(\c*x+\d)))}
text{q=\k=1?\(v \circ f(x)=texmath(1/(\a*x+\b))),\(v \circ g(x)=texmath(\c/x+\d)),\(f \circ v(x)=texmath(\a/x+\b)),\(g \circ v(x)=texmath(1/(\c*x+\d))):\(v \circ f(x)=texmath(\a/x+\b)),\(v \circ g(x)=texmath(1/(\c*x+\d))),\(f \circ v(x)=texmath(1/(\a*x+\b))),\(g \circ v(x)=texmath(\c/x+\d))}
text{rep=\k=1?1,2,1,2:2,1,2,1}
# endif
#if defined TARGET_exprcomp4
\matrix{ql=\(w \circ f(x)=texmath(sqrt(\a*x+\b))),\(w \circ f(x)=texmath(\a* sqrt(x)+\b))
\(w \circ g(x)=texmath(sqrt(\c*x+\d))),\(w \circ g(x)=texmath(\c*sqrt(x)+\d))
\(f \circ w(x)=texmath(\a* sqrt(x)+\b)),\(f \circ w(x)=texmath(sqrt(\a*x+\b)))
\(g \circ w(x)=texmath(\c*sqrt(x)+\d)),\(g \circ w(x)=texmath(sqrt(\c*x+\d)))}
text{q=\k=1?\(w \circ f(x)=texmath(sqrt(\a*x+\b))),\(w \circ g(x)=texmath(\c*sqrt(x)+\d)),\(f \circ w(x)=texmath(\a* sqrt(x)+\b)),\(g \circ w(x)=texmath(sqrt(\c*x+\d))):\(w \circ f(x)=texmath(\a* sqrt(x)+\b)),\(w \circ g(x)=texmath(sqrt(\c*x+\d))),\(f \circ w(x)=texmath(sqrt(\a*x+\b))),\(g \circ w(x)=texmath(\c*sqrt(x)+\d))}
text{rep=\k=1?1,2,1,2:2,1,2,1}
# endif
\text{q=\ql[1;\rep[1]],\ql[2;+\rep[2]],\ql[3;\rep[3]],\ql[4;\rep[4]]}
\text{f=texmath(\a*x+\b)}
\text{g=texmath(\c*x+\d)}
\text{u=texmath(x^2)}
\text{v=texmath(1/x)}
\text{w=texmath(sqrt(x))}
\statement{
  \name_instruction[1;]
<div class="wimscenter">
\(f: x \mapsto \f) ,  \(g: x \mapsto \g), \(u: x \mapsto \u),
\(v: x \mapsto \v), \(w: x \mapsto \w).
</div>
  \name_instruction[2;]?
<ol>
<li> \q[1]: \embed{reply1} </li>
<li> \q[2]: \embed{reply2} </li>
<li> \q[3]: \embed{reply3} </li>
<li> \q[4]: \embed{reply4} </li>
</ol>

}
\answer{\q[1]}{\rep[1];\lstrep}{type=radio}
\answer{\q[2]}{\rep[2];\lstrep}{type=radio}
\answer{\q[3]}{\rep[3];\lstrep}{type=radio}
\answer{\q[4]}{\rep[4];\lstrep}{type=radio}
#endif
