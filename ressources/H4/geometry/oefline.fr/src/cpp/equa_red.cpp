target=equa_red

#include "header.inc"
#include "lang_titles.inc"

\keywords{line_equation}
\text{equg=a}
\text{equr=a}
\for{i=1 to 3}{
\integer{a=random(-1,1)*randint(1..10)}
\integer{b=random(-1,1)*randint(1..10)}
\integer{c=random(-1,1)*randint(1..10)}
\function{f=maxima(\a*x+\b*y+\c)}
\function{fr=maxima(-\a*x/\b-\c/\b)}
\text{equg=\equg,
\(\f= 0\)
}
\text{equr=\equr,
\(y = \fr\)
}
\function{f=maxima(-\a*x+\b*y+\c)}
\function{fr=maxima(\a*x/\b-\c/\b)}
\text{equg=\equg,
\(\f = 0\)
}
\text{equr=\equr,
\(y = \fr\)
}
}

\text{equg=item(2..7,\equg)}
\text{equr=item(2..7,\equr)}

#include "lang.inc"

\statement{
\name_statement:
<div class="wimscenter">\embed{reply 1, 100 x 200 x 200}</div>
}

\answer{}{\equg;\equr}{type=correspond}{option=shuffle}
