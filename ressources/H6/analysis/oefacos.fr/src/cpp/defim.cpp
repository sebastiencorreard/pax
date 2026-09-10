target=defim defim2 defim3
#include "author.inc"
\precision{10000}
\computeanswer{no}
#if defined TARGET_defim
# define NUM I
#endif
#if defined TARGET_defim2
# define NUM II
#endif
#if defined TARGET_defim3
# define NUM III
#endif
#include "lang_titles.inc"
#include "lang.inc"

\text{lb=&#91;}
\text{rb=&#93;}
\text{minf=\(-infty)}
\text{pinf=\(infty)}
\text{mp2=\(-pi/2)}
\text{pp2=\(pi/2)}
\text{c11=\lb -1 &#44; 1 \rb}
\text{o11=\rb -1 &#44; 1 \lb}
\text{cpp=\lb\(-pi) &#44; \(pi)\rb}
\text{opp=\rb\(-pi) &#44; \(pi)\lb}
\text{c0p=\lb 0 &#44; \(pi)\rb}
\text{o0p=\rb 0 &#44; \(pi)\lb}
\text{c01=\lb 0 &#44; 1\rb}
\text{o01=\rb 0 &#44; 1\lb}
#if defined TARGET_defim3
\text{h01=\rb 0 &#44; 1\rb}
\text{c10=\lb-1 &#44; 0\rb}
\text{o10=\rb-1 &#44; 0\lb}
#endif
\text{cpp2=\lb\mp2 &#44; \pp2\rb}
\text{opp2=\rb\mp2 &#44; \pp2\lb}
\text{cinf=\lb\minf &#44; \pinf\rb}
\text{oinf=\rb\minf &#44; \pinf\lb}
\text{c0inf=\lb 0 &#44; \pinf\rb}
\text{o0inf=\rb 0 &#44; \pinf\lb}
#if defined TARGET_defim
&&&& function,	definition,	image, derivable
\matrix{data=randomrow(
arccos(x),	\c11, \c0p, \o11
arcsin(x),	\c11, \cpp2, \o11
arctan(x),	\oinf, \opp2, \oinf)}
#endif
#if defined TARGET_defim2
%%%% function,	definition,	image, ident
\matrix{data=randomrow(
arccos(cos(x)),	\oinf, \c0p, \c0p
arcsin(sin(x)),	\oinf, \cpp2, \cpp2
cos(arccos(x)),	\c11, \c11, \c11
sin(arcsin(x)),	\c11, \c11, \c11
tan(arctan(x)), \oinf, \oinf, \oinf)}
#endif
#if defined TARGET_defim3
%%% function,	definition,	image
\matrix{data=randomrow(
arcsin(cos(x)),	\oinf, \cpp2
arccos(sin(x)),	\oinf, \c0p
sin(arccos(x)),	\c11, \c01
cos(arcsin(x)),	\c11, \c01
tan(arcsin(x)), \o11, \oinf
sin(arctan(x)),	\oinf, \o11
cos(arctan(x)),	\oinf, \h01
)}
#endif
#if defined TARGET_defim || defined TARGET_defim2
\text{bad=\c11,\o11,\cpp,\opp,\c0p,\o0p,\cpp2,\opp2,\cinf,\oinf,\c01,\o01,\c0inf,\o0inf}
#endif
#if defined TARGET_defim3
\text{bad=\c11,\o11,\cpp,\opp,\c0p,\o0p,\cpp2,\opp2,\cinf,\oinf,\c01,\o01,\c10,\o10,\c0inf,\o0inf,\h01}
#endif
\text{size=110x40}

\statement{\name_enonce
<div>
\name_question1[1] \(x \mapsto \data[1]) \name_question1[2]
\embed{r1,\size}.
</div><div>
\name_question2 \embed{r2,\size}.
</div>
#if defined TARGET_defim || defined TARGET_defim2
<div>
\name_question3 \embed{r3,\size}.
</div>
#endif
}

\reply{\name_answer[1]}{\data[2];\bad}{type=clickfill}
\reply{\name_answer[2]}{\data[3];\bad}{type=clickfill}
#if defined TARGET_defim || defined TARGET_defim2
\reply{I\name_answer[3]}{\data[4];\bad}{type=clickfill}
#endif
