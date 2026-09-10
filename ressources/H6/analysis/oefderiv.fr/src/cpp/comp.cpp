target=comp1 comp2 compmixt
#if defined TARGET_comp1
# define NUM I
#endif
#if defined TARGET_comp2
# define NUM II
#endif
\language{fr}
\range{-5..5}
#include "xiao.inc"
#if defined TARGET_comp1
\computeanswer{no}
#endif
#if defined TARGET_comp2 || defined TARGET_compmixt
\computeanswer{yes}
#endif
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\integer{range=15}
#if defined TARGET_comp1 || defined TARGET_comp2
\integer{a11=random(-\range..\range)}
\integer{a12=random(-\range..\range)}
\integer{a13=random(-\range..\range)}
\integer{a14=random(-\range..\range)}
\integer{a15=random(-\range..\range)}
\integer{a16=random(-\range..\range)}
\integer{a17=random(-\range..\range)}
#endif
#if defined TARGET_compmixt
\integer{a11=random(1..\range)*random(-1,1)}
\integer{a12=random(1..\range)*random(-1,1)}
\integer{a13=random(1..\range)*random(-1,1)}
\integer{a14=random(1..\range)*random(-1,1)}
\integer{a15=random(1..\range)*random(-1,1)}
#endif
\integer{a21=random(-\range..\range)}
\integer{a22=random(-\range..\range)}
\integer{a23=random(-\range..\range)}
\integer{a24=random(-\range..\range)}
\integer{a25=random(-\range..\range)}
#if defined TARGET_comp1 || defined TARGET_comp2
\integer{a26=random(-\range..\range)}
\integer{a27=random(-\range..\range)}
\integer{b11=random(-3..3)}
\integer{b12=random(-3..3)}
\integer{b13=random(-3..3)}
\integer{b14=random(-3..3)}
\integer{b15=random(-3..3)}
\integer{b16=random(-3..3)}
\integer{b17=random(-3..3)}
\integer{b21=random(-\range..\range)}
\integer{b22=random(-\range..\range)}
\integer{b23=random(-\range..\range)}
\integer{b24=random(-\range..\range)}
\integer{b25=random(-\range..\range)}
\integer{b26=random(-\range..\range)}
\integer{b27=random(-\range..\range)}
# if defined TARGET_comp2
\integer{c11=random(-3..3)}
\integer{c12=random(-3..3)}
\integer{c13=random(-3..3)}
\integer{c14=random(-3..3)}
\integer{c15=random(-3..3)}
\integer{c16=random(-3..3)}
\integer{c17=random(-3..3)}
\integer{c21=random(-\range..\range)}
\integer{c22=random(-\range..\range)}
\integer{c23=random(-\range..\range)}
\integer{c24=random(-\range..\range)}
\integer{c25=random(-\range..\range)}
\integer{c26=random(-\range..\range)}
\integer{c27=random(-\range..\range)}
# endif
\integer{x0=random(-3..3)}
# if defined TARGET_comp1
\integer{b1=item(\x0+4,\b11,\b12,\b13,\b14,\b15,\b16,\b17)}
\integer{a1=item(\b1+4,\a11,\a12,\a13,\a14,\a15,\a16,\a17)}
\integer{a2=item(\b1+4,\a21,\a22,\a23,\a24,\a25,\a26,\a27)}
\integer{b2=item(\x0+4,\b21,\b22,\b23,\b24,\b25,\b26,\b27)}
\integer{sol=\a2*(\b2)}
# endif
# if defined TARGET_comp2
\integer{c1=item(\x0+4,\c11,\c12,\c13,\c14,\c15,\c16,\c17)}
\integer{c2=item(\x0+4,\c21,\c22,\c23,\c24,\c25,\c26,\c27)}
\integer{b1=item(\c1+4,\b11,\b12,\b13,\b14,\b15,\b16,\b17)}
\integer{b2=item(\c1+4,\b21,\b22,\b23,\b24,\b25,\b26,\b27)}
\integer{a1=item(\b1+4,\a11,\a12,\a13,\a14,\a15,\a16,\a17)}
\integer{a2=item(\b1+4,\a21,\a22,\a23,\a24,\a25,\a26,\a27)}
\integer{sol=\a2*(\b2)*(\c2)}
# endif
#endif
#if defined TARGET_compmixt
\integer{x0=random(-2..2)}
\integer{a1=item(\x0+3,\a11,\a12,\a13,\a14,\a15)}
\integer{a2=item(\x0+3,\a21,\a22,\a23,\a24,\a25)}
\integer{c1=random(2..\range)*random(-1,1)}
\integer{c2=random(2..\range)*random(-1,1)}
\integer{c3=random(2..\range)*random(-1,1)}
\integer{d1=random(1..\range)*random(-1,1)}
\integer{d2=random(1..\range)*random(-1,1)}
\integer{d3=random(1..\range)*random(-1,1)}
\integer{p1=random(2..5)}
\function{g=random(
  \c1*x^2+\c2*x+\d1,
  \c1*x^2+\c2*x+\d1,
  sin(\c1*x+\d1),
  cos(\c1*x+\d1),
  (\c1*x+\d1)^\p1,
  \c1*sin(x)+\c2*cos(x)
)}
\real{b1=evalue(\g,x=\a1)}
\function{diff=diff(\g,x)}
\text{hg=texmath(\g)}
\real{b2=evalue(\diff,x=\a1)}
\real{sol=\a2*(\b2)}
#endif
\statement{\name_enonce
<table class="wimscenter wimsborder">
#if defined TARGET_comp1 || defined TARGET_comp2
<tr><th>x</th><th>-3</th><th>-2</th><th>-1</th><th>0</th><th>1</th><th>2</th><th>3</th></tr>
<tr><th>\(f(x)\)</th>
<td>\a11</td><td>\a12</td><td>\a13</td><td>\a14</td><td>\a15</td><td>\a16</td><td>\a17</td></tr>
<tr><th>\(f '(x)\)</th>
<td>\a21</td><td>\a22</td><td>\a23</td><td>\a24</td><td>\a25</td><td>\a26</td><td>\a27</td></tr>
<tr><th>\(g(x)\)</th>
<td>\b11</td><td>\b12</td><td>\b13</td><td>\b14</td><td>\b15</td><td>\b16</td><td>\b17</td></tr>
<tr><th>\(g'(x)\)</th>
<td>\b21</td><td>\b22</td><td>\b23</td><td>\b24</td><td>\b25</td><td>\b26</td><td>\b27</td></tr>
# if defined TARGET_comp2
<tr><th>\(h(x)\)</th>
<td>\c11</td><td>\c12</td><td>\c13</td><td>\c14</td><td>\c15</td><td>\c16</td><td>\c17</td></tr>
<tr><th>\(h'(x)\)</th>
<td>\c21</td><td>\c22</td><td>\c23</td><td>\c24</td><td>\c25</td><td>\c26</td><td>\c27</td></tr>
# endif
#endif
#if defined TARGET_compmixt
<tr><th>x</th><th>-2</th><th>-1</th><th>0</th><th>1</th><th>2</th></tr>
<tr><th>\(f(x)\)</th>
<td>\a11</td><td>\a12</td><td>\a13</td><td>\a14</td><td>\a15</td></tr>
<tr><th>\(f '(x)\)</th>
<td>\a21</td><td>\a22</td><td>\a23</td><td>\a24</td><td>\a25</td></tr>
#endif
</table>
#if defined TARGET_compmixt
\name_question[1] \(g(x) = \)\(\hg\)  \name_question[2] \(s(x) = g(f(x))\).
#endif
#if defined TARGET_comp1 || defined TARGET_comp2
\name_question[1]
# if defined TARGET_comp1
\(s(x) = f(g(x))\).
#endif
# if defined TARGET_comp2
\(s(x) = f(g(h(x)))\).
# endif
#endif
\name_question[3] \(s'(\x0)\).
}
\answer{\(s'(\x0)\)}{\sol}{type=numeric}
#if defined TARGET_comp1
\text{name_sol=On a, d'où,}
\solution{\name_sol[1] \(g(\x0)=\b1\), \name_sol[2]
<p>\(s'(\x0) = f '(g(\x0)) g'(\x0)
= f '(\b1) g'(\x0) = \a2 \times \b2 = \sol\).
</p>
}
#endif
#if defined TARGET_compmixt
\solution{\name_sol[1] <div class="wimscenter">
  \(g'(f(\x0)) = g'(\a1) = \b2\),
</div> \name_sol[2]
<div class="wimscenter">
 \(s'(\x0) = g'(f(\x0)) f '(\x0) =
 (\b2)(\a2) = \sol\).
</div>
}
#endif
