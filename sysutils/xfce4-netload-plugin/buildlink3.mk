# $NetBSD: buildlink3.mk,v 1.39 2013/09/02 19:50:50 adam Exp $

BUILDLINK_TREE+=	xfce4-netload-plugin

.if !defined(XFCE4_NETLOAD_PLUGIN_BUILDLINK3_MK)
XFCE4_NETLOAD_PLUGIN_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.xfce4-netload-plugin+=	xfce4-netload-plugin>=0.4.0
BUILDLINK_ABI_DEPENDS.xfce4-netload-plugin+=	xfce4-netload-plugin>=0.4.0nb19
BUILDLINK_PKGSRCDIR.xfce4-netload-plugin?=	../../sysutils/xfce4-netload-plugin

.include "../../x11/xfce4-panel/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.endif # XFCE4_NETLOAD_PLUGIN_BUILDLINK3_MK

BUILDLINK_TREE+=	-xfce4-netload-plugin
