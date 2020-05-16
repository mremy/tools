# SOF
# Makefile

# This allow to change the colours of all exisiting sessions configuration

all:
	@echo "available colors themes"
	@echo " nord from https://raw.githubusercontent.com/arcticicestudio/nord-putty/develop/src/nord.reg"

# nord colors theme
nord: export COLOR0 := 216,222,233
nord: export COLOR1 := 216,222,233
nord: export COLOR2 := 46,52,64
nord: export COLOR3 := 46,52,64
nord: export COLOR4 := 46,52,64
nord: export COLOR5 := 216,222,233
nord: export COLOR6 := 59,66,82
nord: export COLOR7 := 76,86,106
nord: export COLOR8 := 191,97,106
nord: export COLOR9 := 191,97,106
nord: export COLOR10 := 163,190,140
nord: export COLOR11 := 163,190,140
nord: export COLOR12 := 235,203,139
nord: export COLOR13 := 235,203,139
nord: export COLOR14 := 129,161,193
nord: export COLOR15 := 129,161,193
nord: export COLOR16 := 180,142,173
nord: export COLOR17 := 180,142,173
nord: export COLOR18 := 136,192,208
nord: export COLOR19 := 143,188,187
nord: export COLOR20 := 239,233,240
nord: export COLOR21 := 226,239,244
nord: color

# The main part, which change the colors
color:
	@git checkout test.reg
	@vim -s change_putty_colors.vim test.reg
	@head -10 test.reg|tail -7

# vim : se ft=make :
# EOF
