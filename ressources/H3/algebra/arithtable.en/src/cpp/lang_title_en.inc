#if defined TARGET_partial2x2 || defined TARGET_partial2x3 || defined TARGET_partial2x4 || defined TARGET_partial3x3 || defined TARGET_partial3x4
# define TIT Partial table
#endif
#if defined TARGET_typed2x2 || defined TARGET_typed2x3 || defined TARGET_typed2x4 || defined TARGET_typed3x3 || defined TARGET_typed3x4
# define TIT Typed table
#endif
#if defined TARGET_table2x2 || defined TARGET_table2x3 || defined TARGET_table2x4 || defined TARGET_table2x5 || defined TARGET_table2x6 || defined TARGET_table2x7 || defined TARGET_table3x3 || defined TARGET_table3x4 || defined TARGET_table3x5 || defined TARGET_table4x4
# define TIT Arithmetic table
#endif
