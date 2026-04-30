#if defined TARGET_giocatore
# define TITLE_en You choose first
#endif
#if defined TARGET_computer
# define TITLE_en The computer chooses first
#endif
#if defined TARGET_partita
# define TITLE_en A single game
#endif
#if defined TARGET_pairs1
# define TITLE_en LEVEL: Stages in the game
#endif
#if defined TARGET_pairs2
# define TITLE_en LEVEL: Triplet comparisons
#endif
#if defined TARGET_pairs3
# define TITLE_en LEVEL: Four tosses
#endif
#if defined TARGET_pairs4
# define TITLE_en LEVEL: Comparing probabilities
#endif
#if defined TARGET_single1
# define TITLE_en LEVEL: Probability for a triplet
#endif
#if defined TARGET_single2
# define TITLE_en LEVEL: Four coin tosses
#endif
\if{\lang=en}{
  \text{testa=H}
  \text{croce=T}
}