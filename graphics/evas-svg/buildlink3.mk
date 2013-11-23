# $NetBSD: buildlink3.mk,v 1.2 2013/09/02 19:50:38 adam Exp $

BUILDLINK_TREE+=	evas-svg

.if !defined(EVAS_SVG_BUILDLINK3_MK)
EVAS_SVG_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.evas-svg+=	evas-svg>=1.7.7
BUILDLINK_ABI_DEPENDS.evas-svg?=	evas-svg>=1.7.7nb1
BUILDLINK_PKGSRCDIR.evas-svg?=	../../graphics/evas-svg

.include "../../fonts/fontconfig/buildlink3.mk"
.include "../../graphics/cairo/buildlink3.mk"
.include "../../graphics/evas/buildlink3.mk"
.include "../../graphics/freetype2/buildlink3.mk"
.include "../../graphics/librsvg/buildlink3.mk"
.include "../../devel/pango/buildlink3.mk"

.endif # EVAS_SVG_BUILDLINK3_MK

BUILDLINK_TREE+=	-evas-svg
