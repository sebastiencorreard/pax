#if defined TARGET_basic
# define TITRE resistor
#endif
#if defined TARGET_parallel
# define TITRE parallel
#endif
#if defined TARGET_serial
# define TITRE serial
#endif
#if defined TARGET_par3
# define TITRE parallel
#endif
#if defined TARGET_ser3
# define TITRE serial
#endif
#if defined TARGET_h
# define TITRE type h
#endif
#if defined TARGET_li
# define TITRE type il
#endif
#if defined TARGET_parser
# define TITRE parallel + serial
#endif
#if defined TARGET_bridge
# define TITRE type H
#endif
