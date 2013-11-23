# $NetBSD: buildlink3.mk,v 1.33 2013/09/02 19:50:46 adam Exp $

.include "../../mk/bsd.fast.prefs.mk"

BUILDLINK_TREE+=	wxGTK24

.if !defined(WXGTK24_BUILDLINK3_MK)
WXGTK24_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.wxGTK24+=	wxGTK24>=2.4.2
BUILDLINK_ABI_DEPENDS.wxGTK24+=	wxGTK24>=2.4.2nb35
BUILDLINK_PKGSRCDIR.wxGTK24?=	../../x11/wxGTK24

.include "../../devel/pangox-compat/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../graphics/MesaLib/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../graphics/tiff/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.endif # WXGTK24_BUILDLINK3_MK

BUILDLINK_TREE+=	-wxGTK24
