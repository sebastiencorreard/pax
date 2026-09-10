%% generation des effectifs
\text{lsteff=}
\integer{someff=0}
\integer{resteval=\efftotal/100}
\integer{borneeff=round(\efftotal/(\nbval-\resteval))}
\for{i=1 to \nbval-\resteval}{
  \integer{eff=randint(5..\borneeff)}
  \integer{someff=\someff+\eff}
  \text{lsteff=wims(append item \eff to \lsteff)}
}
\for{i=1 to \resteval-1}{
  \integer{eff=(\efftotal-\someff)/\resteval}
  \integer{someff=\someff+\eff}
  \text{lsteff=wims(append item \eff to \lsteff)}
}
\integer{eff=\efftotal-\someff}
\text{lsteff=wims(append item \eff to \lsteff)}
\text{lsteff=shuffle(\lsteff)}
