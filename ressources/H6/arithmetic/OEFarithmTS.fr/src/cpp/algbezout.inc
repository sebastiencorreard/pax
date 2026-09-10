/// relation de bezout liant bza et bzb
\integer{bza1=1}
\integer{bza2=0}
\integer{bza3=\bza}
\integer{bzb1=0}
\integer{bzb2=1}
\integer{bzb3=\bzb}
\while{\bza3<>0}{
  \integer{bzt1=\bza1}
  \integer{bzt2=\bza2}
  \integer{bzt3=\bza3}
  \integer{bza1=\bzb1-\bza1*floor(\bzb3/\bza3)}
  \integer{bza2=\bzb2-\bza2*floor(\bzb3/\bza3)}
  \integer{bza3=\bzb3-\bza3*floor(\bzb3/\bza3)}
  \integer{bzb1=\bzt1}
  \integer{bzb2=\bzt2}
  \integer{bzb3=\bzt3}
}
/// bzb1=u, bzb2=v et bzb3=gcd(bza,bzb)
