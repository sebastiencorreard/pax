target=expression1 expression2 expression3 expression5
\language{fr}
\computeanswer{yes}
\precision{1000}
\format{html}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a = (-1)^random(0,1)*random(1..10)}
\integer{b = (-1)^random(0,1)*random(1..10)}
\integer{c = (-1)^random(0,1)*random(1..10)}
\integer{d = (-1)^random(0,1)*random(1..10)}
\integer{k1 = (-1)^random(0,1)*random(1..10)}
\integer{k2 = (-1)^random(0,1)*random(1..10)}
\integer{k3 = (-1)^random(0,1)*random(1..10)}
#if defined TARGET_expression2 || defined TARGET_expression3
\integer{e = (-1)^random(0,1)*random(1..10)}
\integer{f = (-1)^random(0,1)*random(1..10)}
\integer{g = (-1)^random(0,1)*random(1..10)}
#endif
#if defined TARGET_expression5
\integer{e = random(1..12)}
\integer{f = random(1..12)}
#endif
\function{u=\a *x + \b}
\function{u=\a==1?x + \b}
\function{u=\a==-1?-x + \b}
\function{v=\d + \c *x}
#if defined TARGET_expression1
\text{liste=\(\k3),\(\u), \(\v), \(\k3/(\u)),\(\v/\k3), \(sqrt(\v)),\(\k3(\u)),\(\k1(\v) + \k2), \(\k3(\v)^2),\(\k1(\u)^2 + \k2),}
\text{reps=2,3,5,7,8}
#endif
#if defined TARGET_expression2
\function{w=\e*x^2 +\f*x + \g}
\text{liste=\(\w),\(\k3(\w)), \((\u) +\k1(\w)) , \( \u + \k3(\v)^2), \( (\u)(\v)) , \((\v/\k3)^2),
\(\k1(\v)^2 + \k2), \(\k1 - \k2(\u)^2) , \(\k3/(\u)^2), \(\u), \(\k2(\w)^2 + \k1), \( (\v)*(\w)), \(sqrt(\w)),\(\k3(\u)/(\v))
}
\text{reps=1,2,3,4,5,6,7,8}
#endif
#if defined TARGET_expression3
\function{w=\e*x^2 +\f*x + \g}
\text{liste=\((\w)^2), \((\u)^2), \((\k3(\u))^2), \((\v/\k3)^2), \((\k1(\u) - \k2(\v))^2),
 \((\u) +\k1(\w)) , \( \u + \k3(\v)^2), \((\u)(\v)) , \(\k3(\w)),
\(\k1(\v)^2) , \(\k1(\u)^2 - \k2(\v)^2) , \(sqrt(\w)) , \(\k3/(\u)^2)
}
\text{reps=1,2,3,4,5}
#endif
#if defined TARGET_expression5
\function{w1=x^2 + \e}
\function{w2=x^2 - \f}
v
\text{liste=\(\k1(\u)(\v)),\((\v)(\w1)),\(\k2(\u)(\v)^2),\(\k3(\w1)^2),\((\v/\k2)^2),
 \((\v)(\w2)), \((\u)^2 + \e), \(\k1(\w2)), \(\k3 + (\u)(\v)) , \(\k2 ((x-\a)^2 - \e)), \(sqrt(\w1)),\(\k2(\u)/(\v))
}
\text{reps=1,2,3,4,5}
#endif
\statement{
<div class="monenonce">
\name_enonce
<div class="wimscenter">\embed{\reply1}</div>
</div>}

\answer{}{\reps ; \liste}{type=checkbox}{option=shuffle}
