	struct S_SPRITE_ATTR
x		byte	0	; X0:7
y		byte	0	; Y0:7
palx8		byte	0	; PPPP Mx My Rt X8 (pal offset, mirrors, rotation, X8)
vpat		byte	0	; V 5B NNNNNN (visible, 5B type, pattern number 0..63)
ext		byte	0	; H N6 T XX YY Y8 (4bit, 7th pattern bit, relative, zoomX, zoomY, Y8)
	ends

sprite	; constants placeholder
.numerals = 0
.gloworb = 32
.gloworb.anicount = 10

;------------------------------------------------------------------------------

	macro sprPatExt pattern?, enabled?, anchor?
		db	$40 | (enabled? << 7) | (pattern? >> 1)
	if anchor?
		db	$80 | (anchor? << 5) | ((pattern? & 1) << 6)
	else
		db	$40 | ((pattern? & 1) << 5)
	endif
	endm
	macro glowframe pattern?, enabled?
		sprPatExt pattern?, enabled?, 1
		sprPatExt (pattern? + 1), enabled?, 0
		sprPatExt (pattern? + 2), enabled?, 0
		sprPatExt (pattern? + 3), enabled?, 0
	endm

		align	256

gloworb_animation_sprattrs:
	dup ($100 - (sprite.gloworb.anicount * 8 * 2)) / 8
		sprPatExt 0, 0, 1
		sprPatExt 0, 0, 0
		sprPatExt 0, 0, 0
		sprPatExt 0, 0, 0
	edup
	dup sprite.gloworb.anicount, pattern?
.pattern = (pattern? * 4) + sprite.gloworb
		glowframe .pattern, 1
	edup
	dup sprite.gloworb.anicount, pattern?
.pattern = (pattern? * 4) + sprite.gloworb
		glowframe .pattern, 1
	edup

;------------------------------------------------------------------------------

; assumed aligned to 256
sprites:
.count = 16
		ds	.count * S_SPRITE_ATTR, 0

	module sprattr

numeralC1	= sprites + (0 * S_SPRITE_ATTR)
numeralC2	= sprites + (1 * S_SPRITE_ATTR)
numeralC3	= sprites + (2 * S_SPRITE_ATTR)
numeralC4	= sprites + (3 * S_SPRITE_ATTR)

gloworb		= sprites + (4 * S_SPRITE_ATTR) ; 4 phases

crossoverlayP1	= sprites + (8 * S_SPRITE_ATTR)
crossoverlayP2	= sprites + (12 * S_SPRITE_ATTR)
crossoverlayP3	= sprites + (16 * S_SPRITE_ATTR)
crossoverlayP4	= sprites + (20 * S_SPRITE_ATTR)
crossoverlayP5	= sprites + (24 * S_SPRITE_ATTR)
crossoverlayP6	= sprites + (28 * S_SPRITE_ATTR)

	endmodule
