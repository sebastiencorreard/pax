target=terminologie1
%% Expression ou équation ou proposition
\language{fr}
\computeanswer{yes}
\precision{1000}
\format{html}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a = random(2..5)}
\integer{b = (-1)^random(0,1)*random(1..5)}
\integer{c = (-1)*random(2..5)}
\integer{d = (-1)^random(0,1)*random(1..5)}

\integer{min = (-1)^random(0,1)*random(1..10)}
\integer{max = \min + random(1..5)}

\function{u=\a*x + \b}
\function{v= \d+\c*x}
\function{w=\a*x^2 + \b*x + \c}
\rational{sol= (\d-\b)/(\a-\c)}

\text{reps= 2,3,1,1,2,3,3,1,1}

\text{ind=shuffle(9)}
\text{phrases=wims(replace internal UUUU by \u in \phrases)}
\text{phrases=wims(replace internal VVVV by \v in \phrases)}
\text{phrases=wims(replace internal WWWW by \w in \phrases)}
\statement{
<div class="monenonce">
\name_enonce
<ol>
\for{i = 1 to 6}{<li> \phrases[\ind[\i];] \embed{reply\i}</li>}
</ol>
</div>
}
\answer{}{\reps[\ind[1]] ; \liste}{type=menu}
\answer{}{\reps[\ind[2]] ; \liste}{type=menu}
\answer{}{\reps[\ind[3]]; \liste}{type=menu}
\answer{}{\reps[\ind[4]] ; \liste}{type=menu}
\answer{}{\reps[\ind[5]] ; \liste}{type=menu}
\answer{}{\reps[\ind[6]] ; \liste}{type=menu}
