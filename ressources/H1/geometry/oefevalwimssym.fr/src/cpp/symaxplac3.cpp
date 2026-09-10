target=symaxplac3

#define NUM 3
#include "lang_titles.inc"
#include "author.inc"
\keywords{symmetry}
\text{col=lightblue}
\real{x1=0}
\real{y1=0.4*randint(-20..20)}
\real{x2=-\x1}
\real{y2=\y1}

\real{x=250+\x2*25+5}
\real{y=250-\y2*25-5}

\text{dessinmod=hline 0,0,\col
vline 0,0,black
text black,-1,9,large,D1}

#include "dessinsymmax.inc"
\statement{
#include "stat_symaxplac.inc"
}

\answer{}{\dessin;circle,\x,\y,12}{type=coord}
