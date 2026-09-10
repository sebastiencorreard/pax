target=mult1 mult2 multmixt

#if defined TARGET_mult1
# define NUM I
#endif
#if defined TARGET_mult2
# define NUM II
#endif
\language{fr}
\range{-5..5}
#include "xiao.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\integer{range=15}
\integer{a11=random(-\range..\range)}
\integer{a12=random(-\range..\range)}
\integer{a13=random(-\range..\range)}
\integer{a14=random(-\range..\range)}
\integer{a15=random(-\range..\range)}
\integer{a21=random(-\range..\range)}
\integer{a22=random(-\range..\range)}
\integer{a23=random(-\range..\range)}
\integer{a24=random(-\range..\range)}
\integer{a25=random(-\range..\range)}
\integer{a31=random(-\range..\range)}
\integer{a32=random(-\range..\range)}
\integer{a33=random(-\range..\range)}
\integer{a34=random(-\range..\range)}
\integer{a35=random(-\range..\range)}
#if defined TARGET_mult1 || defined TARGET_mult2
\integer{b11=random(-\range..\range)}
\integer{b12=random(-\range..\range)}
\integer{b13=random(-\range..\range)}
\integer{b14=random(-\range..\range)}
\integer{b15=random(-\range..\range)}
\integer{b21=random(-\range..\range)}
\integer{b22=random(-\range..\range)}
\integer{b23=random(-\range..\range)}
\integer{b24=random(-\range..\range)}
\integer{b25=random(-\range..\range)}
\integer{b31=random(-\range..\range)}
\integer{b32=random(-\range..\range)}
\integer{b33=random(-\range..\range)}
\integer{b34=random(-\range..\range)}
\integer{b35=random(-\range..\range)}
#endif
\integer{x0=random(-2..2)}
\integer{a1=item(\x0+3,\a11,\a12,\a13,\a14,\a15)}
\integer{a2=item(\x0+3,\a21,\a22,\a23,\a24,\a25)}
#if defined TARGET_mult1 || defined TARGET_mult2
\integer{b1=item(\x0+3,\b11,\b12,\b13,\b14,\b15)}
\integer{b2=item(\x0+3,\b21,\b22,\b23,\b24,\b25)}
#endif
#if defined TARGET_mult1
\integer{sol=\a1*(\b2)+(\a2)*(\b1)}
#endif
#if defined TARGET_mult2
\integer{a3=item(\x0+3,\a31,\a32,\a33,\a34,\a35)}
\integer{b3=item(\x0+3,\b31,\b32,\b33,\b34,\b35)}
\integer{sol=\a1*(\b3)+(\a3)*(\b1)+2*(\a2)*(\b2)}
#endif
#if defined TARGET_multmixt
\integer{c1=random(2..\range)*random(-1,1)}
\integer{c2=random(2..\range)*random(-1,1)}
\integer{c3=random(2..\range)*random(-1,1)}
\integer{d1=random(1..\range)*random(-1,1)}
\integer{d2=random(1..\range)*random(-1,1)}
\integer{d3=random(1..\range)*random(-1,1)}
\integer{p1=random(2..5)}
\function{g=random(
	(\c1*x^2+\c2*x+\d1),
	(\c1*x^2+\c2*x+\d1),
	sin(\c1*x+\d1),
	cos(\c1*x+\d1),
	(\c1*x+\d1)^\p1,
	(\c1*sin(x)+\c2*cos(x))
)}
\real{b1=evalue(\g,x=\x0)}
\function{diff=diff(\g,x)}
\text{hg=texmath(\g)}
\real{b2=evalue(\diff,x=\x0)}
\real{sol=\a1*(\b2)+(\a2)*(\b1)}
#endif
#if defined TARGET_mult1 || defined TARGET_multmixt
\text{hh=h'(\x0)}
#endif
#if defined TARGET_mult2
\text{hh=h''(\x0)}
#endif
\statement{\name_enonce:
<table class="wimscenter wimsborder">
<tr><th>\(x\)</th><th>-2</th><th>-1</th><th>0</th><th>1</th><th>2</th></tr>
<tr><th>\(f(x)\)</th>
<td>\a11</td><td>\a12</td><td>\a13</td><td>\a14</td><td>\a15</td></tr>
<tr><th>\(f '(x)\)</th>
<td>\a21</td><td>\a22</td><td>\a23</td><td>\a24</td><td>\a25</td></tr>
#if defined TARGET_mult1 || defined TARGET_mult2
# if defined TARGET_mult2
<tr><th>\(f ''(x)\)</th>
<td>\a31</td><td>\a32</td><td>\a33</td><td>\a34</td><td>\a35</td></tr>
# endif
<tr><th>\(g(x)\)</th>
<td>\b11</td><td>\b12</td><td>\b13</td><td>\b14</td><td>\b15</td></tr>
<tr><th>\(g'(x)\)</th>
<td>\b21</td><td>\b22</td><td>\b23</td><td>\b24</td><td>\b25</td></tr>
# if defined TARGET_mult2
<tr><th>\(g''(x)\)</th>
<td>\b31</td><td>\b32</td><td>\b33</td><td>\b34</td><td>\b35</td></tr>
# endif
#endif
</table>
\name_question[1]
#if defined TARGET_mult1 || defined TARGET_mult2
\(h = f g\).
#endif
#if defined TARGET_multmixt
\(h(x) = \hg f(x)\).
#endif
\name_question[2] \(\hh\).
}
\answer{\(\hh\)}{\sol}{type=numeric}
#if defined TARGET_multmixt
\hint{\name_hint[1] \hg \name_hint[2] \(x_0=\x0\),
  \name_hint[3]}
\solution{\name_sol[1] \(g(x)=\hg\). \name_sol[2] \(g(\x0)=\b1\),
\(g'(\x0)=\b2\), \name_sol[3]<div class="wimscenter">
 \(h'(\x0) = f(\x0)g'(\x0) + f '(\x0)g(\x0) = (\a1)(\b2) + (\a2)(\b1) = \sol.\)
</div>
}
#endif
