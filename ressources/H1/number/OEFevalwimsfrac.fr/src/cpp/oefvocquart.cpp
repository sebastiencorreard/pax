target=oefvocabquart1 oefvocabquart2 oefvocabquart3 oefvocabquart4 oefvocabquart5
#define TITRE Vocabulaire sur les fractions
\langage{fr}
\author{Jean-Luc,Donadoni}
\email{jluc.donadoni@laposte.net}
\format{html}

\text{mot=la moitié,le double,le tiers,le triple,le quart,le quadruple}
\text{mot2=La moitié,Le double,Le tiers,Le triple,Le quart,Le quadruple}
\integer{f=randint(1..3)}

#if defined TARGET_oefvocabquart1
\title{TITRE 1}
\integer{a=randint(1..15)}
\integer{b=\a*(\f+1)}
\integer{n=2*(\f-1)+1}
\text{enonc=\mot2[\n] du nombre \b est le nombre : }
\text{rep=\a}
\integer{large=5}
#endif

#if defined TARGET_oefvocabquart2
\title{TITRE 2}
\integer{a=randint(1..15)}
\integer{b=\a*(\f+1)}
\integer{n=2*\f}
\text{enonc= \mot2[\n] du nombre \a est le nombre : }
\text{rep=\b}
\integer{large=5}
#endif

#if defined TARGET_oefvocabquart3
\title{TITRE 3}
\integer{a=randint(1..15)}
\integer{b=\a*(\f+1)}
\integer{n=2*(\f-1)+1}
\text{enonc=Le nombre \a est }
\text{enonc2=du nombre \b }
\text{rep=\mot[\n]}
\integer{large=12}
#endif

#if defined TARGET_oefvocabquart4
\title{TITRE 4}
\integer{a=randint(1..15)}
\integer{b=\a*(\f+1)}
\integer{n=2*\f}
\text{enonc=Le nombre \b est }
\text{enonc2=du nombre \a }
\text{rep=\mot[\n]}
\integer{large=12}
#endif

#if defined TARGET_oefvocabquart5
\title{TITRE 5}
\integer{a=randint(1..15)}
\integer{b=\a*(\f+1)}
\integer{i=randint(1..2)}
\if{\i=1}{\integer{n=2*(\f-1)+1}}
{\integer{n=2*\f}}
\if{\i=1}{\text{enonc=Le nombre \a est }
\text{enonc2=du nombre \b }}
{\text{enonc=Le nombre \b est }
\text{enonc2=du nombre \a }}
\text{rep=\mot[\n]}
\integer{large=12}
#endif

\statement{\enonc \embed{r1,\large} \enonc2}

\answer{}{\rep}
