# $NetBSD: buildlink3.mk,v 1.36 2013/09/02 19:50:50 adam Exp $

BUILDLINK_TREE+=	xfce4-wavelan-plugin

.if !defined(XFCE4_WAVELAN_PLUGIN_BUILDLINK3_MK)
XFCE4_WAVELAN_PLUGIN_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.xfce4-wavelan-plugin+=	xfce4-wavelan-plugin>=0.5.3
BUILDLINK_ABI_DEPENDS.xfce4-wavelan-plugin+=	xfce4-wavelan-plugin>=0.5.4nb19
BUILDLINK_PKGSRCDIR.xfce4-wavelan-plugin?=	../../net/xfce4-wavelan-plugin

.include "../../x11/xfce4-panel/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.endif # XFCE4_WAVELAN_PLUGIN_BUILDLINK3_MK

BUILDLINK_TREE+=	-xfce4-wavelan-plugin
