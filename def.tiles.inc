TILE_BASE	= 0
TILE_BLOB	= 2
TILE_BLOCKED	= 4
TILE_TELE	= 6
TILE_PATH	= 8
TILE_CROSS	= 10
TILE_NOP	= 12

DIRECTION_LEFT	= %00
DIRECTION_UP	= %01
DIRECTION_RIGHT	= %10
DIRECTION_DOWN	= %11

PATH_HORIZONTAL	= 0
PATH_VERTICAL	= 2
PATH_POINT_L	= 4
PATH_POINT_U	= 6
PATH_POINT_R	= 8
PATH_POINT_D	= 10
PATH_CORNER_L	= 12
PATH_CORNER_U	= 14
PATH_CORNER_R	= 16
PATH_CORNER_D	= 18

	module tilemap

background	= 0
tilebackground	= 1

edging
.corner_TL	= 0
.corner_TR	= 1
.corner_BL	= 2
.corner_BR	= 3
.edge_TL	= 4
.edge_TR	= 5
.edge_BL	= 6
.edge_BL	= 7
.edge_LU	= 8
.edge_RU	= 9
.edge_LD	= 10
.edge_RD	= 11
.path_L		= 12
.path_R		= 13
.path_U		= 14
.path_D		= 15

base
.void		= 0
.C1		= 4
.C2		= 5
.C3		= 6
.C4		= 7
.ptr		= 16

rotation	= 8
switch		= 12
cross		= 28
blocked
.ptr		= 32
.cross		= 44

colorblob
.C1		= 48
.C2		= 64
.C3		= 80
.C4		= 96

arrow
.L		= 116
.U		= 120
.R		= 124
.D		= 112

tick
.C1		= 128
.C2		= 132
.C3		= 136
.C4		= 140

endpoint
.C1		= 144
.C2		= 148
.C3		= 152
.C4		= 156

teleport	= 160

border
.ptr		= 240
.edgeT		= 240
.edgeR		= 241
.edgeL		= 242
.edgeB		= 243
.inner_TL	= 244
.inner_TR	= 245
.inner_BL	= 246
.inner_BR	= 247
.outer_TL	= 248
.outer_TR	= 249
.outer_BL	= 250
.outer_BR	= 251

	endmodule

;;-----------------------------------------------------------------------------

	macro s2fn fn?, attr?
	opt push listoff
		db	fn?
		db	attr?
	opt pop
	endm

	macro sgap cnt?
	opt push listoff
	dup cnt?
		dw	TILE_NOP
	edup
	opt pop
	endm

	macro s2path tile?, color?
.c = (color?) << 4
	opt push listoff
		s2fn	tile?, .c + PATH_HORIZONTAL	; 128
		s2fn	tile?, .c + PATH_VERTICAL	; 129
		sgap 2
		s2fn	tile?, .c + PATH_POINT_L	; 132
		s2fn	tile?, .c + PATH_POINT_U	; 133
		s2fn	tile?, .c + PATH_POINT_R	; 134
		s2fn	tile?, .c + PATH_POINT_D	; 135
		s2fn	tile?, .c + PATH_CORNER_L	; 136
		s2fn	tile?, .c + PATH_CORNER_U	; 137
		s2fn	tile?, .c + PATH_CORNER_R	; 138
		s2fn	tile?, .c + PATH_CORNER_D	; 139
		sgap 4
	opt pop
	endm

;;-----------------------------------------------------------------------------

		align	256

sprite2fntab:	dw	TILE_NOP			; 000
		s2fn	TILE_BASE, tilemap.base.void	; 001
		s2fn	TILE_BASE, tilemap.switch	; 002
		s2fn	TILE_BLOCKED, tilemap.base.void	; 003
		s2fn	TILE_BLOB, tilemap.colorblob.C1	; 004
		s2fn	TILE_BLOB, tilemap.colorblob.C2	; 005
		s2fn	TILE_BLOB, tilemap.colorblob.C3	; 006
		s2fn	TILE_BLOB, tilemap.colorblob.C4	; 007
		s2fn	TILE_BASE, tilemap.tick.C1	; 008
		s2fn	TILE_BASE, tilemap.tick.C2	; 009
		s2fn	TILE_BASE, tilemap.tick.C3	; 010
		s2fn	TILE_BASE, tilemap.tick.C4	; 011
		s2fn	TILE_BASE, tilemap.arrow.L	; 012
		s2fn	TILE_BASE, tilemap.arrow.U	; 013
		s2fn	TILE_BASE, tilemap.arrow.R	; 014
		s2fn	TILE_BASE, tilemap.arrow.D	; 015
		s2fn	TILE_BASE, tilemap.rotation	; 016
		sgap 15					; 017 ... 031
		s2fn	TILE_TELE, tilemap.teleport	; 032
		sgap 31					; 033 ... 063
		s2fn	TILE_BASE, tilemap.cross	; 064
		sgap 63					; 065 ... 127
		s2path	TILE_PATH, tilemap.base.C1	; 128 ... 143
		s2path	TILE_PATH, tilemap.base.C2	; 144 ... 159
		s2path	TILE_PATH, tilemap.base.C3	; 160 ... 175
		s2path	TILE_PATH, tilemap.base.C4	; 176 ... 191
		s2path	TILE_CROSS, tilemap.base.C1	; 192 ... 207
		s2path	TILE_CROSS, tilemap.base.C2	; 208 ... 223
		s2path	TILE_CROSS, tilemap.base.C3	; 224 ... 239
		s2path	TILE_CROSS, tilemap.base.C4	; 240 ... 255

						;    6 7 8
						;    5   1
