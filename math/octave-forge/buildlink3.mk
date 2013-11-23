# $NetBSD: buildlink3.mk,v 1.12 2013/09/01 12:14:06 obache Exp $

BUILDLINK_TREE+=	octave-forge

.if !defined(OCTAVE_FORGE_BUILDLINK3_MK)
OCTAVE_FORGE_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.octave-forge+=	octave-forge>=2005.06.13
BUILDLINK_ABI_DEPENDS.octave-forge+=	octave-forge>=2006.03.17nb9
BUILDLINK_PKGSRCDIR.octave-forge?=	../../math/octave-forge

.include "../../math/octave/buildlink3.mk"
.endif # OCTAVE_FORGE_BUILDLINK3_MK

BUILDLINK_TREE+=	-octave-forge
