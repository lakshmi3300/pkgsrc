# $NetBSD: buildlink3.mk,v 1.27 2013/09/02 19:50:49 adam Exp $

BUILDLINK_TREE+=	xfce4-places-plugin

.if !defined(XFCE4_PLACES_PLUGIN_BUILDLINK3_MK)
XFCE4_PLACES_PLUGIN_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.xfce4-places-plugin+=	xfce4-places-plugin>=1.0.0
BUILDLINK_ABI_DEPENDS.xfce4-places-plugin+=	xfce4-places-plugin>=1.0.0nb22
BUILDLINK_PKGSRCDIR.xfce4-places-plugin?=	../../x11/xfce4-places-plugin

.include "../../sysutils/xfce4-thunar/buildlink3.mk"
.include "../../x11/xfce4-panel/buildlink3.mk"
.include "../../x11/libSM/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.endif # XFCE4_PLACES_PLUGIN_BUILDLINK3_MK

BUILDLINK_TREE+=	-xfce4-places-plugin