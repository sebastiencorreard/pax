target=symaxplac5
#define NUM 5
#include "lang_titles.inc"
#include "author.inc"
\keywords{symmetry}
\text{col=lightblue}
\real{x1=2*randint(-4..4)}
\real{y1=2*randint(-4..4)}
\real{x2=\y1}
\real{y2=\x1}

\real{x=250+\x2*25+5}
\real{y=250-\y2*25-5}

\text{dessinmod=hline 0,0,\col
vline 0,0,\col
segment 10,10,-10,-10,black
text black,9,9,large,D1}

#include "dessinsymmax.inc"
\statement{
  #include "stat_symaxplac.inc"
}

\answer{}{\dessin;circle,\x,\y,12}{type=coord}
