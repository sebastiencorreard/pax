target=calctersuite1 calctersuite2 calctersuite3 calctersuite4
#include "author.inc"
#if defined TARGET_calctersuite1
#define NUM 1
#endif
#if defined TARGET_calctersuite2
#define NUM 2
#endif
#if defined TARGET_calctersuite3
#define NUM 3
#endif
#if defined TARGET_calctersuite4
#define NUM 4
#endif
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_calctersuite1
\precision{100}
\integer{u0=random(1,2,3,4,5,10)}
\real{u1=100/(\u0)^2}
\real{u2=100/(\u1)^2}
\real{u3=100/(\u2)^2}
\text{size=5}
\integer{n1=1}
\integer{n2=2}
\integer{n3=3}
#endif
#if defined TARGET_calctersuite2
\precision{100}
\integer{u0=random(1,2,3,4,8,9)}
\real{u1=0.5*(\u0+10000/\u0)}
\real{u2=0.5*(\u1+10000/\u1)}
\real{u3=0.5*(\u2+10000/\u2)}
\text{size=3}
\integer{n1=1}
\integer{n2=2}
\integer{n3=3}
#endif
#if defined TARGET_calctersuite3
\precision{100}
\integer{a=random(-3,-2,2,4,5)}
\integer{b=randint(1..10)}
\integer{sgn=random (1,-1)}
\if {\sgn==1} {\text{ op=+}} {\text{ op=}}
\integer{b=\b*\sgn}
\integer{u0=random(1,2,3,4,5,10)}
\real{u1=\a*\u0+\b}
\real{u2=\a*\u1+\b}
\real{u3=\a*\u2+\b}
\text{size=3}
\integer{n1=1}
\integer{n2=2}
\integer{n3=3}
#endif
#if defined TARGET_calctersuite4
\precision{100}
\integer{a=random(-3,-2,2,4,5)}
\integer{b=randint(5..10)}
\integer{n1=random(1,2,3,4,5,10)}
\integer{n2=random(20,30,50)}
\integer{n3=random(100,200,500)}
\real{u1=\a*\n1^2/(\n1+\b)}
\real{u2=\a*\n2^2/(\n2+\b)}
\real{u3=\a*\n3^2/(\n3+\b)}
\text{size=3}
#endif

\statement{
<p>
#if defined TARGET_calctersuite4
\name_statement:
#else
\name_statement[1] \(u_0 = \u0\) \name_statement[2]:
#endif
</p>
<div class="wimscenter">
#if defined TARGET_calctersuite1
\( u_{n+1} = \frac{100}{ u_{n}^2}\).
#endif
#if defined TARGET_calctersuite2
\( u_{n+1} = \frac{1}{2}\left(u_{n}+\frac{10000}{ u_{n}}\right)\).
#endif
#if defined TARGET_calctersuite3
\( u_{n+1} = \a{ u_{n}}\op\b\).
#endif
#if defined TARGET_calctersuite4
\( u_{n} = \frac{\a n^2}{ n+\b}\).
#endif
</div>
<p>
\name_calcul[1] \(u_\n1\), \(u_\n2\) \name_calcul[2] \(u_\n3\) \name_calcul[3]
</p>
#if defined TARGET_calctersuite1 || defined TARGET_calctersuite2 || defined TARGET_calctersuite4
<div class="wims_instruction">\name_instruction</div>
#endif
<ul><li>
  <label for="reply1">\(u_\n1\) =</label> \embed{reply 1,\size}
</li><li>
  <label for="reply1">\(u_\n2\) =</label> \embed{reply 2,\size}
</li><li>
  <label for="reply1">\(u_\n3\) =</label> \embed{reply 3,\size}
</li></ul>
}

\answer{\(u_1\)}{\u1}{type=numeric}
\answer{\(u_1\)}{\u2}{type=numeric}
\answer{\(u_1\)}{\u3}{type=numeric}
