target=rectangle1 rectangle2 rectangle3 rectangle4 rectangle5 rectangle6

#include "xiao.inc"
\computeanswer{no}
#if defined TARGET_rectangle1
# define NUM I
#endif
#if defined TARGET_rectangle2
# define NUM II
#endif
#if defined TARGET_rectangle3
# define NUM III
#endif
#if defined TARGET_rectangle4
# define NUM IV
#endif
#if defined TARGET_rectangle5
# define NUM V
#endif
#if defined TARGET_rectangle6
# define NUM VI
#endif
#include "lang_titles.inc"
#include "lang.inc"
\text{dir=random(1,2)}
\text{direction=item(\dir,\name_direction)}
\text{sign=item(\dir,+,-)}
\real{a=randint(15..50)/10}
\text{lw=random(1,2)}
\text{LW=item(\lw,\name_long)}
\integer{w=randint(10..30)}
\integer{l=randint(\w+5..2*\w+10)}
\integer{peri=2*(\w+\l)}
\integer{area=\w*\l}
#if defined TARGET_rectangle1
  \text{fix=item(\lw,\name_larg)}
  \text{constant=\name_constante}
  \text{fixval=item(\lw,\w,\l)}
  \text{fixunit=\name_cm}
  \text{first=\name_la \LW}
  \text{ref=\name_sa \LW}
  \text{r=item(\lw,\l,\w)}
  \text{runit=\name_cm}
  \integer{C=\fixval}
  \real{sol=\sign(\C)*\a}
  \text{solunit=cm<sup>2</sup>/s}
  \text{second=\name_sarea}
#endif
#if defined TARGET_rectangle2
  \text{fix=\name_peri}
  \text{constant=\name_constant}
  \text{fixval=\peri}
  \text{fixunit=\name_cm}
  \text{first=\name_la \LW}
  \text{ref=\name_sa \LW}
  \text{r=item(\lw,\l,\w)}
  \text{runit=\name_cm}
  \integer{C=\l+\w}
  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign(\C-2*\t)*\a}
  \text{solunit=cm<sup>2</sup>/s}
  \text{second=\name_sarea}
#endif
#if defined TARGET_rectangle3
  \text{fix=\name_peri}
  \text{constant=\name_constant}
  \text{fixval=\peri}
  \text{fixunit=\name_cm}
  \text{first=\name_la \LW}
  \text{ref=\name_sa item(\lw,\name_larg)}
  \text{r=item(\lw,\w,\l)}
  \text{runit=\name_cm}
  \integer{C=\l+\w}
  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign(\C-2*\t)*\a}
  \text{solunit=cm<sup>2</sup>/s}
  \text{second=\name_sarea}
#endif
#if defined TARGET_rectangle4
  \text{fix=\name_peri}
  \text{constant=\name_constant}
  \text{fixval=\peri}
  \text{fixunit=\name_cm}
  \text{first=\name_la \LW}
  \text{ref=\name_sarea}
  \real{r=\area}
  \text{runit=\name_cm2}
  \integer{C=\l+\w}
  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign(\C-2*\t)*\a}
  \text{solunit=cm<sup>2</sup>/s}
  \text{second=\name_sarea}
#endif
#if defined TARGET_rectangle5
  \text{fix=\name_area0}
  \text{constant=\name_constante}
  \text{fixval=\area}
  \text{fixunit=\name_cm2}
  \text{first=\name_la \LW}
  \text{ref=\name_sa \LW}
  \text{r=item(\lw,\l,\w)}
  \text{runit=\name_cm}
  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign 2*(1-\area/(\t^2))*\a}
  \text{solunit=cm/s}
  \text{second=\name_speri}
#endif
#if defined TARGET_rectangle6
  \text{fix=\name_area0}
  \text{constant=\name_constante}
  \text{fixval=\area}
  \text{fixunit=\name_cm2}
  \text{first=\name_la \LW}
  \text{ref=\name_sa item(\lw,\name_larg)}
  \text{r=item(\lw,\w,\l)}
  \text{runit=\name_cm}

  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign 2*(1-\area/(\t^2))*\a}
  \text{solunit=cm/s}
  \text{second=\name_speri}
#endif
\statement{\name_statement[1;] \first \direction
  \name_statement[2;] \a \name_statement[3;] \fix
  \name_statement[4;] \constant \name_statement[5;] \fixval \fixunit.
  \name_statement[6;] \ref \name_statement[7;] \r \runit,
  \name_statement[8;] \second
  (\name_statement[9;] \solunit)?
}

\answer{\name_answer}{\sol}{type=numeric}

\latex{\begin{statement}
\name_statement[1;] \first \direction
  \name_statement[2;] \a \name_statement[3;] \fix
  \name_statement[4;] \constant \name_statement[5;] \fixval \fixunit.
  \name_statement[6;] \ref \name_statement[7;] \r \runit,
  \name_statement[8;] \second
  (\name_statement[9;] \solunit)?
\end{statement}
}
