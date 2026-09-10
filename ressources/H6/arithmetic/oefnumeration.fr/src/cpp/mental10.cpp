target=mental10

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\text{base=10}
\text{a=pari(random\(100000000) + 7000)}
\text{b=pari(random\(\a-6000))}
\text{ c = pari (\a-\b)}
\real{p = floor(log(\b)/log(\base))+1}
\text{differ = pari(10^(\p) - \b)}
\text{somme = pari(\a + \differ)}

#include "lang.inc"

\statement{\name_statement

<table class="wimsborder wimscenter">
<tr><td>
 \name_numbdig \(p\) \name_of \(\b\) : </td><td>
\embed{reply1}
</td></tr>
<tr><td>
\(10^p - \b\)</td><td> \embed{reply2}
</td></tr>
<tr><td></td><td>\(\a\)</td></tr>
<tr><td>
\(\a + (10^p - \b) \)</td><td>\embed{reply3}
</td></tr>
<tr><td>
\(\a - \b\)</td><td> \embed{reply4}
</td></tr>
</table>
}
\answer{\(p\)}{\p}
\answer{\(10^p - \b\)}{\differ}
\answer{\(\a + (10^p - \b)\)}{\somme}
\answer{\(\a - \b\)}{\c}
\help{\name_help1
<ul>
<li>\name_help2
<div class="wimscenter">\(\a + (10^p - \b) - 10^p\). </div>
</li><li>
\name_help3
</li><li>
\name_help4
</li></ul>
\name_help5}

