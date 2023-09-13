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

; assumed aligned to 256
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
