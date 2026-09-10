target=multparm3 multparm4

#include "header.inc"

#if defined TARGET_multparm3
# define DEG 3
#endif
#if defined TARGET_multparm4
# define DEG 4
#endif

#include "lang_titles.inc"

\text{roots=shuffle(wims(makelist x for x=-20 to 20))}
\integer{mult=2}
\text{rootm=\roots[1]}
\text{roots=item(1 .. DEG,\rootm,\roots)}
\text{poly=wims(makelist (x - y) for y in \roots)}
\function{poly=randitem(1,-1,2,-2,3,-3)*wims(translate internal , to * in \poly)}
\integer{parmdeg=randint(0..2)}
\function{dev=pari(P=\poly;cc=polcoeff(P,\parmdeg);P+(m-cc)*x^\parmdeg)}
\integer{cc=pari(cc)}

#include "lang.inc"

\statement{\name_statement
<div class="wimscenter">
\(P(x) = \dev)
</div>
<div class="wims_instruction">
<strongo>\name_warning</strong>. \name_instruction
</div>
}

\answer{\(m)}{\mm}{type=number}
\answer{\name_answer}{\rm}{type=number}

\function{p=wims(mathsubst m=\mm in \dev)}
\function{deriv=diff(\p,x)}
\real{t1=evalue(\p,x=\rm)}
\real{t2=evalue(\deriv,x=\rm)}

\condition{\(\rm) \name_condition \(\p)}{\t1 = 0 and \t2 = 0}

\feedback{\t1 != 0}{
 \(\rm) \name_feedback1 \(\p)&nbsp;! \name_feedback2
}

\feedback{\t1 = 0 and \t2 != 0}{
 \(\rm) \name_feedback3 \(P(x) = \p). \name_feedback4 \(\rm)
 \name_feedback5 \(P(x)),
 \name_feedback6
}

