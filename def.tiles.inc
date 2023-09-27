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
PATH_TELEPT_IN	= 4
PATH_TELEPT_OUT	= 6
PATH_POINT_R	= 8
PATH_POINT_D	= 10
PATH_POINT_L	= 12
PATH_POINT_U	= 14
PATH_CORNER_L	= 16
PATH_CORNER_U	= 18
PATH_CORNER_R	= 20
PATH_CORNER_D	= 22
PATH_TELEPT_R	= 24
PATH_TELEPT_D	= 26
PATH_TELEPT_L	= 28
PATH_TELEPT_U	= 30

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

numerals	= 176
status_color	= 188
letters
.L		= 192
.E		= 193
.V		= 194
.C		= 195
.O		= 196
.D		= 197
.R		= 198
.colon		= 199

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
.c = (color?) << 5
	opt push listoff
		s2fn	tile?, .c + PATH_HORIZONTAL	; 128
		s2fn	tile?, .c + PATH_VERTICAL	; 129
		s2fn	tile?, .c + PATH_TELEPT_IN	; 130
		s2fn	tile?, .c + PATH_TELEPT_OUT	; 131
		s2fn	tile?, .c + PATH_POINT_L	; 132
		s2fn	tile?, .c + PATH_POINT_U	; 133
		s2fn	tile?, .c + PATH_POINT_R	; 134
		s2fn	tile?, .c + PATH_POINT_D	; 135
		s2fn	tile?, .c + PATH_CORNER_L	; 136
		s2fn	tile?, .c + PATH_CORNER_U	; 137
		s2fn	tile?, .c + PATH_CORNER_R	; 138
		s2fn	tile?, .c + PATH_CORNER_D	; 139
		s2fn	tile?, .c + PATH_TELEPT_L	; 140
		s2fn	tile?, .c + PATH_TELEPT_U	; 141
		s2fn	tile?, .c + PATH_TELEPT_R	; 142
		s2fn	tile?, .c + PATH_TELEPT_D	; 143
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
		ds	9, 0			; %00001111 ~ %00010111
		db	tilemap.border.edgeR	; %00011000
		db	0			; %00011001
		db	0			; %00011010
		db	0			; %00011011
		db	tilemap.border.inner_BL	; %00011100
		db	0			; %00011101
		db	0			; %00011110
		db	0			; %00011111
		db	tilemap.border.outer_BR	; %00100000
		ds	15, 0			; %00100001 ~ %00101111
		db	tilemap.border.edgeR	; %00110000
		ds	5, 0			; %00110001 ~ %00110101
		db	tilemap.border.inner_BL	; %00110110
		db	0			; %00110111
		db	tilemap.border.edgeR	; %00111000
		ds	5, 0			; %00111001 ~ %00111101
		db	tilemap.border.inner_BL	; %00111110
		ds	33, 0			; %00111111 ~ %01011111
		db	tilemap.border.edgeB	; %01100000
		db	0			; %01100001
		db	0			; %01100010
		db	tilemap.border.inner_TR	; %01100011
		ds	12, 0			; %01100100 ~ %01101111
		db	tilemap.border.inner_TL	; %01110000
		ds	15, 0			; %01110001 ~ %01111111
		db	tilemap.border.outer_BL	; %10000000
		db	tilemap.border.edgeL	; %10000001
		db	0			; %10000010
		db	tilemap.border.edgeL	; %10000011
		ds	9, 0			; %10000100 ~ %10001100
		db	tilemap.border.inner_BR	; %10001101
		db	0			; %10001110
		db	tilemap.border.inner_BR	; %10001111
		ds	48, 0			; %10010000 ~ %10111111
		db	tilemap.border.edgeB	; %11000000
		db	tilemap.border.inner_TR	; %11000001
		ds	22, 0			; %11000010 ~ %11010111
		db	tilemap.border.inner_TL	; %11011000
		ds	7, 0			; %11011001 ~ %11011111
		db	tilemap.border.edgeB	; %11100000
		db	0			; %11100001
		db	0			; %11100010
		db	tilemap.border.inner_TR	; %11100011
		ds	20, 0			; %11100100 ~ %11110111
		db	tilemap.border.inner_TL	; %11111000
		ds	7, 0			; %11111001 ~ %11111111

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

path_corners	db	%01010101	; PATH_HORIZONTAL
		db	0
		db	%10101010	; PATH_VERTICAL
		db	0
		db	%00000000	; PATH_TELEPT_IN
		db	128
		db	%00000000	; PATH_TELEPT_OUT
		db	0
		db	%01000100	; PATH_POINT_R
		db	128
		db	%10100000	; PATH_POINT_D
		db	128
		db	%00010001	; PATH_POINT_L
		db	128
		db	%00001010	; PATH_POINT_U
		db	128
		db	%01000010	; PATH_CORNER_L
		db	%00000010
		db	%10000001	; PATH_CORNER_U
		db	%00000100
		db	%00100100	; PATH_CORNER_R
		db	%00001000
		db	%00011000	; PATH_CORNER_D
		db	%00000001
		db	%01000100	; PATH_TELEPT_R
		db	0
		db	%10100000	; PATH_TELEPT_D
		db	0
		db	%00010001	; PATH_TELEPT_L
		db	0
		db	%00001010	; PATH_TELEPT_U
		db	0

statusbar_line	block	2, tilemap.background
		db	tilemap.letters.L
		db	tilemap.letters.E
		db	tilemap.letters.V
		db	tilemap.letters.E
		db	tilemap.letters.L
		db	tilemap.background
		block	4, tilemap.numerals + 10
		block	19, tilemap.background
		db	tilemap.letters.O
		db	tilemap.background
		db	tilemap.letters.C
		db	tilemap.letters.O
		db	tilemap.letters.L
		db	tilemap.letters.O
		db	tilemap.letters.R
		block	2 + TILEMAP_CHAR_WIDTH, tilemap.background
