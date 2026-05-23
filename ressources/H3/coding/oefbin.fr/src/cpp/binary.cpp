target=binary
\language{fr}
\range{-5..5}

\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{S=pari(k=3;n=0;nbin=0; for(i=1,k, n1=RANDOM(2); n=n+n1*2^(i-1);
nbin=nbin+n1*10^(i-1)); [n,nbin])}
\text{n=item(1,\S)}
\text{nbin=item(2,\S)}

\integer{k=5}
\integer{n=0}
\integer{nbin=0}
\text{liste=2}
\for{i=1 to \k}{
  \integer{n1=random(1,0)}
  \integer{n= \n+\n1*2^(\i-1)}
  \integer{nbin=\nbin+\n1*10^(\i-1)}
  \text{liste=  \liste, \n1}
  }
\text{nbin=pari(\nbin)}
\text{rep1=item(\k+1,\liste)}
\text{rep2=item(\k,\liste)}
\text{rep3=item(\k-1,\liste)}
\text{rep4=item(\k-2,\liste)}
\text{rep5=item(\k-3,\liste)}

\statement{ \name_enonce[1] \n \name_enonce[2]

<table class="wimscenter wimsborder">
 <tr>
  <th>\name_power 2</th>
  <th> \(2^4)</th>
  <th> \(2^3)</th>
  <th> \(2^2)</th>
  <th>\(2^1)</th>
  <th>\(2^0) </th>
</tr><tr>
  <td></td>
  <td>16</td>
  <td>8</td>
  <td>4</td>
  <td>2</td>
  <td>1</td>
</tr><tr>
   <td>\n</td>
  <td>\embed{reply 1,4}</td>
  <td>\embed{reply 2,4}</td>
  <td>\embed{reply 3,4}</td>
  <td>\embed{reply 4,4}</td>
  <td>\embed{reply 5,4}</td>
</tr>
</table>}


\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
\answer{}{\rep3}{type=numeric}
\answer{}{\rep4}{type=numeric}
\answer{}{\rep5}{type=numeric}
\feedback{1=1}{\name_feed[1] \n \name_feed[2] \nbin}
