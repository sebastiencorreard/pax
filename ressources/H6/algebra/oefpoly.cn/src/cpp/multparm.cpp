target=multparm3 multparm4

#include "xiao.inc"

#if #TARGET (multparm3)
 #define DEG 3
#endif
#if #TARGET (multparm4)
 #define DEG 4
#endif

\title{DEG 次含参数多项式的重根}

\text{roots=shuffle(wims(makelist x for x=-20 to 20))}
\integer{mult=2}
\text{rootm=\roots[1]}
\text{roots=item(1 .. DEG,\rootm,\roots)}
\text{poly=wims(makelist (x - y) for y in \roots)}
\function{poly=randitem(1,-1,2,-2,3,-3)*wims(translate internal , to * in \poly)}
\integer{parmdeg=randint(0..2)}
\function{dev=pari(P=\poly;cc=polcoeff(P,\parmdeg);P+(m-cc)*x^\parmdeg)}
\integer{cc=pari(cc)}

\statement{求 \(m) 的一个值使以下多项式有一个重根,
并求出这个重根.
<p><center>
\(P(x) = \dev)
</center>
<b>警告</b>. 本练习的回答中不能有近似数! 
解都是整数. 找找看.
}

\answer{\(m)}{\mm}{type=number}
\answer{重根}{\rm}{type=number}

\function{p=wims(mathsubst m=\mm in \dev)}
\function{deriv=diff(\p,x)}
\real{t1=evalue(\p,x=\rm)}
\real{t2=evalue(\deriv,x=\rm)}

\condition{\(\rm) 是 \(\p) 的重根}{\t1 = 0 and \t2 = 0}

\feedback{\t1 != 0}{
 \(\rm) 甚至不是 \(\p) 的根! 错了.
}

\feedback{\t1 = 0 and \t2 != 0}{
 \(\rm) 实际上是 \(P(x) = \p 的根). 为了使它成为重根,
\(\rm) 也应该是 \(P(x)) 的导数的根, 
可惜不是. 请重新验算一下.
}
