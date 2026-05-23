target=oefsysequa1 oefsysequa2 oefsysequa3 oefsysequa4 oefsysequa5 oefsysequa6 oefsysequa7 oefsysequa8
#if defined TARGET_oefsysequa1
# define NUM 1
#endif
#if defined TARGET_oefsysequa2
# define NUM 2
#endif
#if defined TARGET_oefsysequa3
# define NUM 3
#endif
#if defined TARGET_oefsysequa4
# define NUM 4
#endif
#if defined TARGET_oefsysequa5
# define NUM 5
#endif
#if defined TARGET_oefsysequa6
# define NUM 6
#endif
#if defined TARGET_oefsysequa7
# define NUM 7
#endif
#if defined TARGET_oefsysequa8
# define NUM 8
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}
#include "valeurs.inc"
\text{x=item(1,\valeurs)}
\text{y=item(2,\valeurs)}

\text{val=shuffle(2,3,4,5,6,7,8,9)}
#if defined TARGET_oefsysequa1 ||defined TARGET_oefsysequa2 || defined TARGET_oefsysequa3 || defined TARGET_oefsysequa4
\integer{a1=\val[1]}
\integer{b1=\val[2]}
\integer{a2=\val[3]}
\integer{b2=\val[4]}
#endif
#if defined TARGET_oefsysequa1
\text{sg1=+}
\text{sg2=+}
#endif
#if defined TARGET_oefsysequa2
\text{sg=shuffle(+,-)}
\text{sg1=randitem(\sg[1],-)}
\text{sg2=randitem(\sg[2],-)}
#endif
#if defined TARGET_oefsysequa3 || defined TARGET_oefsysequa4
\text{sg1=randitem(+,-)}
\text{sg2=randitem(+,-)}
#endif
#if defined TARGET_oefsysequa4
\text{sg=shuffle(\,-)}
\text{sg3=randitem(\sg[1],-)}
\text{sg4=randitem(\sg[2],-)}
#endif
#if defined TARGET_oefsysequa5
\text{sg1=+}
\text{sg2=+}
#endif
#if defined TARGET_oefsysequa6
\text{sg=shuffle(+,-)}
\text{sg1=randitem(\sg[1],-)}
\text{sg2=randitem(\sg[2],-)}
#endif
#if defined TARGET_oefsysequa7
\text{sg1=randitem(+,-)}
\text{sg2=randitem(+,-)}
#endif
#if defined TARGET_oefsysequa8
\text{sg1=randitem(+,-)}
\text{sg2=randitem(+,-)}
\text{sg=shuffle(\,-)}
\text{sg3=randitem(\sg[1],-)}
\text{sg4=randitem(\sg[2],-)}
#endif
#if defined TARGET_oefsysequa5 || defined TARGET_oefsysequa6 || defined TARGET_oefsysequa7 || defined TARGET_oefsysequa8
\text{nb=1,\val[1],\val[2],\val[3]}
\text{af=\,\val[1],\val[2],\val[3]}
\text{c=shuffle(4)}
\text{a1=\nb[\c[1]]}
\text{b1=\nb[\c[2]]}
\text{a2=\nb[\c[3]]}
\text{b2=\nb[\c[4]]}
#endif
#if defined TARGET_oefsysequa1 || defined TARGET_oefsysequa2 || defined TARGET_oefsysequa3 || defined TARGET_oefsysequa5 || defined TARGET_oefsysequa6 || defined TARGET_oefsysequa7
\real{c1=\a1*\x \sg1 \b1*\y}
\real{c2=\a2*\x \sg2 \b2*\y}
#endif
#if defined TARGET_oefsysequa4
\if{\sg3=-}{\real{c1=\sg3 \a1*\x \sg1 \b1*\y}}{\real{c1=\a1*\x \sg1 \b1*\y}}
\if{\sg4=-}{\real{c2=\sg4 \a2*\x \sg2 \b2*\y}}{\real{c2=\a2*\x \sg2 \b2*\y}}
#endif
#if defined TARGET_oefsysequa8
\if{\sg3=-}{\real{c1=\sg3 \a1*\x \sg1 \b1*\y}}{\real{c1=\a1*\x \sg1 \b1*\y}}
\if{\sg4=-}{\real{c2=\sg4 \a2*\x \sg2 \b2*\y}}{\real{c2=\a2*\x \sg2 \b2*\y}}
#endif
#if defined TARGET_oefsysequa1 || defined TARGET_oefsysequa2 || defined TARGET_oefsysequa3
\text{enonce=\begin{array}{ccc}
\a1 x \sg1 \b1 y &=& \c1 \\\\
 \a2 x \sg2 \b2 y &=& \c2
\end{array}}
#endif
#if defined TARGET_oefsysequa5 || defined TARGET_oefsysequa6 || defined TARGET_oefsysequa7
\text{enonce=\begin{array}{ccc}
\af[\c[1]] x \sg1 \af[\c[2]] y &=& \c1 \\\\
 \af[\c[3]] x \sg2 \af[\c[4]] y &=& \c2
\end{array}}
#endif
#if defined TARGET_oefsysequa8
\text{enonce=\begin{array}{ccc}
\sg3 \af[\c[1]] x \sg1 \af[\c[2]] y &=& \c1 \\\\
 \sg4 \af[\c[3]] x \sg2 \af[\c[4]] y &=& \c2
\end{array}}
#endif
#if defined TARGET_oefsysequa4
\text{enonce=\begin{array}{ccc}
\sg3 \a1 x \sg1 \b1 y &=& \c1 \\\\
 \sg4 \a2 x \sg2 \b2 y &=& \c2
\end{array}}
#endif
\text{sys=\(\left \lbrace\enonce \right.\)}
\statement{
\name_enonce <div class="wimscenter">\sys</div>
<div class="wims_question">\name_solution
<div class="wimscenter">
<label for="reply1">\(x\) =</label> \embed{r1,5}
  \name_and <label for="reply2">\(y\) =</label> \embed{r2,5}.
</div>
</div>
<div class="wims_instruction">\name_instruction</div>
}

\answer{}{\x}{type=numeric}
\answer{}{\y}{type=numeric}

\latex{
\begin{statement}
  \name_enonce \sys.
  \par
  \name_instruction
  \par
  \(x = \cdots\) \name_and \(y = \cdots\).
\end{statement}
}
