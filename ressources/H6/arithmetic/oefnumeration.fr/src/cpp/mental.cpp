target=mental

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\text{base=randint(5,6,7,3)}
\text{a=pari(random\(10000) + 70)}
\text{b=pari(random\(\a-60))}
\text{a = wims(exec float_calc
obase=\base; ibase=10;\a)}

\text{b = wims(exec float_calc
obase=\base; ibase=10;\b)}

\text{c =wims(exec float_calc
obase=\base; ibase=\base;\a - \b)}

\real{p = floor(log(\b)/log(10))+1}
\text{p=wims(exec float_calc
obase=\base; ibase=10;\p)}

\text{differ = wims(exec float_calc
obase=\base; ibase=\base;10^\p - \b)}

\text{somme = wims(exec float_calc
obase=\base; ibase=\base; \a + \differ)}

#include "lang.inc"
\text{size=\p}
\statement{\name_statement

<table class="wimsborder wimscenter">
<tr><th>
\name_numbdig \(p\) \name_of \(\b\)</th><td>
\embed{reply1,\p}
</td></tr>
<tr><th>
\(10^p - \b\)</th><td> \embed{reply2,\p}
</td></tr>
<tr><td></td><td>\(\a\)</td></tr>
<tr><th>
\(\a + (10^p - \b) \)</th><td>\embed{reply3,\p}
</td></tr>
<tr><th>
\(\a - \b\)</th><td> \embed{reply4,\p}
</td></tr>
</table>
<div class="wims_instruction">\name_instruction</div>
}
\answer{\(p\)}{\p}{type=numexp}
\answer{\(10^p - \b\)}{\differ}{type=numexp}
\answer{\(\a + (10^p - \b)\)}{\somme}{type=numexp}
\answer{\(\a - \b\)}{\c}{type=numexp}
\help{\name_help1
<ul>
<li>
\name_help2
<div class="wimscenter">\(\a + (10^p - \b) - 10^p\). </div>
</li><li>
\name_help3
</li><li>
\name_help4
</li></ul>
}
