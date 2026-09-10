target=div1
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
\integer{b11=random(1..\range)*random(-1,1)}
\integer{b12=random(1..\range)*random(-1,1)}
\integer{b13=random(1..\range)*random(-1,1)}
\integer{b14=random(1..\range)*random(-1,1)}
\integer{b15=random(1..\range)*random(-1,1)}
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
\integer{x0=random(-2..2)}
\integer{a1=item(\x0+3,\a11,\a12,\a13,\a14,\a15)}
\integer{a2=item(\x0+3,\a21,\a22,\a23,\a24,\a25)}
\integer{b1=item(\x0+3,\b11,\b12,\b13,\b14,\b15)}
\integer{b2=item(\x0+3,\b21,\b22,\b23,\b24,\b25)}
\real{sol=(\a2*(\b1)-(\a1)*(\b2))/(\b1)^2}
\statement{\name_enonce:
<table class="wimscenter wimsborder">
<tr><th>x</th><th>-2</th><th>-1</th><th>0</th><th>1</th><th>2</th></tr>
<tr><th>\(f(x))</th>
<td>\a11</td><td>\a12</td><td>\a13</td><td>\a14</td><td>\a15</td></tr>
<tr><th>\(f '(x))</th>
<td>\a21</td><td>\a22</td><td>\a23</td><td>\a24</td><td>\a25</td></tr>
<tr><th>\(g(x))</th>
<td>\b11</td><td>\b12</td><td>\b13</td><td>\b14</td><td>\b15</td></tr>
<tr><th>\(g'(x))</th>
<td>\b21</td><td>\b22</td><td>\b23</td><td>\b24</td><td>\b25</td></tr>
</table>
\name_question[1] \(h(x) = f(x)/g(x)\). \name_question[2] \(h'(\x0)\).
}

\answer{\(h'(\x0)\)}{\sol}{type=numeric}
