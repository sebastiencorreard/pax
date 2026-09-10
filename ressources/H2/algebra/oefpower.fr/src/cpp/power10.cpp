target=power10
#include "lang_titles.inc"
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{10000}

\integer{n=randint(2..11)*randitem(1,-1)}
\integer{m=randint(2..11)*randitem(1,-1)}
\integer{p=randint(2..11)*randitem(1,-1)}
\integer{o=randint(2..11)*randitem(1,-1)}
\integer{q=randint(2..11)*randitem(1,-1)}
\text{a=10^{\n}}
\text{b=10^(\m)}
\text{c=10^(\o)}
\text{d=10^(\p)}
\text{f=10^(\q)}
\integer{sol= (\n)+(\m)+(\o)-(\p)-(\q)}

\statement{\name_statement \(10^n\):
<div class="wimscenter">
<label for="reply1">\(\frac{10^{\n}\times 10^{\m} \times 10^{\o}}{10^{\p}\times 10^{\q}})
</label>= 10<sup><sup>\embed{reply 1,3}</sup></sup></div>
}
\answer{\name_answer}{\sol}{type=numeric}
