target=negationMath

#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\range{-10..10}
\text{monaide=wims(record 11 of \glossaire)}
\help{\monaide}

\integer{y=random(-20..20)}
\integer{z=random(-20..20)}
\integer{n=random(1..20)}
\integer{m=\n-1}
\text{x=randitem(x,y,z,t)}
\function{diff= \x-\z}
\text{dist= |\diff|}

\integer{cas=random(1..7)}
\integer{a=random(-12..12)}
\integer{b=\a+random(0..10)}

\text{A=
\pourtout \(\x) \reel&#44; &nbsp;  \(\dist \le \n),
\linequation \(f(\x) < \y ) \aaumoins \n \solutions,
\(\y < \x < \z),
\(\x \in A \cap B) ,
\pourtout \reel \(\x)&#44;  &nbsp; \(\x \le \y),
\pourtout \reel \(\x) \strictementpositif&#44; &nbsp; \(f(\x) > \y ),
\(\x \in [\a,\b])
}

\text{nonA=
\ilexiste \reel \(\x) \telque &nbsp; \( \dist > \n  ),
\linequation \(f(\x) < \y ) \aauplus \m \solutions,
\(\x \le \y \ou  \x \ge \z\),
\(\x \notin A \ou \x \notin B\) ,
\ilexiste \reel \(\x) \telque \(\x > \y),
\ilexiste \reel \(\x) \strictementpositif \telque &nbsp; \(f(\x) \le \y ),
\(\x) &#8712;  &nbsp;&#93;-&#8734;&#44;\a &#91; &#8746; &#93; \b&#44;+&#8734; &#91;
}

\text{choix=(\cas==1)?\ilexiste \reel \(\x) \telque &nbsp; \( \dist \le \n  ),
\pourtout \reel \(\x)&#44; &nbsp; \( \dist > \n  ),
\pourtout \reel \(\x)&#44; &nbsp; \( \dist > \n  )
}

\text{choix=(\cas==2)?\linequation \(f(\x) < \y ) \aauplus \n \solutions,
\linequation \(f(\x) < \y ) \amoinsde \m \solutions,
\linequation \(f(\x) < \y ) \aplusde \n \solutions,
\linequation \(f(\x) < \y ) \naaucune \solution,
\linequation \(f(\x) < \y ) \auneinfinite \solutions
}

\text{choix=(\cas==3)?\(\x \le \y  \et \x \ge \z\),
\(\x < \y  \ou  \x > \z\), \(\y < \x \ou  \x < \z\)
}

\text{choix=(\cas==4)?\(\x \notin A  \et \x \notin B\),\(\x \in A \ou \x \in B\)
}

\text{choix=(\cas==5)?\pourtout \reel \(\x) &#44; &nbsp; \(\x < \y),
\ilexiste \reel \(\x) \telque \(\x \ge \y \et f(\x) \le 0 \)
}

\text{choix=(\cas==6)?\pourtout \reel \(\x) \strictementpositif &#44; &nbsp; \(f(\x) \le \y ),
\pourtout \reel \(\x) \negatif &#44; &nbsp; \(f(\x) >  \y ),
\ilexiste \reel \(\x) \negatif \telque \(f(\x) >  \y )
}

\text{choix=(\cas==7)?\(\x\le\a \ou \x\ge\b\),\(\x<\a  \et \x<\b\),
\(\x) &#8712;  &nbsp; &#93; -&#8734; &#44;\a &#93; &#8746; &#91; \b &#44; +&#8734; &#91;
}
\integer{i=random(0,1)}
\text{aff=(i==0)?item(\cas,\A):item(\cas,\nonA)}
\text{neg=(i==0)?item(\cas,\nonA):item(\cas,\A)}

\statement{<div class="wims_question">

<p>\name_statement1 \(P) : &#34; \aff &#34; </p>
<p>\name_statement2 \(P)\spacebeforecolon?</p>
</div>
}

\choice{ \(\not{P}) : }{\neg}{\choix}