; assumed aligned to 256			;    4 3 2
edges2border:	db	0			;  87654321
		db	0			; %00000001
		db	tilemap.border.outer_TL	; %00000010
		db	tilemap.border.edgeL	; %00000011
		db	0			; %00000100
		db	0			; %00000101
		db	tilemap.border.edgeT	; %00000110
		db	0			; %00000111
		db	tilemap.border.outer_TR	; %00001000
		db	0			; %00001001
		db	0			; %00001010
		db	0			; %00001011
		db	tilemap.border.edgeT	; %00001100
		db	0			; %00001101
		db	tilemap.border.edgeT	; %00001110
		db	0			; %00001111
		db	0			; %00010000
		db	0			; %00010001
		db	0			; %00010010
		db	0			; %00010011
		db	0			; %00010100
		db	0			; %00010101
		db	0			; %00010110
		db	0			; %00010111
		db	tilemap.border.edgeR	; %00011000
		db	0			; %00011001
		db	0			; %00011010
		db	0			; %00011011
		db	tilemap.border.inner_BL	; %00011100
		db	0			; %00011101
		db	0			; %00011110
		db	0			; %00011111
		db	tilemap.border.outer_BR	; %00100000
		db	0			; %00100001
		db	0			; %00100010
		db	0			; %00100011
		db	0			; %00100100
		db	0			; %00100101
		db	0			; %00100110
		db	0			; %00100111
		db	0			; %00101000
		db	0			; %00101001
		db	0			; %00101010
		db	0			; %00101011
		db	0			; %00101100
		db	0			; %00101101
		db	0			; %00101110
		db	0			; %00101111
		db	tilemap.border.edgeR	; %00110000
		db	0			; %00110001
		db	0			; %00110010
		db	0			; %00110011
		db	0			; %00110100
		db	0			; %00110101
		db	tilemap.border.inner_BL	; %00110110
		db	0			; %00110111
		db	tilemap.border.edgeR	; %00111000
		db	0			; %00111001
		db	0			; %00111010
		db	0			; %00111011
		db	0			; %00111100
		db	0			; %00111101
		db	tilemap.border.inner_BL	; %00111110
		db	0			; %00111111
		db	0			; %01000000
		db	0			; %01000001
		db	0			; %01000010
		db	0			; %01000011
		db	0			; %01000100
		db	0			; %01000101
		db	0			; %01000110
		db	0			; %01000111
		db	0			; %01001000
		db	0			; %01001001
		db	0			; %01001010
		db	0			; %01001011
		db	0			; %01001100
		db	0			; %01001101
		db	0			; %01001110
		db	0			; %01001111
		db	0			; %01010000
		db	0			; %01010001
		db	0			; %01010010
		db	0			; %01010011
		db	0			; %01010100
		db	0			; %01010101
		db	0			; %01010110
		db	0			; %01010111
		db	0			; %01011000
		db	0			; %01011001
		db	0			; %01011010
		db	0			; %01011011
		db	0			; %01011100
		db	0			; %01011101
		db	0			; %01011110
		db	0			; %01011111
		db	tilemap.border.edgeB	; %01100000
		db	0			; %01100001
		db	0			; %01100010
		db	tilemap.border.inner_TR	; %01100011
		db	0			; %01100100
		db	0			; %01100101
		db	0			; %01100110
		db	0			; %01100111
		db	0			; %01101000
		db	0			; %01101001
		db	0			; %01101010
		db	0			; %01101011
		db	0			; %01101100
		db	0			; %01101101
		db	0			; %01101110
		db	0			; %01101111
		db	tilemap.border.inner_TL	; %01110000
		db	0			; %01110001
		db	0			; %01110010
		db	0			; %01110011
		db	0			; %01110100
		db	0			; %01110101
		db	0			; %01110110
		db	0			; %01110111
		db	0			; %01111000
		db	0			; %01111001
		db	0			; %01111010
		db	0			; %01111011
		db	0			; %01111100
		db	0			; %01111101
		db	0			; %01111110
		db	0			; %01111111
		db	tilemap.border.outer_BL	; %10000000
		db	tilemap.border.edgeL	; %10000001
		db	0			; %10000010
		db	tilemap.border.edgeL	; %10000011
		db	0			; %10000100
		db	0			; %10000101
		db	0			; %10000110
		db	0			; %10000111
		db	0			; %10001000
		db	0			; %10001001
		db	0			; %10001010
		db	0			; %10001011
		db	0			; %10001100
		db	tilemap.border.inner_BR	; %10001101
		db	0			; %10001110
		db	tilemap.border.inner_BR	; %10001111
		db	0			; %10010000
		db	0			; %10010001
		db	0			; %10010010
		db	0			; %10010011
		db	0			; %10010100
		db	0			; %10010101
		db	0			; %10010110
		db	0			; %10010111
		db	0			; %10011000
		db	0			; %10011001
		db	0			; %10011010
		db	0			; %10011011
		db	0			; %10011100
		db	0			; %10011101
		db	0			; %10011110
		db	0			; %10011111
		db	0			; %10100000
		db	0			; %10100001
		db	0			; %10100010
		db	0			; %10100011
		db	0			; %10100100
		db	0			; %10100101
		db	0			; %10100110
		db	0			; %10100111
		db	0			; %10101000
		db	0			; %10101001
		db	0			; %10101010
		db	0			; %10101011
		db	0			; %10101100
		db	0			; %10101101
		db	0			; %10101110
		db	0			; %10101111
		db	0			; %10110000
		db	0			; %10110001
		db	0			; %10110010
		db	0			; %10110011
		db	0			; %10110100
		db	0			; %10110101
		db	0			; %10110110
		db	0			; %10110111
		db	0			; %10111000
		db	0			; %10111001
		db	0			; %10111010
		db	0			; %10111011
		db	0			; %10111100
		db	0			; %10111101
		db	0			; %10111110
		db	0			; %10111111
		db	tilemap.border.edgeB	; %11000000
		db	tilemap.border.inner_TR	; %11000001
		db	0			; %11000010
		db	0			; %11000011
		db	0			; %11000100
		db	0			; %11000101
		db	0			; %11000110
		db	0			; %11000111
		db	0			; %11001000
		db	0			; %11001001
		db	0			; %11001010
		db	0			; %11001011
		db	0			; %11001100
		db	0			; %11001101
		db	0			; %11001110
		db	0			; %11001111
		db	0			; %11010000
		db	0			; %11010001
		db	0			; %11010010
		db	0			; %11010011
		db	0			; %11010100
		db	0			; %11010101
		db	0			; %11010110
		db	0			; %11010111
		db	tilemap.border.inner_TL	; %11011000
		db	0			; %11011001
		db	0			; %11011010
		db	0			; %11011011
		db	0			; %11011100
		db	0			; %11011101
		db	0			; %11011110
		db	0			; %11011111
		db	tilemap.border.edgeB	; %11100000
		db	0			; %11100001
		db	0			; %11100010
		db	tilemap.border.inner_TR	; %11100011
		db	0			; %11100100
		db	0			; %11100101
		db	0			; %11100110
		db	0			; %11100111
		db	0			; %11101000
		db	0			; %11101001
		db	0			; %11101010
		db	0			; %11101011
		db	0			; %11101100
		db	0			; %11101101
		db	0			; %11101110
		db	0			; %11101111
		db	0			; %11110000
		db	0			; %11110001
		db	0			; %11110010
		db	0			; %11110011
		db	0			; %11110100
		db	0			; %11110101
		db	0			; %11110110
		db	0			; %11110111
		db	tilemap.border.inner_TL	; %11111000
		db	0			; %11111001
		db	0			; %11111010
		db	0			; %11111011
		db	0			; %11111100
		db	0			; %11111101
		db	0			; %11111110
		db	0			; %11111111

; assumed aligned to 256
dir2tile:	db	0	; x  = mirrored left  10 + left  00
		db	139	; ┘  = mirrored left  10 + up    01
		db	128	; ─  = mirrored left  10 + right 10
		db	137	; ┐  = mirrored left  10 + down  11
		db	139	; ┘  = mirrored up    11 + left  00
		db	0	; x  = mirrored up    11 + up    01
		db	136	; └  = mirrored up    11 + right 10
		db	129	; │  = mirrored up    11 + down  11
		db	128	; ─  = mirrored right 00 + left  00
		db	136	; └  = mirrored right 00 + up    01
		db	0	; x  = mirrored right 00 + right 10
		db	138	; ┌  = mirrored right 00 + down  11
		db	137	; ┐  = mirrored down  01 + left  00
		db	129	; │  = mirrored down  01 + up    01
		db	138	; ┌  = mirrored down  01 + right 10
		db	0	; x  = mirrored down  01 + down  11
