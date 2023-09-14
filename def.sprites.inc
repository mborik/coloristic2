	struct S_SPRITE_ATTR
x		byte	0	; X0:7
y		byte	0	; Y0:7
palx8		byte	0	; PPPP Mx My Rt X8 (pal offset, mirrors, rotation, X8)
vpat		byte	0	; V 0 NNNNNN (visible, 5B type=off, pattern number 0..63)
ext		byte	0	; H N6 T XX YY Y8 (4bit, 7th pattern bit, relative, zoomX, zoomY, Y8)
	ends

		align	256

sprites:
.count = 16
		ds	.count * S_SPRITE_ATTR, 0

	module sprattr

numeralC1 = sprites + (0 * S_SPRITE_ATTR)
numeralC2 = sprites + (1 * S_SPRITE_ATTR)
numeralC3 = sprites + (2 * S_SPRITE_ATTR)
numeralC4 = sprites + (3 * S_SPRITE_ATTR)

gloworbC1 = sprites + (4 * S_SPRITE_ATTR)
gloworbC2 = sprites + (5 * S_SPRITE_ATTR)
gloworbC3 = sprites + (6 * S_SPRITE_ATTR)
gloworbC4 = sprites + (7 * S_SPRITE_ATTR)

	endmodule

sprite
.numerals = 0
.gloworb = 32
.gloworb.anicount = 10
