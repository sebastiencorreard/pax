\integer{eff1=randint(0..3)}
\integer{eff2=randint(4..8)}
\integer{eff3=randint(8..12)}
\integer{eff4=randint(7..10)}
\integer{eff5=randint(1..3)}

\integer{effc1=\eff1}
\integer{effc2=\effc1+\eff2}
\integer{effc3=\effc1+\eff2+\eff3}
\integer{effc4=\effc1+\eff2+\eff3+\eff4}
\integer{effc5=\effc1+\eff2+\eff3+\eff4+\eff5}

\real{freq1=floor(1000*\eff1/\effc5)/10}
\real{freq2=floor(1000*\eff2/\effc5)/10}
\real{freq3=floor(1000*\eff3/\effc5)/10}
\real{freq4=floor(1000*\eff4/\effc5)/10}
\real{freq5=floor(1000*\eff5/\effc5)/10}
