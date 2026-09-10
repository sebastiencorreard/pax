target=oefecrit101 oefecrit102

#include "author.inc"
\precision{100000}
#include "lang_titles.inc"
#include "lang.inc"
\integer{n=randint(3..6)}
\text{chiff=shuffle(9)}
\text{ord=}
\for{a=1 to \n}{\text{ord=wims(append item \a to \ord)}}
\text{dix=1,10,100,1 000,10 000,100 000}
\integer{large=5}
#if defined TARGET_oefecrit101
\if{\n=3}{\text{pos=1,2,3}}
\if{\n=4}{\text{pos=0,1,2,3}}
\if{\n=5}{\text{pos=0,1,2,3,0}}
\if{\n=6}{\text{pos=0,1,0,2,3,0}}
\text{pos=shuffle(\pos)}
\for{j=1 to 6}{\if{\pos[\j]=1}{\integer{rep1=10^(\j-1)}}}
\for{j=1 to 6}{\if{\pos[\j]=2}{\integer{rep2=10^(\j-1)}}}
\for{j=1 to 6}{\if{\pos[\j]=3}{\integer{rep3=10^(\j-1)}}}
\integer{nb=0}
\for{i=1 to \n}{\integer{nb=\nb+\chiff[\i]*10^(\i-1)}}
#endif
#if defined TARGET_oefecrit102
\text{ord=shuffle(\ord)}
\if{\n=3}{\text{pos=1,2,3}}
\if{\n=4}{\text{pos=0,1,2,3}}
\if{\n=5}{\text{pos=0,1,2,3,0}}
\if{\n=6}{\text{pos=0,1,0,2,3,0}}
\text{pos=shuffle(\pos)}
\for{j=1 to 6}{\if{\pos[\j]=1}{\integer{rep1=10^(\j-1)}}}
\for{j=1 to 6}{\if{\pos[\j]=2}{\integer{rep2=10^(\j-1)}}}
\for{j=1 to 6}{\if{\pos[\j]=3}{\integer{rep3=10^(\j-1)}}}
\integer{nb=0}
\for{i=1 to \n}{\integer{nb=\nb+\chiff[\i]*10^(\i-1)}}
#endif
\statement{
\name_statement: \(\nb =\)
\if{\n=3}{(\chiff[\ord[3]] x \embed{r\pos[\ord[3]],\large}) + (\chiff[\ord[2]] x \embed{r\pos[\ord[2]],\large}) +(\chiff[\ord[1]] x \embed{r\pos[\ord[1]],\large})}
\if{\n=4}{
    \if{\pos[\ord[4]]=0}{(\chiff[\ord[4]] x \dix[\ord[4]]) +}{(\chiff[\ord[4]] x \embed{r\pos[\ord[4]],\large}) + }
    \if{\pos[\ord[3]]=0}{(\chiff[\ord[3]] x \dix[\ord[3]]) +}{(\chiff[\ord[3]] x \embed{r\pos[\ord[3]],\large}) + }
    \if{\pos[\ord[2]]=0}{(\chiff[\ord[2]] x \dix[\ord[2]]) +}{(\chiff[\ord[2]] x \embed{r\pos[\ord[2]],\large}) + }
    \if{\pos[\ord[1]]=0}{(\chiff[\ord[1]] x \dix[\ord[1]]) }{(\chiff[\ord[1]] x \embed{r\pos[\ord[1]],\large})}
}
\if{\n=5}{
    \if{\pos[\ord[5]]=0}{(\chiff[\ord[5]] x \dix[\ord[5]]) +}{(\chiff[\ord[5]] x \embed{r\pos[\ord[5]],\large}) + }
    \if{\pos[\ord[4]]=0}{(\chiff[\ord[4]] x \dix[\ord[4]]) +}{(\chiff[\ord[4]] x \embed{r\pos[\ord[4]],\large}) + }
    \if{\pos[\ord[3]]=0}{(\chiff[\ord[3]] x \dix[\ord[3]]) +}{(\chiff[\ord[3]] x \embed{r\pos[\ord[3]],\large}) + }
    \if{\pos[\ord[2]]=0}{(\chiff[\ord[2]] x \dix[\ord[2]]) +}{(\chiff[\ord[2]] x \embed{r\pos[\ord[2]],\large}) + }
    \if{\pos[\ord[1]]=0}{(\chiff[\ord[1]] x \dix[\ord[1]]) }{(\chiff[\ord[1]] x \embed{r\pos[\ord[1]],\large})}
}
\if{\n=6}{
    \if{\pos[\ord[6]]=0}{(\chiff[\ord[6]] x \dix[\ord[6]]) +}{(\chiff[\ord[6]] x \embed{r\pos[\ord[6]],\large}) + }
    \if{\pos[\ord[5]]=0}{(\chiff[\ord[5]] x \dix[\ord[5]]) +}{(\chiff[\ord[5]] x \embed{r\pos[\ord[5]],\large}) + }
    \if{\pos[\ord[4]]=0}{(\chiff[\ord[4]] x \dix[\ord[4]]) +}{(\chiff[\ord[4]] x \embed{r\pos[\ord[4]],\large}) + }
    \if{\pos[\ord[3]]=0}{(\chiff[\ord[3]] x \dix[\ord[3]]) +}{(\chiff[\ord[3]] x \embed{r\pos[\ord[3]],\large}) + }
    \if{\pos[\ord[2]]=0}{(\chiff[\ord[2]] x \dix[\ord[2]]) +}{(\chiff[\ord[2]] x \embed{r\pos[\ord[2]],\large}) + }
    \if{\pos[\ord[1]]=0}{(\chiff[\ord[1]] x \dix[\ord[1]]) }{(\chiff[\ord[1]] x \embed{r\pos[\ord[1]],\large})}
}
}
\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
\answer{}{\rep3}{type=numeric}
