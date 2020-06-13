# SOF
# Makefile

# This allow to change the colours of all exisiting sessions configuration

all:
	@echo "available colors themes"
	@echo " nord from https://raw.githubusercontent.com/arcticicestudio/nord-putty/develop/src/nord.reg"
	@echo " solarized dark & light from https://ethanschoonover.com/solarized/"

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

# Solarized light
solarized_light: export COLOR0 := 101,123,131
solarized_light: export COLOR1 := 88,110,117
solarized_light: export COLOR2 := 253,246,227
solarized_light: export COLOR3 := 238,232,213
solarized_light: export COLOR4 := 238,232,213
solarized_light: export COLOR5 := 101,123,131
solarized_light: export COLOR6 := 7,54,66
solarized_light: export COLOR7 := 0,43,54
solarized_light: export COLOR8 := 220,50,47
solarized_light: export COLOR9 := 203,75,22
solarized_light: export COLOR10 := 133,153,0
solarized_light: export COLOR11 := 88,110,117
solarized_light: export COLOR12 := 181,137,0
solarized_light: export COLOR13 := 101,123,131
solarized_light: export COLOR14 := 38,139,210
solarized_light: export COLOR15 := 131,148,150
solarized_light: export COLOR16 := 211,54,130
solarized_light: export COLOR17 := 108,113,196
solarized_light: export COLOR18 := 42,161,152
solarized_light: export COLOR19 := 147,161,161
solarized_light: export COLOR20 := 238,232,213
solarized_light: export COLOR21 := 253,246,227
solarized_light: color

# Solarized dark
solarized_dark: export COLOR0 := 131,148,150
solarized_dark: export COLOR1 := 147,161,161
solarized_dark: export COLOR2 := 0,43,54
solarized_dark: export COLOR3 := 7,54,66
solarized_dark: export COLOR4 := 0,43,54
solarized_dark: export COLOR5 := 238,232,213
solarized_dark: export COLOR6 := 7,54,66
solarized_dark: export COLOR7 := 0,43,56
solarized_dark: export COLOR8 := 220,50,47
solarized_dark: export COLOR9 := 203,75,22
solarized_dark: export COLOR10 := 133,153,0
solarized_dark: export COLOR11 := 88,110,117
solarized_dark: export COLOR12 := 181,137,0
solarized_dark: export COLOR13 := 101,123,131
solarized_dark: export COLOR14 := 38,139,210
solarized_dark: export COLOR15 := 131,148,150
solarized_dark: export COLOR16 := 211,54,130
solarized_dark: export COLOR17 := 108,113,196
solarized_dark: export COLOR18 := 42,161,152
solarized_dark: export COLOR19 := 147,161,161
solarized_dark: export COLOR20 := 238,232,213
solarized_dark: export COLOR21 := 253,246,227
solarized_dark: color

# The main part, which change the colors
color:
	@git checkout test.reg
	@vim -s change_putty_colors.vim test.reg
	@head -10 test.reg|tail -7

# vim : se ft=make :
# EOF
